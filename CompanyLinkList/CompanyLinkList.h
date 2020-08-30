#ifndef COMPANYLINKLIST_H
#define COMPANYLINKLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 枚举默认从0开始
// 成功状态 FALSE不成功 TRUE成功
typedef enum
{
    TRUE,
    FALSE
} BOOLEAN;

// 状态信息 ERROR发生错误 OK正常
typedef enum
{
    ERROR,
    OK
} STATUS;

// 链表小节点
typedef struct LINKNODE
{
    struct LINKNODE *next;
} LinkNode;

// 链表节点
typedef struct LINKLIST
{
    LinkNode head;
    int size;
} LinkList;

// 创建链表并初始化
LinkList *Init_LinkList();

// 插入数据 根据位置插入
int Insert_LinkList(LinkList *list, int pos, LinkNode *data);

// 删除数据 根据位置删除
int Remove_LinkList(LinkList *list, int pos);

// 查找数据，根据数据内容
int Find_LinkList(LinkList *list, LinkNode *data, int (*COMPARE)(LinkNode *, LinkNode *));

// 遍历链表
int Foreach_LinkList(LinkList *list, void (*FOREACH)(LinkNode *));

// 返回链表大小
int Size_LinkList(LinkList *list);

// 清空数据 链表仍然可用
int Clear_LinkList(LinkList *list);

// 销毁链表
int FreeSpace_LinkList(LinkList *list);

#endif