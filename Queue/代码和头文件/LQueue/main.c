/***************************************************************************************
 *	FileName					:	main.c
 *	CopyRight					:	
 *	ModuleName					:	������ 
 *
 *	CPU							:	
 *	RTOS						:
 *
 *	Create Data					:	2020/4/11
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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LQueue.c"

/**************************************************************
*	Function Define Section
**************************************************************/

/**
 *  @name:void tips()
 *	@description:�������ָ�� 
 *	@param:None
 *	@return:None	
 *  @notice:None
 */
 void tips()
 {
 	printf("|��������a.��ʼ������    ��������|\n");
 	printf("|��������b.�����Ƿ�Ϊ��  ��������|\n");
 	printf("|��������c.��ȡͷ������ݡ�������|\n");
 	printf("|��������d.���г���      ��������|\n");
 	printf("|��������e.���          ��������|\n");
 	printf("|��������f.����          ��������|\n");
 	printf("|��������g.��ն���      ��������|\n");
 	printf("|��������h.�������      ��������|\n");
 	printf("|��������i.�˳�          ��������|\n");
 	printf("�����룺");
 }
 
 
int main()
{
	LQueue *Q;
	char ch,temp;
	void *e;
	int flag;
	Q = (LQueue*)malloc(sizeof(LQueue));
	Q->front = Q->rear = NULL;
	Q->length = 0;
	e = (void*)malloc(sizeof(void));
	flag = 0;
	tips();
	while(1)
	{
		while((ch = getch('a','i'))!='i')
		{
			printf("���ѡ��%c\n",ch);
			switch(ch)
			{
				case 'a':InitLQueue(Q);break;//��ʼ������ 
				case 'b':{//�ж϶����Ƿ�Ϊ��	
					if(IsEmptyLQueue(Q)) printf("����Ϊ�գ�\n");
					else
					{
						printf("����Ϊ�գ�(��δ��ʼ�����ȳ�ʼ��)\n");
					}
					break;
				}
				case 'c':{//��ȡͷ�ڵ����� 
					if(GetHeadLQueue(Q,e)) 
					{
						printf("��ͷԪ��:");
						LPrint(e);
						printf("\n");
					}
					break;
				}
				case 'd':{//��ȡ���г��� 
					if(!Q->front || !Q->rear)
					{
						printf("����δ��ʼ����\n");
						break;
					}
					printf("���г���Ϊ%d\n",LengthLQueue(Q));
					break;
				}
				case 'e':{//��� 
					choices();
					switch(temp = getch('a','d'))
					{
						case 'a':type = 'i';break;
						case 'b':type = 'd';break;
						case 'c':type = 'c';break;
						case 'd':type = 's';break;
						default:flag = 1;break;
					}
					if(flag)
					{
						system("cls");
						tips();
						break;
					}
					if(!get_data(e,type)) break;
					if(EnLQueue(Q,e)) printf("��ӳɹ���\n");
					else printf("���ʧ�ܣ�\n");
					break;
				}
				case 'f':{//���� 
					if(DeLQueue(Q)) printf("���ӳɹ���\n");
					else printf("�޷�����\n");
					break;
				}
				case 'g':{//��ն��� 
					ClearLQueue(Q);
					break;
				}
				case 'h':{//�������� 
					TraverseLQueue(Q,LPrint);
					break;
				}
				case 'i':break;
				default:flag = 1;break; 
			}
			if(flag)
			{
				flag = 0;
				printf("�������\n���������룺");
			}
			else break;
		}
		if(ch == 'i') break;
		system("pause");
		system("cls");
		tips();
	}
	DestoryLQueue(Q);
	free(Q);
	return 0;
}

