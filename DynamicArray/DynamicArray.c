#include "DynamicArray.h"

// 初始化
Dynamic_Array *Init_Array()
{
    // 分配数组的默认空间
    int *newSpace = (int *)malloc(sizeof(int) * 10);
    if (NULL == newSpace)
    {
        exit(1);
    }

    // 分配动态数组Dynamic_Array的空间
    Dynamic_Array *newArray = (Dynamic_Array *)malloc(sizeof(Dynamic_Array));
    if (NULL == newArray)
    {
        exit(1);
    }

    newArray->pAddr = newSpace;
    newArray->capacity = 10;
    return newArray;
}

// 插入
void PushBack_Array(Dynamic_Array *arr, int value)
{
    if (NULL == arr)
    {
        return;
    }

    // 判断空间是否足够
    if (arr->size == arr->capacity)
    {
        // 第一步 申请一块更大的内存空间 新空间是旧空间的2倍
        int *newSpace = (int *)malloc((sizeof(int) * arr->capacity) * 2);
        // 第二步 拷贝数据到新的空间
        memcpy(newSpace, arr->pAddr, arr->capacity * sizeof(int));
        // 第三步 释放旧空间的内存
        free(arr->pAddr);

        // 更新容量
        arr->capacity = arr->capacity * 2;
        arr->pAddr = newSpace;
    }

    // 插入新元素
    arr->pAddr[arr->size] = value;
    arr->size++;
}

// 根据位置刪除
void RemoveByPos_Array(Dynamic_Array *arr, int pos)
{
    if (NULL == arr)
    {
        return;
    }

    // 判断位置是否有效
    if (pos < 0 || pos >= arr->size)
    {
        return;
    }

    // 删除元素
    for (int i = pos; i < arr->size; i++)
    {
        arr->pAddr[i] = arr->pAddr[i + 1];
    }

    arr->size--;
    // 个人觉得这里有个内存泄漏的地方，类似水位线原理
    // 比如，数组经过多次扩容，某次达到了163840的容量，但是随着元素的删除，加入只剩下10个元素了
    // 但是10个元素还是占着163840的容量
}

// 根据值刪除
void RemoveByValue_Array(Dynamic_Array *arr, int value)
{
    if (NULL == arr)
    {
        return;
    }

    // 找到值的位置
    int pos = -1;
    for (int i = 0; i < arr->size; i++)
    {
        if (arr->pAddr[i] == value)
        {
            pos = i;
            break;
        }
    }

    // 根据位置删除
    RemoveByPos_Array(arr, pos);
}

// 查找
int Find_Array(Dynamic_Array *arr, int value)
{
    if (NULL == arr)
    {
        return -1;  // 这里暂时用-1，防止正常返回值和异常返回值，混淆
    }

    int pos = -1;
    for (int i = 0; i < arr->size; i++)
    {
        if (arr->pAddr[i] == value)
        {
            pos = i;
            break;
        }
    }
    return pos;
}

// 打印
void Print_Array(Dynamic_Array *arr)
{
    if (NULL == arr)
    {
        return;
    }
    for (int i = 0; i < arr->size; i++)
    {
        printf("%d ", arr->pAddr[i]);
    }
    printf("\n");
}

// 释放动态数组的内存
void FreeSpace_Array(Dynamic_Array *arr)
{
    if (NULL == arr)
    {
        return;
    }

    free(arr->pAddr);
    arr->pAddr = NULL;
    free(arr);
    arr = NULL;
}

// 清空数组
void Clear_Array(Dynamic_Array *arr)
{
    if (NULL == arr)
    {
        return;
    }

    arr->size = 0;
}

// 获得动态数组容量
int Capacity_Array(Dynamic_Array *arr)
{
    if (NULL == arr)
    {
        return -1;  // 这里暂时用-1，防止正常返回值和异常返回值，混淆
    }

    return arr->capacity;
}

// 获得动态数组当前元素个数
int Size_Array(Dynamic_Array *arr)
{
    if (NULL == arr)
    {
        return -1;  // 这里暂时用-1，防止正常返回值和异常返回值，混淆
    }

    return arr->size;
}

// 根据位置获得某个位置元素
int At_Array(Dynamic_Array *arr, int pos)
{
    // 判断位置是否有效
    if (pos < 0 || pos >= arr->size)
    {
        return -1;  // 这里暂时用-1，防止正常返回值和异常返回值，混淆
    }

    return arr->pAddr[pos];
}
