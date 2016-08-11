/*************************************************************************
    > File Name: main.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com
    > Created Time: 2016年07月15日 星期五 16时55分31秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <string.h>
#include <time.h>
#include "phread.hpp"

void *kkk(void *arg)
{
//	while(1);
	//sleep(1);
	printf("hello\n");
	return NULL;
}
void func()
{
	int i;
	for(i = 0;i < 4;i++)
	{
		pool_add_worker(kkk,NULL);
	}
}

int main(int argc,char *argv[])
{
	pool_init(4);
	func();
	printf("------------------\n");
	func();
	sleep(10);
	pool_destroy();
	return 0;
}
