#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// 中（根）序递归遍历
void MiddleRecursion(BinaryNode *root)
{
    if (NULL == root)
    {
        return;
    }

    // 先遍历左子树
    MiddleRecursion(root->lchild);
    // 再访问根节点
    printf("%c", root->ch);
    // 再遍历右子树
    MiddleRecursion(root->rchild);
}

// 后（根）序递归遍历
void LastRecursion(BinaryNode *root)
{
    if (NULL == root)
    {
        return;
    }

    // 先遍历左子树
    LastRecursion(root->lchild);
    // 再遍历右子树
    LastRecursion(root->rchild);
    // 再访问根节点
    printf("%c", root->ch);
}


// 求叶子数目
void CaculateLeafNum(BinaryNode *root, int *leafNum)
{
    if (NULL == root)
    {
        return;
    }

    if (NULL == root->lchild && NULL == root->rchild)
    {
        (*leafNum)++;
    }

    // 左子树叶子数量
    CaculateLeafNum(root->lchild, leafNum);
    // 右子树叶子数量
    CaculateLeafNum(root->rchild, leafNum);
}

// 求二叉树的深度
int CaculateDepth(BinaryNode *root)
{
    if (NULL == root)
    {
        return 0;  // 这里一定是0，这里如果是-1，结果会比正确结果小1
    }

    // 左子树叶子数量
    int nLeft = CaculateDepth(root->lchild);
    // 右子树叶子数量
    int nRight = CaculateDepth(root->rchild);

    return nLeft > nRight ? nLeft + 1 : nRight + 1;
}

// 拷贝二叉树
BinaryNode *CopyBinaryTree(BinaryNode *root)
{
    if (NULL == root)
    {
        return NULL;
    }

    // 拷贝左子树
    BinaryNode *lchild = CopyBinaryTree(root->lchild);
    // 拷贝右子树
    BinaryNode *rchild = CopyBinaryTree(root->rchild);

    // 创建节点
    BinaryNode *newnode = (BinaryNode *)malloc(sizeof(BinaryNode));
    newnode->ch = root->ch;
    newnode->lchild = lchild;
    newnode->rchild = rchild;

    return newnode;
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
    // 中序遍历
    MiddleRecursion(&node1);
    printf("\n");
    // 后序遍历
    LastRecursion(&node1);
    printf("\n");
    // 叶子数量
    int num = 0;
    CaculateLeafNum(&node1, &num);
    printf("叶子数量：%d\n", num);

    // 有点问题
    int depth = CaculateDepth(&node1);
    printf("树的深度：%d\n", depth);

    // 拷贝二叉树
    BinaryNode *root = CopyBinaryTree(&node1);
    FirstRecursion(root);
    printf("\n");
    // 释放二叉树
    FreeSpaceBinaryTree(root);
}

int main()
{
    CreateBinaryTree();

    return 0;
}