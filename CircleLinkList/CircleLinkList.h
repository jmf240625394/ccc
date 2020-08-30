#ifndef CIRCLELINKLIST_H
#define CIRCLELINKLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// typedef enum
// {
//     ERROR,
//     OK
// } STATUS;

// 自定义循环链表节点数据类型
typedef struct CIRCLELINKLISTNODE
{
    struct CIRCLELINKLISTNODE *next;
} CircleLinkListNode;

//创建结构体管理链表
typedef struct CIRCLELINKLIST
{
    //循环链表头结点
    CircleLinkListNode header;
    //循环链表游标
    CircleLinkListNode *slider;
    //循环链表长度
    int length;
} CircleLinkList;

// 创建循环链表
CircleLinkList *CircleLinkList_Create();

// 销毁循环链表
void CircleLinkList_Destroy(CircleLinkList *list);

// 清空循环链表
void CircleLinkList_Clear(CircleLinkList *list);

// 获取循环链表长度
int CircleList_Length(CircleLinkList *list);

// 在循环链表中插入新节点
int CircleLinkList_Insert(CircleLinkList *list, CircleLinkListNode *node, int pos);

// 获取循环链表中的指定位置的节点
CircleLinkListNode *CircleLinkList_Get(CircleLinkList *list, int pos);

// 删除循环链表中的指定位置的节点
void CircleLinkList_Delete(CircleLinkList *list, int pos);

// 循环列表元素遍历
void CircleLinkList_Foreach(CircleLinkList *List, void (*FOREACH)(CircleLinkListNode *));

// ------------------ new add ------------------

// 根据元素，确定元素位置
int CircleLinkList_index(CircleLinkList *list, CircleLinkListNode *node);

// 直接指定删除链表中的某个数据元素
void CircleLinkList_DeleteNode(CircleLinkList *list, CircleLinkListNode *node);

// 将游标重置指向链表中的第一个数据元素
void CircleLinkList_Reset(CircleLinkList *list);

// 获取当前游标指向的数据元素
CircleLinkListNode *CircleLinkList_Current(CircleLinkList *list);

// 将游标移动指向到链表中的下一个数据元素
void CircleLinkList_Next(CircleLinkList *list);

#endif