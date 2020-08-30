#include <string.h>
#include "CircleLinkList.h"

typedef struct PERSON
{
    CircleLinkListNode node;
    char name[64];
    int age;
} Person;

void Print(CircleLinkListNode *node)
{
    Person *p = (Person *)node;
    printf("姓名：%s，年龄：%d\n", p->name, p->age);
    return;
}

int Compare(CircleLinkListNode *n1, CircleLinkListNode *n2)
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
    CircleLinkList *list = CircleLinkList_Create();

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
    CircleLinkList_Insert(list, (CircleLinkListNode *)&p1, 1);
    CircleLinkList_Insert(list, (CircleLinkListNode *)&p2, 1);
    CircleLinkList_Insert(list, (CircleLinkListNode *)&p3, 3);
    CircleLinkList_Insert(list, (CircleLinkListNode *)&p4, 4);
    CircleLinkList_Insert(list, (CircleLinkListNode *)&p5, 5);

    printf("插入5条数据后遍历:\n");
    printf("数据条数： %d\n", CircleList_Length(list));
    CircleLinkList_Foreach(list, Print);

    // 这个函数有待补充
    // Person p6;
    // p6.age = 30;
    // strcpy(p6.name, "ccc");
    // int index = CircleLinkList_index(list, (CircleLinkListNode *)&p6, Compare);
    // printf("查找元素的name=ccc,age=30,是链表中第 %d 个元素\n", (index));

    // 删除元素
    CircleLinkList_Delete(list, 5);
    printf("删除第2个节点后遍历：\n");
    CircleLinkList_Foreach(list, Print);

    return 0;
}