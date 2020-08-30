#include "LinkStack.h"

typedef struct PERSON
{
    LinkNode node;
    char name[64];
    int age;
} Person;

int main()
{
    // 创建栈
    LinkStack *stack = Init_LinkStack();

    // 创建数据
    Person p1, p2, p3, p4, p5;
    strcpy(p1.name, "aaa");
    strcpy(p2.name, "bbb");
    strcpy(p3.name, "ccc");
    strcpy(p4.name, "ddd");
    strcpy(p5.name, "eee");

    p1.age = 10;
    p2.age = 20;
    p3.age = 30;
    p4.age = 40;
    p5.age = 50;

    // 入栈
    Push_LinkStack(stack, (LinkNode *)&p1);
    Push_LinkStack(stack, (LinkNode *)&p2);
    Push_LinkStack(stack, (LinkNode *)&p3);
    Push_LinkStack(stack, (LinkNode *)&p4);
    Push_LinkStack(stack, (LinkNode *)&p5);

    // 输出
    while (Size_LinkStack(stack) > 0)
    {
        // 访问栈顶元素
        Person *person = (Person *)Top_LinkStack(stack);
        printf("Name: %s Age: %d\n", person->name, person->age);
        // 弹出栈顶元素
        Pop_LinkStack(stack);
    }

    // 释放内存
    FreeSpace_LinkStack(stack);
}