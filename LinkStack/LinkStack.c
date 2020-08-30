#include "LinkStack.h"

// 初始化函数
LinkStack *Init_LinkStack()
{
    LinkStack *stack = (LinkStack *)malloc(sizeof(LinkStack));
    if (NULL == stack)
    {
        return NULL;
    }
    stack->header.next = NULL;
    stack->size = 0;

    return stack;
}

// 入栈
int Push_LinkStack(LinkStack *stack, LinkNode *data)
{
    if (NULL == stack || NULL == data)
    {
        return FALSE;
    }
    data->next = stack->header.next;
    stack->header.next = data;
    stack->size++;
    return TRUE;
}

// 出栈
int Pop_LinkStack(LinkStack *stack)
{
    if (NULL == stack || stack->size == 0)
    {
        return FALSE;
    }
    // 第一个有效节点
    LinkNode *pNext = stack->header.next;
    stack->header.next = pNext->next;
    stack->size--;
    return TRUE;
}

// 返回栈顶元素
LinkNode *Top_LinkStack(LinkStack *stack)
{
    if (NULL == stack || stack->size == 0)
    {
        return NULL;
    }
    return stack->header.next;
}

// 返回栈元素的个数
int Size_LinkStack(LinkStack *stack)
{
    if (NULL == stack)
    {
        return FALSE;
    }
    return stack->size;
}

// 清空栈
int Clear_LinkStack(LinkStack *stack)
{
    if (NULL == stack)
    {
        return FALSE;
    }
    stack->header.next = NULL;
    stack->size = 0;
    return TRUE;
}

// 销毁栈
int FreeSpace_LinkStack(LinkStack *stack)
{
    if (NULL == stack)
    {
        return FALSE;
    }
    free(stack);
    return TRUE;
}