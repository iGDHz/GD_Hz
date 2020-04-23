#define ERROR 0
#define TRUE 1 
typedef struct postfix
{
	double num[50];
	int data[100];//以data作为存储数据和符号的标志 ，1表示该位存放数字，0表示该为存放运算符 
	char sign[50]; 
	int s_top;//运算符栈顶 
	int data_top;// 后缀表达式栈顶 
	int num_top;//数值栈顶 
}Postfix;//存储后缀表达式的 

typedef struct stack
{
	double data[30];
	char sign[30];
	int top;
}stack;//计算时所用的栈 
/*
* 入栈以及出栈函数都各设置俩个，用于运算符和数据的出入栈 
*/ 
//入栈 
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
 
 //出栈
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
