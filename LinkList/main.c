#include "LinkList.h"

// 自定义类型
typedef struct PERSON
{
    char name[64];
    int age;
    int score;
} Person;

// 打印函数
void MyPrint(void *data)
{
    Person *p = (Person *)data;
    printf("Name: %s Age: %d Score: %d\n", p->name, p->age, p->score);
}

int MyCompare(void *data1, void *data2)
{
    if (NULL == data1)
    {
        return 0;
    }
    if (NULL == data2)
    {
        return 0;
    }
    Person *p1 = (Person *)data1;
    Person *p2 = (Person *)data2;
    printf("******* p1->name: %s  p1->age: %d  p1->score: %d\n", p1->name, p1->age, p1->score);
    printf("******* p2->name: %s  p2->age: %d  p2->score: %d\n", p2->name, p2->age, p2->score);
    if (strcmp(p1->name, p2->name) == 0 && p1->age == p2->age && p1->score == p2->score)
    {
        printf("*******ok*******");
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    // 创建链表
    LinkList *list = Init_LinkList();

    // 创建数据
    Person p1 = {"aaa", 18, 100};
    Person p2 = {"bbb", 17, 57};
    Person p3 = {"ccc", 20, 63};
    Person p4 = {"ddd", 22, 87};
    Person p5 = {"eee", 16, 32};

    // 数据插入链表
    Insert_LinkList(list, 0, &p1);
    Insert_LinkList(list, 0, &p2);
    Insert_LinkList(list, 0, &p3);
    Insert_LinkList(list, 0, &p4);
    Insert_LinkList(list, 0, &p5);

    // 打印
    Print_LinkList(list, MyPrint);

    // 删除3
    RemoveByPos_LinkList(list, 3);

    // 打印
    printf("------------------\n");
    Print_LinkList(list, MyPrint);

    printf("------------------\n");
    Person *p = (Person *)Front_LinkList(list);
    printf("Name: %s Age: %d Score: %d\n", p->name, p->age, p->score);

    // 查找p1的位置
    printf("------------------\n");
    int ret = Find_LinkList(list, MyCompare, &p1);
    printf("p1位置: %d\n", ret);

    // 销毁链表
    FreeSpace_LinkList(list);

    return 0;
}