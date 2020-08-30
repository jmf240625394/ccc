#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ERROR -1;
#define FALSE 0;
#define TRUE 1;

#define MAX_SIZE 1024

// 顺序队列结构体
typedef struct SEQQUEUE
{
    void *data[MAX_SIZE];
    int size;
} SeqQueue;

// 初始化
SeqQueue *Init_SeqQueue();
// 入队
int Push_SeqQueue(SeqQueue *queue, void *data);
// 返回队头元素
void *Front_SeqQueue(SeqQueue *queue);
// 出队
int Pop_SeqQueue(SeqQueue *queue);
// 返回队尾元素
void *Back_SeqQueue(SeqQueue *queue);
// 返回大小
int Size_SeqQueue(SeqQueue *queue);
// 清空队列
int Clear_SeqQueue(SeqQueue *queue);
// 销毁
int FreeSpace_SeqQueue(SeqQueue *queue);

#endif