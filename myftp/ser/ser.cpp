/*************************************************************************
    > File Name: 3.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com
    > Created Time: 2016年07月07日 星期四 10时08分55秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <event.h>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ifaddrs.h>

#include "mysql.hpp"
#include "phread.hpp"
#include "memorypool.hpp"
//#include "memorypool_push.hpp"

struct event_base *base;  
void onRead(int clifd,short event,void *arg);
char error[6] = "error";
char ok[5] = "ok";
typedef struct _Sockfd
{
	bool ready;
	int sockfd;
	int ssockfd;
}Sockfd;

void my_lsalnum(char *p,char *str,int k)
{
	char s[128] = {0};
	int n = 0;
	int i;
	int j = 0;
	for( i = 0;p[i] != 0;++i)
	{
		if(p[i] != ' ')
		{
			if(n == k-1)
				s[j++] = p[i];
		}
		else
		{
			n++;
			if(n > k)
				break;
		}
	}
	strcpy(str,s);
}

int create_csocket(const char *ip4,int hton)
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(hton);
	saddr.sin_addr.s_addr = inet_addr(ip4);
	int res = connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	if(res == -1) perror("connect");

	return sockfd;
}
int service_send(int service_sockfd,const char *data_buff)
{
	char local_buff[128] = {0};
	int send_size = strlen(data_buff);
	int now_size = 0;
	sprintf(local_buff,"%d",send_size);
	strcpy(local_buff+4,data_buff);

	now_size = send(service_sockfd,local_buff,send_size+4,0);
	if(now_size <= 0)
	{
		printf("send error\n");
	}
	return now_size;
}

int service_recv(int service_sockfd,char *data_buff)
{
	char local_buff[128] = {0};
	int now_size = 0;
	int recv_size = 0;
	int flag = 0;

	recv(service_sockfd,local_buff,4,0);
	//printf("%s\n",local_buff);
	//exit(-1);
	recv_size = atoi(local_buff);
	memset(local_buff,0,128);

	while(recv_size)
	{
		now_size = recv(service_sockfd,local_buff,recv_size,0);
		if(now_size <= 0)
		{
			printf("recv error\n");
		}	

		recv_size -= now_size;
		strncpy(data_buff+flag,local_buff,now_size);
		memset(local_buff,0,128);
		flag += now_size;
	}
	return flag;
}

MemoryNode *process_arg(char *username,int sockfd,char *path,long long size,long long old_size)
{

	MemoryNode* tmp =	MemoryNodeList_malloc();
	
	tmp->id = '0';
	memset(tmp->path,0,128);
	
	sprintf(tmp->path,"%s %d %s %lld %lld",username,sockfd,path,size,old_size);

	return tmp;
}

//void service_down(int service_sockfd,char *path)
//{
//	long long old_size = 0;
//	struct stat st;
//	int fd = stat(path,&st);
//	if(fd == -1) //success
//	{
//		printf("llllllllllllll\n");
//		return;//error
//	}
//	else
//	{
//		long long file_size = st.st_size;
////		if(old_size != 0)
////		{	
////			if(my_md5())
////			{                //看是否改变
////				file_size -= old_size;
////			}
////			else
////			{
////				return ;//error
////			}
////		}
//		char buff[128] = {0};
//		char ip[128] = {0};
//		sprintf(buff,"%lld",file_size);
//		service_send(service_sockfd,buff);
//		service_recv(service_sockfd,buff);
//		my_lsalnum(buff,ip,2);
//		int htons = atoi(ip);
//		my_lsalnum(buff,ip,1);
//		int process_sockfd = create_csocket(ip,htons);
//		MemoryNode *tmp = process_arg(file_size,process_sockfd,path,old_size);
//		printf("%d\n",process_sockfd);	
//
//		pool_add_worker(process_down,tmp);		
//		pool_add_worker(process_down,tmp);		
//	}
//}
//
//void my_down(int sockfd,char *recv_buff)
//{
//	char buff[128] = {0};
//	my_lsalnum(recv_buff,buff,2);
//	//mysql(buff);
//	//strcpy(buff,"/home/wengduo/lianxi/ftp/2/2.rmvb");
//	service_down(sockfd,buff);	
//}
//

void my_cd(int sockfd,char *recv_buff)
{
	char path[128] = {0};
	my_lsalnum(recv_buff,path,2);
	
}

void do_login(int sockfd,char * recv_buff)
{
	char name[128] = {0};
	char passwd[128] = {0};
	char result_buff[128] = {0};
	char send_buff[128] = {0};

  my_lsalnum(recv_buff,name,2);
	my_lsalnum(recv_buff,passwd,3);

	bool tag = Login(name,passwd,result_buff);

	if(tag)
	{
		sprintf(send_buff,"ok%s",result_buff);
		printf("%s\n",send_buff);
		service_send(sockfd,send_buff);
		printf("ok\n");
	}
	else
	{
		service_send(sockfd,error);
		printf("error\n");
	}

}


void do_register(int sockfd,char * recv_buff)
{
	char name[128] = {0};
	char passwd[128] = {0};

  my_lsalnum(recv_buff,name,2);
	my_lsalnum(recv_buff,passwd,3);

	bool tag = Register(name,passwd);

	if(tag)
	{
		service_send(sockfd,ok);
		printf("ok\n");
	}
	else
	{
		service_send(sockfd,error);
		printf("error\n");
	}

}

void *process_push(void *arg)
{
	char username[12] = {0};
	char buff[24] = {0};
	char path[48] = {0};
	char path_name[24] = {0};
	char md5[36] = {0};
	char result_buff[128] = {0};
	int flag = 0;
	char *tmp = (char *)arg;
	
	my_lsalnum(tmp,username,2);
	int ser_sockfd = atoi(username);
	
	my_lsalnum(tmp,username,1);
	my_lsalnum(tmp,path,3);
	my_lsalnum(tmp,path_name,4);
	my_lsalnum(tmp,md5,5);
	my_lsalnum(tmp,result_buff,6);
	printf("arg:%s-%d-%s-%s-%s-%s\n",username,ser_sockfd,path,path_name,md5,result_buff);
	service_recv(ser_sockfd,buff);
	long long file_size = atol(buff+2);
	printf("%lld\n",file_size);
	memset(buff,0,24);
	strcpy(buff,ok);

	FILE *fd = fopen(result_buff,"wb");
	assert(NULL != fd);

	memset(tmp,0,4096);
	memset(buff,0,24);
	int file_read = 0;
	while(1)
	{
			file_read = recv(ser_sockfd,tmp,4096,0);
			if(file_read <= 0)
			{
				close(ser_sockfd);
				printf("client close\n");
			}
			service_send(ser_sockfd,ok);
			printf("recv:%d\n",file_read);
			file_read = fwrite(tmp,1,file_read,fd);

			printf("fwrite:%d\n",file_read);
			if(file_read < 4096)
				break;
	}
	
	bool tag = insert_file(result_buff,username,path,path_name,md5,true);
	if(tag) printf("push success\n");
	fclose(fd);
	free(tmp);
	close(ser_sockfd);
	return NULL;
}



void do_push(int sockfd,char * recv_buff,char *username)
{
	  char result_buff[128] = {0};
    char path[128] = {0};
		char push_name[128] = {0};
		char md5[64] = {0};
		char buff[32] = "ok1";
    
	  my_lsalnum(recv_buff,path,3);
		my_lsalnum(recv_buff,push_name,4);
		my_lsalnum(recv_buff,md5,5);
		printf("kl%s\n",username);
		bool tag = insert_file(result_buff,username,path,push_name,md5,false);
		printf("kkkk%d-%s\n",tag,result_buff);

		if( tag )
		{
			if(result_buff[0] == '1')
			{
				service_send(sockfd,buff);
			}
			else
			{
				service_send(sockfd,ok);
		    
				strcpy(result_buff,result_buff+1);
				memset(recv_buff,0,128);
				service_recv(sockfd,recv_buff);
				printf("%s\n",recv_buff);
				
				char ip[16] = {0};
				char cport[10] = {0};
				int port = 0;
				my_lsalnum(recv_buff, ip, 1);
				my_lsalnum(recv_buff, cport, 2);
				port = atoi(cport);

				int ser_sockfd = create_csocket(ip,port);
				char *arg = (char *)malloc(sizeof(char)*4096);

				memset(arg,0,4096);
				sprintf(arg,"%s %d %s %s %s %s",username,ser_sockfd,path,push_name,md5,result_buff);
				printf("%s\n",arg);

				pool_add_worker(process_push,arg);
			}
		}
		else
		{
			service_send(sockfd,error);
		}
}

void *process_down(void *arg)
{
	char buff[128] = {0};
	int flag = 0;
	MemoryNode *tmp = (MemoryNode *)arg;
	
	pthread_mutex_lock(&tmp->queue_lock);
	if(tmp->id == '0')
	{
		tmp->id = '1';
		flag = 1;
	}
	pthread_mutex_unlock(&tmp->queue_lock);
	
	if(flag == 1)
	{
		my_lsalnum(tmp->path,buff,2);
		int process_sockfd = atoi(buff);
		memset(buff,0,128);
		my_lsalnum(tmp->path,buff,4);
		long long file_size = atol(buff);
		printf("tmp->path:%lld-%d\n",file_size,process_sockfd);
		
		int file_read = 0;	
		while(1)
		{
			sem_wait(&tmp->sem_r);
			file_read = send(process_sockfd,tmp->queue_head->data,tmp->queue_head->size,0);
			printf("service_send%lld-%d\n",tmp->queue_head->size,file_read);
			service_recv(process_sockfd,buff);

			sem_post(&tmp->sem_w);
			tmp->queue_head = tmp->queue_head->next;
			if(file_read < QueueNode_size) 
				break;
		}

		MemoryNodeList_free(tmp);
		close(process_sockfd);
	}
	else
	{	
		char now_path[128] = {0};
		my_lsalnum(tmp->path,now_path,3);
		printf("now_path:%s\n",now_path);
		
		FILE *fd = fopen(now_path,"r");
		assert(NULL != fd);

		Dirqueue *head_write = tmp->queue_head;
		assert(head_write != NULL);
	
		long long file_read = 0;
		while(1)
		{
			sem_wait(&tmp->sem_w);
			file_read = fread(head_write->data,1,QueueNode_size,fd);
			if(file_read < 0) printf("error\n");
			printf("file_read%lld\n",file_read);
			head_write->size = file_read;
			head_write = head_write->next; 

			sem_post(&tmp->sem_r);
			if(file_read < QueueNode_size)
				break;
		}
		
		fclose(fd);
	}
	return NULL;
}


void do_down(int sockfd,char *recv_buff,char *usename)
{
	  long long old_size = 0;
    char path[128] = {0};
		char buff[128] = {0};
		char recv[128] = {0};	
		char file_name[128] = {0};
		struct stat st;

	  my_lsalnum(recv_buff,path,3);
    my_lsalnum(recv_buff,file_name,4);
   
	  bool tag = true; 
		tag = get_real_path(path,usename,path,file_name);
	  if(tag)
  	{
			int fd = stat(path,&st);
			if( fd == -1)
			{
				perror("read file info error\n");
				return ;
			}
			long long file_size = st.st_size;

			sprintf(buff,"%lld",file_size);
			service_send(sockfd,buff);
			printf("%lld\n",file_size);
			memset(buff,0,128);

			char ip[16] = {0};
			char post[8] = {0};
			service_recv(sockfd,buff);
			printf("%s\n",buff);
			my_lsalnum(buff,ip,1);
			my_lsalnum(buff,post,2);
			int hton = atoi(post);
			printf("%s-%d\n",ip,hton);
			int process_sockfd = create_csocket(ip,hton);
			
			MemoryNode *tmp = process_arg(usename,process_sockfd,path,file_size,old_size);

			printf("%s\n",tmp->path);

			pool_add_worker(process_down,tmp);
			pool_add_worker(process_down,tmp);
	  	printf("ok\n");
	  }
	  else
	  {
	  	service_send(sockfd,error);
	  	printf("error\n");
	  }
}

void do_rename(int sockfd,char * recv_buff,char *username)
{
	char old_name[128] = {0};
	char now_name[128] = {0};

	my_lsalnum(recv_buff,old_name,3);
	my_lsalnum(recv_buff,now_name,4);

	bool flag = ReName(username,old_name,now_name);
	if(flag)
	{
		service_send(sockfd,ok);
	}
	else
	{
		service_send(sockfd,error);
	}
}

void do_remove(int sockfd,char *recv_buff,char *username)
{
	char now_name[128] = {0};
	char d_path[128] = {0};

	my_lsalnum(recv_buff,d_path,2);
	my_lsalnum(recv_buff,now_name,3);

	bool flag = remove_file(username,d_path,now_name);
	if(flag)
	{
		service_send(sockfd,ok);
	}
	else
	{
		service_send(sockfd,error);
	}
}

void do_mkdir(int sockfd,char *recv_buff,char *username)
{
	char dir_name[128] = {0};
	char d_path[128] ={0};
	
	my_lsalnum(recv_buff,d_path,3);
	my_lsalnum(recv_buff,dir_name,4);

	bool flag = mysql_mkdir_file(username,d_path,dir_name);
	if(flag)
	{
		service_send(sockfd,ok);
	}
	else
	{
		service_send(sockfd,error);
	}
}

void do_cd(int sockfd,char *recv_buff,char *username)
{
	 char result_buff[128] = {0};
   char path[128] = {0};

   my_lsalnum(recv_buff+1,path,3);

   printf("%s\n",recv_buff);

   bool tag = Get_File(result_buff,username,path,false);
	 printf("%s\n",result_buff);
   if(tag)
   {
		 service_send(sockfd,result_buff);
   }
   else
   {
 		 service_send(sockfd,result_buff);
   }
   
}

void do_recv_buff(int sockfd, char * recv_buff)
{
	char str[128] = {0};
	char username[128] = {0};
	my_lsalnum(recv_buff+1,str,1);
	printf("recv:%s\n",recv_buff);
	switch(recv_buff[0])
	{
		case '0':
			if(strcmp(str,"register") == 0)
			{
			  do_register(sockfd,recv_buff+1);
			}
			else if(strcmp(str,"login") == 0)
			{
				do_login(sockfd,recv_buff+1);
			}
			break;
		case '1':
		  strcpy(username,str);

      my_lsalnum(recv_buff,str,2);
      if(strcmp(str,"push") == 0)
		  {
        do_push(sockfd,recv_buff,username); 
      }
      else if(strcmp(str,"down") == 0)
      {
        do_down(sockfd,recv_buff,username);
      }
      else if(strcmp(str,"cd") == 0)
      {
        do_cd(sockfd,recv_buff,username);
      }
      else if(strcmp(str,"rm") == 0)
      {
        do_remove(sockfd,recv_buff,username);
      }
      else if(strcmp(str,"mkdir") == 0)
      {
			  do_mkdir(sockfd,recv_buff,username);
      }
      else if(strcmp(str,"mv") == 0)
      {
			  do_rename(sockfd,recv_buff,username);
      }
			break;
		default:
			printf("recv_buff information error\n");
			service_send(sockfd,error);
	}
}

void *work(void *arg)
{
	Sockfd *tmp = (Sockfd *)arg;
	char recv_buff[128] = {0};
	int ilen;
	while(!tmp->ready);	
	ilen = service_recv(tmp->sockfd,recv_buff);
	printf("%s\n",recv_buff);
	if(ilen <= 0)
	{
		printf("Client close\n");  
		close(tmp->sockfd);
		return NULL;
	}
	do_recv_buff(tmp->sockfd,recv_buff);
	
	struct event *pread = new event;  
  event_set(pread,tmp->sockfd,EV_READ|EV_PERSIST,onRead,pread);
  event_base_set(base,pread);  
  event_add(pread,NULL); 
	memset(recv_buff,0,128);
	free(tmp);
	return NULL;
}

void onRead(int clifd,short event,void *arg)  
{
	Sockfd *pa = (Sockfd *)malloc(sizeof(Sockfd));
	memset(pa,0,sizeof(Sockfd));
	pa->ready = false;
	pa->sockfd = clifd;

	pool_add_worker(work,pa);
	
	struct event *pread = (struct event*)arg;  
	event_del(pread);  
	delete pread;  
	pa->ready = true;
}  

void onAccept(int svrfd,short ievent,void *arg)  
{  
  int clifd;  
  struct sockaddr_in cliaddr;  

  socklen_t sinsize = sizeof(cliaddr);
  clifd = accept(svrfd,(struct sockaddr*)&cliaddr,&sinsize);  
  
  struct event *pread = new event;  
  event_set(pread,clifd,EV_READ|EV_PERSIST,onRead,pread);  // 注册读(写)事件  
  event_base_set(base,pread);  
  event_add(pread,NULL);  
}  

int main(int argc,char *argv[])
{
	int svrfd;  
	struct sockaddr_in svraddr;  

	pool_init(20);
	MemoryNodeList_init();
	//MemoryNodeList_init_push();
	memset(&svraddr,0,sizeof(svraddr));  
	svraddr.sin_family = AF_INET;  
	svraddr.sin_port = htons(6510);  
	svraddr.sin_addr.s_addr = inet_addr("192.168.2.135");  

	svrfd = socket(AF_INET,SOCK_STREAM,0);  
	bind(svrfd,(struct sockaddr*)&svraddr,sizeof(svraddr));  

	listen(svrfd,10);

	// 初始化事件库  
	base = event_base_new();  

	// 初始化一个连接事件,EV_PRESIST指定重复执行该事件  
	struct event evlisten;  
	event_set(&evlisten,svrfd,EV_READ|EV_PERSIST,onAccept,NULL);  

	// 设置为base事件  
	event_base_set(base,&evlisten);  
	// 添加事件  
	event_add(&evlisten,NULL);  
	// 事件循环  
	event_base_dispatch(base); 
	return 0;
}
