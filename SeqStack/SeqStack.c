#include "SeqStack.h"

// 初始化栈
SeqStack *Init_SeqStack()
{
    SeqStack *stack = (SeqStack *)malloc(sizeof(SeqStack));
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        stack->data[i] = NULL;
    }
    stack->size = 0;
    return stack;
}

// 返回栈顶元素
void *Top_SeqStack(SeqStack *stack)
{
    if (NULL == stack || stack->size == 0)
    {
        return NULL;
    }
    return stack->data[stack->size - 1];
}

// 入栈
int Push_SeqStack(SeqStack *stack, void *data)
{
    if (NULL == stack || stack->size == MAX_SIZE || NULL == data)
    {
        return FALSE;
    }
    stack->data[stack->size] = data;
    stack->size++;
    return TRUE;
}
// 出栈
int Pop_SeqStack(SeqStack *stack)
{
    if (NULL == stack || stack->size == 0)
    {
        return FALSE;
    }
    stack->data[stack->size - 1] = NULL;
    stack->size--;
    return TRUE;
}
// 判断栈是否为空
int IsEmpty_SeqStack(SeqStack *stack)
{
    if (NULL == stack)
    {
        return -1;
    }
    if (stack->size == 0)
    {
        return TRUE;
    }
    return FALSE;
}

// 返回栈中元素的个数
int Size_SeqStack(SeqStack *stack)
{
    if (NULL == stack)
    {
        return -1;
    }
    return stack->size;
}

// 清空栈
int Clear_SeqStack(SeqStack *stack)
{
    if (NULL == stack)
    {
        return -1;
    }
    for (int i = 0; i < stack->size; ++i)
    {
        stack->data[i] = NULL;
    }
    stack->size = 0;
    return TRUE;
}

// 销毁
int FreeSpace_SeqStack(SeqStack *stack)
{
    if (NULL == stack)
    {
        return -1;
    }
    free(stack);
    return TRUE;
}