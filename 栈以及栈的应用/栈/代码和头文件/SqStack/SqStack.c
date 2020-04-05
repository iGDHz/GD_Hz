#include"../head/SqStack.h"

Status initStack(SqStack *s,int sizes)//��ʼ��ջ
{
	if(!s->elem) clearStack(s);//ջ����ʱ��ջ���и�ʽ�� 
	if(sizes <= 0 )
	{
		printf("�޷�����һ������С�ڵ���0��ջ\n");
		return ERROR;
	}
	s->elem = (int*)malloc(sizeof(int)*sizes);
	if(!s->elem) return ERROR;
	s->top = -1;//��ʼ��Ϊ��ջ 
	s->size = sizes;
	return SUCCESS;
}


Status isEmptyStack(SqStack *s)//�ж�ջ�Ƿ�Ϊ��
{
	if(s->top == -1) return SUCCESS;//ֱ�Ӱ��հ�ջ�ĳ����ж� 
	return ERROR;
}
Status getTopStack(SqStack *s,ElemType *e) //�õ�ջ��Ԫ��
{
	if(s->top == -1) return ERROR;//ջΪ���޷���ȡջ��Ԫ�� 
	*e = *(s->elem + s->top);
	return SUCCESS;
}
Status clearStack(SqStack *s)//���ջ
{
	if(s->top == -1) return ERROR; 
	s->top = -1;//ֱ����top��ֵΪ-1��Ϊ��ջ�Ĳ��� 
	return SUCCESS;
}
Status destroyStack(SqStack *s)//����ջ
{
	if(!s) return ERROR;//�������������Ѿ�ȷ��s��Ϊ��ָ�룬���Դ˺���ֻ�ܷ���SUCCESS 
	free(s);
	return SUCCESS;
}
Status stackLength(SqStack *s,int *length)//���ջ����
{
	if(!length) return ERROR;
	*length = s->size;
	return SUCCESS;
}
Status pushStack(SqStack *s,ElemType data)//��ջ
{
	if(s->top == s->size-1)
	{
		printf("ջ��������ջʧ��!\n");
		return ERROR;
	}
	s->top++;
	*(s->elem + s->top) = data;
	return SUCCESS;
}
Status popStack(SqStack *s,ElemType *data)//��ջ
{
	if(s->top == -1)
	{
		printf("ջΪ�գ���ջʧ��!\n");
		return ERROR; 
	}
	*data = *(s->elem + s->top);
	s->top--;
	return SUCCESS;
}

