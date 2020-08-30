#ifndef SEQSTACK_H
#define SEQSTACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 数组去模拟栈的顺序存储
#define MAX_SIZE 1024

/* 
统一使用-1作为错误返回值；
数值返回值的函数，利用flag标志位标记，成功返回数值；不成功返回-1，0,1都是成功的返回值
flag?index:-1;  // index是返回值

操作型函数 将int作为返回类型时，由于非零是真，因此操作成功返回True；操作失败返回FALSE
操作型函数 返回具体的数据类型时，报错返回NULL，类似malloc
*/

#define ERROR -1;
#define FALSE 0;
#define TRUE 1;


typedef struct SEQSTACK
{
    void *data[MAX_SIZE];
    int size;
} SeqStack;

// 初始化栈
SeqStack *Init_SeqStack();
// 返回栈顶元素
void *Top_SeqStack(SeqStack *stack);
// 入栈
int Push_SeqStack(SeqStack *stack, void *data);
// 出栈
int Pop_SeqStack(SeqStack *stack);
// 判断栈是否为空
int IsEmpty_SeqStack(SeqStack *stack);
// 返回栈中元素的个数
int Size_SeqStack(SeqStack *stack);
// 清空栈
int Clear_SeqStack(SeqStack *stack);
// 销毁
int FreeSpace_SeqStack(SeqStack *stack);

#endif
