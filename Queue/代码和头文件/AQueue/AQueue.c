/***************************************************************************************
 *	FileName					:	AQueue.c
 *	CopyRight					:	
 *	ModuleName					:	function 
 *
 *	CPU							:
 *	RTOS						:
 *
 *	Create Data					:	2020/4/11
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

#include"AQueue.h"

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
		case 'd':for(i = (ch[0] == '-')?1:0;i<len;i++) if((ch[i]<'0' || ch[i]>'9') && ch[i]!='.') break;break;
		default:i = len;break;
	}
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
 *  @name        : void InitAQueue(AQueue *Q)
 *  @description : ��ʼ������
 *  @param       : Q ����ָ��Q
 *  @notice      : None
 */
void InitAQueue(AQueue *Q) 
{
	int i;
	if(!Q->length) DestoryAQueue(Q);//�������Ѿ���ʼ�����ʽ������ 
	for(i = 0;i < MAXQUEUE;i++) Q->data[i] = (void *)malloc(sizeof(void));
	Q->length = Q->front = Q->rear = 0;	
}


/**
 *  @name        : void DestoryAQueue(AQueue *Q)
 *  @description : ���ٶ���
 *  @param       :  Q ����ָ��Q
 *  @notice      : None
 */
void DestoryAQueue(AQueue *Q)
{
	int i;
	for(i = 0;i < MAXQUEUE;i++) free(Q->data[i]);
}

/**
 *  @name        : Status IsFullAQueue(const AQueue *Q)
 *  @description : �������Ƿ�����
 *  @param       : Q ����ָ��Q
 *  @return      : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsFullAQueue(const AQueue *Q)
{
	if((Q->rear+1)%MAXQUEUE == Q->front) return TRUE;
	return FALSE;
}

/**
 *  @name        : Status IsEmptyAQueue(const AQueue *Q)
 *  @description : �������Ƿ�Ϊ��
 *  @param       :  Q ����ָ��Q
 *  @return      : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsEmptyAQueue(const AQueue *Q)
{
	if(Q->length) return FALSE;
	return TRUE; 
}


/**
 *  @name        : Status GetHeadAQueue(AQueue *Q, void *e)
 *  @description : �鿴��ͷԪ��
 *  @param       : Q ����ָ��Q�����Ԫ��e
 *  @return      : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
Status GetHeadAQueue(AQueue *Q, void *e)
{
	if(IsEmptyAQueue(Q)) return FALSE;
	switch(datatype[Q->front])//����datatype�ҳ���ӦԪ�ص����Ͳ���� 
	{
		case 'i':*(int*)e = *(int*)Q->data[Q->front];printf("��ͷԪ�أ�%d\n",*(int*)e);break;
		case 'f':*(float*)e = *(float*)Q->data[Q->front];printf("��ͷԪ�أ�%f\n",*(float*)e);break;
		case 'd':*(double*)e = *(double*)Q->data[Q->front];printf("��ͷԪ�أ�%lf\n",*(double*)e);break; 
		case 'c':*(char*)e = *(char*)Q->data[Q->front];printf("��ͷԪ�أ�%c\n",*(char*)e);break;
		case 's':*(char*)e = *(char*)Q->data[Q->front];printf("��ͷԪ�أ�%s\n",(char*)e);break;
	}
	return TRUE;
}		



/**
 *  @name        : int LengthAQueue(AQueue *Q)
 *  @description : ȷ�����г���
 *  @param       : Q ����ָ��Q
 *  @return      : ���г���count
 *  @notice      : None
 */
int LengthAQueue(AQueue *Q)
{
	return Q->length;
}	
/**
 *  @name        : Status EnAQueue(AQueue *Q, void *data)
 *  @description : ��Ӳ���
 *  @param       : Q ����ָ��Q,�������ָ��data
 *  @return      : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ����˻�Ϊ��
 */
Status EnAQueue(AQueue *Q, void *data)
{
	char d_type,temp;
	int i,len;
	if(!Q->data[0])
	{
		printf("����δ��ʼ����\n");
		return FALSE;
	}
	if(IsFullAQueue(Q))
	{
		printf("����������\n");
		return FALSE;
	}
	data = (void*)malloc(sizeof(void));
	choices();//�������ѡ�� 
	switch((temp = getch('a','d')))//����ѡ��ѡ���Ӧ����ֵ 
	{
		case 'a':d_type = datatype[Q->rear] = 'i';break;//int
		case 'b':d_type = datatype[Q->rear] = 'd';break;//double
		case 'c':d_type = datatype[Q->rear] = 'c';break;//char
		case 'd':d_type = datatype[Q->rear] = 's';break;//string
		default:printf("�������\n");return FALSE;
	}
	printf("���������ݣ�");
	if(!get_data(data,d_type))
	{
		return FALSE;
	}
	Q->length++;
	switch(temp)
	{
		case 'a':*(int*)Q->data[Q->rear] = *(int *)data;break;
		case 'b':*(double*)Q->data[Q->rear] = *(double*)data;break;
		case 'c':*(char*)Q->data[Q->rear] = *(char *)data;break;
		case 'd':strcpy((char*)Q->data[Q->rear],(char*)data);break;
	}
	Q->rear = (Q->rear+1)%MAXQUEUE;//ѭ������ 
	return TRUE;
}



/**
 *  @name        : Status DeAQueue(AQueue *Q)
 *  @description : ���Ӳ���
 *  @param       : Q ����ָ��Q
 *  @return      : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeAQueue(AQueue *Q)
{
	if(IsEmptyAQueue(Q))
	{
		return FALSE;	
	}		
	Q->length--;
	Q->front = (Q->front+1)%MAXQUEUE;
	return TRUE;
}	



/**
 *  @name        : void ClearAQueue(Queue *Q)
 *  @description : ��ն���
 *  @param       : Q ����ָ��Q
 *  @notice      : None
 */
void ClearAQueue(AQueue *Q)
{
	Q->length = Q->front = Q->rear = 0;
}	



/**
 *  @name        : Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
 *  @description : ������������
 *  @param       : Q ����ָ��Q����������ָ��foo
 *  @return      : None
 *  @notice      : None
 */
Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
{
	int i;
	if(IsEmptyAQueue(Q))
	{
		return FALSE;
	}
	i = Q->front;
	do
	{
		type = datatype[i];
		foo(Q->data[i]);
		i = (i+1)%MAXQUEUE;
	}while(i != Q->rear);
	printf("\b\b\b    \n");//�ÿո����ġ�->������ 
	return TRUE;		
}	


/**
 *  @name        : void APrint(void *q)
 *  @description : ��������
 *  @param       : q ָ��q
 *  @notice      : None
 */
void APrint(void *q)
{
	switch(type)
	{
		case 'i':printf("%d -> ",*(int*)q);break;
		case 'd':printf("%lf -> ",*(double*)q);break;
		case 'c':printf("%c -> ",*(char*)q);break;
		case 's':printf("%s -> ",(char*)q);break;
	}
}
