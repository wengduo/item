#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <iostream>
#include <mysql/mysql.h>
#include <libmemcached/memcached.h>
#include <event.h>
#include <pthread.h>
using namespace std;


typedef enum
{
    EN_LOGIN,
    EN_REGISTER,
    EN_LOGIN_SUCCESS,
    EN_LOGIN_ERROR,
    EN_REGISTER_SUCCESS,
    EN_REGISTER_ERROR
}MsgHeader;

typedef struct _NetMsg
{
    MsgHeader enMsgHeader;
    union
    {
        struct Login
        {
            char name[20];
            char pwd[20];
        }LoginMsg;
        
        struct Register
        {
            char name[20];
            char pwd[20];
        }RegisterMsg;
    }MsgBody;
}NetMsg;

//全局的reator的指针
struct event_base* base = NULL;

//memcached缓存模块
class CMemcached
{
public:
    CMemcached(char *ip, unsigned short port)
    {
        mpmemc = memcached_create(NULL);
        mpservers = memcached_server_list_append(NULL, ip, port, &rc);
        rc = memcached_server_push(mpmemc, mpservers);
    }
    ~CMemcached()
    {
        memcached_free(mpmemc);
    }
    char* queryKey(char *key)
    {
        size_t value_length = 0;
        memcached_return rc;
        uint32_t flags = 0;
        char *result = NULL;
        result = memcached_get(mpmemc, key, strlen(key), &value_length, &flags, &rc);
        if(rc == MEMCACHED_SUCCESS)
            return result;
        else
            return NULL;
    }
    void saveValue(char *key, char *value)
    {
        memcached_return rc;
        rc = memcached_set(mpmemc, key, strlen(key), value, strlen(value), 0, 0);
        if(rc != MEMCACHED_SUCCESS)
        {
            cout<<"save memcached error"<<endl;
        }
    }
private:
    memcached_st *mpmemc;
    memcached_return rc;
    memcached_server_st *mpservers;
    static int mmemcachedSpotcount;
};
int CMemcached::mmemcachedSpotcount = 0;

//数据库模块
class CMySQL
{
public:
    CMySQL(char *ip, unsigned short port, char *user, char *pwd)
        :mpcon(NULL), mpres(NULL), mpMemcached(NULL)
    {
        mpcon = mysql_init((MYSQL*)0);
        if(mpcon == NULL)
        {
            cout<<"mysql_init error!"<<endl;
            exit(0);
        }
        
        if(!mysql_real_connect(mpcon,ip,user,pwd,NULL,port,NULL,0))
        {
            cout<<"mysql_real_connect error!"<<endl;
            exit(0);
        }
        else
        {
            if (mysql_select_db(mpcon, "User"))
            {
                cout<<"mysql_select_db error!"<<endl;
                exit(0);
            }
        }
        
        initMemcachedClient();
    }
    void initMemcachedClient()
    {
        char ip[20];
        unsigned short port;

        cout<<"please init Memcached param..."<<endl;
        cout<<"ip:";
        cin.getline(ip, 20);
        
        cout<<"port:";
        cin>>port;
        cin.get();

        mpMemcached = new CMemcached(ip, port);
        if(mpMemcached == NULL)
        {
            cout<<"Memcached module start error"<<endl;
            exit(0);
        }
        else
        {
            cout<<"Memcached module start success"<<endl;
        }
    }
    ~CMySQL()
    {
        if(mpres != NULL)
            mysql_free_result(mpres);  
        if(mpcon != NULL)
            mysql_close(mpcon);
    }
    bool queryRegister(char *name, char *pwd)
    {
        bool queryflag = false;
        
        //从memcached当中查询
        char *value = mpMemcached->queryKey(name);
        if(value != NULL)
        {
            if(strcmp(value, pwd) == 0)
            {
                return true;
            }
            else
                return false;
        }
            
        //再从数据库中查询
        char sql[100]={0};
        sprintf(sql, "select * from user where name='%s' and pwd='%s';", name, pwd);
        
        if(!mysql_real_query(mpcon,sql,strlen(sql)))
        {
            mpres = mysql_store_result(mpcon);
            while(mrow = mysql_fetch_row(mpres))  
            {  
                if(strcmp(name, mrow[0]) == 0)
                {
                    if(strcmp(pwd, mrow[1]) == 0)
                    {
                        //把数据库中查询的数据缓存到memcached
                        mpMemcached->saveValue(name, pwd);
                        return true;
                    }
                }
            }
            return false;
        }
        else
        {
            return false;
        }
    }
private:
    MYSQL *mpcon;
	MYSQL_RES *mpres;
	MYSQL_ROW mrow;
    CMemcached *mpMemcached;
    static int mMySqlQueryCount;
};
int CMySQL::mMySqlQueryCount = 0;

//服务器模块
class CTcpServer
{
public:
    CTcpServer(char *ip, unsigned short port):pMySQL(NULL)
    {
        mlistenfd = socket(AF_INET, SOCK_STREAM, 0);
        if(mlistenfd == -1)
        {
            cout<<"socket create error"<<endl;
            exit(0);
        }
        
        struct sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        server.sin_addr.s_addr = inet_addr(ip);
        
        if(-1 == bind(mlistenfd, (struct sockaddr*)&server, sizeof(server)))
        {
            cout<<"bind error"<<endl;
            exit(0);
        }
        
        if(-1 == listen(mlistenfd, 20))
        {
            cout<<"listen error"<<endl;
            exit(0);
        }
    }
    ~CTcpServer()
    {
        close(mlistenfd);
    }
    int getListenfd()const{return mlistenfd;}
    void run()
    {
        char ip[20];
        unsigned short port;
        char user[20];
        char pwd[20];
        
        cout<<"server is starting..."<<endl;
        cout<<"please init MySQL param..."<<endl;
        cout<<"ip:";
        cin.getline(ip, 20);
        
        cout<<"port:";
        cin>>port;
        cin.get();
        
        cout<<"username:";
        cin.getline(user, 20);
        
        cout<<"password:";
        cin.getline(pwd, 20);
        
        pMySQL = new CMySQL(ip, port, user, pwd);
        if(pMySQL == NULL)
        {
            cout<<"MySQL module start error"<<endl;
            exit(0);
        }
        else
        {
            cout<<"MySQL module start success"<<endl;
        }
        cout<<"server starting success..."<<endl;
    }
    bool doRegister(NetMsg &msg)
    {
        bool ret = pMySQL->queryRegister(msg.MsgBody.RegisterMsg.name,
                                         msg.MsgBody.RegisterMsg.pwd);
        return ret;
    }
private:
    int mlistenfd;
    CMySQL *pMySQL;
    
    //friend void listen_cb( int fd, short event, void* argc);
};

void client_cb(int fd, short event, void *argc)
{
    CTcpServer *pTcpServer = ( CTcpServer* )argc;
    NetMsg netMsg;
    int msglen = sizeof(NetMsg);
    bool ret;
    
    int len = recv(fd, &netMsg, msglen, 0);
    if(len <= 0)
    {
        close(fd);
        return;
    }
    
    switch(netMsg.enMsgHeader)
    {
    case EN_LOGIN:
    {
        //ret = pTcpServer->doLogin(netMsg);
        if(ret)
            netMsg.enMsgHeader = EN_LOGIN_SUCCESS;
        else
            netMsg.enMsgHeader = EN_LOGIN_ERROR;
        send(fd, &netMsg, sizeof(NetMsg), 0);
    }
    break;
    case EN_REGISTER:
    {
        ret = pTcpServer->doRegister(netMsg);
        if(ret)
            netMsg.enMsgHeader = EN_REGISTER_SUCCESS;
        else
            netMsg.enMsgHeader = EN_REGISTER_ERROR;
        send(fd, &netMsg, sizeof(NetMsg), 0);
       
    }
    break;
    }
}

//libevent监听listenfd发生事件的回调函数
void listen_cb( int fd, short event, void* argc)
{
    struct sockaddr_in client;
    socklen_t socklen = sizeof(client);

    int clientfd = accept(fd, (struct sockaddr*)&client, &socklen);
    if(clientfd == -1)
    {
        cout<<"TcpServer core dump!"<<endl;
        close(fd);
        exit(0);
    }
    
    cout<<"client connected! ip:"<<inet_ntoa(client.sin_addr)<<" port:"<<
    ntohs(client.sin_port)<<endl;
    
    //把新用户通信的fd添加到reator
    struct event* client_event = event_new( base, clientfd,  // event
        EV_READ|EV_PERSIST, client_cb, argc);
    event_add(client_event, NULL);  // event -> reator
}  

int main(int argc, char **argv)
{
    if(argc < 3 )
    {
        cout<<"command is invalid! ./a.out ip port!"<<endl;
        exit(0);
    }
    
    unsigned short port = atoi(argv[2]);
    CTcpServer server(argv[1], port);
    server.run();
    
    //初始化libevent    统一事件源  signal  time   io
    int listenfd = server.getListenfd();
    base = event_init();  // reator
    struct event* listen_event = event_new( base, listenfd,  // event
            EV_READ|EV_WRITE|EV_PERSIST, listen_cb, &server);
    event_add(listen_event, NULL);  // event -> reator
    
    // demuplex
    event_base_dispatch( base );
    
    //释放资源的地方
    event_free( listen_event );
    event_base_free( base );
    
    return 0;
}
