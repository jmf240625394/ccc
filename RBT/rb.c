#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义元素类型
typedef int ElementType;

#define RED 1
#define BLACK 0
#define TRUE 1
#define FALSE 0

// 定义红黑树节点
typedef struct RBTNode
{
    ElementType value;
    int color;
    struct RBTNode *parent;
    struct RBTNode *lchild;
    struct RBTNode *rchild;
} RBTNode;

// 定义红黑树
typedef struct RBTREE
{
    RBTNode *root;
    int size;
} RbTree;

// 默认的比较函数
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

// 返回红黑树的大小
int RBT_Size(RbTree *rbtree)
{
    if (NULL == rbtree->root)
    {
        return 0;
    }
    return rbtree->size;
}

// 是否为空
int RBT_IsEmpty(RbTree *rbtree)
{
    return rbtree->root == NULL ? 1 : 0;
}

// 清空所有元素

// 打印二叉树，先序遍历打印
void RBT_PrinterInnerFirst(RBTNode *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%d(%d) ", root->value, root->color);

    // 打印左子树
    RBT_PrinterInnerFirst(root->lchild);

    // 打印右子树
    RBT_PrinterInnerFirst(root->rchild);
}

// 打印二叉树，中序遍历打印
void RBT_PrinterInnerMiddle(RBTNode *root)
{
    if (root == NULL)
    {
        return;
    }

    // 打印左子树
    RBT_PrinterInnerMiddle(root->lchild);

    printf("%d(%d) ", root->value, root->color);

    // 打印右子树
    RBT_PrinterInnerMiddle(root->rchild);
}

// 对外提供接口，统一接收二叉树结构体指针作为参数
void RBT_PrinterOuterMiddle(RbTree *rbtree)
{
    if (rbtree->root == NULL || rbtree->size == 0)
    {
        printf("红黑树长度为0");
    }

    RBT_PrinterInnerMiddle(rbtree->root);
}

// 对外提供接口，统一接收二叉树结构体指针作为参数
void RBT_PrinterOuterFirst(RbTree *rbtree)
{
    if (rbtree->root == NULL || rbtree->size == 0)
    {
        printf("红黑树长度为0");
    }

    RBT_PrinterInnerFirst(rbtree->root);
}

// 判断节点是否是黑色的
int isBlack(RBTNode *node)
{
    // 红黑树比较特殊，如果node是NULL，也是黑色
    if (node == NULL)
    {
        return TRUE;
    }
    return node->color == BLACK ? TRUE : FALSE;
}

// 判断节点颜色是否是红色
int isRed(RBTNode *node)
{
    if (node == NULL)
    {
        return FALSE;
    }
    return node->color == RED ? TRUE : FALSE;
}

// 查找节点颜色
int colorOf(RBTNode *node)
{
    if (node == NULL)
    {
        return -1;
    }
    return node->color;
}

// 给指定节点染色
int color(RBTNode *node, int color)
{
    if (node == NULL)
    {
        return -1;
    }
    node->color = color;
    return TRUE;
}

// 判断给定节点是否是叶子节点
int isLeaf(RBTNode *node)
{
    return node->lchild != NULL && node->rchild == NULL;
}

// 判断给定节点是否是左子节点
int isLeftChild(RBTNode *node)
{
    return node->parent != NULL && node == node->parent->lchild;
}

// 判断给定节点是否是右子节点
int isRightChild(RBTNode *node)
{
    return node->parent != NULL && node == node->parent->rchild;
}

// 获取指定节点的兄弟节点
RBTNode *sibling(RBTNode *node)
{
    if (isLeftChild(node))
    {
        return node->parent->rchild;
    }

    if (isRightChild(node))
    {
        return node->parent->lchild;
    }

    return NULL;
}

// 左旋转
// 和之前的AVL树一样
static int rotateLeft(RbTree *rbtree, RBTNode *grand)
{
    RBTNode *parent = grand->rchild;
    RBTNode *child = parent->lchild;
    grand->rchild = parent->lchild;
    parent->lchild = grand;

    // 让parent成为子树的根节点
    parent->parent = grand->parent;
    int ret1 = isLeftChild(grand);
    int ret2 = isRightChild(grand);
    if (ret1)
    {
        grand->parent->lchild = parent;
    }
    else if (ret2)
    {
        grand->parent->rchild = parent;
    }
    else // grand是rbt的root节点
    {
        rbtree->root = parent;
    }

    // 更新child的parent
    if (child != NULL)
    {
        child->parent = grand;
    }

    // 更新grand的parent
    grand->parent = parent;

    // // 更新高度
    // AVL_UpdateHeight(grand);
    // AVL_UpdateHeight(parent);

    return 1;
}

// 右旋转
static int rotateRight(RbTree *rbtree, RBTNode *grand)
{
    RBTNode *parent = grand->lchild;
    RBTNode *child = parent->rchild;
    grand->lchild = child;
    parent->rchild = grand;

    // 让parent成为子树的根节点
    parent->parent = grand->parent;
    int ret1 = isLeftChild(grand);
    int ret2 = isRightChild(grand);
    if (ret1)
    {
        grand->parent->lchild = parent;
    }
    else if (ret2)
    {
        grand->parent->rchild = parent;
    }
    else // grand是rbt的root节点
    {
        rbtree->root = parent;
    }

    // 更新child的parent
    if (child != NULL)
    {
        child->parent = grand;
    }

    // 更新grand的parent
    grand->parent = parent;

    // // 更新高度
    // AVL_UpdateHeight(grand);
    // AVL_UpdateHeight(parent);

    return 1;
}

// 增加节点之后的处理步骤
int afterAdd(RbTree *rbtree, RBTNode *newnode)
{
    RBTNode *parent = newnode->parent;
    // 添加的是根节点或者上溢到达了根节点
    if (parent == NULL)
    {
        color(newnode, BLACK);
        return TRUE;
    }

    // 如果父节点是黑色，直接返回
    if (isBlack(parent))
    {
        return TRUE;
    }

    // 叔父节点
    RBTNode *uncle = sibling(parent);
    // 祖父节点
    RBTNode *grand = parent->parent;
    if (isRed(uncle)) // 叔父节点是红色
    {
        color(parent, BLACK);
        color(uncle, BLACK);
        // 把祖父节点当做是新添加的节点
        color(grand, RED);
        afterAdd(rbtree, grand);
        return TRUE;
    }

    // 叔父节点不是红色，还是这里，非常容易出错
    int ret1 = isLeftChild(parent);
    int ret2 = isLeftChild(newnode);
    if (ret1) // L
    {
        if (ret2) // LL
        {
            color(parent, BLACK);
            color(grand, RED);
            rotateRight(rbtree, grand);
        }
        else // LR
        {
            color(newnode, BLACK);
            color(grand, RED);
            rotateLeft(rbtree, parent);
            rotateRight(rbtree, grand);
        }
    }
    else // R
    {
        if (ret2) // RL
        {
            color(newnode, BLACK);
            color(grand, RED);
            rotateRight(rbtree, parent);
            rotateLeft(rbtree, grand);
        }
        else // RR
        {
            color(parent, BLACK);
            color(grand, RED);
            rotateLeft(rbtree, grand);
        }
    }
}

int RBT_AddNode(RbTree *rbtree, ElementType value, int (*Compare)(ElementType v1, ElementType v2))
{
    // 注意新加节点颜色默认是red，如果添加的是根节点颜色染黑即可
    if (NULL == Compare)
    {
        Compare = Compare_default;
    }

    // 添加第一个节点
    if (rbtree->root == NULL)
    {
        RBTNode *newnode;
        newnode = (RBTNode *)malloc(sizeof(RBTNode));
        memset(newnode, 0, sizeof(RBTNode));
        if (NULL == newnode)
        {
            return -1;
        }
        rbtree->root = newnode;
        rbtree->root->value = value;
        rbtree->root->parent = NULL;
        rbtree->root->lchild = NULL;
        rbtree->root->rchild = NULL;
        rbtree->size++;
        afterAdd(rbtree, newnode);
        return 1;
    }

    // 添加的不是第一个节点
    // 找到父节点
    RBTNode *node_temp = rbtree->root;
    RBTNode *parent = NULL;
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
    RBTNode *newnode;
    newnode = (RBTNode *)malloc(sizeof(RBTNode));
    memset(newnode, 0, sizeof(RBTNode));
    newnode->value = value;
    newnode->color = RED;
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

    rbtree->size++;
    afterAdd(rbtree, newnode);
    return 1;
}

// 是否包含某元素，如果包含返回节点
// 这种方式只适合二叉搜索树不能存储重复值的情况
RBTNode *RBT_ReturnNode(RbTree *rbtree, ElementType value, int (*Compare)(ElementType v1, ElementType v2))
{
    if (NULL == Compare)
    {
        Compare = Compare_default;
    }

    RBTNode *node = rbtree->root;
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
RBTNode *predecessor(RbTree *rbtree, RBTNode *node)
{
    if (NULL == node || NULL == rbtree->root)
    {
        return NULL;
    }

    // 前驱节点在左子树中left->rchild->rchild->rchild->......
    RBTNode *p = node->lchild;
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
RBTNode *successor(RbTree *rbtree, RBTNode *node)
{
    if (NULL == node || NULL == rbtree->root)
    {
        return NULL;
    }

    // 前驱节点在左子树中left->lchild->lchild->lchild->......
    RBTNode *p = node->rchild;
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
int childrenNum(RBTNode *node)
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

// 红黑树删除节点之后的处理
int afterRemove(RbTree *rbtree, RBTNode *node, RBTNode *replacenode)
{
    int node_ret = isRed(node);
    int replace_ret = isRed(replacenode);
    // 如果删除的节点是红色的
    // 判断是否是红、黑节点要非常小心，因为当对象是NULL时，返回-1
    // 如果用真假直接判断，-1也是真，会有问题；当然这里情况特殊是可以的
    if (node_ret == 1)
    {
        return TRUE;
    }

    // 用以取代node的子节点是红色
    if (replace_ret == 1)
    {
        color(replacenode, BLACK);
        return TRUE;
    }

    RBTNode *parent = node->parent;
    // 删除的是根节点
    if (parent == NULL)
    {
        return TRUE;
    }
    // 删除的是黑色叶子节点——下溢
    // 判断被删除的node是左子节点还是右子节点
    int left = parent->lchild == NULL || isLeftChild(node);
    RBTNode *sibling = left ? parent->rchild : parent->lchild;
    if (left) // 被删除的节点在左边，兄弟节点在右边
    {
        // 兄弟节点是红色
        int ret_sibling = isRed(sibling);
        if (ret_sibling)
        {
            color(sibling, BLACK);
            color(parent, RED);
            rotateLeft(rbtree, parent);
            // 更换兄弟
            sibling = parent->rchild;
        }

        // 兄弟节点必然是黑色
        int ret_sibling_lchild = isBlack(sibling->lchild);
        int ret_sibling_rchild = isBlack(sibling->rchild);
        if (ret_sibling_lchild && ret_sibling_rchild)
        {
            // 兄弟节点没有1个红色子节点，父节点要向下跟兄弟节点合并
            int ret_parent = isBlack(parent);
            color(parent, BLACK);
            color(sibling, RED);
            if (ret_parent)
            {
                afterRemove(rbtree, parent, NULL);
            }
        }
        else // 兄弟节点至少有1个红色子节点，向兄弟节点借元素
        {
            // 兄弟节点的右边是黑色，兄弟要先旋转
            int ret_sibling_right = isBlack(sibling->rchild);
            if (ret_sibling_right)
            {
                rotateRight(rbtree, sibling);
                sibling = parent->rchild;
            }

            int color_parent = colorOf(parent);
            color(sibling, color_parent);
            color(sibling->rchild, BLACK);
            color(parent, BLACK);
            rotateLeft(rbtree, parent);
        }
    }
    else // 被删除的节点在右边，兄弟节点在左边
    {
        // 兄弟节点是红色
        int ret_sibling = isRed(sibling);
        if (ret_sibling)
        {
            color(sibling, BLACK);
            color(parent, RED);
            rotateRight(rbtree, parent);
            // 更换兄弟
            sibling = parent->lchild;
        }

        // 兄弟节点必然是黑色
        int ret_sibling_lchild = isBlack(sibling->lchild);
        int ret_sibling_rchild = isBlack(sibling->rchild);
        if (ret_sibling_lchild && ret_sibling_rchild)
        {
            // 兄弟节点没有1个红色子节点，父节点要向下跟兄弟节点合并
            int ret_parent = isBlack(parent);
            color(parent, BLACK);
            color(sibling, RED);
            if (ret_parent)
            {
                afterRemove(rbtree, parent, NULL);
            }
        }
        else // 兄弟节点至少有1个红色子节点，向兄弟节点借元素
        {
            // 兄弟节点的左边是黑色，兄弟要先旋转
            int ret_sibling_left = isBlack(sibling->lchild);
            if (ret_sibling_left)
            {
                rotateLeft(rbtree, sibling);
                // 重置sibling
                sibling = parent->lchild;
            }

            int color_parent = colorOf(parent);
            color(sibling, color_parent);
            color(sibling->lchild, BLACK);
            color(parent, BLACK);
            rotateRight(rbtree, parent);
        }
    }
}

// 根据元素删除节点
int RBT_RemoveNode(RbTree *rbtree, ElementType value, int (*Compare)(ElementType v1, ElementType v2))
{
    if (NULL == Compare)
    {
        Compare = Compare_default;
    }

    if (NULL == rbtree->root)
    {
        return -1;
    }

    // 获得待删除节点，这里决定了这个函数不能递归调用
    RBTNode *node = RBT_ReturnNode(rbtree, value, Compare);
    if (NULL == node)
    {
        return 0;
    }

    // 待删除节点度为2，需要使用后继节点的值替换待删除节点的值，并删除后继节点
    int cn = childrenNum(node);
    if (cn == 2)
    {
        // 找到后继节点，这里不用判断succ是否为空，node的度为2，succ肯定不为空
        RBTNode *succ = successor(rbtree, node);
        // 用后继节点的值覆盖度为2的节点的值
        node->value = succ->value;
        // 删除后继节点
        // ?后继节点度数要么是1要么是0，再次执行当前函数，后走到下面的删除度为0或者1的逻辑里面
        // 这里只会执行一次，不会无限的递归下去
        // BST_RemoveNode(rbtree, succ->value, Compare);  // 这里不能直接这么用，这时node和succ的值都是succ的值
        node = succ; // 这样可以走下面的逻辑删除度为1或者0的后继节点
    }

    // 最多只有一个孩子节点
    RBTNode *child = node->lchild == NULL ? node->rchild : node->lchild;
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
            rbtree->root = child;
            child->parent = NULL;
        }
        afterRemove(rbtree, node, child);
        free(node);
    }
    else if (node->parent == NULL) // 待删除节点度为0[叶子节点]，且为根节点
    {
        rbtree->root = NULL;
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
        afterRemove(rbtree, node, NULL);
        free(node);
    }

    rbtree->size--;
}

int main()
{
    int arr[] = {55, 87, 56, 74, 96, 22, 62, 20, 70, 68, 90, 50};

    RbTree rbtree = {NULL, 0};
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        RBT_AddNode(&rbtree, arr[i], NULL);
    }

    RBT_PrinterOuterMiddle(&rbtree);
    printf("\n");
    RBT_PrinterOuterFirst(&rbtree);
    printf("\n");

    RBT_RemoveNode(&rbtree, 74, NULL);
    RBT_PrinterOuterMiddle(&rbtree);
    printf("\n");
    RBT_PrinterOuterFirst(&rbtree);
    printf("\n");
}