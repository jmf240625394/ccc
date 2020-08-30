#include "LinkQueue.h"

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

// 入队，从链表尾入队
// 如果不是企业链表，要给node分配存储空间
int Push_LinkQueue(LinkQueue *queue, LinkQueueNode *node)
{
    if (NULL == queue || NULL == node)
    {
        return ERROR;
    }

    // 新节点从链表尾入队
    if (queue->size == 0)
    {
        queue->head = node;
    }
    else
    {
        queue->tail->next = node;
    }
    queue->tail = node;

    queue->size++;
    return TRUE;
}

// 从从链表尾返回队头元素
LinkQueueNode *Front_LinkQueue(LinkQueue *queue)
{
    if (NULL == queue || queue->size == 0)
    {
        return NULL;
    }
    return queue->tail;
}

// 从链表头出队
int Pop_LinkQueue(LinkQueue *queue)
{
    if (NULL == queue || queue->size == 0)
    {
        return ERROR;
    }

    queue->head = queue->head->next;
    if (queue->size == 1)
    {
        queue->tail = queue->head; // 两个都是NULL
    }

    queue->size--;
    return TRUE;
}

// 从链表头返回队尾元素
LinkQueueNode *Back_LinkQueue(LinkQueue *queue)
{
    if (NULL == queue || queue->size == 0)
    {
        return NULL;
    }
    return queue->head;
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

// 清空队列
int Clear_LinkQueue(LinkQueue *queue)
{
    if (NULL == queue)
    {
        return ERROR;
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
    free(queue);
    queue = NULL;
    return TRUE;
}