#include "LinkStack.h"

#define MyFalse 0
#define MyTrue 1

// 二叉树节点
typedef struct BINARYNODE
{
    char ch;
    struct BINARYNODE *lchild;
    struct BINARYNODE *rchild;
} BinaryNode;

// 二叉树LinkStack节点
typedef struct BITREESTACKNODE
{
    LinkNode node;
    BinaryNode *root;
    int flag;
} BiTreeStackNode;

// 创建栈中的节点
BiTreeStackNode *CreateBiTreeStackNode(BinaryNode *node, int flag)
{
    BiTreeStackNode *newnode = (BiTreeStackNode *)malloc(sizeof(BiTreeStackNode));
    newnode->root = node;
    newnode->flag = flag;
    return newnode;
}

// 非递归遍历
void NonRecursion(BinaryNode *root)
{
    // 创建栈
    LinkStack *stack = Init_LinkStack();
    // 把根节点入栈
    Push_LinkStack(stack, (LinkNode *)CreateBiTreeStackNode(root, MyFalse));

    while (Size_LinkStack(stack) > 0)
    {
        // 先弹出栈顶元素
        BiTreeStackNode *node = (BiTreeStackNode *)Top_LinkStack(stack);
        Pop_LinkStack(stack);

        // 判断弹出的节点是否为空
        if (NULL == node->root)
        {
            free(node);
            continue;
        }

        if (node->flag == MyTrue)
        {
            printf("%c", node->root->ch);
            free(node);
        }
        else
        {
            // 当前节点右子节点入栈
            Push_LinkStack(stack, (LinkNode *)CreateBiTreeStackNode(node->root->rchild, MyFalse));
            // 当前节点左子节点入栈
            Push_LinkStack(stack, (LinkNode *)CreateBiTreeStackNode(node->root->lchild, MyFalse));
            // 当前节点入栈
            node->flag = MyTrue;
            Push_LinkStack(stack, (LinkNode *)node);
        }
    }
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

    // 非递归遍历的先（根）序遍历
    NonRecursion(&node1);
    printf("\n");
}

BinaryNode *CreateBinaryTree2()
{

    fflush(stdin);
    char ch;
    scanf("%c", &ch);

    BinaryNode *node;
    if (ch == '#')
    {
        node = NULL;
    }
    else
    {
        node = (BinaryNode *)malloc(sizeof(BinaryNode));
        node->ch = ch;
        node->lchild = CreateBinaryTree2();
        node->rchild = CreateBinaryTree2();
    }
    return node;
}

int main()
{
    BinaryNode *root = CreateBinaryTree2();
    NonRecursion(root);

    return 0;
}