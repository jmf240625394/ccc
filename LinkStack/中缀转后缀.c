#include <string.h>
#include "LinkStack.h"

typedef struct MYCHAR
{
    LinkNode node;
    char *p;
} MyChar;

// 创建MyChar
MyChar *CreateMyChar(char *p)
{
    MyChar *mychar = (MyChar *)malloc(sizeof(MyChar));
    mychar->p = p; // 这里之前写成了==，排查了好长时间
    return mychar;
}

// 判断是否时数字
int IsNumber(char c)
{
    return c >= '0' && c <= '9';
}

// 判断是不是左括号
int IsLeft(char c)
{
    return c == '(';
}

// 判断是不是右括号
int IsRight(char c)
{
    return c == ')';
}

// 判断是不是运算符
int IsOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 返回运算符的优先级
int GetPriority(char c)
{
    if (c == '*' || c == '/')
    {
        return 2;
    }
    if (c == '+' || c == '-')
    {
        return 1;
    }
    return 0;
}

// 运算符号的操作
void OperatorOperate(LinkStack *stack, char *p)
{
    // 先取出栈顶符号
    MyChar *mychar = (MyChar *)Top_LinkStack(stack);
    if (NULL == mychar)
    {
        Push_LinkStack(stack, (LinkNode *)CreateMyChar(p));
        return;
    }
    // 如果栈顶元素为左括号，直接入栈
    if (*(mychar->p) == '(')
    {
        Push_LinkStack(stack, (LinkNode *)CreateMyChar(p));
        return;
    }

    int gp1 = GetPriority(*(mychar->p));
    int gp2 = GetPriority(*p);

    // 如果栈顶优先级低于当前字符的优先级 直接入栈
    if(GetPriority(*(mychar->p)) < GetPriority(*p))
    // if (gp1 < gp2)
    {
        Push_LinkStack(stack, (LinkNode *)CreateMyChar(p));
        return;
    }

    // 如果栈顶符号优先级不低
    else
    {
        while (Size_LinkStack(stack) > 0)
        {
            MyChar *mychar2 = (MyChar *)Top_LinkStack(stack);
            // 如果优先级低 当前符号入栈
            if (GetPriority(*(mychar2->p) < GetPriority(*p)))
            {
                Push_LinkStack(stack, (LinkNode *)CreateMyChar(p));
                break;
            }
            printf("%c", *(mychar2->p));
            Pop_LinkStack(stack);
            free(mychar2);
        }
    }
}

// 数字操作
void NumberOperate(char *p)
{
    printf("%c", *p);
}

// 左括号的操作
void LeftOperate(LinkStack *stack, char *p)
{
    Push_LinkStack(stack, (LinkNode *)CreateMyChar(p));
}

// 右括号操作
void RightOperate(LinkStack *stack)
{
    // 先判断栈中有没有元素
    while (Size_LinkStack(stack) > 0)
    {
        MyChar *mychar = (MyChar *)Top_LinkStack(stack);
        // 如果匹配到左括号
        if (IsLeft(*(mychar->p)))
        {
            Pop_LinkStack(stack);
            break;
        }
        // 打印
        printf("%c", *(mychar->p));

        // 弹出
        Pop_LinkStack(stack);
        // 释放内存
        free(mychar);
    }
}

int main()
{
    char *str = "8+(3-1)*5";
    char *p = str;

    // 创建栈
    LinkStack *stack = Init_LinkStack();

    while (*p != '\0')
    {
        // 如果是数字
        if (IsNumber(*p))
        {
            NumberOperate(p);
            p++;
            continue;
        }

        // 如果是左括号，直接进栈
        if (IsLeft(*p))
        {
            LeftOperate(stack, p);
            p++;
            continue;
        }

        // 如果是右括号
        if (IsRight(*p))
        {
            RightOperate(stack);
            p++;
            continue;
        }

        // 如果是运算符号
        if (IsOperator(*p))
        {
            OperatorOperate(stack, p);
            p++;
            continue;
        }
    }

    while (Size_LinkStack(stack) > 0)
    {
        MyChar *mychar = (MyChar *)Top_LinkStack(stack);
        printf("%c", *(mychar->p));
        Pop_LinkStack(stack);
        free(mychar);
    }

    FreeSpace_LinkStack(stack);

    return 0;
}