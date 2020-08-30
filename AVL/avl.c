#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义元素类型
typedef int ElementType;

// 定义二叉搜索树节点
typedef struct AVLNODE
{
    ElementType value;
    int height;
    struct AVLNODE *parent;
    struct AVLNODE *lchild;
    struct AVLNODE *rchild;
} AVLNode;

// 定义二叉搜索树
typedef struct AVLTree
{
    AVLNode *root;
    int size;
} AVLTree;

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
int AVL_Size(AVLTree *avltree)
{
    if (NULL == avltree->root)
    {
        return 0;
    }
    return avltree->size;
}

// 是否为空
int AVL_IsEmpty(AVLTree *avltree)
{
    return avltree->root == NULL ? 1 : 0;
}

// 清空所有元素，这里用递归的方法
// 调用方得手动将bstree的size置为0，因此这个函数不对外开放
static void AVL_ClearNode(AVLNode *root)
{
    if (NULL == root)
    {
        return;
    }

    // 左子树
    AVL_ClearNode(root->lchild);

    // 右子树
    AVL_ClearNode(root->rchild);

    free(root);
    root = NULL;
}

// 对上面的BST_ClearNode包装一层
int AVL_FreeSpace(AVLTree *avltree)
{
    if (avltree->root == NULL && avltree->size == 0)
    {
        return 1;
    }

    if (avltree->root == NULL && avltree->size != 0)
    {
        avltree->size = 0;
        return 1;
    }

    if (avltree->root != NULL)
    {
        AVL_ClearNode(avltree->root);
        avltree->size = 0;
        return 1;
    }
    return 0;
}

// 打印二叉树，中序遍历打印
static void AVL_PrinterMiddle(AVLNode *root)
{
    if (root == NULL)
    {
        return;
    }

    // 打印左子树
    AVL_PrinterMiddle(root->lchild);

    printf("%d ", root->value);

    // 打印右子树
    AVL_PrinterMiddle(root->rchild);
}

// 打印二叉树，先序遍历打印
static void AVL_PrinterFirst(AVLNode *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%d ", root->value);

    // 打印左子树
    AVL_PrinterFirst(root->lchild);

    // 打印右子树
    AVL_PrinterFirst(root->rchild);
}

// 对外提供接口，统一接收二叉树结构体指针作为参数
void AVL_PrinterOuterMiddle(AVLTree *avltree)
{
    if (avltree->root == NULL || avltree->size == 0)
    {
        printf("二叉搜索书长度为0");
    }

    AVL_PrinterMiddle(avltree->root);
}

// 对外提供接口，统一接收二叉树结构体指针作为参数
void AVL_PrinterOuterFirst(AVLTree *avltree)
{
    if (avltree->root == NULL || avltree->size == 0)
    {
        printf("二叉搜索书长度为0");
    }

    AVL_PrinterFirst(avltree->root);
}

// 计算给点节点的平衡因子
static int AVL_BalanceFactor(AVLNode *node)
{
    int leftHeight, rightHeight;
    leftHeight = (node->lchild == NULL ? 0 : node->lchild->height);
    rightHeight = (node->rchild == NULL ? 0 : node->rchild->height);
    return leftHeight - rightHeight;
}

// 判断某个节点是否平衡
static int AVL_IsBalanced(AVLNode *node)
{
    // ★注意：这里如果将条件判断中的ret换成abs(AVL_BalanceFactor(node))
    // 会出问题，千万要注意
    int ret = abs(AVL_BalanceFactor(node));
    if (ret <= 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static int AVL_Max(int n1, int n2)
{
    return n1 > n2 ? n1 : n2;
}

// 更新节点的高度
static int AVL_UpdateHeight(AVLNode *node)
{
    if (NULL == node)
    {
        return -1;
    }
    int leftHeight, rightHeight;
    leftHeight = (node->lchild == NULL ? 0 : node->lchild->height);
    rightHeight = (node->rchild == NULL ? 0 : node->rchild->height);
    node->height = 1 + AVL_Max(leftHeight, rightHeight);
    return 1;
}

// 判断节点是否为叶子节点
static int AVL_IsLeaf(AVLNode *node)
{
    return node->lchild == NULL && node->rchild == NULL;
}

// 判断节点是否是其父节点的左孩子
static int AVL_IsLeftChild(AVLNode *node)
{
    return node->parent != NULL && node == node->parent->lchild;
}

// 判断节点是否是其父节点的右孩子
static int AVL_IsRightChild(AVLNode *node)
{
    return node->parent != NULL && node == node->parent->rchild;
}

// 判断节点是否有两个孩子
static int AVL_HasTwoChild(AVLNode *node)
{
    return node->lchild != NULL && node->rchild != NULL;
}

// 找到节点的左右子树中树高比较高的子树
static AVLNode *AVL_TallHigherChild(AVLNode *node)
{
    if (NULL == node)
    {
        return NULL;
    }
    int leftHeight, rightHeight;
    leftHeight = (node->lchild == NULL ? 0 : node->lchild->height);
    rightHeight = (node->rchild == NULL ? 0 : node->rchild->height);
    if (leftHeight < rightHeight)
    {
        return node->rchild;
    }
    else if (leftHeight > rightHeight)
    {
        return node->lchild;
    }
    return AVL_IsLeftChild(node) ? node->lchild : node->rchild;
}

// 左旋转
static int AVL_RotateLeft(AVLTree *avltree, AVLNode *grand)
{
    AVLNode *parent = grand->rchild;
    AVLNode *child = parent->lchild;
    grand->rchild = parent->lchild;
    parent->lchild = grand;

    // 让parent成为子树的根节点
    parent->parent = grand->parent;
    int ret1 = AVL_IsLeftChild(grand);
    int ret2 = AVL_IsRightChild(grand);
    if (ret1)
    {
        grand->parent->lchild = parent;
    }
    else if (ret2)
    {
        grand->parent->rchild = parent;
    }
    else // grand是avl的root节点
    {
        avltree->root = parent;
    }

    // 更新child的parent
    if (child != NULL)
    {
        child->parent = grand;
    }

    // 更新grand的parent
    grand->parent = parent;

    // 更新高度
    AVL_UpdateHeight(grand);
    AVL_UpdateHeight(parent);

    return 1;
}

// 右旋转
static int AVL_RotateRight(AVLTree *avltree, AVLNode *grand)
{
    AVLNode *parent = grand->lchild;
    AVLNode *child = parent->rchild;
    grand->lchild = child;
    parent->rchild = grand;

    // 让parent成为子树的根节点
    parent->parent = grand->parent;
    int ret1 = AVL_IsLeftChild(grand);
    int ret2 = AVL_IsRightChild(grand);
    if (ret1)
    {
        grand->parent->lchild = parent;
    }
    else if (ret2)
    {
        grand->parent->rchild = parent;
    }
    else // grand是avl的root节点
    {
        avltree->root = parent;
    }

    // 更新child的parent
    if (child != NULL)
    {
        child->parent = grand;
    }

    // 更新grand的parent
    grand->parent = parent;

    // 更新高度
    AVL_UpdateHeight(grand);
    AVL_UpdateHeight(parent);

    return 1;
}

// 统一的rotate函数
static int AVL_Rotate(
    AVLTree *avltree,
    AVLNode *r, // 需要恢复平衡的子树的根节点
    AVLNode *a, AVLNode *b, AVLNode *c,
    AVLNode *d,
    AVLNode *e, AVLNode *f, AVLNode *g)
{
    // 从图中可以看出4中旋转，最后都是以d为根
    // 同时a和g是没有动的

    // 让d成为这颗子树的根节点
    d->parent = r->parent;
    int ret1 = AVL_IsLeftChild(r);
    int ret2 = AVL_IsRightChild(r);
    if (ret1)
    {
        r->parent->lchild = d;
    }
    else if (ret2)
    {
        r->parent->rchild = d;
    }
    else
    {
        avltree->root = d;
    }

    // a-b-c
    // AVL树和红黑树不用考虑a的
    // b->lchild = a;
    // if (a != NULL)
    // {
    //     a->parent = b;
    // }
    b->rchild = c;
    if (c != NULL)
    {
        c->parent = b;
    }
    AVL_UpdateHeight(b);

    // e-f-g
    // AVL树和红黑树不用考虑g的
    f->lchild = e;
    if (e != NULL)
    {
        e->parent = f;
    }
    // f->rchild = g;
    // if (g != NULL)
    // {
    //     g->parent = f;
    // }
    AVL_UpdateHeight(f);

    // b-d-f
    d->lchild = b;
    d->rchild = f;
    b->parent = d;
    f->parent = d;
    AVL_UpdateHeight(d);
}

// 使用统一的旋转函数的rebalance函数
static int AVL_Rebalance2(AVLTree *avltree, AVLNode *grand)
{
    // 获得高度大的子节点（由于增加节点导致的不平衡，因此一般高的子节点就是增加节点的子树）
    AVLNode *parent = AVL_TallHigherChild(grand);
    AVLNode *node = AVL_TallHigherChild(parent);
    int ret1 = AVL_IsLeftChild(parent);
    if (ret1) // L
    {
        int ret2 = AVL_IsLeftChild(node);
        if (ret2) // LL
        {
            AVL_Rotate(avltree, grand, node->lchild, node, node->rchild, parent, parent->rchild, grand, grand->rchild);
            // AVL_RotateRight(avltree, grand);
        }
        else // LR
        {
            AVL_Rotate(avltree, grand, parent->lchild, parent, node->lchild, node, node->rchild, grand, grand->rchild);
            // AVL_RotateLeft(avltree, parent);
            // AVL_RotateRight(avltree, grand);
        }
    }
    else // R
    {
        int ret2 = AVL_IsLeftChild(node);
        if (ret2) // RL
        {
            AVL_Rotate(avltree, grand, grand->lchild, grand, node->lchild, node, node->rchild, parent, parent->rchild);
            // AVL_RotateRight(avltree, parent);
            // AVL_RotateLeft(avltree, grand);
        }
        else // RR
        {
            AVL_Rotate(avltree, grand, grand->lchild, grand, parent->lchild, parent, node->lchild, node, node->rchild);
            // AVL_RotateLeft(avltree, grand);
        }
    }
}

// 恢复平衡函数，grand高度最低的那个不平衡节点
static int AVL_Rebalance(AVLTree *avltree, AVLNode *grand)
{
    // 获得高度大的子节点（由于增加节点导致的不平衡，因此一般高的子节点就是增加节点的子树）
    AVLNode *parent = AVL_TallHigherChild(grand);
    AVLNode *node = AVL_TallHigherChild(parent);
    int ret1 = AVL_IsLeftChild(parent);
    if (ret1) // L
    {
        int ret2 = AVL_IsLeftChild(node);
        if (ret2) // LL
        {
            AVL_RotateRight(avltree, grand);
        }
        else // LR
        {
            AVL_RotateLeft(avltree, parent);
            AVL_RotateRight(avltree, grand);
        }
    }
    else // R
    {
        int ret2 = AVL_IsLeftChild(node);
        if (ret2) // RL
        {
            AVL_RotateRight(avltree, parent);
            AVL_RotateLeft(avltree, grand);
        }
        else // RR
        {
            AVL_RotateLeft(avltree, grand);
        }
    }
}

// 添加node之后的调整，node是新添加的节点
// 新加节点必定是叶子节点
int AVL_AfterAdd(AVLTree *avltree, AVLNode *node)
{
    while ((node = node->parent) != NULL)
    {
        // 平衡就更新高度？
        int ret = AVL_IsBalanced(node);
        if (ret)
        {
            // 更新高度，在这里就顺便把相关的父节点高度更新了
            AVL_UpdateHeight(node);
        }
        else
        {
            // 恢复平衡
            AVL_Rebalance2(avltree, node); // 使用统一的旋转函数
            // AVL_Rebalance(avltree, node); // 使用分类处理的旋转函数
            // 整棵树恢复平衡
            break;
        }
    }
}

// 根据element添加元素，简单数据类型可以直接比较
// 复杂的数据类型需要自己定义比较函数
int AVL_AddNode(AVLTree *avltree, ElementType value, int (*Compare)(ElementType v1, ElementType v2))
{
    if (NULL == Compare)
    {
        Compare = Compare_default;
    }

    // 添加第一个节点
    if (avltree->root == NULL)
    {
        AVLNode *newnode;
        newnode = (AVLNode *)malloc(sizeof(AVLNode));
        memset(newnode, 0, sizeof(AVLNode));
        newnode->height = 1; // 新增节点必定是叶子节点，叶子节点高度默认是1
        if (NULL == newnode)
        {
            return -1;
        }
        avltree->root = newnode;
        avltree->root->value = value;
        avltree->root->parent = NULL;
        avltree->root->lchild = NULL;
        avltree->root->rchild = NULL;
        avltree->size++;
        AVL_AfterAdd(avltree, newnode);
        return 1;
    }

    // 添加的不是第一个节点
    // 找到父节点
    AVLNode *node_temp = avltree->root;
    AVLNode *parent = NULL;
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
    AVLNode *newnode;
    newnode = (AVLNode *)malloc(sizeof(AVLNode));
    memset(newnode, 0, sizeof(AVLNode));
    newnode->height = 1;
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

    avltree->size++;
    AVL_AfterAdd(avltree, newnode);
    return 1;
}

// 是否包含某元素，如果包含返回节点
// 这种方式只适合二叉搜索树不能存储重复值的情况
AVLNode *AVL_ReturnNode(AVLTree *avltree, ElementType value, int (*Compare)(ElementType v1, ElementType v2))
{
    if (NULL == Compare)
    {
        Compare = Compare_default;
    }

    AVLNode *node = avltree->root;
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
AVLNode *AVL_Predecessor(AVLTree *avltree, AVLNode *node)
{
    if (NULL == node || NULL == avltree->root)
    {
        return NULL;
    }

    // 前驱节点在左子树中left->rchild->rchild->rchild->......
    AVLNode *p = node->lchild;
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
AVLNode *AVL_Successor(AVLTree *avltree, AVLNode *node)
{
    if (NULL == node || NULL == avltree->root)
    {
        return NULL;
    }

    // 前驱节点在左子树中left->lchild->lchild->lchild->......
    AVLNode *p = node->rchild;
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
int AVL_ChildrenNum(AVLNode *node)
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

// 删除node之后的调整，node是被删除的节点
int AVL_AfterRemove(AVLTree *avltree, AVLNode *node)
{
    while ((node = node->parent) != NULL)
    {
        // 平衡就更新高度？
        int isb = AVL_IsBalanced(node);
        if (isb)
        {
            // 更新高度，在这里就顺便把相关的父节点高度更新了
            AVL_UpdateHeight(node);
        }
        else
        {
            // 恢复平衡
            AVL_Rebalance2(avltree, node);
        }
    }
}

// 根据元素删除节点
int AVL_RemoveNode(AVLTree *avltree, ElementType value, int (*Compare)(ElementType v1, ElementType v2))
{
    if (NULL == Compare)
    {
        Compare = Compare_default;
    }

    if (NULL == avltree->root)
    {
        return -1;
    }

    // 获得待删除节点，这里决定了这个函数不能递归调用
    AVLNode *node = AVL_ReturnNode(avltree, value, Compare);
    if (NULL == node)
    {
        return 0;
    }

    // 待删除节点度为2，需要使用后继节点的值替换待删除节点的值，并删除后继节点
    int cn = AVL_ChildrenNum(node);
    if (cn == 2)
    {
        // 找到后继节点，这里不用判断succ是否为空，node的度为2，succ肯定不为空
        AVLNode *succ = AVL_Successor(avltree, node);
        // 用后继节点的值覆盖度为2的节点的值
        node->value = succ->value;
        // 删除后继节点
        // ?后继节点度数要么是1要么是0，再次执行当前函数，后走到下面的删除度为0或者1的逻辑里面
        // 这里只会执行一次，不会无限的递归下去
        // BST_RemoveNode(bstree, succ->value, Compare);  // 这里不能直接这么用，这时node和succ的值都是succ的值
        node = succ; // 这样可以走下面的逻辑删除度为1或者0的后继节点
    }

    // 最多只有一个孩子节点
    AVLNode *child = node->lchild == NULL ? node->rchild : node->lchild;
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
            avltree->root = child;
            child->parent = NULL;
        }
        // 删除节点之后的处理，这里真正要删除的是后继节点
        AVL_AfterRemove(avltree, node);
        free(node);
    }
    else if (node->parent == NULL) // 待删除节点度为0[叶子节点]，且为根节点
    {
        avltree->root = NULL;
        // 删除节点之后的处理，这里真正要删除的是后继节点
        AVL_AfterRemove(avltree, node);
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
        // 删除节点之后的处理，这里真正要删除的是后继节点
        AVL_AfterRemove(avltree, node);
        free(node);
    }

    avltree->size--;
}

int main()
{
    int arr[] = {11, 6, 8, 4, 16, 12, 14, 15};
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
    AVLTree avltree2 = {NULL, 0};

    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        AVL_AddNode(&avltree2, arr[i], NULL);
        printf("二叉搜索树长度：%d，本次增加节点%d\n", AVL_Size(&avltree2), arr[i]);
        AVL_PrinterOuterFirst(&avltree2);
        printf("\n");
        AVL_PrinterOuterMiddle(&avltree2);
        printf("\n");
        printf("根节点为：%d\n", avltree2.root->value);
        printf("-----------------\n");
    }

    AVL_RemoveNode(&avltree2, 16, NULL);
    printf("二叉搜索树长度：%d\n", AVL_Size(&avltree2));
    AVL_PrinterOuterFirst(&avltree2);
    printf("\n");
    AVL_PrinterOuterMiddle(&avltree2);
    printf("\n");
    printf("根节点为：%d\n", avltree2.root->value);

    AVL_RemoveNode(&avltree2, 11, NULL);
    printf("二叉搜索树长度：%d\n", AVL_Size(&avltree2));
    AVL_PrinterOuterFirst(&avltree2);
    printf("\n");
    AVL_PrinterOuterMiddle(&avltree2);
    printf("\n");
    printf("根节点为：%d\n", avltree2.root->value);

    AVL_FreeSpace(&avltree2);

    return 0;
}