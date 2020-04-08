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
char getch(char from,char to)//�û�ѡ�����루�ַ�����ȡ�󷵻���Чѡ���ܣ���Χ��from��to�� 
{
	char str[50];
	int i,len;
	gets(str);//�ַ�����ȡ 
	len = strlen(str);
	for(i = 0; i<len; i++) { 
		if(str[i]>=from && str[i]<=to) return str[i];//������Чѡ��ֱ�ӷ��� 
	}
	return str[len-1];//������֮����Ҳ�����Ч����ֱ�ӷ���������� 
}
int main()
{
	char s[10001];
	int i,len,max,max_temp,j,temp_j;
	while(1)
	{
		printf("���룺");
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
		printf("\n����'y'�˳��������������...   ");
		if((getch('y','y'))=='y') break;
	}
	return 0;
}
