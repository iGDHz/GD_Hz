/***************************************************************************************
 *	FileName					:	
 *	CopyRight					:
 *	ModuleName					:	
 *
 *	CPU							:
 *	RTOS						:
 *
 *	Create Data					:	
 *	Author/Corportation			:	
 *
 *	Abstract Description		:	
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *	
 *
 ***************************************************************************************/
 
 
/**************************************************************
*	Include File Section
**************************************************************/
#include"../inc/qgsort.h"
/**************************************************************
*	Function Define Section
**************************************************************/

/**
 *  @name        : void insertSort(int *a,int n);
 *  @description : 插入排序
 *  @param       : 数组指针 a, 数组长度 n
 */
void insertSort(int *a,int n)
{
	int i,j,temp;
	for(i = 1 ; i < n ; i++)
	{
		temp = *(a+i);
		for(j = i ; j > 0 && *(a+j-1) > temp ; j--) 
		{
			*(a+j) = *(a+j-1);
		}
		*(a+j) = temp;
	}
}


/**
 *  @name        : void MergeArray(int *a,int begin,int mid,int end,int *temp);
 *  @description : 归并排序（合并数组）
 *  @param       : 数组指针a，数组起点begin，数组中点mid，数组终点end，承载数组指针temp
 */
void MergeArray(int *a,int begin,int mid,int end,int *temp)
{
	int i = begin,j = mid+1;
	int m = mid,n = end;
	int k = 0;
	while(i<=m && j<=n)  temp[k++] = a[i]<=a[j]?a[i++]:a[j++];
	while(i<=m)  temp[k++] = a[i++];
	while(j<=n)  temp[k++] = a[j++];
	for(i=0;i<k;i++)  a[begin+i] = temp[i];
}


/**
 *  @name        : void MergeSort(int *a,int begin,int end,int *temp);
 *  @description : 归并排序
 *  @param       : 数组指针a，数组起点begin，数组终点end，承载数组指针temp
 */
 void MergeSort(int *a,int begin,int end,int *temp)
 {
 	int mid;
 	if(begin<end)
	{
		mid = (begin+end)/2;
		MergeSort(a,begin,mid,temp);
		MergeSort(a,mid+1,end,temp);
		MergeArray(a,begin,mid,end,temp);
	}
 }
/*void MergeSort(int *a,int begin,int end,int *temp)
{
    if (begin >= end) return;
    int len,mid,begin1,end1,begin2,end2,i;
    len = end - begin;
    mid = len/2 + begin;
    begin1 = begin,end1 = mid,begin2 = mid + 1,end2 = end;
    MergeSort(a, begin1, end1, temp);
    MergeSort(a, begin2, end2, temp);
    i = begin;
    while (begin1 <= end1 && begin2 <= end2)  temp[i++] = a[begin1] < a[begin2] ? a[begin1++] : a[begin2++];
    while (begin1 <= end1)  temp[i++] = a[begin1++];
    while (begin2 <= end2)  temp[i++] = a[begin2++];
    for (i = begin; i <= end; i++)  a[i] = temp[i];
}*/


/**
 *  @name        : void QuickSort(int *a, int begin, int end);
 *  @description : 快速排序（递归版）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
void QuickSort_Recursion(int *a, int begin, int end)
{
 	if (begin < end)  
    {  
        int i = begin, j = end, x = a[begin];  
        while (i < j)  
        {  
            while(i < j && a[j] >= x) j--;    
            if(i < j)   a[i++] = a[j]; 
            while(i < j && a[i] < x)  i++;    
            if(i < j)  a[j--] = a[i];  
        }  
        a[i] = x;  
        QuickSort_Recursion(a, begin, i - 1); // 递归调用   
        QuickSort_Recursion(a, i + 1, end);  
    }  	
}


/**
 *  @name        : void QuickSort(int *a,int size)
 *  @description : 快速排序（非递归版）
 *  @param       : 数组指针a，数组长度size
 */
void QuickSort(int *a,int size);


/**
 *  @name        : void QuickSort(int *a, int begin, int end)
 *  @description : 快速排序（枢轴存放）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
int Partition(int *a, int begin, int end);


/**
 *  @name        : void CountSort(int *a, int size , int max)
 *  @description : 计数排序
 *  @param       : 数组指针a，数组长度size，数组最大值max
 */
void CountSort(int *a, int size , int max)
{
	int *temp,*result,i,j;
	temp = (int*)malloc(sizeof(int)*(max+1));
	result = (int*)malloc(sizeof(int)*size);
	for(i = 0; i <= max; i++) *(temp+i) = 0;
	for(i = 0; i < size; i++) *(result+i) = 0;
	for(i = 0; i < size; i++)
	{
		(*(temp + *(a + i)))++;
	}
	for(i = 1; i <= max; i++)
	{
		*(temp + i) = *(temp + i) + *(temp + i - 1);
	}
	putchar('\n');
	for(i = max; i > 0; i--)
	{
		result[--temp[a[i-1]]] = *(a + i - 1);
	}
	for(i = 0; i < size; i++)
	{
		*(a + i) = *(result + i);
	}
	free(temp);
	free(result);
}


/**
 *  @name        : void RadixCountSort(int *a,int size)
 *  @description : 基数计数排序
 *  @param       : 数组指针a，数组长度size
 */
int GetMaxPos(int *a, int size)
{
    int max = 0;
    int i;
    for(i = 0; i < size; i ++)
    {
        if(a[i] > max)
        {
            max = a[i];
        }
    }
    i = 0;
    while(max)
    {
        max /= 10;
        i ++;
    }
    return i;
}
void RadixCountSort(int *a,int size){
	int bucket[10];
	int *temp;
	int bits = 1, pos;
	int i, j;
	temp = (int *)malloc(size * sizeof(int));

	pos = GetMaxPos(a, size);
	for(j = 0; j < pos; j ++){
		for(i = 0; i < size; i++){
			temp[i] = a[i];
		}
		for(i = 0; i < 10; i ++){
			bucket[i] = 0;
		}
		//收集
		for(i = 0; i < size; i ++){
			bucket[a[i] / bits % 10] ++;
		}
		//统计
		for(i = 1; i < 10; i ++){
			bucket[i] += bucket[i - 1];
		}

		//分配
		i = size - 1;
		while(i >= 0)
        {
			a[ -- bucket[temp[i] / bits % 10]] = temp[i];
			i--;
		}
		bits *= 10;
	}
}


/**
 *  @name        : void ColorSort(int *a,int size)
 *  @description : 颜色排序
 *  @param       : 数组指针a（只含0，1，2元素），数组长度size
 */
void ColorSort(int *a,int size);


/**
 *  @name        : 自拟
 *  @description : 在一个无序序列中找到第K大/小的数
 *  @param       : 数组指针a，数组长度size
 */
