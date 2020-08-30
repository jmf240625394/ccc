#include "DynamicArray.h"

int main()
{
    // 初始化动态数组
    Dynamic_Array *myArray = Init_Array();
    // 打印容量
    printf("数组容量：%d\n", myArray->capacity);
    printf("数组大小：%d\n", myArray->size);
    // 插入元素
    for (int i = 0; i < 30; i++)
    {
        PushBack_Array(myArray, i);
    }
    printf("数组容量：%d\n", myArray->capacity);
    printf("数组大小：%d\n", myArray->size);
    // 打印
    Print_Array(myArray);
    // 删除元素
    RemoveByPos_Array(myArray, 0);
    RemoveByValue_Array(myArray, 27);
    // 打印
    Print_Array(myArray);
    // 查找数值5的位置
    int pos1 = Find_Array(myArray, 5);
    printf("5查找到：pos %d %d\n", pos1, At_Array(myArray, pos1));
    int pos2 = Find_Array(myArray, 200);
    printf("200查找到：pos %d %d\n", pos2, At_Array(myArray, pos2));

    // 销毁
    FreeSpace_Array(myArray);
}