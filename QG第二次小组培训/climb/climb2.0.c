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
	int i,n,temp;
	int f[3];
	while(1)
	{
		printf("����:"); 
		if(get_data(&n) && n)
		/*��n>2ʱÿ�ζ����һ��̨��,�������ָ�����һ��̨��·�ߣ���
		������һ��̨��Ϊǰ����̨��֮�� */ 
		{
			f[0] = 1, f[1] = 2;
			if(n<=2)
			{
				printf("���:%d\n",f[n-1]);
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
				printf("���:%d\n",f[2]);	
			}
		}
		else printf("�������\n");
		printf("����'y'�˳��������������...  ");
		if((getch('y','y')) == 'y') break;
	}
	return 0;
 } 
