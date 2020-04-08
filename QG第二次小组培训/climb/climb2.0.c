/***************************************************************************************
 *	FileName					:	climb2.0.c
 *	CopyRight					:	None
 *	ModuleName					:	
 *
 *	CPU							:
 *	RTOS						:
 *
 *	Create Data					:	2020/4/8
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
	int i,n,temp;
	int f[3];
	while(1)
	{
		printf("输入:"); 
		if(get_data(&n) && n)
		/*当n>2时每次多添加一级台阶,则多两条指向最后一级台阶路线，、
		则增加一级台阶为前两级台阶之和 */ 
		{
			f[0] = 1, f[1] = 2;
			if(n<=2)
			{
				printf("输出:%d\n",f[n-1]);
			}
			else
			{	
				f[2] = f[0]+f[1];
				for(i=4;i<=n;i++)
				{
					temp = f[2];
					f[2] = f[2] + f[1];
					f[0] = f[1];
					f[1] = temp;
				}	
				printf("输出:%d\n",f[2]);	
			}
		}
		else printf("输入错误！\n");
		printf("输入'y'退出程序，任意键继续...  ");
		if((getch('y','y')) == 'y') break;
	}
	return 0;
 } 
