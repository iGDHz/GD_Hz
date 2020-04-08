/***************************************************************************************
 *	FileName					:	Pstring_2.c
 *	CopyRight					:	
 *	ModuleName					:	get the longest palindrome string
 *
 *	CPU							:
 *	RTOS						:
 *
 *	Create Data					:	2020/4/7
 *	Author/Corportation			:	Hz
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
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../head/input.h"

/**************************************************************
*	Function Define Section
**************************************************************/

/**
 *  @name:int** Matrix_Create(int n)
 *	@description:Creat a n*n matrix filled with zero
 *	@param:n		
 *	@return	:int **	
 *  @notice:None
 */
 int** Matrix_Create(int n)
 {
 	int **matrix;
 	int i,j;
 	matrix = (int **)malloc(sizeof(int*)*n);
 	for(i=0;i<n;i++) *(matrix+i) = (int *)malloc(sizeof(int)*n);
 	for(i=0;i<n;i++)
 	{
 		for(j=0;j<n;j++)
 		{
 			*(*(matrix+i)+j)= 0;
		 }
	 }
	return matrix;
 }
 
 /**
 *  @name:char* Plongest(char *s,int *max)
 *	@description:retrun the head of the longest palindrome string and return the max_length to max
 *	@param:s,max	
 *	@return:char *	
 *  @notice:None
 */
 
 char* Plongest(char *s,int *max)
 {
 	int **matrix,max_start,max_len,cur_len,i,j,n;
	max_start = max_len = 0;
  	n = strlen(s);
 	matrix = Matrix_Create(n);//建立一个n*n的0矩阵，单位矩阵也可 
 	for(j=0;j<n;j++)//matrix[i][j]为从s[i]到s[j]是否为回文字符串 
 	{
 		for(i=0;i<=j;i++)
 		{
 			if(j - i < 2)	*(*(matrix+i)+j) = (s[i] == s[j]);//当s[i]和s[j]相邻时仅判断两者是否相等 
			else	*(*(matrix+i)+j) = ((s[i] == s[j]) && *(*(matrix+i+1)+j-1));//若从i+1到j-1为回文字符串则判断s[i]和s[j]能否继续添加至当前回文字符串 
			cur_len = j + 1 - i;
			if(*(*(matrix+i)+j) && cur_len > max_len)
			{
				max_start = i;
				max_len = cur_len;
			}
		 }
	 }
	*max = max_len;
	return &s[max_start];
 } 
 
 /**
 *  @name:char getch(char from,char to)
 *	@description:get a correct character from a string
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
 	int n,i,j,max;
 	char s[1001],*str;
 	printf("输入:");
	while(1)
 	{
 		gets(s);
 		str = Plongest(s,&max);
 		*(str+max) = '\0';
		printf("输出:%s\n",str);
		printf("输入'y'退出程序，任意键继续...   ");
		if((getch('y','y'))=='y') break;
		printf("输入:");
	}
 	return 0;
 }
