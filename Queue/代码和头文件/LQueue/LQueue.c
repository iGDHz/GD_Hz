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

#include"LQueue.h"

/**************************************************************
*	Function Define Section
**************************************************************/

  /**
 *  @name:void choices()
 *	@description:�������ѡ�� 
 *	@param:None
 *	@return:None	
 *  @notice:None
 */
 void choices()
 {
 	system("cls");
 	printf("\t*****ѡ����������*****\n");
	printf("|��������     a.int��      ��������|\n");
	printf("|��������    b.double��    ��������|\n");
	printf("|��������     c.char��     ��������|\n");
	printf("|��������d.string(20�ַ���)��������|\n");
	printf("�����룺");
 }
 
/**
 *  @name:char getch(char from,char to)
 *	@description:��ȡ�û��������Чѡ�� 
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
/**
 *  @name:Status get_data(void *e,char d_type)
 *	@description:������������ 
 *	@param:e
 *	@return:Status	
 *  @notice:None
 */
Status get_data(void *e,char d_type)//�������루�������̣� 
{
	char ch[30];
	int len,i;
	long long int result_int;
	double result_double;
	printf("�������ݣ�");
	gets(ch);
	len = strlen(ch); 
	if(len>20) 
	{
		printf("�����ַ�������\n");
		return FALSE;
	}
	switch(d_type)// ����ѡ���ж������Ƿ���ȷ 
	{
		case 'i':for(i = (ch[0] == '-')?1:0;i<len;i++) if(ch[i]<'0' || ch[i]>'9') break;break;
		case 'f':
		case 'd':for(i=0;i<len;i++) if((ch[i]<'0' || ch[i]>'9') && ch[i]!='.') break;break;
		default:i = len;break;
	}
	type = d_type;
	if(i!=len)
	{
		printf("�����ʽ����\n");
		return FALSE;
	}
	switch(d_type)
	{
		case 'i':{
			if((result_int = strtol(ch,NULL,0)) < -2147483648LL || result_int > 2147483647LL)
			{
				printf("���������\n");
				return FALSE;
			}//���������������� 
			break;
		}
		case 'f':
		case 'd': result_double = atof(ch);break;//float��doubleΪͬ����ת������ 
		case 'c':{
			*(char*)e = ch[0];
			return TRUE;
		}
		case 's':{
			strcpy((char*)e,ch);//��ch���Ƹ�eָ����ָ������� 
			return TRUE;
		}
	}
	if(d_type == 'i')
	{
		*(int*)e = (int)result_int;
	}
	else if(d_type == 'f')
	{
		*(float*)e = (float)result_double;
	}
	else *(double*)e = result_double;
	return TRUE;
 } 
 
 /**
 *  @name        : void InitLQueue(LQueue *Q)
 *  @description : ��ʼ������
 *  @param       : Q ����ָ��Q
 *  @notice      : None
 */
void InitLQueue(LQueue *Q)
{
	if(!Q->front || !Q->rear) DestoryLQueue(Q);
	Q->rear = Q->front = (Node*)malloc(sizeof(Node));
	Q->front->next = NULL;
	Q->length = 0;
	Q->front->data = malloc(sizeof(void));
	data_head = 0;//�������͵�ͷλ�� 
	data_rear = 0;//�������͵�βλ�� 
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *  @description : ���ٶ���
 *  @param       : Q ����ָ��Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q)
{
	Node *p1,*p2;
	p1 = p2 =Q->front;
	while(p1)
	{
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *  @description : �������Ƿ�Ϊ��
 *  @param       : Q ����ָ��Q
 *  @return      : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q)
{
	if(Q->length) return FALSE;
	return TRUE;
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *  @description : �鿴��ͷԪ��
 *  @param       : Q e ����ָ��Q,��������ָ��e
 *  @return      : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
Status GetHeadLQueue(LQueue *Q, void *e)
{
	if(IsEmptyLQueue(Q))
	{
		return FALSE;
	}
	switch(type = datatype[data_head])
	{
		case 'i':type = 'i';*(int*)e = *(int*)Q->front->data;break;
		case 'd':type = 'd';*(double*)e = *(double*)Q->front->data;break;
		case 'c':type = 'c';*(char*)e = *(char*)Q->front->data;break;
		case 's':type = 's';strcpy((char*)e,(char*)Q->front->data);break;
	}
	return TRUE;
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *  @description : ȷ�����г���
 *  @param       : Q ����ָ��Q
 *  @return      : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q)
{
	return Q->length;
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *  @description : ��Ӳ���
 *  @param       :  Q ����ָ��Q,�������ָ��data
 *  @return      : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ�Ϊ��
 */
Status EnLQueue(LQueue *Q, void *data)
{
	Node *new_node;
	if(!Q->front || !Q->rear) 
	{
		printf("����δ��ʼ����\n");
		return FALSE;
	}
	datatype[data_head] = type;
	if(!Q->length)//�ճ�ʼ��ʱֱ�����ó�ʼ����ͷ�ڵ������ֵ 
	{
		switch(type)
		{
			case 'i':*(int*)Q->front->data = *(int*)data;break;
			case 'd':*(double*)Q->front->data = *(double*)data;break;
			case 'c':*(char*)Q->front->data = *(char*)data;break;
			case 's':strcpy((char*)Q->front->data,(char*)data);break;
		}
		Q->length++; 
		return TRUE;
	}
	new_node = (Node*)malloc(sizeof(Node));
	new_node->data = (void*)malloc(sizeof(void));
	if(!new_node || !new_node->data)
	{
		printf("�ڵ��ڴ����ʧ�ܣ�\n");
		return FALSE;
	 } 
	switch(type)
	{
		case 'i':*(int*)new_node->data = *(int*)data;break;
		case 'd':*(double*)new_node->data = *(double*)data;break;
		case 'c':*(char*)new_node->data = *(char*)data;break;
		case 's':strcpy((char*)new_node->data,(char*)data);break;
	}
	new_node->next = NULL;//�½ڵ��ӿսڵ� 
	new_node = Q->rear->next;//�½ڵ����ԭ���е�β�ڵ� 
	Q->rear = new_node;//β�ڵ���������
	Q->length++; 
	data_rear = (data_rear+1)%30;//��������βλ�������һλ 
	return TRUE;
}

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *  @description : ���Ӳ���
 *  @param       : Q ����ָ��Q
 *  @return      : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q)
{
	Node *free_Q;
	if(IsEmptyLQueue(Q))
	{
		return FALSE;
	}
	if(Q->front == Q->rear) InitLQueue(Q);//ֻ��һ���ڵ�ʱֱ�Ӹ�ʽ�� 
	free_Q = Q->front;
	Q->front = Q->front->next;
	free(free_Q);
	Q->length--;
	data_head = (data_head+1)%30;//��������ͷλ�������һλ 
	return TRUE;
}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *  @description : ��ն���
 *  @param       : Q ����ָ��Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q)
{
	if(!Q->length) return ;
	DestoryLQueue(Q);
	InitLQueue(Q);
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *  @description : ������������
 *  @param       : Q ����ָ��Q����������ָ��foo
 *  @return      : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
{
	Node *p;
	int i;
	if(!Q->front || !Q->rear)
	{
		printf("����δ��ʼ����");
		return FALSE;
	}
	if(!Q->length)
	{
		printf("����Ϊ�գ�");
		return FALSE;
	}
	i = data_head;
	p = Q->front;
	while(p)
	{
		type = datatype[i];//�������� 
		foo(p->data);//�����Ӧ���� 
		p = p->next;
		i = (i+1)%30;
		printf(" -> ");
	}	
	printf("\b\b\b   \n");
	return TRUE;
}
/**
 *  @name        : void LPrint(void *q)
 *  @description : ��������
 *  @param       : q ָ��q
 
 *  @notice      : None
 */
void LPrint(void *q)
{
	switch(type)
	{
		case 'i':printf("%d",*(int*)q);break;
		case 'd':printf("%lf",*(double*)q);break;
		case 'c':printf("%c",*(char*)q);break;
		case 's':printf("%s",(char*)q);break; 
	}
}
