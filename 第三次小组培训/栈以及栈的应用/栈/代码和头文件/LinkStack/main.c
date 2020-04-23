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
		printf("内存分配失败，正在尝试重新初始化...\n\n");
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
			printf("你的选择是：%c\n",ch); 
			if(ch == 'a')
			{
				if(initLStack(s)) printf("初始化成功!\n");
				else printf("初始化失败!\n");
			}
			else if(ch>='b' && ch<='h')
			{
				option(s,ch);
			}
			else flag = 1;
			if(flag)
			{
				flag = 0;
				printf("错误的输入格式!请重新输入\n");
				printf("请选择:");
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
	printf("|————a.初始化栈      ————|\n");
	printf("|————b.判断是否为空栈————|\n");
	printf("|————c.入栈          ————|\n");
	printf("|————d.出栈          ————|\n"); 
	printf("|————e.获取栈顶数据  ————|\n");
	printf("|————f.显示栈的长度  ————|\n");
	printf("|————g.清空栈        ————|\n");
	printf("|————h.显示栈内元素  ————|\n");
	printf("|————i.退出          ————|\n"); 
	printf("请选择:");
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
Status get_data(ElemType *e)//数据输入（防滚键盘） 
{
	char ch[30];
	int flag,i,len;
	long long int result;
	result = 0,i = 0,flag = 1;
	len = strlen(ch); 
	gets(ch);
	if(ch[i] == '-')//判断输入是否为负数 
	{
		flag = -1;
		i++; 
	}
	while(ch[i])
	{
		if(ch[i]<'0' || ch[i]>'9') 
		{
			printf("输入格式错误!\n");
			return ERROR;
		}
		else if(result < -2147483648LL || result > 2147483647LL)//判断是否会造成数据溢出 
		{  
			printf("数据溢出！\n");
			return ERROR;
		}
		result = result*10 + ch[i] - '0';
		i++;		
	}
	*e = (int)result * flag;//flag判断正负 
	return SUCCESS;
 } 
void option(LinkStack *s,char ch)
{
	int data,data_pop,data_top,s_length;
	LinkStackPtr temp;
	if(!s->top)
	{
		printf("栈未初始化，请先初始化!\n");
		return ; 
	} 
	switch(ch)
	{
		case 'b':
		{
			if(isEmptyLStack(s)) printf("栈为空！\n");
			else printf("栈为非空!\n");
			break;
		}
		case 'c':
		{
			printf("输入要插入的数据：");//循环输入数据，防止错误格式的输入 
			while(!get_data(&data))
			{
				printf("输入'y'继续输入数据，任意键结束!\n");
				if(getch('y','y')!='y') return;
				printf("输入要插入的数据：");
			}
			if(pushLStack(s,data)) 
			{
				s->count++;//栈元素的记录 
				printf("入栈成功！\n");
			}
			else printf("入栈失败！\n");
			break;
		}
		case 'd':
		{
			if(!s->count) printf("空栈无法进行出栈操作！\n");
			else
			{
				if(popLStack(s,&data)) 
				{
					printf("%d出栈成功！\n",data);
					s->count--;
				}
				else printf("出栈失败!\n"); 
			}
			break;
		 } 
		case 'e':
		{
			if(getTopLStack(s,&data_top))
			{
				printf("栈顶元素：%d\n",data_top);
				return ;	
			}	
			printf("栈为空，无栈顶元素!\n");
			break;
		} 
		case 'f':
		{
			if(LStackLength(s,&s_length))
			{
				printf("栈的长度为:%d\n",s_length);	
			}	
			else printf("栈为空!\n");
			break;
		} 
		case 'g':
		{
			if(clearLStack(s))
			{
				printf("清除成功!\n");
				return ;
			}
			printf("空栈不需要清除!\n");
			break;
		}
		case 'h':
		{
			if(!s->count) 
			{
				printf("栈为空!\n");
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
