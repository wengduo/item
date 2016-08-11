/*************************************************************************
    * File Name: main.cpp
    * Author   : essity
    * Mail     : 1677921708@qq.com
    * Time     : 2016年05月29日 星期日 17时23分54秒
 ************************************************************************/

#include "enter.hpp"
#include <iostream>
#include <cstdio>
#include <cassert>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <event.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ifaddrs.h>
#include <map>
#include <string>
#include "phread.hpp"
#include "sock.hpp"
#include "enter.hpp"
#include "memorypool.hpp"
#include "md5.hpp"
using namespace std;
#define MAX_LINE_LEN 128

char us_name[24];
char dyna_path[128] = "/";
char global_ok[3] = "ok";
char error[6] = "error";
char global_ip[16] = {0};
int global_hton = 6501;
int global_sockfd;
char file_path[128] = "/home/wengduo/lianxi/myftp/client1/";

void *process_down(void *arg)
{
	char file_name[128] = {0};

	MemoryNode *tmp = (MemoryNode *)arg;
	my_lsalnum(tmp->path,file_name,1);
	int process_sockfd = atoi(file_name);

	memset(file_name,0,128);
	my_lsalnum(tmp->path,file_name,2);
	long long size = atol(file_name);

	FILE *fd = fopen(file_name,"wb");
	assert(NULL != fd);

	int file_read = 0;
	char buff[4] = "ok";
	while(1)
	{
		file_read = recv(process_sockfd,tmp->path,MemoryNodeSize,0);
		printf("%d\n",file_read);
		client_send(process_sockfd,buff);
		file_read = fwrite(tmp->path,1,file_read,fd);
		memset(tmp->path,0,MemoryNodeSize);
		if(file_read < MemoryNodeSize)
			break;
	}
	fclose(fd);
	MemoryNodeList_free(tmp);
	return NULL;
}

void do_cd(int sockfd,char *send_buff)
{
	printf("%s\n",send_buff);
	char buff[128] = {0};
	my_lsalnum(send_buff,buff,2);

	sprintf(dyna_path+strlen(dyna_path),"%s/",buff);

	memset(send_buff,0,128);
	add_buff(send_buff,'2',us_name,dyna_path);

	client_send(sockfd,send_buff);
	printf("%s\n",send_buff);
	memset(send_buff,0,128);
	client_recv(sockfd,send_buff);

	file_display(send_buff);
}

void do_down(int sockfd,char *send_buff)
{
	printf("%s\n",send_buff);
	char buff[128] = {0};
	char now_file[128] = {0};
	my_lsalnum(send_buff,buff,2);

	sprintf(now_file,"%s%s",file_path,buff);
	memset(send_buff,0,128);
	add_buff(send_buff,'3',us_name,dyna_path);
	sprintf(send_buff+strlen(send_buff)," %s",buff);

	client_send(sockfd,send_buff);
	printf("%s\n",send_buff);

	memset(buff,0,128);
	client_recv(sockfd,buff);
	long long size = atol(buff);
	memset(send_buff,0,128);
		
	sprintf(send_buff,"%s %d",global_ip,global_hton);
	client_send(sockfd,send_buff);
		
	printf("%s-%s-%d\n",send_buff,global_ip,global_hton);
	int process_sockfd = get_sockfd(global_sockfd);
	printf("%d\n",process_sockfd);

	MemoryNode *tmp = MemoryNodeList_malloc();
	assert(NULL != tmp);

	sprintf(tmp->path,"%d %s %lld",process_sockfd,now_file,size);

	printf("path:%s\n",tmp->path);
	pool_add_worker(process_down,tmp);

}

void *process_push(void *arg)
{
	MemoryNode *tmp = (MemoryNode *)arg;

	char file_name[48] = {0};
	my_lsalnum(tmp->path,file_name,1);
	int process_sockfd = atoi(file_name);

	memset(file_name,0,48);
	my_lsalnum(tmp->path,file_name,2);
	long long size = atol(file_name);
	
	memset(file_name,0,48);
	my_lsalnum(tmp->path,file_name,3);

	memset(tmp->path,0,MemoryNodeSize);
	printf("arg:%s-%d-%lld\n",file_name,process_sockfd,size);
	FILE *fd = fopen(file_name,"r");
	assert(NULL != fd);

	long long file_read = 0;
	char buff[128] = {0};

	sprintf(buff,"%lld",size);
	client_send(process_sockfd,buff);

	while(1)
	{
		file_read = fread(tmp->path,1,ListNode_size,fd);
	
		printf("fread%lld\n",file_read);
		file_read = send(process_sockfd,tmp->path,file_read,0);
		client_recv(process_sockfd,buff);
		if(file_read < ListNode_size)
			break;
		printf("send%lld\n",file_read);
	}

	fclose(fd);
	MemoryNodeList_free(tmp);
	return NULL;
}

void do_push(int sockfd,char *send_buff)
{
	printf("%s\n",send_buff);
	char buff[128] = {0};
	char new_path[128] = {0};
	char md5_buff[36] = {0}; 

	my_lsalnum(send_buff,buff,2);
	sprintf(new_path,"%s%s",file_path,buff);
	my_md5(new_path,md5_buff);

	memset(send_buff,0,128);

	add_buff(send_buff,'4',us_name,dyna_path);
	sprintf(send_buff+strlen(send_buff)," %s %s",buff,md5_buff);

	client_send(sockfd,send_buff);

	printf("%s\n",send_buff);
	memset(send_buff,0,128);
	client_recv(sockfd,send_buff);
	if(strncmp(send_buff,"ok1",3) == 0)
	{
		printf("push success\n");
	}
	else if(strncmp(send_buff,"ok",2) == 0)
	{
		memset(send_buff,0,128);
		struct stat st;
		stat(new_path,&st);
		long long size = st.st_size;

		printf("%lld",size);
		memset(buff,0,128);
		sprintf(buff,"%s %d",global_ip,global_hton);

		client_send(sockfd,buff);
		printf("ip:%s\n",buff);
		int cli_c = get_sockfd(global_sockfd);

		MemoryNode *tmp = MemoryNodeList_malloc();
		sprintf(tmp->path,"%d %lld %s",cli_c,size,new_path);
		
		printf("%s\n",tmp->path);
		printf("kkkkkkk\n");
		pool_add_worker(process_push,tmp);
	}
	else
	{
		printf("bu neng chong ming\n");
	}
}

void do_mkdir(int sockfd,char *send_buff)
{
	printf("%s\n",send_buff);
	char now_dir[128] = {0};
	char buff[128] = {0};

	my_lsalnum(send_buff,buff,2);

	memset(send_buff,0,128);
	add_buff(send_buff,'5',us_name,dyna_path);
	sprintf(send_buff+strlen(send_buff)," %s",buff);

	client_send(sockfd,send_buff);
	printf("%s\n",send_buff);
	memset(send_buff,0,128);

	client_recv(sockfd,send_buff);
	if(strncmp(send_buff,ok,2) == 0)
	{
		printf("makdir success\n");
	}
	else
	{
		printf("makdir error\n");
	}
}

void do_mv(int sockfd,char *send_buff)
{
	printf("%s\n",send_buff);
	char old_name[128] = {0};
	char now_name[128] = {0};
	char buff[128] = {0};

	my_lsalnum(send_buff,now_name,2);//
	sprintf(old_name,"%s%s",dyna_path,now_name);
	memset(now_name,0,128);
	my_lsalnum(send_buff,buff,3);//
	sprintf(now_name,"%s%s",dyna_path,buff);


	memset(send_buff,0,128);
	add_buff(send_buff,'6',us_name,old_name);
	sprintf(send_buff+strlen(send_buff)," %s",now_name);
	client_send(sockfd,send_buff);

	printf("%s\n",send_buff);
	memset(send_buff,0,128);

	client_recv(sockfd,send_buff);
	if(strncmp(send_buff,ok,2) == 0)
	{
		printf("success\n");
	}
	else
	{
		printf("error\n");
	}
}

void do_rm(int sockfd,char *send_buff)
{
	printf("%s\n",send_buff);
	char now_name[128] = {0};

	my_lsalnum(send_buff,now_name,2);
	memset(send_buff,0,128);
	add_buff(send_buff,'7',us_name,dyna_path);
	sprintf(send_buff," %s",now_name);

	client_send(sockfd,send_buff);
	printf("%s\n",send_buff);
	memset(send_buff,0,128);

	client_recv(sockfd,send_buff);
	if(strncmp(send_buff,ok,2) == 0)
	{
		printf("rm success\n");
	}
	else
	{
		printf("rm error\n");
	}
}

void Mnue_2(int sockfd)
{
	char send_buff[128] = {0};
	while(1)
	{
		memset(send_buff,0,128);
		send_buff[0] = '1';
		std::cout << "->";
		fgets(send_buff+1,128,stdin);
		send_buff[strlen(send_buff)-1] = 0;

		if (strncmp(send_buff,"1cd ",4) == 0)
		{
			do_cd(sockfd,send_buff);
		}
		else if(strncmp(send_buff,"1down ",6) == 0)
		{
			do_down(sockfd,send_buff);
		}
		else if(strncmp(send_buff,"1push ",6) == 0)
		{
			do_push(sockfd,send_buff);
		}
		else if(strncmp(send_buff,"1mkdir ",7) == 0)
		{
			do_mkdir(sockfd,send_buff);
		}
		else if(strncmp(send_buff,"1mv ",4) == 0)
		{
			do_mv(sockfd,send_buff);
		}
		else if(strncmp(send_buff,"1rm ",4) == 0)
		{
			do_rm(sockfd,send_buff);
		}
		else if(strcmp(send_buff+1,"1exit") == 0)
		{
			break;
		}

		std::cout << send_buff << std::endl;
	}
}



void my_start(int sockfd)
{
	bool flag = false;
	CliFace user(sockfd);
	user.init(flag,us_name);
	Mnue_2(sockfd);
}

int main(int argc, char *argv[])
{
	std::cout << "  欢迎进入云存储空间 " << std::endl;

	pool_init(10);
	MemoryNodeList_init();

	int sockfd = init_socket("192.168.2.135",6510);
	get_ip(global_ip);
	create_bsocket(&global_sockfd,&global_hton,global_ip);
	printf("global_sockfd:%d global_hton:%d global_ip:%s\n",global_sockfd,global_hton,global_ip);
	my_start(sockfd);
	return 0;
}
