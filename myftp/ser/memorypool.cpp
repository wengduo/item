
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <semaphore.h>

int MemoryNodeNum  = 20;
int MemoryNodeSize = 4096;
int Queue_num = 20;
long long QueueNode_size = 1024*1024*4;

pthread_mutex_t m_lock;

typedef struct _Dirqueue
{
	char *data;
	long long size;
	struct _Dirqueue *next;
}Dirqueue;

typedef struct _MemoryNode
{
	char path[128];
	char id;
	struct _Dirqueue *queue_head;
	struct _MemoryNode *next;
	pthread_mutex_t queue_lock;
	sem_t sem_r;
	sem_t sem_w;
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
	
	tmp->next = NULL;
	tmp->queue_head = (Dirqueue *)malloc(sizeof(Dirqueue));
	assert(NULL != tmp->queue_head);
	
	sem_init(&tmp->sem_r,0,0);
	sem_init(&tmp->sem_w,0,20);

	Dirqueue *qhead = tmp->queue_head;

	qhead->data = (char *)malloc(sizeof(char)*QueueNode_size);
	assert(NULL != qhead->data);
	memset(qhead->data,0,QueueNode_size);

	for(int i = 1;i < Queue_num;++i)
	{
		qhead->next = (Dirqueue *)malloc(sizeof(Dirqueue));
		assert(NULL != qhead->next);
		
		qhead->next->data = (char *)malloc(sizeof(char)*QueueNode_size);
		assert(NULL != qhead->next->data);
		
		memset(qhead->next->data,0,QueueNode_size);
		qhead = qhead->next;
	}
	
	qhead->next = tmp->queue_head;

	MemoryNodeList_free(tmp);
}

void MemoryNodeList_free(MemoryNode *ptr)
{
	pthread_mutex_lock(&m_lock);
	sem_destroy(&ptr->sem_r);
	sem_destroy(&ptr->sem_w);


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
	
	pthread_mutex_init(&tmp->queue_lock,NULL);
	sem_init(&tmp->sem_r,0,0);
	sem_init(&tmp->sem_w,0,20);
	return tmp;
}

int main(int argc,char *argv[])
{
	printf("kkkkkkkkkkkkk\n");
	MemoryNodeList_init();
	printf("kkkkkkkkkkkkk\n");
	FILE *fd = fopen("/home/wengduo/lianxi/ftp/2/2.rmvb","r");
	assert(NULL != fd);
	MemoryNode *tmp = MemoryNodeList_malloc();
	Dirqueue *head = tmp->queue_head;
	for(int i = 0;i < 20;++i)
	{
		//strcpy(head->data,"hello");
		head->size  = fread(head->data,1,QueueNode_size,fd);
		printf("%lld-%lld\n",head->size,QueueNode_size);
		head = head->next;
	}
	int j;
	for(int i = 0;i < 20;++i)
	{
	//	strcpy(head->data,"hello");
		j = 0;
		while(j < head->size)
			printf("%c",head->data[j++]);
		printf("\n");
		head = head->next;
	}
	assert(tmp != NULL);
	printf("%p\n",tmp);
	strcpy(tmp->path,"hello");
	printf("%s\n",tmp->path);
	MemoryNodeList_free(tmp);
	return 0;
}
