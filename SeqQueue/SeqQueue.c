#include "SeqQueue.h"

// 初始化
SeqQueue *Init_SeqQueue()
{
    SeqQueue *queue = (SeqQueue *)malloc(sizeof(SeqQueue));
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        queue->data[i] = NULL;
    }
    queue->size = 0;
}

// 入队
int Push_SeqQueue(SeqQueue *queue, void *data)
{
    // 数组左边当做队头
    if (NULL == queue || NULL == data || queue->size == MAX_SIZE)
    {
        return FALSE;
    }
    queue->data[queue->size] = data;
    queue->size++;
    return TRUE;
}

// 返回队头元素
void *Front_SeqQueue(SeqQueue *queue)
{
    if (NULL == queue || queue->size == 0)
    {
        return NULL;
    }
    return queue->data[0];
}

// 出队
int Pop_SeqQueue(SeqQueue *queue)
{
    /* 需要移动元素 */
    if (NULL == queue || queue->size == 0)
    {
        return FALSE;
    }
    for (int i = 0; i < queue->size - 1; ++i)
    {
        queue->data[i] = queue->data[i + 1];
    }
    queue->size--;
    return TRUE;
}

// 返回队尾元素
void *Back_SeqQueue(SeqQueue *queue)
{
    if (NULL == queue || queue->size == 0)
    {
        return NULL;
    }
    return queue->data[queue->size - 1];
}

// 返回大小
int Size_SeqQueue(SeqQueue *queue)
{
    if (NULL == queue)
    {
        return -1;
    }
    return queue->size;
}

// 清空队列
int Clear_SeqQueue(SeqQueue *queue)
{
    if (NULL == queue)
    {
        return FALSE;
    }
    return TRUE;
}

// 销毁
int FreeSpace_SeqQueue(SeqQueue *queue)
{
    if (NULL == queue)
    {
        return FALSE;
    }
    free(queue);
    return TRUE;
}