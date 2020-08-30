#include "LinkStack.h"

typedef struct MYCHAR
{
    LinkNode node;
    char *pAddress;
    int index;
} MyChar;

int IsLeft(char c)
{
    return c == '(';
}

int IsRight(char c)
{
    return c == ')';
}

// 左括号准备准备入栈（分配内存，记录指针和位置）
MyChar *CreateMyChar(char *p, int index)
{
    MyChar *mychar = (MyChar *)malloc(sizeof(MyChar));
    mychar->pAddress = p;
    mychar->index = index;
    return mychar;
}

// 打印原字符，并且在错误的pos出打出A字符
void ShowError(char *str, int pos)
{
    printf("%s\n", str);
    for (int i = 0; i < pos; ++i)
    {
        printf(" ");
    }
    printf("A");
}

int main()
{
    char *str = "1+2+6(dsf)dfsflp((sdfs)";

    LinkStack *stack = Init_LinkStack();
    char *p = str;
    int index = 0;

    while (*p != '\0')
    {
        // 如果左括号，直接进栈
        if (IsLeft(*p))
        {
            Push_LinkStack(stack, (LinkNode *)CreateMyChar(p, index));
        }
        // 如果右括号，判断栈顶是不是左括号，如果是左括号就从栈顶弹出
        if (IsRight(*p))
        {
            if (Size_LinkStack(stack) > 0)
            {
                // 获取栈顶元素，并进行判断
                MyChar *mychar = (MyChar *)Top_LinkStack(stack);
                if (IsLeft(*(mychar->pAddress)))
                {
                    // 出栈，并且释放CreateMyChar函数创建的mychar对象
                    Pop_LinkStack(stack);
                    free(mychar);
                }
            }
            else
            {
                printf("右括号没有匹配的左括号：\n");
                ShowError(str, index);
                break;
            }
        }
        p++;
        index++;
    }

    while (Size_LinkStack(stack) > 0)
    {
        MyChar *mychar = (MyChar *)Top_LinkStack(stack);
        printf("左括号没有匹配的右括号：\n");
        ShowError(str, mychar->index);
        Pop_LinkStack(stack);
        free(mychar);
    }

    printf("\n");

    return 0;
}