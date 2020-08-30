#ifndef LINKQUEUE2_H
#define LINKQUEUE2_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ERROR -1;
#define FALSE 0;
#define TRUE 1;

typedef struct LINKQUEUENODE
{
    void *data;
    struct LINKQUEUENODE *next;
} LinkQueueNode;

typedef struct LINKQUEUE
{
    LinkQueueNode *head;
    LinkQueueNode *tail;
    int size;
} LinkQueue;

// 初始化
LinkQueue *Init_LinkQueue();

// 入队，如果不是企业链表，要给node分配存储空间
int Push_LinkQueue(LinkQueue *queue, void *data);

// 返回队头元素
void *Front_LinkQueue(LinkQueue *queue);

// 出队
int Pop_LinkQueue(LinkQueue *queue);

// 返回队尾元素
void *Back_LinkQueue(LinkQueue *queue);

// 返回大小
int Size_LinkQueue(LinkQueue *queue);

// 清空队列
int Clear_LinkQueue(LinkQueue *queue);

// 销毁
int FreeSpace_LinkQueue(LinkQueue *queue);

#endif