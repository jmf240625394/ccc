#include "LinkList.h"

// 初始化链表
LinkList *Init_LinkList()
{
    LinkList *list = (LinkList *)malloc(sizeof(LinkList));
    list->size = 0;

    // 头节点，是不保存数据信息
    list->head = (LinkNode *)malloc(sizeof(LinkNode));
    list->head->data = NULL;
    list->head->next = NULL;

    return list;
}

// 指定位置插入
void Insert_LinkList(LinkList *list, int pos, void *data)
{
    if (NULL == list)
    {
        return;
    }
    if (NULL == data)
    {
        return;
    }

    // 友好的处理，pos越界
    if (pos < 0 || pos > list->size)
    {
        pos = list->size;
    }

    // 创建新节点
    LinkNode *newnode = (LinkNode *)malloc(sizeof(LinkNode));
    newnode->data = data;
    newnode->next = NULL;

    // 找节点
    // 辅助指针变量
    LinkNode *pCurrent = list->head;
    for (int i = 0; i < pos; i++)
    {
        pCurrent = pCurrent->next;
    }

    // 新节点入链表
    newnode->next = pCurrent->next;
    pCurrent->next = newnode;

    list->size++;
}

// 删除指定位置的值
void RemoveByPos_LinkList(LinkList *list, int pos)
{
    if (NULL == list)
    {
        return;
    }

    // 友好的处理，pos越界
    if (pos < 0 || pos >= list->size)
    {
        return;
    }

    // 查找删除节点的前一个节点
    LinkNode *pCurrent = list->head;
    for (int i = 0; i < pos; i++)
    {
        pCurrent = pCurrent->next;
    }

    // 缓存删除的节点
    LinkNode *pDel = pCurrent->next;
    pCurrent->next = pDel->next;
    // 释放删除节点的内存
    free(pDel);

    list->size--;
}

// 获得链表的长度
int Size_LinkList(LinkList *list)
{
    return list->size;
}

// 查找
int Find_LinkList(LinkList *list, COMPARE isequal, void *data)
{
    if (NULL == list)
    {
        return -1;
    }

    // 遍历查找，由于链表是单独的头结点，存储结点是从0开始
    // 因此这里i是-1，头结点也比较一下，否则返回的数字有可能异常
    LinkNode *pCurrent = list->head;
    int i = -1;
    while (pCurrent != NULL)
    {
        if (isequal(pCurrent->data, data) == 1)
        {
            break;
        }
        i++;
        pCurrent = pCurrent->next;
    }

    return i;
}

// 返回第一个节点
void *Front_LinkList(LinkList *list)
{
    return list->head->next->data;
}

// 打印链表节点
void Print_LinkList(LinkList *list, PRINTLINKNODE print)
{
    if (NULL == list)
    {
        return;
    }

    // 辅助指针变量
    LinkNode *pCurrent = list->head->next;
    while (pCurrent != NULL)
    {
        print(pCurrent->data);
        pCurrent = pCurrent->next;
    }
}

// 释放链表内存
void FreeSpace_LinkList(LinkList *list)
{
    if (NULL == list)
    {
        return;
    }

    // 辅助指针变量
    LinkNode *pCurrent = list->head;
    while (pCurrent != NULL)
    {
        // 缓存下一个节点
        LinkNode *pNext = pCurrent->next;
        free(pCurrent);
        pCurrent = pNext;
    }

    // 释放链表内存
    list->size = 0;
    free(list);
}
