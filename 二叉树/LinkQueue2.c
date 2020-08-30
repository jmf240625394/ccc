#include "LinkQueue2.h"

// typedef struct LINKQUEUENODE
// {
//     void *data;
//     struct LINKQUEUENODE *next;
// } LinkQueueNode;

// typedef struct LINKQUEUE
// {
//     LinkQueueNode *head;
//     LinkQueueNode *tail;
//     int size;
// } LinkQueue;

// 初始化
LinkQueue *Init_LinkQueue()
{
    LinkQueue *queue = (LinkQueue *)malloc(sizeof(LinkQueue));
    if (NULL == queue)
    {
        return NULL;
    }

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;

    return queue;
}

// 从队尾入队
int Push_LinkQueue(LinkQueue *queue, void *data)
{
    if (NULL == queue || NULL == data)
    {
        return ERROR;
    }

    // 创建新节点
    LinkQueueNode *newnode = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    newnode->data = data;
    newnode->next = NULL;

    // 新节点从链表尾入队
    if (queue->size == 0)
    {
        queue->head = newnode;
    }
    else
    {
        queue->tail->next = newnode;
    }
    queue->tail = newnode;
    queue->size++;
    return TRUE;
}

// 从链表尾返回队头元素
void *Front_LinkQueue(LinkQueue *queue)
{
    if (NULL == queue || queue->size == 0)
    {
        return NULL;
    }
    return queue->tail->data;
}

// 从链表头出队
int Pop_LinkQueue(LinkQueue *queue)
{
    if (NULL == queue || queue->size == 0)
    {
        return ERROR;
    }

    // 先把老得head地址保存，等会释放
    LinkQueueNode *pTemp = queue->head;
    queue->head = queue->head->next;
    if (queue->size == 1)
    {
        queue->tail = queue->head; // 两个都是NULL
    }
    queue->size--;

    // 释放内存
    free(pTemp);
    pTemp = NULL;

    return TRUE;
}

// 从链表头返回队尾元素
void *Back_LinkQueue(LinkQueue *queue)
{
    if (NULL == queue || queue->size == 0)
    {
        return NULL;
    }
    return queue->head->data;
}

// 返回大小
int Size_LinkQueue(LinkQueue *queue)
{
    if (NULL == queue)
    {
        return ERROR;
    }
    return queue->size;
}

// 判断队列是否为空
int IsEmpty_LinkQueue(LinkQueue *queue)
{
    if (NULL == queue)
    {
        return ERROR;
    }
    return queue->size > 0 ? 1 : 0;
}

// 清空队列
int Clear_LinkQueue(LinkQueue *queue)
{
    if (NULL == queue)
    {
        return ERROR;
    }

    // 释放队列里面元素的空间
    while (queue->size != 0)
    {
        LinkQueueNode *pCurrrent = queue->head;
        queue->head = queue->head->next;
        if (queue->size == 1)
        {
            queue->tail = queue->head; // 两个都是NULL
        }

        free(pCurrrent);
        pCurrrent = NULL;
    }

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;

    return TRUE;
}

// 销毁
int FreeSpace_LinkQueue(LinkQueue *queue)
{
    if (NULL == queue)
    {
        return ERROR;
    }

    while (queue->size != 0)
    {
        LinkQueueNode *pCurrrent = queue->head;
        queue->head = queue->head->next;
        if (queue->size == 1)
        {
            queue->tail = queue->head; // 两个都是NULL
        }

        free(pCurrrent);
        pCurrrent = NULL;
    }

    // 比清空队列代码多下面两行
    free(queue);
    queue = NULL;

    return TRUE;
}
