#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义元素类型
typedef int ElementType;

// 定义二叉搜索树节点
typedef struct BSTNode
{
    ElementType value;
    struct BSTNode *parent;
    struct BSTNode *lchild;
    struct BSTNode *rchild;
} BSTNode;

// 定义二叉搜索树
typedef struct BSTREE
{
    BSTNode *root;
    int size;
} BsTree;

// 默认进行数值比较
// v1 > v2，返回1；v1 == v2，返回0；v1 < v2，返回-1
int Compare_default(ElementType v1, ElementType v2)
{
    if (v1 > v2)
    {
        return 1;
    }
    else if (v1 < v2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

// 元素的数量
int BST_Size(BsTree *bstree)
{
    if (NULL == bstree->root)
    {
        return 0;
    }
    return bstree->size;
}

// 是否为空
int BST_IsEmpty(BsTree *bstree)
{
    return bstree->root == NULL ? 1 : 0;
}

// 清空所有元素，这里用递归的方法
// 调用方得手动将bstree的size置为0，因此这个函数不对外开放
void BST_ClearNode(BSTNode *root)
{
    if (NULL == root)
    {
        return;
    }

    // 左子树
    BST_ClearNode(root->lchild);

    // 右子树
    BST_ClearNode(root->rchild);

    free(root);
    root = NULL;
}

// 对上面的BST_ClearNode包装一层
int BST_FreeSpace(BsTree *bstree)
{
    if (bstree->root == NULL && bstree->size == 0)
    {
        return 1;
    }

    if (bstree->root == NULL && bstree->size != 0)
    {
        bstree->size = 0;
        return 1;
    }

    if (bstree->root != NULL)
    {
        BST_ClearNode(bstree->root);
        bstree->size = 0;
        return 1;
    }
    return 0;
}

// 打印二叉树，中序遍历打印
void BST_PrinterInner(BSTNode *root)
{
    if (root == NULL)
    {
        return;
    }

    // 打印左子树
    BST_PrinterInner(root->lchild);

    printf("%d ", root->value);

    // 打印右子树
    BST_PrinterInner(root->rchild);
}

// 对外提供接口，统一接收二叉树结构体指针作为参数
void BST_PrinterOuter(BsTree *bstree)
{
    if (bstree->root == NULL || bstree->size == 0)
    {
        printf("二叉搜索书长度为0");
    }

    BST_PrinterInner(bstree->root);
}

// 根据element添加元素，简单数据类型可以直接比较
// 复杂的数据类型需要自己定义比较函数
int BST_AddNode(BsTree *bstree, ElementType value, int (*Compare)(ElementType v1, ElementType v2))
{
    if (NULL == Compare)
    {
        Compare = Compare_default;
    }

    // 添加第一个节点
    if (bstree->root == NULL)
    {
        BSTNode *newnode;
        newnode = (BSTNode *)malloc(sizeof(BSTNode));
        memset(newnode, 0, sizeof(BSTNode));
        if (NULL == newnode)
        {
            return -1;
        }
        bstree->root = newnode;
        bstree->root->value = value;
        bstree->root->parent = NULL;
        bstree->root->lchild = NULL;
        bstree->root->rchild = NULL;
        bstree->size++;
        return 1;
    }

    // 添加的不是第一个节点
    // 找到父节点
    BSTNode *node_temp = bstree->root;
    BSTNode *parent = NULL;
    int cmp = 0;

    // 循环到node_temp是空的时候，parent有值
    while (node_temp != NULL)
    {
        parent = node_temp;
        cmp = Compare(value, node_temp->value);
        if (cmp > 0)
        {
            node_temp = node_temp->rchild;
        }
        else if (cmp < 0)
        {
            node_temp = node_temp->lchild;
        }
        else
        {
            node_temp->value = value;
            return 1;
        }
    }

    // 看看插入到父节点的哪个位置
    BSTNode *newnode;
    newnode = (BSTNode *)malloc(sizeof(BSTNode));
    memset(newnode, 0, sizeof(BSTNode));
    newnode->value = value;
    newnode->lchild = NULL;
    newnode->rchild = NULL;
    if (cmp > 0)
    {
        parent->rchild = newnode;
        newnode->parent = parent;
    }
    else
    {
        parent->lchild = newnode;
        newnode->parent = parent;
    }

    bstree->size++;
    return 1;
}

// 是否包含某元素，乳沟包含返回节点
// 这种方式只适合二叉搜索树不能存储重复值的情况
BSTNode *BST_ReturnNode(BsTree *bstree, ElementType value, int (*Compare)(ElementType v1, ElementType v2))
{
    if (NULL == Compare)
    {
        Compare = Compare_default;
    }

    BSTNode *node = bstree->root;
    while (node != NULL)
    {
        int cmp = Compare(value, node->value);
        if (cmp == 0)
        {
            return node;
        }
        else if (cmp > 0)
        {
            node = node->rchild;
        }
        else
        {
            node = node->lchild;
        }
    }
    return NULL;
}

// 返回指定节点的前驱
BSTNode *BST_Predecessor(BsTree *bstree, BSTNode *node)
{
    if (NULL == node || NULL == bstree->root)
    {
        return NULL;
    }

    // 前驱节点在左子树中left->rchild->rchild->rchild->......
    BSTNode *p = node->lchild;
    if (NULL != p)
    {
        while (NULL != p->rchild)
        {
            p = p->rchild;
        }
        return p;
    }

    // 从父节点、祖父节点中寻找前驱节点
    while (node->parent != NULL && node == node->parent->lchild)
    {
        node = node->parent;
    }
    // node->parent == NULL
    // node == node->paraent->rchild
    return node->parent;
}

// 返回指定节点的后继
BSTNode *BST_Successor(BsTree *bstree, BSTNode *node)
{
    if (NULL == node || NULL == bstree->root)
    {
        return NULL;
    }

    // 前驱节点在左子树中left->lchild->lchild->lchild->......
    BSTNode *p = node->rchild;
    if (NULL != p)
    {
        while (NULL != p->lchild)
        {
            p = p->lchild;
        }
        return p;
    }

    // 从父节点、祖父节点中寻找前驱节点
    while (node->parent != NULL && node == node->parent->rchild)
    {
        node = node->parent;
    }
    // node->parent == NULL
    // node == node->paraent->lchild
    return node->parent;
}

// 返回指定节点孩子数量（度数）
int BST_ChildrenNum(BSTNode *node)
{
    if (NULL == node)
    {
        return -1;
    }
    if (NULL == node->rchild && NULL == node->lchild)
    {
        return 0;
    }
    else if (NULL == node->lchild || NULL == node->rchild)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

// 根据元素删除节点
int BST_RemoveNode(BsTree *bstree, ElementType value, int (*Compare)(ElementType v1, ElementType v2))
{
    if (NULL == Compare)
    {
        Compare = Compare_default;
    }

    if (NULL == bstree->root)
    {
        return -1;
    }

    // 获得待删除节点，这里决定了这个函数不能递归调用
    BSTNode *node = BST_ReturnNode(bstree, value, Compare);
    if (NULL == node)
    {
        return 0;
    }

    // 待删除节点度为2，需要使用后继节点的值替换待删除节点的值，并删除后继节点
    int cn = BST_ChildrenNum(node);
    if (cn == 2)
    {
        // 找到后继节点，这里不用判断succ是否为空，node的度为2，succ肯定不为空
        BSTNode *succ = BST_Successor(bstree, node);
        // 用后继节点的值覆盖度为2的节点的值
        node->value = succ->value;
        // 删除后继节点
        // ?后继节点度数要么是1要么是0，再次执行当前函数，后走到下面的删除度为0或者1的逻辑里面
        // 这里只会执行一次，不会无限的递归下去
        // BST_RemoveNode(bstree, succ->value, Compare);  // 这里不能直接这么用，这时node和succ的值都是succ的值
        node = succ; // 这样可以走下面的逻辑删除度为1或者0的后继节点
    }

    // 最多只有一个孩子节点
    BSTNode *child = node->lchild == NULL ? node->rchild : node->lchild;
    if (child != NULL) // node度为1
    {
        child->parent = node->parent;
        if (node == node->parent->lchild)
        {
            node->parent->lchild = child;
        }
        else if (node == node->parent->rchild)
        {
            node->parent->rchild = child;
        }
        else if (node->parent == NULL)
        {
            bstree->root = child;
            child->parent = NULL;
        }
        free(node);
    }
    else if (node->parent == NULL) // 待删除节点度为0[叶子节点]，且为根节点
    {
        bstree->root = NULL;
        free(node);
    }
    else // 待删除节点度为0[叶子节点]，但不为根节点
    {
        if (node == node->parent->lchild)
        {
            node->parent->lchild = NULL;
        }
        else if (node == node->parent->rchild)
        {
            node->parent->rchild = NULL;
        }
        free(node);
    }

    bstree->size--;
}

int main()
{
    int arr[] = {7, 4, 2, 1, 3, 5, 6, 9, 8, 11, 10, 12};
    // BsTree bstree1; // 这里默认初始化，里面会有数据，如果下面不初始化，第一个元素就插入不进去
    // // 一定要初始化，即使malloc分配内存之后，添加了memset清空指令
    // if (bstree1.root != NULL)
    // {
    //     printf("hehe\n"); // 会打印出hehe
    // }
    // printf("%d\n", bstree1.size); // 15775231
    // bstree1.root = NULL;
    // bstree1.size = 0;

    // 建议的初始化格式
    BsTree bstree2 = {NULL, 0};

    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        BST_AddNode(&bstree2, arr[i], NULL);
    }

    printf("二叉搜索树长度：%d\n", BST_Size(&bstree2));
    BST_PrinterOuter(&bstree2);
    printf("\n");

    BST_RemoveNode(&bstree2, 6, NULL);

    // printf("根：%d\n", bstree1.root->value);
    // printf("根左节点：%d\n", bstree1.root->lchild->value);
    // printf("根右节点：%d\n", bstree1.root->rchild->value);
    BST_PrinterOuter(&bstree2);
    printf("\n");

    BST_FreeSpace(&bstree2);

    printf("二叉树长度：%d\n", BST_Size(&bstree2));
    return 0;
}
