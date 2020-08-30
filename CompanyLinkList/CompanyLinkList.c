#include "CompanyLinkList.h"

// 创建链表并初始化
LinkList *Init_LinkList()
{
    LinkList *list = (LinkList *)malloc(sizeof(LinkList));
    list->size = 0;
    list->head.next = NULL;
    return list;
}

// 插入数据 根据位置插入，pos从1开始
int Insert_LinkList(LinkList *list, int pos, LinkNode *data)
{
    if (NULL == list || NULL == data)
    {
        return ERROR;
    }
    // 位置太小插入到第一个位置
    if (pos < 1)
    {
        pos = 1;
    }
    // 位置太大插入到尾部
    if (pos > list->size)
    {
        pos = list->size + 1;
    }

    // 找到插入位置的前驱节点
    LinkNode *pCurrent = &list->head;
    for (int i = 1; i < pos; i++)
    {
        pCurrent = pCurrent->next;
    }

    // 这里不用分配内存
    data->next = pCurrent->next;
    pCurrent->next = data;
    list->size++;
    return OK;
}

// 删除数据 根据位置删除 pos从1开始
int Remove_LinkList(LinkList *list, int pos)
{
    // list为NULL 或者位置非法 直接返回
    if (NULL == list || pos < 1 || pos > list->size)
    {
        return ERROR;
    }

    LinkNode *pCurrent = &list->head;
    // 同样找到删除节点的前驱
    for (int i = 1; i < pos; i++)
    {
        pCurrent = pCurrent->next;
    }
    // 将不要的元素略过，因为我们只维护用户提供的数据的地址，释放内存不归我们管
    pCurrent->next = pCurrent->next->next;
    list->size--;
    return OK;
}

// 查找数据，根据数据内容，返回时链表中的第几个元素，从1开始计数 ，找到返回index，没找到返回-1
// Compare 用户提供 结点元素比较的回调函数
int Find_LinkList(LinkList *list, LinkNode *data, int (*COMPARE)(LinkNode *, LinkNode *))
{
    if (NULL == list || NULL == data || NULL == COMPARE)
    {
        return ERROR;
    }
    LinkNode *nCurrent = list->head.next;
    int flag = 0; // 是否找到的标志
    int index = 1;
    while (nCurrent != NULL)
    {
        if (COMPARE(nCurrent, data))
        {
            flag = 1;
            break;
        }
        nCurrent = nCurrent->next;
        index++;
    }
    return flag ? index : -1;
}

// 遍历链表
// Foreach 用户提供的遍历链表元素的回调函数
int Foreach_LinkList(LinkList *list, void (*FOREACH)(LinkNode *))
{
    if (NULL == list || NULL == FOREACH)
    {
        return ERROR;
    }
    LinkNode *nCurrent = list->head.next;
    while (NULL != nCurrent)
    {
        FOREACH(nCurrent);
        nCurrent = nCurrent->next;
    }
    return OK;
}

// 返回链表大小，这里还是存在二义性
int Size_LinkList(LinkList *list)
{
    if (NULL == list)
    {
        return ERROR;
    }
    return list->size;
}

// 清空数据 链表仍然可用
int Clear_LinkList(LinkList *list)
{
    if (NULL == list)
    {
        return ERROR;
    }
    list->size = 0;
    list->head.next = NULL;
    return OK;
}

// 销毁链表
int FreeSpace_LinkList(LinkList *list)
{
    if (NULL == list)
    {
        return ERROR;
    }
    free(list);
    list = NULL;
    return OK;
}