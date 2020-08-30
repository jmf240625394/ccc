#include "LinkQueue2.h"

// 二叉树节点
typedef struct BINARYNODE
{
    char ch;
    struct BINARYNODE *lchild;
    struct BINARYNODE *rchild;
} BinaryNode;

// 先（根）序递归遍历
void FirstRecursion(BinaryNode *root)
{
    if (NULL == root)
    {
        return;
    }

    // 先访问根节点
    printf("%c", root->ch);
    // 再遍历左子树
    FirstRecursion(root->lchild);
    // 再遍历右子树
    FirstRecursion(root->rchild);
}

// 利用队列完成层序遍历
// 一定要注意，因为LinkQueue2.c的普通链表中：
// 普通链表在入栈时虽然分配内存，但是这个内存在出栈时释放
// 但是对传入的数据没有影响，因为普通链表的节点中data是指针类型
void SeqTraverseBinaryTree(BinaryNode *root)
{
    if (NULL == root)
    {
        return;
    }

    LinkQueue *queue = Init_LinkQueue();
    Push_LinkQueue(queue, root);
    while (IsEmpty_LinkQueue(queue))
    {
        BinaryNode *node = Back_LinkQueue(queue);
        printf("%c ", node->ch);
        if (node->lchild)
        {
            Push_LinkQueue(queue, node->lchild);
        }
        if (node->rchild)
        {
            Push_LinkQueue(queue, node->rchild);
        }
        Pop_LinkQueue(queue);
    }
    printf("\n");
}

// 释放二叉树
void FreeSpaceBinaryTree(BinaryNode *root)
{
    if (NULL == root)
    {
        return;
    }
    // 释放左子树
    FreeSpaceBinaryTree(root->lchild);
    // 释放右子树
    FreeSpaceBinaryTree(root->rchild);
    // 释放当前节点
    free(root);
}

void CreateBinaryTree()
{
    // 建立节点
    BinaryNode node1 = {'A', NULL, NULL};
    BinaryNode node2 = {'B', NULL, NULL};
    BinaryNode node3 = {'C', NULL, NULL};
    BinaryNode node4 = {'D', NULL, NULL};
    BinaryNode node5 = {'E', NULL, NULL};
    BinaryNode node6 = {'F', NULL, NULL};
    BinaryNode node7 = {'G', NULL, NULL};
    BinaryNode node8 = {'H', NULL, NULL};

    // 建立节点关系
    node1.lchild = &node2;
    node1.rchild = &node6;
    node2.rchild = &node3;
    node3.lchild = &node4;
    node3.rchild = &node5;
    node6.rchild = &node7;
    node7.lchild = &node8;

    // 先序遍历
    FirstRecursion(&node1);
    printf("\n");

    SeqTraverseBinaryTree(&node1);

    printf("%c\n", node1.ch);
    printf("%c\n", node2.ch);
    printf("%c\n", node3.ch);
    printf("%c\n", node4.ch);
    printf("%c\n", node5.ch);
    printf("%c\n", node6.ch);
    printf("%c\n", node7.ch);
    printf("%c\n", node8.ch);

    // free(&node1);  // attempt to free a non-heap object ‘node1’

    // // 释放二叉树，非堆上数据才能释放
    // FreeSpaceBinaryTree(&node1);
}

int main()
{
    CreateBinaryTree();

    return 0;
}