#include "CircleLinkList.h"

// 创建循环链表
CircleLinkList *CircleLinkList_Create()
{
    // 定义CircleLinkList指针变量，并分配内存空间
    CircleLinkList *list = (CircleLinkList *)malloc(sizeof(CircleLinkList));
    if (NULL == list)
    {
        printf("error: can not malloc memory!\n");
        return NULL;
    }
    // 数据初始化
    list->header.next = NULL;
    list->slider = NULL;
    list->length = 0;

    return list;
}

// 销毁循环链表
void CircleLinkList_Destroy(CircleLinkList *list)
{
    // 判断list是否为有效指针
    if (NULL == list)
    {
        printf("error: list 为无效指针\n");
        return;
    }
    free(list);
}

// 清空循环链表
void CircleLinkList_Clear(CircleLinkList *list)
{
    // 判断list是否为有效指针
    if (NULL == list)
    {
        printf("error: list 为无效指针\n");
        return;
    }
    //将长度重置为0
    list->length = 0;
    //头结点指针域指向空
    list->header.next = NULL;
    //游标指向空
    list->slider = NULL;
}

// 获取循环链表长度
int CircleList_Length(CircleLinkList *list)
{
    // 判断list是否为有效指针
    if (NULL == list)
    {
        printf("error: list 为无效指针\n");
        return -1;
    }
    return list->length;
}

// 在循环链表中插入新节点，节点从1开始
int CircleLinkList_Insert(CircleLinkList *list, CircleLinkListNode *node, int pos)
{
    if (NULL == list || NULL == node || pos < 1 || pos > (list->length + 1))
    {
        return -1;
    }

    // 第一次插入元素
    if (list->length == 0)
    {
        node->next = node;
        list->header.next = node;
        list->length++;
        return 0;
    }

    // 稍微注意一下：list->header.next和后面的pCurrent->next是同一个东西
    // 因为list->header和pCurrent的对象不同，因此用法不一样

    // 元素插入
    // 定义辅助指针变量
    // step 1: 使用辅助指针变量，指向头节点
    CircleLinkListNode *pCurrent = &list->header;
    // step 2: 找到pos-1位置节点
    for (int i = 1; i < pos; i++)
    {
        pCurrent = pCurrent->next;
    }

    // step 3: 将node节点的指针指向当前节点pos-1的后继节点pos
    // 这条语句兼容尾节点插入
    node->next = pCurrent->next;

    // step 4: 当前节点的指针指向node节点的地址
    if (pos == 1)
    {
        // 头节点插入
        CircleLinkListNode *last = CircleLinkList_Get(list, list->length);
        last->next = node;
    }
    pCurrent->next = node;
    list->length++;
    return 0;
}

// 获取循环链表中的指定位置的节点
CircleLinkListNode *CircleLinkList_Get(CircleLinkList *list, int pos)
{
    if (NULL == list || pos < 1 || pos > list->length)
    {
        return NULL;
    }

    // 辅助指针，初始化是指向头节点
    CircleLinkListNode *pCurrent = &list->header;
    // 找到pos的前一个位置
    for (int i = 1; i < pos; i++)
    {
        pCurrent = pCurrent->next;
    }
    return pCurrent->next;
}

// 删除循环链表中的指定位置的节点
void CircleLinkList_Delete(CircleLinkList *list, int pos)
{
    if (NULL == list || pos < 1 || pos > list->length)
    {
        return;
    }

    // 辅助指针，初始化是指向头节点
    CircleLinkListNode *pCurrent = &list->header;
    // 找到pos的前一个位置
    for (int i = 1; i < pos; i++)
    {
        pCurrent = pCurrent->next;
    }
    if (pos == 1)
    {
        // 删除第一个元素，要更新尾节点的指针
        CircleLinkListNode *last = CircleLinkList_Get(list, list->length);
        last->next = pCurrent->next->next;
    }
    pCurrent->next = pCurrent->next->next;
    list->length--;
}

// 循环列表元素遍历
void CircleLinkList_Foreach(CircleLinkList *list, void (*FOREACH)(CircleLinkListNode *))
{
    if (NULL == list || NULL == FOREACH || list->length == 0)
    {
        return;
    }
    // 找到第一个元素
    CircleLinkListNode *pCurrent = list->header.next;
    for (int i = 1; i <= list->length; i++)
    {
        FOREACH(pCurrent);
        pCurrent = pCurrent->next;
    }
    return;
}

// ------------------ new add 自己去补充------------------

// 根据元素，确定元素位置
int CircleLinkList_index(CircleLinkList *list, CircleLinkListNode *node)
{
    if (NULL == list || NULL == node || list->length == 0)
    {
        return -1;
    }
    // 将辅助指针指向第一个元素
    CircleLinkListNode *pCurrent = &list->header;
    pCurrent = pCurrent->next;
    for (int i = 1; i <= list->length; ++i)
    {
        if (pCurrent == node)
        {
            return i;
        }
        pCurrent = pCurrent->next;
    }
    return -1;
}

// 直接指定删除链表中的某个数据元素
void CircleLinkList_DeleteNode(CircleLinkList *list, CircleLinkListNode *node)
{
    if (NULL == list || NULL == node || list->length == 0)
    {
        return;
    }

    int ret;
    ret = CircleLinkList_index(list, node);
    if (ret == -1)
    {
        return; // 这里应该报错的
    }
    CircleLinkList_Delete(list, ret);
    return;
}

// 将游标重置指向链表中的第一个数据元素
void CircleLinkList_Reset(CircleLinkList *list)
{
    if (NULL == list)
    {
        return;
    }
    CircleLinkListNode *pCurrent = &list->header;
    pCurrent = pCurrent->next;
    list->slider = pCurrent;
    return;
}

// 获取当前游标指向的数据元素
CircleLinkListNode *CircleLinkList_Current(CircleLinkList *list)
{
    if (NULL == list)
    {
        return NULL;
    }
    return list->slider;
}

// 将游标移动指向到链表中的下一个数据元素
void CircleLinkList_Next(CircleLinkList *list)
{
    if (NULL == list)
    {
        return;
    }
    list->slider = list->slider->next;
}
