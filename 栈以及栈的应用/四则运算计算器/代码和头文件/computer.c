#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"function.c"
char getch(char from,char to);
void print_p(Postfix *p);//后缀表达式输出 
void calculate(Postfix *p,stack*s);//后缀表达式运算 
char next_sign(char *s,int i);//获取下一个字符 
int main()
{
	int i,len,flag,times,temp_i;
	double d1,temp;
	char ch;
	char str[50],str_temp[20];
	Postfix* p;
	stack* s;
	p = (Postfix*)malloc(sizeof(Postfix));//后缀表达式栈的建立 
	s = (stack*)malloc(sizeof(stack));//计算使用栈的距建立 
	p->data_top=p->num_top=p->s_top=0; 
	s->top = 0;
	times =0;
	flag = 1;//初始化 
	while(1)
	{
		printf("请输入：");
		gets(str);
		len = strlen(str);
		for(i=0;i<len;i++)
		{
			if(str[i] == ' ') continue;//输入中遇到空格直接跳至下一位读取 
			else if(str[i]>='0' && str[i]<='9' || ((i==0 || (i!=0 && str[i-1]=='(') || (i!=0 && str[i-1]==' ')) && str[i] == '-' && str[i+1]>='0' && str[i+1]<='9'))
			//数值的获取，读取负数只能在开头,数字前有括号,或用空格隔开时读取 
			{
				temp = atof(str+i);//temp存储转化后的数值 
				p->data[p->data_top++] = 1;//1表示此处为数字
				p->num[p->num_top++] = temp;
				if(str[i] == '-') i++;//跳过开头的负号 
				while(str[i]>='0' && str[i]<='9' || str[i] == '.') 
				{
					if(str[i] == '.') times++;//记录.出现的数字防止“12.22.33”类型的输入 
					i++;
				}//让str跳转至下一个位置 
				if(times>1) //.出现次数超过1次则报错并跳出循环 
				{
					flag = 0;
					break;
				}
				times = 0;
				i--;
			}
			else if(str[i] == ')')//遇到右括号出栈至‘（’ 
			{
				while(pop_sign(s,&ch))
				{
					if(ch == '(') break;
					else 
					{
						p->data[p->data_top++] = 0;//0为符号 
						p->sign[p->s_top++] = ch;
					}
				}
				if(ch!='(')//只有右括号没有左括号时报错 
				{
					flag = 0;
					break;
				}
			}
			else if(str[i] == '(') push_sign(s,str[i]);//左括号直接入栈 
			else if(next_sign(str,i+1) == 't')
			//输入运算符的下一个字符，防止 “+ + - *” 类型的重复输入 
			{
				flag = 0;
				break;
			}			
			else if(!s->top || str[i] == '(') push_sign(s,str[i]);//栈为空或为左括号时直接入栈
			else if(str[i] == '+' || str[i] == '-') 
			{
				while(pop_sign(s,&ch))//+-符号的优先级仅低于左括号 
				{
					if(ch == '(')
					{
						push_sign(s,ch); //仅左括号运算符低于+ - ，此处将删除的+ - 重新存入 
						break;	
					}	
					else 
					{
						p->data[p->data_top++] = 0;//字符存入 
						p->sign[p->s_top++] = ch;
					} 
				}
				push_sign(s,str[i]);//出栈后再将运算符存入 
			 }
			 else if(str[i] == '/' || str[i]=='*') 
			{
				while(pop_sign(s,&ch))
				{
					if(ch == '/' || ch == '*')//乘除运算符优先级最高，仅当同等级时才入栈 
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
				printf("输入错误！\n");
				flag = 0;
				break;
			}	
		}
		if(s->top) //将栈内元素清空 
		while(pop_sign(s,&ch))
		{
			if(ch == '(')
			{
				printf("输入错误!\n");
				flag = 0;
				break;
			}
			p->data[p->data_top++] = 0;
			p->sign[p->s_top++] = ch;
		}
		if(flag) 
		{
		print_p(p);//后缀表达式输出 
		calculate(p,s);//计算结果输出 
		}
		printf("输入'y'退出，任意键继续...\n");
		if((getch('y','y'))=='y') break;
		p->data_top=p->num_top=p->s_top=0;
		s->top = 0;
		times =0;
		flag = 1;//重新初始化 
	}
	return 0;
}
char getch(char from,char to)//用户选择输入（字符串读取后返回有效选择功能，范围从from到to） 
{
	char str[50];
	int i,len;
	gets(str);//字符串读取 
	len = strlen(str);
	for(i = 0; i<len; i++) { 
		if(str[i]>=from && str[i]<=to) return str[i];//遇到有效选项直接返回 
	}
	return str[len-1];//访问完之后查找不到有效数字直接返回最后数字 
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
					printf("非法除0操作!\n");
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
