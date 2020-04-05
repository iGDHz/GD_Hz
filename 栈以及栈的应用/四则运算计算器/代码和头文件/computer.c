#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"function.c"
char getch(char from,char to);
void print_p(Postfix *p);//��׺���ʽ��� 
void calculate(Postfix *p,stack*s);//��׺���ʽ���� 
char next_sign(char *s,int i);//��ȡ��һ���ַ� 
int main()
{
	int i,len,flag,times,temp_i;
	double d1,temp;
	char ch;
	char str[50],str_temp[20];
	Postfix* p;
	stack* s;
	p = (Postfix*)malloc(sizeof(Postfix));//��׺���ʽջ�Ľ��� 
	s = (stack*)malloc(sizeof(stack));//����ʹ��ջ�ľཨ�� 
	p->data_top=p->num_top=p->s_top=0; 
	s->top = 0;
	times =0;
	flag = 1;//��ʼ�� 
	while(1)
	{
		printf("�����룺");
		gets(str);
		len = strlen(str);
		for(i=0;i<len;i++)
		{
			if(str[i] == ' ') continue;//�����������ո�ֱ��������һλ��ȡ 
			else if(str[i]>='0' && str[i]<='9' || ((i==0 || (i!=0 && str[i-1]=='(') || (i!=0 && str[i-1]==' ')) && str[i] == '-' && str[i+1]>='0' && str[i+1]<='9'))
			//��ֵ�Ļ�ȡ����ȡ����ֻ���ڿ�ͷ,����ǰ������,���ÿո����ʱ��ȡ 
			{
				temp = atof(str+i);//temp�洢ת�������ֵ 
				p->data[p->data_top++] = 1;//1��ʾ�˴�Ϊ����
				p->num[p->num_top++] = temp;
				if(str[i] == '-') i++;//������ͷ�ĸ��� 
				while(str[i]>='0' && str[i]<='9' || str[i] == '.') 
				{
					if(str[i] == '.') times++;//��¼.���ֵ����ַ�ֹ��12.22.33�����͵����� 
					i++;
				}//��str��ת����һ��λ�� 
				if(times>1) //.���ִ�������1���򱨴�����ѭ�� 
				{
					flag = 0;
					break;
				}
				times = 0;
				i--;
			}
			else if(str[i] == ')')//���������ų�ջ�������� 
			{
				while(pop_sign(s,&ch))
				{
					if(ch == '(') break;
					else 
					{
						p->data[p->data_top++] = 0;//0Ϊ���� 
						p->sign[p->s_top++] = ch;
					}
				}
				if(ch!='(')//ֻ��������û��������ʱ���� 
				{
					flag = 0;
					break;
				}
			}
			else if(str[i] == '(') push_sign(s,str[i]);//������ֱ����ջ 
			else if(next_sign(str,i+1) == 't')
			//�������������һ���ַ�����ֹ ��+ + - *�� ���͵��ظ����� 
			{
				flag = 0;
				break;
			}			
			else if(!s->top || str[i] == '(') push_sign(s,str[i]);//ջΪ�ջ�Ϊ������ʱֱ����ջ
			else if(str[i] == '+' || str[i] == '-') 
			{
				while(pop_sign(s,&ch))//+-���ŵ����ȼ������������� 
				{
					if(ch == '(')
					{
						push_sign(s,ch); //�����������������+ - ���˴���ɾ����+ - ���´��� 
						break;	
					}	
					else 
					{
						p->data[p->data_top++] = 0;//�ַ����� 
						p->sign[p->s_top++] = ch;
					} 
				}
				push_sign(s,str[i]);//��ջ���ٽ���������� 
			 }
			 else if(str[i] == '/' || str[i]=='*') 
			{
				while(pop_sign(s,&ch))
				{
					if(ch == '/' || ch == '*')//�˳���������ȼ���ߣ�����ͬ�ȼ�ʱ����ջ 
					{
						p->data[p->data_top++] = 0;
						p->sign[p->s_top++] = ch;
					}
					else 
					{
						push_sign(s,ch);
						break;
					}
				}
				push_sign(s,str[i]);	
			}
			else
			{
				printf("�������\n");
				flag = 0;
				break;
			}	
		}
		if(s->top) //��ջ��Ԫ����� 
		while(pop_sign(s,&ch))
		{
			if(ch == '(')
			{
				printf("�������!\n");
				flag = 0;
				break;
			}
			p->data[p->data_top++] = 0;
			p->sign[p->s_top++] = ch;
		}
		if(flag) 
		{
		print_p(p);//��׺���ʽ��� 
		calculate(p,s);//��������� 
		}
		printf("����'y'�˳������������...\n");
		if((getch('y','y'))=='y') break;
		p->data_top=p->num_top=p->s_top=0;
		s->top = 0;
		times =0;
		flag = 1;//���³�ʼ�� 
	}
	return 0;
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
void print_p(Postfix *p)
{
	int i,j,k;
	j = k = 0;
	for(i=0;i<p->data_top;i++)
	{
		if(p->data[i]) printf("%.2lf ",p->num[j++]);
		else printf("%c ",p->sign[k++]);
	}
}
void calculate(Postfix *p,stack*s)
{
	int i,j,k;
	double a,b,result;
	i = j = k = 0;
	for(;i<p->data_top;i++)
	{
		if(p->data[i]) push_data(s,p->num[j++]);
		else
		{
			pop_data(s,&b);
			pop_data(s,&a);
			switch(p->sign[k++])
			{
				case '+':push_data(s,a+b);break;
				case '*':push_data(s,a*b);break;
				case '/':if(b == 0)
				{
					printf("�Ƿ���0����!\n");
					return ;
				}push_data(s,a/b);break;
				case '-':push_data(s,a-b);break;
			}
		}
	}
	pop_data(s,&result);
	printf(" = %.2lf\n",result);
}
char next_sign(char *s,int i)
{
	for(;s[i]!='\0';i++)
	{
		if((s[i] == '+' || s[i] =='-' || s[i] == '*' || s[i] == '/' ) && (s[i+1]<'0' || s[i+1]>'9'))
		return 't';
		else if(s[i+1]<'0' || s[i+1]>'9') return 'f';
	}
	return 'f';
}
