#include"../head/LinkStack.h"

Status initLStack(LinkStack *s)//��ʼ��ջ
{
	s->top = (LinkStackPtr)malloc(sizeof(StackNode));
	if(!s->top) return ERROR;
	s->top->next = NULL;
	return SUCCESS;		
 } 

Status isEmptyLStack(LinkStack *s)//�ж�ջ�Ƿ�Ϊ��
{
	if(s->count) return ERROR;
	return SUCCESS;
}

Status getTopLStack(LinkStack *s,ElemType *e)//�õ�ջ��Ԫ��
{
	if(s->count)
	{
		*e = s->top->data;
		return SUCCESS;
	}
	return ERROR;
}
Status clearLStack(LinkStack *s)//���ջ
{
	if(s->count)
	{
		destroyLStack(s);//��ջȫ�����ٺ����³�ʼ�� 
		initLStack(s);
		return SUCCESS;
	}
	else return ERROR;
}
Status destroyLStack(LinkStack *s)//����ջ
{
	LinkStackPtr S2,S1;
	if(!s) return ERROR; 
	S2=S1=s->top;//S1ʼ��ָ��ǰ�ڵ㣬S2ָ����һ�ڵ㣬�����ͷ� 
	while(S1)
	{
		S2 = S1->next;
		free(S1);
		S1 = S2;
	}
	return SUCCESS;
}
Status LStackLength(LinkStack *s,int *length)//���ջ����
{
	if(s->count && length!=NULL)
	//����ǰ���Ѿ���s���й��жϣ����Դ˴�ֻ�ж�length�Ƿ�Ϊ����ջ�Ƿ�Ϊ�� 
	{
		*length = s->count;
		return SUCCESS;
	}
	return ERROR;
}
Status pushLStack(LinkStack *s,ElemType data)//��ջ
{
	LinkStackPtr new_Node,top = s->top;
	if(s->count == 0) 
	{
		top->data = data;
		return SUCCESS;
	}
	new_Node = (LinkStackPtr)malloc(sizeof(StackNode));//�����½ڵ� 
	if(!new_Node)
	{
		printf("�ڵ㽨��ʧ��!\n");
		return ERROR;	
	}		
	new_Node->next = s->top;
	new_Node->data = data;
	s->top = new_Node;//���½ڵ���Ϊͷ�ڵ���� 
	return SUCCESS; 
}
Status popLStack(LinkStack *s,ElemType *data)//��ջ
{
	LinkStackPtr top = s->top;
	if(!data) return ERROR;//����ǰ���Ѿ���s�Ƿ�Ϊ�ս������ж������Դ˴�dataΪΨһ�Ŀ��ܳ���ĵط� 
	*data = top->data;
	s->top = top->next;
	free(top);
	if(!s->top)//��ֹȫ��ɾ��ʱ�ع�δ��ʼ����״̬
	initLStack(s);
	return SUCCESS; 
}
