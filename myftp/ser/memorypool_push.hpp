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

int MemoryNodeNum_push  = 20;
int MemoryNodeSize_push = 4096;
long long ListNode_size_push = 1024*1024*4;

pthread_mutex_t m_lock_push;

typedef struct _MemoryNode_push
{
	union _Path_p
	{
		struct
		{
			char *path;
		};
		struct
		{
			char username[24];
			int sockfd;
			char path_1[24];
			char name[24];
			char md5[36];
			char file_path[128];
		};
	}u_str;
	struct _MemoryNode_push *next;
}MemoryNode_push;

typedef struct _MemoryHead_push
{
	struct _MemoryNode_push *head;
	struct _MemoryNode_push *tail;
	int Now_MemoryNodeNum;
}MemoryHead_push;

MemoryHead_push *Mhead_p = NULL;
MemoryNode_push *MemoryNodeList_p_malloc();

void MemoryNodeList_init_push();
void Memory_malloc_push();
void MemoryNodeList_p_free(MemoryNode_push *ptr);

void MemoryNodeList_init_push()
{
	Mhead_p = (MemoryHead_push *)malloc(sizeof(MemoryHead_push));
	assert(NULL != Mhead_p);

	memset(Mhead_p,0,sizeof(MemoryHead_push));
  Mhead_p->head = Mhead_p->tail = NULL;
	Mhead_p->Now_MemoryNodeNum = 0;
	pthread_mutex_init(&m_lock_push,NULL);
	for(int i = 0;i < MemoryNodeNum_push; ++i)
	{
		Memory_malloc_push();
	}
}

void Memory_malloc_push()
{
	MemoryNode_push *tmp = (MemoryNode_push	*)malloc(sizeof(MemoryNode_push));
	assert(NULL != tmp);
	
	tmp->u_str.path = (char *)malloc(sizeof(char)*ListNode_size_push);
	assert(NULL != tmp->u_str.path);
	tmp->next = NULL;

	if(Mhead_p->head == NULL)
	{
		Mhead_p->head = tmp;
		
	}
   else
	{
		Mhead_p->tail->next = tmp;
	}

	Mhead_p->tail = tmp;
	
	++Mhead_p->Now_MemoryNodeNum;
}

void MemoryNodeList_p_free(MemoryNode_push *ptr)
{
	pthread_mutex_lock(&m_lock_push);

	if(Mhead_p->tail == NULL)
	{
		Mhead_p->head = ptr;
		Mhead_p->tail = ptr;
	}
	else
	{
		Mhead_p->tail->next = ptr;
		Mhead_p->tail = ptr;
	}
	
	Mhead_p->Now_MemoryNodeNum += 1;

	pthread_mutex_unlock(&m_lock_push);
}

MemoryNode_push *MemoryNodeList_p_malloc()
{
	pthread_mutex_lock(&m_lock_push);

	MemoryNode_push *tmp = NULL;
	if(Mhead_p->Now_MemoryNodeNum == 0)
	{
		Memory_malloc_push();
		MemoryNodeNum_push += 1;
		tmp = MemoryNodeList_p_malloc();
	}
	else
	{
		tmp = Mhead_p->head;
		Mhead_p->head = Mhead_p->head->next;
		Mhead_p->Now_MemoryNodeNum -= 1;
		if(Mhead_p->head == NULL)
			Mhead_p->tail = NULL;
	}

	pthread_mutex_unlock(&m_lock_push);
	
	return tmp;
}
