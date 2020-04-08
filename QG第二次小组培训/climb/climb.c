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
 *	Abstract Description		:	��ÿ��ֻ����һ�����̨��ʱ����������n��̨�� ���м��ַ�ʽ 
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
 *	@description:�ݹ鷵������¥�ݣ�ÿ����1~2�������еķ�ʽ�������� 
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
char getch(char from,char to)//�û�ѡ�����루�ַ�����ȡ�󷵻���Чѡ���ܣ���Χ��from��to�� 
{
	char str[50];
	int i,len;
	gets(str);//�ַ�����ȡ 
	len = strlen(str);
	for(i = 0; i < len; i++) { 
		if(str[i]>=from && str[i]<=to) return str[i];//������Чѡ��ֱ�ӷ��� 
	}
	return str[len-1];//������֮����Ҳ�����Ч����ֱ�ӷ���������� 
}
  /**
 *  @name:int get_data(int *e)
 *	@description:return whether input-string is a correct number and save to e 
 *	@param:e
 *	@return:int 	
 *  @notice:None
 */
int get_data(int *e)//�������루�������̣� 
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
		else if(result < -2147483648LL || result > 2147483647LL)//�ж��Ƿ������������ 
		{  
			printf("���������\n");
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
		printf("����:"); 
		if(get_data(&n) && n) printf("���:%d\n",climb(0,n));
		else printf("�������\n");
		printf("����'y'�˳��������������...  ");
		if((getch('y','y')) == 'y') break;
	}
	return 0;
 } 
