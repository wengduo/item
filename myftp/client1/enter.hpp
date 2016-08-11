/*************************************************************************
    * File Name: maic.cpp
    * Author   : essity
    * Mail     : 1677921708@qq.com
    * Time     : 2016年05月29日 星期日 17时14分46秒
 ************************************************************************/
#ifndef ENTER_HPP
#define ENTER_HPP

#include <cstdio>
#include <iostream>
#include "sock.hpp"
#include <string>
#include <cstring>
using namespace std;

char ok[3] ="ok";
class CliFace{
	private:
		char nickname[16];
		char passwd[12];
		int sockfd;
	public:
		CliFace() { };
		CliFace(int sockfd);
		int Mnue();
		bool Regist();
		bool Login(char *name);
		void init(bool flag,char *name);
};

CliFace::CliFace(int sockfd)
{
	this->sockfd = sockfd;
}

int CliFace::Mnue()
{
	std::string select;
	int i;
	do{
		std::cout << "       请选择菜单" <<std::endl;
		std::cout << "        0.登陆" <<std::endl;
		std::cout << "        1.注册" <<std::endl;
		std::cout << "        2.退出" <<std::endl;
		std::cout << "       请选择:";
		std::cin >> select;
		std::cin.get();
		std::cout << std::endl << std::endl << std::endl;
		i = select.c_str()[0] - 48;
	}while(i < 0 || i > 2);
	return i;
}

void CliFace::init(bool flag,char *name)
{
	memset(nickname,0,16);
	memset(passwd,0,12);
	int fd;
	while(1)
	{
ppp:
		fd = Mnue();
		switch(fd)
		{
			case 0:
				flag = Login(name);
				break;
			case 1:
				Regist();
				goto ppp;
			case 2:
				exit(-1);
			default:
				break;
		}
		if(flag)
			break;
	}
}


bool CliFace::Regist()
{
	std::cout << "   注   册   页   面" <<std::endl;
	
	char tmp[16]={0};
	std::cout << "     昵        称:";
	fgets(tmp,16,stdin);
	while (strlen(tmp) > 16 || strlen(tmp) < 5)
	{
		memset(tmp,0,strlen(tmp));
		std::cout << "输入有误，重新输入！" <<endl;
		std::cout << "     昵        称:";
	  fgets(tmp,16,stdin);
	}
	strcpy(nickname,tmp);

	std::cout << "     密        码:";
	char temp[12]={0};
	fgets(temp,12,stdin);
	while (strlen(temp) > 12 || strlen(temp) < 6)
	{
		memset(temp,0,strlen(temp));
		std::cout << "输入有误，重新输入！" <<endl;
		std::cout << "     密        码:";
	   fgets(temp,12,stdin);
	}

	std::cout << "     再次输入密码:";
	char temp1[16] = {0};
	fgets(temp1,16,stdin);
	while ( strcmp(temp,temp1) )
	{
		memset(temp1,0,strlen(temp1));
		std::cout << "输入有误，重新输入！" <<endl;
		std::cout << "     再次输入密码:";
	  fgets(temp1,16,stdin);
	}
	strcpy(passwd, temp1);

	char regist_buff[MAX_LINE_LEN] = {0};
	nickname[strlen(nickname)-1] = 0;
	passwd[strlen(passwd)-1] = 0;
	add_buff(regist_buff,'0',nickname,passwd);
	client_send(sockfd,regist_buff);
	printf("send%s\n",regist_buff);
	memset(regist_buff,0,128);
	client_recv(sockfd,regist_buff);
	printf("recv%s\n",regist_buff);

	std::cout << std::endl << std::endl << std::endl;

	if (strncmp(regist_buff,ok,2) == 0)
		return true;
	else 
		return false;
};

bool CliFace::Login(char *name)
{
	std::cout << "       登录" << std::endl;

	std::cout << "    名称:";
	char temp[12] = {0};
	fgets(temp,12,stdin);
	while (strlen(temp) > 12 || strlen(temp) < 4)
	{
		memset(temp,0,strlen(temp));
		std::cout << "输入有误，重新输入！" <<endl;
		std::cout << "    名称:";
		fgets(temp,12,stdin);
	}
	strcpy(nickname,temp);

	std::cout << "    密码:";
	char temp1[16] = {0};
	fgets(temp1,16,stdin);
	while (strlen(temp1) > 16 || strlen(temp1) < 6)
	{
		memset(temp1,0,strlen(temp1));
		std::cout << "输入有误，重新输入！" <<endl;
		std::cout << "    密码:";
		fgets(temp1,16,stdin);
	}
	strcpy(passwd,temp1);

	char login_buff[MAX_LINE_LEN] = {0}; 
	nickname[strlen(nickname)-1] = 0;
	passwd[strlen(passwd)-1] = 0;
	add_buff(login_buff,'1',nickname,passwd);
	client_send(sockfd,login_buff);
	memset(login_buff,0,128);
	client_recv(sockfd,login_buff);
	printf("\nrecv : %s\n",login_buff);

	std::cout << std::endl << std::endl << std::endl;

	if (strncmp(login_buff,"ok",2) == 0)
	{
		strcpy(name,nickname);
		cout << "->" << endl;
		file_display(login_buff+2);
		return true;
	}
	else 
	{
		return false;
	}
}

#endif
