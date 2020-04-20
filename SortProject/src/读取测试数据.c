#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"qgsort.c"

/**
 *  @name:void tips()
 *	@description:排序算法选择 
 *	@param:None			
 *	@return	:None	
 *  @notice:None
 */
void tips()//排序方式选择 
{
	printf("|————a.插入排序————|\n");
	printf("|————b.归并排序————|\n"); 
	printf("|————c.快速排序————|\n");
	printf("|————d.基数排序————|\n");
}

 /**
 *  @name:char getch(char from,char to)
 *	@description:获取正确输入选项 
 *	@param:from,to			
 *	@return:char	
 *  @notice:None
 */
char getch(char from,char to)//用户选择输入（字符串读取后返回有效选择功能，范围从from到to） 
{
	char str[50];
	int i,len;
	gets(str);//字符串读取 
	len = strlen(str);
	for(i = 0; i<len; i++) { 
		if(str[i]>=from && str[i]<=to) return str[i];//遇到有效选项直接返回 
	}
	return str[len-1];//访问完之后查找不到有效数字直接返回最后数字 
}

int main()
{
	int i,a[50000],*temp;
	FILE *fp;
	char ch;
	i = 0;
	fp = fopen("test_data","r");
	;
	while(!feof(fp))
	{
		fscanf(fp,"%d",&a[i]);
		i++;
	 } 
	temp = (int*)malloc(sizeof(int)*5000);
	fclose(fp);
	tips();
	while(1)
	{
		ch = getch('a','e');
		switch(ch)
		{
			case 'a':{
				insertSort(a,5000);
				break;
			}
			case 'b':{
				MergeSort(a,0,5000,temp);
				break;
			}
			case 'c':{
				QuickSort_Recursion(a,0,5000);
				break;
			}
			case 'd':{
				RadixCountSort(a,5000); 
				break;
			}
			default:{
				printf("输入错误！请重新输入！\n"); 
				break;
			}
		}
		if(ch >= 'a' && ch <= 'd') break;
	}
	if(ch != 'e')
	{
		fp = fopen("test_data","w");
		for(i = 0; i <= 5000; i++)
		{
			fprintf(fp,"%d ",a[i]);
		}
		fclose(fp);
	}
	return 0;
}
