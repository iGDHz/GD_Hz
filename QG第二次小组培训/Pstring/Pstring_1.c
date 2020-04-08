/***************************************************************************************
 *	FileName					:	Pstring_1.c
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
#include<string.h>
#include"../head/input.h"
/**
 *  @name:int Plongest(int i,char *s,int *max)
 *	@description:retrun the head of the longest palindrome string and change the max
 *	@param:	i,s(string),max()
 *	@return:int		
 *  @notice:None
 */
int Plongest(int i,char *s,int *max)
{
	int j,max_temp;
	max_temp = j = 1;
	while((i-j)>=0 && *(s+i-j) == *(s+i+j))
	{
		max_temp += 2;
		j++;
	}
	(*max) = (*max)>max_temp?(*max):max_temp;
	max_temp = j = 0;
	while((i-j)>=0 && *(s+i-1-j) == *(s+i+j))
	{
		max_temp += 2;
		j++;
	}
	(*max) = (*max)>max_temp?(*max):max_temp;
	return i-(*max)/2;
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
	char s[10001];
	int i,len,max,max_temp,j,temp_j;
	while(1)
	{
		printf("输入：");
		gets(s);
		i = 0;
		max_temp = max = 1;
		len = strlen(s);
		temp_j = j = 0;
		for(i=1;i < len;i++)
		{
			temp_j = Plongest(i,s,&max_temp);
			if(max_temp > max)
			{
				max = max_temp;
				j = temp_j;
			}
			max_temp = max;
		}
		printf("max:%d\nstring:",max);
		temp_j = j;
		for(;j<max+temp_j;j++)
		{
			printf("%c",*(s+j));
		}
		printf("\n输入'y'退出程序，任意键继续...   ");
		if((getch('y','y'))=='y') break;
	}
	return 0;
}
