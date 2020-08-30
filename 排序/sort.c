#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/timeb.h>

#define MAX 50000

// 获取系统时间
long getSystemTime()
{
    struct timeb tb;
    ftime(&tb);
    return tb.time * 1000 + tb.millitm;
}

// 快速排序
/* 
快速排序是一种分治策略
分治法基本思想：
- 先从数列中取出一个数作为基准数（枢轴）。
- 分区过程将比这个数大的数全放到它的右边，小于或等于它的数全放到它的左边。(升序)
    - 对r[s...t]中记录进行一趟快速排序，假设两个指针i和j，设枢轴记录rp=r[s],x=rp.key
    - 初始时令i=s,j=t
    - 首先从j所指位置向前搜索第一个关键字小于x的记录，并和rp交换；从后向前
    - 再从i所指位置起向后搜索，找到第一个关键字大于x的记录，和rp交换；从前往后
    - 重复上述两步，直到i==j为止。
- 再对左右区间重复第二步，直到各区间只有一个数。
*/
void QuickSort(int arr[], int start, int end)
{
    // 基准数
    int i = start, j = end;
    if (i > j)
    {
        return;
    }
    // 拿出第一个元素，保存到x中，第一个位置成为一个坑
    int x = arr[start];
    while (i < j)
    {
        // 从右向左 找比基准数小的
        while (i < j && arr[j] >= x)
        {
            // 左移，直到遇到小于等于x的数
            j--;
        }
        if (i < j)
        {
            // 将右侧占到的小于x的元素放入左侧坑中
            // 右侧出现一个坑，左侧元素索引后移
            arr[i] = arr[j]; // j变成坑
            i++;
        }

        // 从左向右 找比基准数大的数
        while (i < j && arr[i] < x)
        {
            // 右移，直到遇到大于x的数
            i++;
        }
        if (i < j)
        {
            //将左侧找到的元素放入右侧坑中, 左侧出现一个坑
            //右侧元素索引向前移动
            arr[j] = arr[i];
            j--;
        }
    }
    // 把基准数放到i位置
    arr[i] = x;
    // 对左半部分进行快速排序
    QuickSort(arr, start, i - 1);
    // 对右半部分进行快速排序
    QuickSort(arr, i + 1, end);
}

// 求待排序序列最大元素位数
int MaxBit(int arr[], int n)
{
    int maxValue = arr[0];
    int MaxBit = 0;
    // 找到序列忠最大元素
    for (int i = 0; i < n; ++i)
    {
        if (arr[i] > maxValue)
        {
            maxValue = arr[i];
        }
    }
    // 求解最大元素的位数
    while (maxValue != 0)
    {
        MaxBit++;
        maxValue /= 10;
    }

    return MaxBit;
}

// 求数字第bit位上的数字，比如238第2位上的数字是3
int BitNumber(int x, int bit)
{
    int temp = 1;
    for (int i = 1; i < bit; i++)
    {
        temp *= 10;
    }
    return (x / temp) % 10;
}

// 基数排序
void RadixSort(int arr[], int length)
{
    int i, j, k, bit, maxbit;
    // 最大元素位数
    maxbit = MaxBit(arr, length);
    int temp[10][MAX];
    for (i = 0; i < 10; i++)
    {
        // 0 ~ 9 10个桶
        // 记录每个桶的数据数量，置为0
        // 每个桶最大只能接收MAX - 1个数
        temp[i][0] = 0;
    }
    for (bit = 1; bit <= maxbit; bit++)
    {
        // 分配
        for (j = 0; j < length; j++)
        {
            // 取arr[j]第bit位上的数字
            int num = BitNumber(arr[j], bit);
            int index = ++temp[num][0];
            temp[num][index] = arr[j];
        }
        // 收集
        for (i = 0, j = 0; i < 10; i++)
        {
            for (k = 1; k <= temp[i][0]; k++)
            {
                arr[j++] = temp[i][k];
            }
            temp[i][0] = 0; // 收集元素个数置0
        }
    }
}

// 打印函数
void PrintArray(int arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int i, j;
    int arr[2][MAX];
    srand((unsigned int)time(NULL));
    for (i = 0; i < MAX; i++)
    {
        int num = rand() % MAX;
        for (j = 0; j < 2; ++j)
        {
            arr[j][i] = num;
        }
    }

    // printf("排序前：\n");
    // PrintArray(arr[0], MAX);
    // RadixSort(arr[0], MAX);
    // printf("排序后：\n");
    // PrintArray(arr[0], MAX);


    long t_start1 = getSystemTime();
    QuickSort(arr[0], 0, MAX - 1);
    long t_end1 = getSystemTime();
    printf("快速排序%d个元素，所需时间：%ld ms\n", MAX, t_end1 - t_start1);


    long t_start2 = getSystemTime();
    RadixSort(arr[1], MAX);
    long t_end2 = getSystemTime();
    printf("基数排序%d个元素，所需时间：%ld ms\n", MAX, t_end2 - t_start2);

    return 0;
}

// 快速排序50000个元素，所需时间：14 ms
// 基数排序50000个元素，所需时间：5 ms
