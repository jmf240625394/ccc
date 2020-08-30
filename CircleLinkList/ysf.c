#include "CircleLinkList.h"

/*
    约瑟夫问题-循环链表典型应用
    n 个人围成一个圆圈，首先第 1 个人从 1 开始一个人一个人顺时针报数，
    报到第 m 个人，令其出列。然后再从下一 个人开始从 1 顺时针报数，报
    到第 m 个人，再令其出列，…，如此下去，求出列顺序。

    求解: 假设 m = 3, n = 8 (1 2 3 4 5 6 7 8)
    结果: 3 6 1 5 2 8 4 7
*/

typedef struct PERSON
{
    CircleLinkListNode node;
    int v;
} Person;

void Print(CircleLinkListNode *node)
{
    Person *p = (Person *)node;
    printf("第 %d 人\n", p->v);
    return;
}

int main()
{
    Person p[8];

    CircleLinkList *list = CircleLinkList_Create();
    // 初始化数组并将节点插入到链表
    for (int i = 1; i < 9; ++i)
    {
        p[i - 1].v = i;
        CircleLinkList_Insert(list, (CircleLinkListNode *)&p[i - 1], i);
    }
    printf("-------完成人员初始化-------\n");
    CircleLinkList_Foreach(list, Print);

    // 准备杀人
    CircleLinkList_Reset(list);
    while (CircleList_Length(list) > 0)
    {
        for (int i = 1; i < 3; ++i)
        {   // 只能移动2次,第3次需要等到删除游标指向的元素再移动
            // 向后移动游标
            CircleLinkList_Next(list);
        }
        // 打印
        Person *pTemp = (Person *)list->slider;
        printf("第 %d 人出列\n", pTemp->v);

        // 保存第m+1个人的指针
        CircleLinkListNode *slnext = list->slider->next;

        CircleLinkList_DeleteNode(list,list->slider); // 如果是堆分配内存，这里也要将对应的Person 对象释放
        CircleLinkList_Foreach(list, Print);

        // 将游标指向下一个人
        list->slider = slnext;
    }

    return 0;
}
