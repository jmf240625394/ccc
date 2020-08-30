#include <stdlib.h>
#include <stdio.h>

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

BinaryNode *CreateBinaryTree()
{
    fflush(stdin);
    char ch;
    ch = getchar();

    BinaryNode *node;
    if (ch == '#')
    {
        node = NULL;
    }
    else
    {
        node = (BinaryNode *)malloc(sizeof(BinaryNode));
        node->ch = ch;
        node->lchild = CreateBinaryTree();
        node->rchild = CreateBinaryTree();
    }

    return node;
}

int main()
{
    BinaryNode *root = CreateBinaryTree();
    FirstRecursion(root);

    return 0;
}