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
#include"AQueue.c"

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
 	printf("|��������b.�����Ƿ�����  ��������|\n");
 	printf("|��������c.�����Ƿ�Ϊ��  ��������|\n");
 	printf("|��������d.��ȡͷ������ݡ�������|\n");
 	printf("|��������e.���г���      ��������|\n");
 	printf("|��������f.���          ��������|\n");
 	printf("|��������g.����          ��������|\n");
 	printf("|��������h.��ն���      ��������|\n");
 	printf("|��������i.�������      ��������|\n");
 	printf("|��������j.�˳�          ��������|\n");
 	printf("�����룺");
 }

int main()
{
	AQueue *Q;
	void *e,*data;
	int flag;
	char ch;
	Q = (AQueue*)malloc(sizeof(AQueue));
	Q->data[0] = NULL;
	e = (void*)malloc(sizeof(void));
	flag = 0;
	InitAQueue(Q);
	tips();
	while(1)
	{
		while((ch = getch('a','j'))!='j')
		{
			printf("���ѡ��%c\n",ch);
			switch(ch)
			{
				case 'a':InitAQueue(Q);break;
				case 'b':{
					if(IsFullAQueue(Q)) printf("����������\n");
					else printf("����δ����\n");
					break;
				}
				case 'c':{	
					if(IsEmptyAQueue(Q)) printf("����Ϊ�գ�\n");
					else printf("���в�Ϊ�գ�\n");
					break;
				}
				case 'd':{
					if(GetHeadAQueue(Q,e)) ;
					else printf("����Ϊ�գ�\n");
					break;
				}
				case 'e':{
					printf("���г���Ϊ%d\n",LengthAQueue(Q));
					break;
				}
				case 'f':{
					if(EnAQueue(Q,data)) printf("��ӳɹ���\n");
					else printf("���ʧ�ܣ�\n");
					break;
				}
				case 'g':{
					if(DeAQueue(Q)) printf("���ӳɹ���\n");
					else printf("����Ϊ�գ��޷�����\n");
					break;
				}
				case 'h':{
					ClearAQueue(Q);
					break;
				}
				case 'i':{
					if(TraverseAQueue(Q,APrint));
					else printf("����Ϊ�գ�\n");
					break;
				}
				default:flag = 1;break; 
			}
			if(flag)
			{
				flag = 0;
				printf("�������\n���������룺");
			}
			else break;
		}
		if(ch == 'j') break;
		system("pause");
		system("cls");
		tips();
	}
	DestoryAQueue(Q);
	free(Q);
	return 0;
}

