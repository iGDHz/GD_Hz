/***************************************************************************************
 *	FileName					:	climb.c
 *	CopyRight					:	None
 *	ModuleName					:	int climb(int i,int n)
 *
 *	CPU							:
 *	RTOS						:
 *
 *	Create Data					:	2020/4/7
 *	Author/Corportation			:	Hz
 *
 *	Abstract Description		:	在每次只能爬一或二级台阶时，返回爬上n阶台阶 共有几种方式 
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
/**************************************************************
*	Function Define Section
**************************************************************/

/**
 *  @name:int climb(int i,int n)
 *	@description:递归返回攀爬楼梯（每次爬1~2级）所有的方式共多少种 
 *	@param: i,n		
 *	@return: int	
 *  @notice: None
 */
int climb(int i,int n)
{
	if(i+1 == n) return 1;
	if(i+2 == n) return 2;
	else return climb(i+1,n)+climb(i+2,n); 
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
	for(i = 0; i < len; i++) { 
		if(str[i]>=from && str[i]<=to) return str[i];//遇到有效选项直接返回 
	}
	return str[len-1];//访问完之后查找不到有效数字直接返回最后数字 
}
  /**
 *  @name:int get_data(int *e)
 *	@description:return whether input-string is a correct number and save to e 
 *	@param:e
 *	@return:int 	
 *  @notice:None
 */
int get_data(int *e)//数据输入（防滚键盘） 
{
	char ch[30];
	int i,len;
	long long int result;
	result = 0,i = 0;
	len = strlen(ch); 
	gets(ch);
	while(ch[i])
	{
		if(ch[i]<'0' || ch[i]>'9') 
		{
			return 0;
		}
		else if(result < -2147483648LL || result > 2147483647LL)//判断是否会造成数据溢出 
		{  
			printf("数据溢出！\n");
			return 0;
		}
		result = result*10 + ch[i] - '0';
		i++;		
	}
	*e = (int)result;
	return 1;
 } 
int main()
{
	int n;
	while(1)
	{
		printf("输入:"); 
		if(get_data(&n) && n) printf("输出:%d\n",climb(0,n));
		else printf("输入错误！\n");
		printf("输入'y'退出程序，任意键继续...  ");
		if((getch('y','y')) == 'y') break;
	}
	return 0;
 } 
