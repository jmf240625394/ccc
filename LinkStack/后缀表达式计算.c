#include <string.h>
#include "LinkStack.h"

typedef struct MYNUM
{
    LinkNode node;
    int val;
} MyNum;

// 判断是否时数字
int IsNumber(char c)
{
    return c >= '0' && c <= '9';
}

int Caculate(int left, int right, char c)
{
    int ret;
    switch (c)
    {
    default:
        break;
    case '+':
        ret = left + right;
        break;
    case '-':
        ret = left - right;
        break;
    case '*':
        ret = left * right;
        break;
    case '/':
        ret = left / right;
        break;
    }

    return ret;
}

int main()
{
    // 后缀表达式
    char *str = "831-5*+";
    char *p = str;

    LinkStack *stack = Init_LinkStack();

    while (*p != '\0')
    {
        if (IsNumber(*p))
        {
            MyNum *num = (MyNum *)malloc(sizeof(MyNum));
            num->val = *p - '0';
            Push_LinkStack(stack, (LinkNode *)num);
        }
        else
        {
            // 先从栈中弹出右操作数
            MyNum *right = (MyNum *)Top_LinkStack(stack);
            int rightNum = right->val;
            Pop_LinkStack(stack);
            free(right);
            // 取出左操作数
            MyNum *left = (MyNum *)Top_LinkStack(stack);
            int leftNum = left->val;
            Pop_LinkStack(stack);
            free(left);

            int ret = Caculate(leftNum, rightNum, *p);
            // 结果入栈
            MyNum *num = (MyNum *)malloc(sizeof(MyNum));
            num->val = ret;
            Push_LinkStack(stack, (LinkNode *)num);
        }
        p++;
    }

    // 打印结果
    if (Size_LinkStack(stack) == 1)
    {
        MyNum *num = (MyNum *)Top_LinkStack(stack);
        printf("运算结果是：%d\n", num->val);
        Pop_LinkStack(stack);
        free(num);
    }

    // 释放栈
    FreeSpace_LinkStack(stack);
    return 0;
}