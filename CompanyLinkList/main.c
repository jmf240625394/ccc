#include <string.h>
#include "CompanyLinkList.h"

typedef struct PERSON
{
    LinkNode node;
    char name[64];
    int age;
} Person;

void Print(LinkNode *node)
{
    Person *p = (Person *)node;
    printf("姓名：%s，年龄：%d\n", p->name, p->age);
    return;
}

int Compare(LinkNode *n1, LinkNode *n2)
{
    Person *p1 = (Person *)n1;
    Person *p2 = (Person *)n2;
    if (p1->age == p2->age && 0 == strcmp(p1->name, p2->name))
    {
        return 1; // 非零为真
    }
    return 0;
}

int main()
{
    // 创建链表
    LinkList *list = Init_LinkList();

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

    // 将节点插入链表
    Insert_LinkList(list, 1, (LinkNode *)&p1);
    Insert_LinkList(list, 1, (LinkNode *)&p2);
    Insert_LinkList(list, 1, (LinkNode *)&p3);
    Insert_LinkList(list, 1, (LinkNode *)&p4);
    Insert_LinkList(list, 1, (LinkNode *)&p5);

    printf("插入5条数据后遍历:\n");
    Foreach_LinkList(list, Print);

    Person p6;
    p6.age = 30;
    strcpy(p6.name, "ccc");
    int index = Find_LinkList(list, (LinkNode *)&p6, Compare);
    printf("查找元素的name=ccc,age=30,是链表中第 %d 个元素\n", (index));

    // 删除元素
    Remove_LinkList(list,2);
    printf("删除第2个节点后遍历：\n");
    Foreach_LinkList(list,Print);

    // 注意上面的数据全部在栈上，堆中指向栈中不推荐
    // 调用方需要给业务对象分配内存，管理内存回收等等

    return 0;
}