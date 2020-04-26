/***************************************************************************************
 *	FileName					:	main.c
 *	CopyRight					:
 *	ModuleName					:	
 *
 *	CPU							:
 *	RTOS						:
 *
 *	Create Data					:	2020/4/26
 *	Author/Corportation			:	Hz
 *
 *	Abstract Description		:	
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *	
 *
 ***************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tree.c"
/**************************************************************
*	Function Define Section
**************************************************************/

/**
 *  @name:void function_tips() 
 *	@description:��������ѡ�� 
 *	@param��None 
 *	@return:None	
 *  @notice:None
 */
void function_tips()
{
	printf("|��������a.��ͨ������ ��������|\n");
	printf("|��������b.���������� ��������|\n");
	printf("|��������c.���ʽ���� ��������|\n");
	printf("|��������    d.�˳�   ��������|\n");
	printf("�����룺");
}

/**
 *  @name:void Traverses() 
 *	@description:������ʽѡ�� 
 *	@param��None 
 *	@return:None	
 *  @notice:None
 */
 void Traverse()
 {
 	printf("|��������a.������� ��������|\n");
 	printf("|��������b.������� ��������|\n");
 	printf("|��������c.������� ��������|\n");
 	printf("|��������d.��α��� ��������|\n");
 	printf("|��������  e.�˳�   ��������|\n");
 	printf("�����룺");
 }
 
  /**
 *  @name:char getch(char from,char to)
 *	@description:��ȡ��ȷ����ѡ�� 
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
	BiTree T;
	char ch,temp;
	while(1)
	{
		system("cls");
		function_tips();
		InitBiTree(&T);
		while((ch = getch('a','d'))<'a' || ch >'d') 
		{
			printf("��������ȷ���ַ���\n�����룺");
		}
		if(ch == 'd') break;
		switch(ch)
		{
			case 'a':{
				printf("�����루��:AB#DF##G##C#E#H##����") ;
				CreateBiTree(&T,"BiTree");
				getchar();//���ն�����Ļس� 
				break;
			}
			case 'b':{
				printf("�����루��:46283��:");
				CreateBiTree(&T,"BSTree");
				break;
			}
			case 'c':{
				printf("������(�磺1 + 4 * 3 / 2 - 7)��");
				while(!CreateBiTree(&T,"BCTree"))
				{
					printf("������󣬰���Y����������...    ");
					if(getch('Y','Y') == 'Y') break;
					getchar();
					printf("������(�磺1+4*4-2)��");
				}
				break;
			}
		}
		while(ch=='a' || ch =='b')
		{
			system("cls");
			Traverse();
			while((temp = getch('a','e'))<'a' || temp >'e') 
			{
				
				printf("��������ȷ���ַ���\n�����룺");
			}
			if(temp == 'e') 
			{
				break;
			}
			else
			{
				switch(temp)
				{
					case 'a':{
					PreOrderTraverse(T,print);//������� 
					putchar('\n');
					break;
					}
					case 'b':{
					InOrderTraverse(T,print);//������� 
					putchar('\n');
					break;
						
					}
					case 'c':{
					PostOrderTraverse(T,print);//������� 
					putchar('\n');
					break;
					}
					case 'd':{
					LevelOrderTraverse(T,print);//��α��� 
					putchar('\n');	
					break;
					}
				}
				system("pause");
			}
		}
		if(ch == 'c')
		{
			PostOrderTraverse(T,print);
			printf("=%d\n",Value(T));
			system("pause"); 
		}
		DestroyBiTree(&T);
	}	
	DestroyBiTree(&T);
	return 0;
}
