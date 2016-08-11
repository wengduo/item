/*************************************************************************
    * File Name: sock.h
    * Author   : essity
    * Mail     : 1677921708@qq.com
    * Time     : 2016年07月14日 星期四 17时41分59秒
 ************************************************************************/
#ifndef SOCK_HPP
#define SOCK_HPP

#include <cstdio>
#include <vector>
#include <pthread.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <map>
#include <string>
#include <iostream>
#include <ifaddrs.h>
using namespace std;

#define MAX_LINE_LEN 128

void create_bsocket(int *sockfd,int *hton,char *ip)
{
	while(1)
	{
		*sockfd = socket(AF_INET,SOCK_STREAM,0);
		struct sockaddr_in saddr;
		memset(&saddr,0,sizeof(saddr));
		saddr.sin_family = AF_INET;
		saddr.sin_port = htons(*hton);
		saddr.sin_addr.s_addr = inet_addr(ip);
		int res = bind(*sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
		if(res != -1)
		{
			break;
		}
		(*hton)++;
	}

	listen(*sockfd,5);
}

int get_sockfd(int sockfd)
{
	while(1)
	{
		struct sockaddr_in caddr;
		int len = sizeof(caddr);
		int c = accept(sockfd,(struct sockaddr*)&caddr,(socklen_t *)&len);
		if(c < 0)
		{
			printf("error\n");
			continue;
		}
		return c;
	}
}

void get_ip(char *ip)
{
	struct ifaddrs * ifAddrStruct=NULL;
	void * tmpAddrPtr=NULL;
	getifaddrs(&ifAddrStruct);
	while (ifAddrStruct!=NULL) 
	{
		if (ifAddrStruct->ifa_addr->sa_family==AF_INET) 
		{
			tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
			char addressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
			//if(strncmp(ifAddrStruct->ifa_name,"wlp4s0",5) == 0)
			if(strncmp(addressBuffer,"192.168.",8) == 0)
			{
				strcpy(ip,addressBuffer);
			}
		}
		ifAddrStruct=ifAddrStruct->ifa_next;
	}
}

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
int init_socket(char *ip, int port)
{
    struct sockaddr_in servaddr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("create socket error: %s(errno: %d\n)\n", strerror(errno), errno);
        return -1;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(ip);
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
		  perror("connect");
        return -1;
    }
    return sockfd;
}

void add_buff(char *source_buff,char flag,char *ckname,char *aim_buff)
{
	source_buff[0] = '1';
	if(flag == '0' || flag == '1')
		source_buff[0] = '0';

	switch(flag)
	{
		case '0':
			sprintf(source_buff+1,"%s","register");
			source_buff[strlen(source_buff)+1] = 0;
			source_buff[strlen(source_buff)] = ' ';
			sprintf(source_buff+strlen(source_buff),"%s",ckname);
			break;
		case '1':
			sprintf(source_buff+1,"%s","login");
			source_buff[strlen(source_buff)+1] = 0;
			source_buff[strlen(source_buff)] = ' ';
			sprintf(source_buff+strlen(source_buff),"%s",ckname);
			break;
		case '2':
			sprintf(source_buff+1,"%s",ckname);
			sprintf(source_buff+strlen(source_buff),"%s"," cd");
			break;
		case '3':
			sprintf(source_buff+1,"%s",ckname);
			sprintf(source_buff+strlen(source_buff),"%s"," down");
			break;
		case '4':
			sprintf(source_buff+1,"%s",ckname);
			sprintf(source_buff+strlen(source_buff),"%s"," push");
			break;
		case '5':
			sprintf(source_buff+1,"%s",ckname);
			sprintf(source_buff+strlen(source_buff),"%s"," mkdir");
			break;
		case '6':
			sprintf(source_buff+1,"%s",ckname);
			sprintf(source_buff+strlen(source_buff),"%s"," mv");
			break;
		case '7':
			sprintf(source_buff+1,"%s",ckname);
			sprintf(source_buff+strlen(source_buff),"%s"," rm");
			break;
		default: break;
	}
	source_buff[strlen(source_buff)+1] = 0;
	source_buff[strlen(source_buff)] = ' ';
	sprintf(source_buff+strlen(source_buff),"%s",aim_buff);
	
}

int client_send(int client_sockfd,char *data_buff)
{
	char local_buff[128] = {0};
	int send_size = strlen(data_buff);
	int now_size = 0;

	sprintf(local_buff,"%d",send_size);
	strcpy(local_buff+4,data_buff);
	now_size = send(client_sockfd,local_buff,send_size+4,0);
	if(now_size <= 0)
	{
		perror("send");
		printf("send error\n");
	}
	return now_size;
}

int client_recv(int service_sockfd,char *data_buff)
{
	char local_buff[128] = {0};
	int now_size = 0;
	int recv_size = 0;
	int flag = 0;

	recv(service_sockfd,local_buff,4,0);
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
	return now_size;
}
void file_display(char *buff)
{
	char buff_name[128] ={0};
	char buff_flag[4] = {0};
	if (buff[0] == '0')
	{
		cout << "没有文件！" << endl;
		return;
	}
	
	char int_size[5] = {0};
	my_lsalnum(buff,int_size,2);
	int k1 = 3+strlen(int_size);
	buff += k1;
	int size = atoi(int_size);
	
	std::map<std::string,int> st;
	std::string stt;	
	for(int i = 0;i < size;i++)
	{
		stt.clear();
		memset(buff_name,0,128);
		memset(buff_flag,0,128);

		my_lsalnum(buff,buff_name,1);
		my_lsalnum(buff,buff_flag,2);

		buff += strlen(buff_name) + strlen(buff_flag) + 2;
		
		stt = buff_name;
		st.insert(make_pair(stt,buff_flag[0]-48));
	}

	for(auto &e:st)
	{
		if (e.second == 1)
		{
   		printf("\033[34m\033[1m%s\033[0m  ",e.first.c_str());
		}
		else
		{
			printf("%s  ",e.first.c_str());
		}
	}
	printf("\n");
};
#endif
