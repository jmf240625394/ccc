#include <string.h>
#include "LinkQueue2.h"

typedef struct PERSON
{
    char name[64];
    int age;
} Person;

void Print(LinkQueueNode *node)
{
    Person *p = (Person *)node;
    printf("姓名：%s，年龄：%d\n", p->name, p->age);
    return;
}

int main()
{
    // 创建链表
    LinkQueue *queue = Init_LinkQueue();

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

    // 将节点插入链
    Push_LinkQueue(queue, &p1);
    Push_LinkQueue(queue, &p2);
    Push_LinkQueue(queue, &p3);
    Push_LinkQueue(queue, &p4);
    Push_LinkQueue(queue, &p5);

    // 输出
    while (Size_LinkQueue(queue) > 0)
    {
        // 从队尾取元素
        Person *p = (Person *)Back_LinkQueue(queue);
        printf("姓名：%s，年龄：%d\n", p->name, p->age);
        // 从队尾弹出元素
        Pop_LinkQueue(queue);
    }

    Clear_LinkQueue(queue);
    // 销毁队列
    FreeSpace_LinkQueue(queue);

    return 0;
}