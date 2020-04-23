#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"LinkStack.c" 
char getch(char from,char to);
Status get_data(ElemType *e);
void option(LinkStack *s,char ch);
void tips();
int main()
{ 
	LinkStack *s = (LinkStack*)malloc(sizeof(LinkStack));
	int flag,times; 
	char ch;
	flag = times = 0;
	if(!s)
	{
		printf("�ڴ����ʧ�ܣ����ڳ������³�ʼ��...\n\n");
		if((times++) >= 10) exit(EXIT_FAILURE);
		s = (LinkStack*)malloc(sizeof(LinkStack));
	}
	s->count = 0;
	s->top = NULL;
	tips();
	while(1)
	{
		while((ch = getch('a','i'))!='i')
		{
			printf("���ѡ���ǣ�%c\n",ch); 
			if(ch == 'a')
			{
				if(initLStack(s)) printf("��ʼ���ɹ�!\n");
				else printf("��ʼ��ʧ��!\n");
			}
			else if(ch>='b' && ch<='h')
			{
				option(s,ch);
			}
			else flag = 1;
			if(flag)
			{
				flag = 0;
				printf("����������ʽ!����������\n");
				printf("��ѡ��:");
			}
			else break;
		}
		if(ch == 'i') break;
		system("pause");
		system("cls");
		tips();
	 } 
	destroyLStack(s);
	free(s);
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
	printf("��ѡ��:");
}
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
void option(LinkStack *s,char ch)
{
	int data,data_pop,data_top,s_length;
	LinkStackPtr temp;
	if(!s->top)
	{
		printf("ջδ��ʼ�������ȳ�ʼ��!\n");
		return ; 
	} 
	switch(ch)
	{
		case 'b':
		{
			if(isEmptyLStack(s)) printf("ջΪ�գ�\n");
			else printf("ջΪ�ǿ�!\n");
			break;
		}
		case 'c':
		{
			printf("����Ҫ��������ݣ�");//ѭ���������ݣ���ֹ�����ʽ������ 
			while(!get_data(&data))
			{
				printf("����'y'�����������ݣ����������!\n");
				if(getch('y','y')!='y') return;
				printf("����Ҫ��������ݣ�");
			}
			if(pushLStack(s,data)) 
			{
				s->count++;//ջԪ�صļ�¼ 
				printf("��ջ�ɹ���\n");
			}
			else printf("��ջʧ�ܣ�\n");
			break;
		}
		case 'd':
		{
			if(!s->count) printf("��ջ�޷����г�ջ������\n");
			else
			{
				if(popLStack(s,&data)) 
				{
					printf("%d��ջ�ɹ���\n",data);
					s->count--;
				}
				else printf("��ջʧ��!\n"); 
			}
			break;
		 } 
		case 'e':
		{
			if(getTopLStack(s,&data_top))
			{
				printf("ջ��Ԫ�أ�%d\n",data_top);
				return ;	
			}	
			printf("ջΪ�գ���ջ��Ԫ��!\n");
			break;
		} 
		case 'f':
		{
			if(LStackLength(s,&s_length))
			{
				printf("ջ�ĳ���Ϊ:%d\n",s_length);	
			}	
			else printf("ջΪ��!\n");
			break;
		} 
		case 'g':
		{
			if(clearLStack(s))
			{
				printf("����ɹ�!\n");
				return ;
			}
			printf("��ջ����Ҫ���!\n");
			break;
		}
		case 'h':
		{
			if(!s->count) 
			{
				printf("ջΪ��!\n");
				return;
			}
			temp = s->top;
			while(temp)
			{
				printf("%d  ",temp->data);
				temp = temp->next;
			}
			printf("\n");
			break;
		}
	}
}
