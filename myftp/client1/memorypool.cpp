/*************************************************************************
    * File Name: my_memorypool.h
    * Author   : essity
    * Mail     : 1677921708@qq.com
    * Time     : 2016年07月15日 星期五 19时38分58秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
using namespace std;

int MemoryNodeNum  = 20;
//int MemoryNodeSize = 4096;
long long ListNode_size = 1024*4;

pthread_mutex_t m_lock;

typedef struct _MemoryNode
{
	char *path;
	struct _MemoryNode *next;
}MemoryNode;

typedef struct _MemoryHead
{
	struct _MemoryNode *head;
	struct _MemoryNode *tail;
	int Now_MemoryNodeNum;
}MemoryHead;

MemoryHead *Mhead = NULL;
MemoryNode *MemoryNodeList_malloc();

void MemoryNodeList_init();
void Memory_malloc();
void MemoryNodeList_free(MemoryNode *ptr);

void MemoryNodeList_init()
{
	Mhead = (MemoryHead *)malloc(sizeof(MemoryHead));
	assert(NULL != Mhead);

	memset(Mhead,0,sizeof(MemoryHead));
   Mhead->head = Mhead->tail = NULL;
	Mhead->Now_MemoryNodeNum = 0;
	pthread_mutex_init(&m_lock,NULL);
	for(int i = 0;i < MemoryNodeNum; ++i)
	{
		Memory_malloc();
	}
}

void Memory_malloc()
{
	MemoryNode *tmp = (MemoryNode	*)malloc(sizeof(MemoryNode));
	assert(NULL != tmp);
	
	tmp->path = (char *)malloc(sizeof(char)*ListNode_size);
	assert(NULL != tmp->path);
	tmp->next = NULL;

	if(Mhead->head == NULL)
	{
		Mhead->head = tmp;
		
	}
   else
	{
		Mhead->tail->next = tmp;
	}

	Mhead->tail = tmp;
	
	++Mhead->Now_MemoryNodeNum;
}

void MemoryNodeList_free(MemoryNode *ptr)
{
	pthread_mutex_lock(&m_lock);

	if(Mhead->tail == NULL)
	{
		Mhead->head = ptr;
		Mhead->tail = ptr;
	}
	else
	{
		Mhead->tail->next = ptr;
		Mhead->tail = ptr;
	}
	
	Mhead->Now_MemoryNodeNum += 1;

	pthread_mutex_unlock(&m_lock);
}

MemoryNode *MemoryNodeList_malloc()
{
	pthread_mutex_lock(&m_lock);

	MemoryNode *tmp = NULL;
	if(Mhead->Now_MemoryNodeNum == 0)
	{
		Memory_malloc();
		MemoryNodeNum += 1;
		tmp = MemoryNodeList_malloc();
	}
	else
	{
		tmp = Mhead->head;
		Mhead->head = Mhead->head->next;
		Mhead->Now_MemoryNodeNum -= 1;
		if(Mhead->head == NULL)
			Mhead->tail = NULL;
	}

	pthread_mutex_unlock(&m_lock);
	
	return tmp;
}

int main()
{
	MemoryNodeList_init();
	for(int i = 0;i < 20;++i)
	{
		MemoryNode * tmp = MemoryNodeList_malloc();
		strcpy(tmp->path,"hello");
		printf("%s\n",tmp->path);
	}
	return 0;
}
