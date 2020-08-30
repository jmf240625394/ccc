#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1
#define FALSE 0
#define TRUE 1

// 定义元素类型
typedef int ElementType;

// 如果ElementType是c语言的基础类型：比如字符串、整数、浮点数等
// 不能与NULL进行比较时，添加如下宏，否则编译会发出warning
#define c_type 1

#define default_capacity 6

// 类似动态数组定义
typedef struct BINARYHEAP
{
    ElementType *pAddr; // 存放数据的地址
    int size;           // 当前有多少个元素
    int capacity;       // 容量，容器当前最大能容纳多少元素
} binaryHeap;

// 默认比较函数
int comparator_default(ElementType e1, ElementType e2)
{
    return e1 >= e2 ? TRUE : FALSE;
}

// 初始化二叉堆
binaryHeap *init_binaryHeap()
{
    // 初始默认容量是6
    int temp_capacity = 6;

    ElementType *pAddr_new = (ElementType *)malloc(sizeof(ElementType) * temp_capacity);
    if (pAddr_new == NULL)
    {
        exit(1);
    }

    // 分配动态数组的空间
    binaryHeap *h = (binaryHeap *)malloc(sizeof(binaryHeap));
    if (h == NULL)
    {
        exit(1);
    }

    h->size = 0;
    h->capacity = temp_capacity;
    h->pAddr = pAddr_new;

    return h;
}

// 返回二叉堆大小
int size_binaryHeap(binaryHeap *h)
{
    if (h == NULL)
    {
        return ERROR;
    }
    return h->size;
}

// 判断二叉堆是否为空
int isEmpty_binaryHeap(binaryHeap *h)
{
    if (h == NULL)
    {
        return ERROR;
    }
    return h->size == 0 ? TRUE : FALSE;
}

// 清空二叉堆，会释放pAddr
int clear_binaryHeap(binaryHeap *h)
{
    if (h == NULL)
    {
        return TRUE;
    }

#ifndef c_type
    // 如果ElementType是自定义的复杂类型，需要置NULL
    for (int i = 0; i < h->size; i++)
    {
        h->pAddr[i] = NULL;
    }
#endif

    h->size = 0;
    h->capacity = 6; // 默认是6
    free(h->pAddr);
    h->pAddr = NULL;
    return TRUE;
}

// 释放二叉堆
int free_binaryHeap(binaryHeap *h)
{
    if (h == NULL)
    {
        return TRUE;
    }
    free(h);
    h = NULL;
    return TRUE;
}

// 确保有足够空间，这里是否需要使用二级指针？？？
int ensureCapacity(binaryHeap *h)
{
    if (h == NULL)
    {
        return ERROR;
    }

    if (h->size < h->capacity)
    {
        return TRUE;
    }

    if (h->size == h->capacity)
    {
        ElementType *temp = (ElementType *)malloc(sizeof(ElementType) * h->capacity * 2);
        if (temp == NULL)
        {
            exit(1);
        }
        for (int i = 0; i < h->capacity; i++)
        {
            temp[i] = h->pAddr[i];
        }
        h->pAddr = temp;
        h->capacity = h->capacity * 2;
    }

    return TRUE;
}

// 让index位置的元素上滤
int siftUp(binaryHeap *h, int index, int (*compare)(ElementType, ElementType))
{
    ElementType e = h->pAddr[index];
    while (index > 0)
    {
        int parentIndex = (index - 1) >> 1;
        ElementType parent = h->pAddr[parentIndex];
        // 父节点大于上滤节点，退出循环
        if (compare(parent, e))
            break;
        // 将父元素安排到index的位置
        h->pAddr[index] = parent;
        // 重新复制index
        index = parentIndex;
    }
    h->pAddr[index] = e;
    return TRUE;
}

// 添加元素
int add_binaryHeap(binaryHeap *h, ElementType e, int (*compare)(ElementType, ElementType))
{
    // 判断新加元素是否是NULL
#ifndef c_type
    if (e == NULL)
    {
        return ERROR;
    }
#endif

    // 第一步：先判断是否需要扩容
    ensureCapacity(h);

    // 第二步：增加新元素
    h->pAddr[h->size] = e;

    // 第三步：上滤
    if (compare == NULL)
    {
        compare = comparator_default;
    }
    siftUp(h, h->size, compare);

    h->size++;

    return TRUE;
}

// 获取堆顶元素，这里的返回值还没有想到有什么好的处理方式
ElementType get_binaryHeap(binaryHeap *h)
{
    if (h == NULL)
    {
        return NULL;
    }

    return h->pAddr[0];
}

// 让index位置的元素下滤
int siftDown(binaryHeap *h, int index, int (*compare)(ElementType, ElementType))
{
    ElementType e = h->pAddr[index];
    int half = h->size >> 1;
    // 第一个叶子节点的索引 == 非叶子节点的数量
    // index < 第一个叶子节点的索引
    // 必须保证index位置是非叶子节点
    while (index < half)
    {
        // index的节点有2种情况
        // 1.只有左子节点
        // 2.同时有左右子节点

        // 默认为左子节点跟它进行比较
        int leftChildIndex = (index << 1) + 1;
        ElementType leftChild = h->pAddr[leftChildIndex];

        // 右子节点
        int rightChildIndex = leftChildIndex + 1;
        ElementType rightChild = h->pAddr[rightChildIndex];
        // 选出左右子节点最大的那个
        if (rightChildIndex < h->size && compare(rightChild, leftChild))
        {
            leftChildIndex = rightChildIndex;
            leftChild = rightChild;
        }

        if (compare(e, leftChild))
            break;

        // 将子节点存放到index位置
        h->pAddr[index] = leftChild;
        // 重置index
        index = leftChildIndex;
    }
    h->pAddr[index] = e;
    return TRUE;
}

// 删除堆顶元素，如果h为NULL，返回值没想到有什么好的处理方式
ElementType remove_binaryHeap(binaryHeap *h, int (*compare)(ElementType, ElementType))
{
    if (h == NULL)
    {
        return NULL;
    }

    int lastIndex = --(h->size);
    ElementType root = h->pAddr[0];
    h->pAddr[0] = h->pAddr[lastIndex];

    siftDown(h, 0, compare);
    return root;
}

// 替换堆顶元素，删除堆顶元素的同时插入一个新元素
ElementType replace_binaryHeap(binaryHeap *h, ElementType e, int (*compare)(ElementType, ElementType))
{
    // 判断新元素是否为空
#ifndef c_type
    if (e == NULL)
    {
        return NULL;
    }
#endif

    if (compare == NULL)
    {
        compare = comparator_default;
    }

#ifndef c_type
    ElementType root = NULL;
#else
    ElementType root;
#endif

    if (h->size == 0)
    {
        h->pAddr[0] = e;
        h->size++;
    }
    else
    {
        root = h->pAddr[0];
        h->pAddr[0] = e;
        siftDown(h, 0, compare);
    }
    return root;
}

// 批量建堆后的调整
int heapify(binaryHeap *h, int (*compare)(ElementType, ElementType))
{
    // // 自上而下的上滤
    // for (int i = 1; i < h->size; i++)
    // {
    //     siftUp(h, i, compare);
    // }

    // 自下而上的下滤
    for (int i = (h->size >> 1) - 1; i >= 0; i--)
    {
        siftDown(h, i, compare);
    }
}

// 根据数组创建二叉堆
binaryHeap *create_binaryHeap(ElementType arr[], int n, int (*compare)(ElementType, ElementType))
{
    // 默认容量是6
    int arr_length = n;
    int capacity;

    // 先判断arr是否为空
    if (arr != NULL)
    {
        capacity = arr_length >= default_capacity ? arr_length : default_capacity;
    }
    else // arr为NULL时，长度一定为0
    {
        arr_length = 0;
    }

    ElementType *pAddr_new = (ElementType *)malloc(sizeof(ElementType) * capacity);
    if (pAddr_new == NULL)
    {
        exit(1);
    }
    if (arr_length != 0)
    {
        for (int i = 0; i < arr_length; i++)
        {
            pAddr_new[i] = arr[i];
        }
    }

    // 分配动态数组的空间
    binaryHeap *h = (binaryHeap *)malloc(sizeof(binaryHeap));
    if (h == NULL)
    {
        exit(1);
    }

    h->size = arr_length;
    h->capacity = capacity;
    h->pAddr = pAddr_new;

    if (compare == NULL)
    {
        compare = comparator_default;
    }
    // 对h->pAddr中的内容进行整理
    heapify(h, compare);

    return h;
}

int main()
{
    // binaryHeap *heap = init_binaryHeap();
    // add_binaryHeap(heap, 68, comparator_default);
    // add_binaryHeap(heap, 72, comparator_default);
    // add_binaryHeap(heap, 43, comparator_default);
    // add_binaryHeap(heap, 50, comparator_default);
    // add_binaryHeap(heap, 38, comparator_default);
    // add_binaryHeap(heap, 10, comparator_default);
    // add_binaryHeap(heap, 90, comparator_default);
    // add_binaryHeap(heap, 65, comparator_default);

    // ElementType arr[] = {68, 72, 43, 50, 38, 10, 90, 65};
    // ElementType arr[] = {30, 34, 73, 60, 68, 43};
    ElementType arr[] = {88, 44, 53, 41, 16, 6, 70, 18, 85, 98, 81, 23, 36, 43, 37};
    binaryHeap *heap = create_binaryHeap(arr, 15, comparator_default);

    for (int i = 0; i < heap->size; i++)
    {
        printf("%d\n", heap->pAddr[i]);
    }

    printf("@@@@@@@@@@@@@@@@@@@@@@\n");
    ElementType temp1 = remove_binaryHeap(heap, comparator_default);
    printf("%d\n", temp1);
    printf("--------------\n");
    for (int i = 0; i < heap->size; i++)
    {
        printf("%d\n", heap->pAddr[i]);
    }

    printf("@@@@@@@@@@@@@@@@@@@@@@\n");
    ElementType temp2 = remove_binaryHeap(heap, comparator_default);
    printf("%d\n", temp2);
    printf("--------------\n");
    for (int i = 0; i < heap->size; i++)
    {
        printf("%d\n", heap->pAddr[i]);
    }

    return 0;
}