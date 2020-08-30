#ifndef LINKSTACK_H
#define LINKSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1;
#define FALSE 0;
#define TRUE 1;

// 链式栈的节点
typedef struct LINKNODE
{
    struct LINKNODE *next;
} LinkNode;

// 链式栈
typedef struct LINKSTACK
{
    LinkNode node;
    LinkNode header;
    int size;
} LinkStack;

// 初始化函数
LinkStack *Init_LinkStack();
// 入栈
int Push_LinkStack(LinkStack *stack, LinkNode *data);
// 出栈
int Pop_LinkStack(LinkStack *stack);
// 返回栈顶元素
LinkNode *Top_LinkStack(LinkStack *stack);
// 返回栈元素的个数
int Size_LinkStack(LinkStack *stack);
// 清空栈
int Clear_LinkStack(LinkStack *stack);
// 销毁栈
int FreeSpace_LinkStack(LinkStack *stack);

#endif