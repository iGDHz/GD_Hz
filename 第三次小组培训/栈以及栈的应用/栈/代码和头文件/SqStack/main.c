#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"SqStack.c"
void tips();//����ָ�� 
char getch(char from,char to);//���������ַ����д�from��to���ַ� 
Status get_data(ElemType *e);//���ݵĻ�ȡ����ֹ�Ǹ�ʽ�����Լ�int�����ݵ������ 
void init(SqStack *s);//ջ�ĳ�ʼ�� 
void option(SqStack *s,char ch); 
void print(SqStack *s)
{
	int i = 0 ;
	for(;i<=s->top;i++)
	{
		printf("%d  ",*(s->elem+i));
	}
	printf("\n"); 
}
int main()
{
	char ch;
	int data,temp,flag= 0;
	SqStack *s = (SqStack*)malloc(sizeof(SqStack));
	s->elem = NULL;
	if(!s)
	{
		printf("�ڴ����ʧ�ܣ������˳�...");
		system("pause");
		exit(EXIT_FAILURE);
	}
	tips();
	while(1)
	{
		while((ch = getch('a','i'))!='i')
		{
			printf("���ѡ����:%c\n",ch); 
			if(ch == 'a') init(s);
			else if(ch >= 'b' && ch <='h') option(s,ch);//�˴���Ϊ���˳�ʼ�����Ҫ�ж��Ƿ��ʼ����������if,else��� 
			else flag = 1;
			if(flag)
			{
				flag = 0; 
				printf("�����������������\n");
				printf("�������ѡ��");
			}
			else break;
		}
		if(ch == 'i') break;
		system("pause");
		system("cls");//ˢ�½��� 
		tips();
	}
	destroyStack(s);
	return 0;
}
void tips()
{
	printf("|��������a.��ʼ��ջ      ��������|\n");
	printf("|��������b.�ж��Ƿ�Ϊ��ջ��������|\n");
	printf("|��������c.��ջ          ��������|\n");
	printf("|��������d.��ջ          ��������|\n"); 
	printf("|��������e.��ȡջ������  ��������|\n");
	printf("|��������f.��ʾջ�ĳ���  ��������|\n");
	printf("|��������g.���ջ        ��������|\n");
	printf("|��������h.��ʾջ��Ԫ��  ��������|\n");
	printf("|��������i.�˳�          ��������|\n"); 
	printf("�������ѡ��:");
}
char getch(char from,char to)//�û�ѡ�����루�ַ�����ȡ�󷵻���Чѡ���ܣ���Χ��from��to�� 
{
	char str[50];
	int i,len;
	gets(str);//�ַ�����ȡ 
	len  = strlen(str);
	for(i = 0; i<len; i++) {
		if(str[i]>=from && str[i]<=to) return str[i];//������Чѡ��ֱ�ӷ��� 
	}
	return str[i];//������֮����Ҳ�����Ч����ֱ�ӷ���������� 
}
Status get_data(ElemType *e)//�������루�������̣� 
{
	char ch[30];
	int flag,i,len;
	long long int result;
	result = 0,i = 0,flag = 1;
	len = strlen(ch); 
	gets(ch);
	if(ch[i] == '-')//�ж������Ƿ�Ϊ���� 
	{
		flag = -1;
		i++; 
	}
	while(ch[i])
	{
		if(ch[i]<'0' || ch[i]>'9') 
		{
			printf("�����ʽ����!\n");
			return ERROR;
		}
		else if(result < -2147483648LL || result > 2147483647LL)//�ж��Ƿ������������ 
		{  
			printf("���������\n");
			return ERROR;
		}
		result = result*10 + ch[i] - '0';
		i++;		
	}
	*e = (int)result * flag;//flag�ж����� 
	return SUCCESS;
 } 
void init(SqStack *s)
{
 	int size,times = 0;
 	printf("���뽨��ջ�Ĵ�С��");
 	while(!get_data(&size))
	{
		printf("����'y'�������룬������˳���\n");
		if(getch('y','y') != 'y') return ; 
		printf("���뽨��ջ�Ĵ�С��");
	} 
 	if(!initStack(s,size)) return ;
	 printf("��ʼ���ɹ�!\n");
 } 
void option(SqStack *s,char ch)//����push��pop��data���Ͳ�ͬ�����Բ�ʹ�ú���ָ�� 
{
	int data,data_pop,data_top,stack_length;
	if(!s->elem)
	{
		printf("ջδ��ʼ�������ȳ�ʼ��!\n");
		return ;
	}
	switch(ch)
	{
	case 'b':
	{
		if(isEmptyStack(s)) printf("����һ����ջ\n");
		else printf("�ⲻ��һ����ջ\n");
		break;
	}
	case 'c'://optionΪ1ʱִ����ջ������Ϊ0ʱִ�г�ջ���� 
	{
		printf("����Ҫ��ջ������:");
		while(!get_data(&data))
		{
			printf("����'y'�������룬������˳���\n");
			if(getch('y','y') != 'y') return;
			if(option) printf("����Ҫ��ջ������:");
	 	} 
	 	if(pushStack(s,data)) printf("��ջ�ɹ���\n");
	 	break;
	}
	case 'd':
	{
		if(popStack(s,&data_pop)) printf("%d �ɹ���ջ��\n",data_pop);
		break;
	}
	case 'e':
	{
		if(getTopStack(s,&data_top)) printf("ջ��Ԫ�أ�%d\n",data_top);
		else printf("ջΪ�գ���ջ������\n");
		break;	
	}
	case 'f':
	{
		if(stackLength(s,&stack_length)) printf("ջ�ĳ���Ϊ%d\n",stack_length);
		else printf("��ȡջ����ʧ��!\n");
		break;
	}
	case 'g':
	{
		if(clearStack(s)) printf("��ճɹ���\n");
		else printf("ջΪ�գ�����Ҫ������ղ���!\n");
		break;
	}
	case 'h':
	{
		if(s->top == -1) printf("ջΪ�գ�\n");
		else print(s);
	}
	}
}
