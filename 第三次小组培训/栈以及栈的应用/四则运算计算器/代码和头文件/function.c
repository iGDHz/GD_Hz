#define ERROR 0
#define TRUE 1 
typedef struct postfix
{
	double num[50];
	int data[100];//��data��Ϊ�洢���ݺͷ��ŵı�־ ��1��ʾ��λ������֣�0��ʾ��Ϊ�������� 
	char sign[50]; 
	int s_top;//�����ջ�� 
	int data_top;// ��׺���ʽջ�� 
	int num_top;//��ֵջ�� 
}Postfix;//�洢��׺���ʽ�� 

typedef struct stack
{
	double data[30];
	char sign[30];
	int top;
}stack;//����ʱ���õ�ջ 
/*
* ��ջ�Լ���ջ��������������������������������ݵĳ���ջ 
*/ 
//��ջ 
int push_sign(stack *L,char e)
{
	if(L->top == 30)
	{
		printf("Error!\n");
		return ERROR;
	}
	L->sign[L->top++] = e;
	return TRUE;
 } 
 int push_data(stack *L,double e)
 {
 	if(L->top == 30)
 	{
 		printf("Error!\n");
 		return ERROR;
	 }
	 L->data[L->top++] = e;
	 return TRUE;
 }
 
 //��ջ
int pop_sign(stack *L,char *e)
 {
 	if(L->top==0)	return ERROR;
 	*e = L->sign[--L->top]; 
 	return TRUE;
} 
int pop_data(stack *L,double *e)
 {
 	if(L->top==0)return ERROR;
 	*e = L->data[--L->top]; 
 	return TRUE;
}
