#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"SqStack.c"
void tips();//操作指南 
char getch(char from,char to);//返回输入字符串中从from到to的字符 
Status get_data(ElemType *e);//数据的获取（防止非格式输入以及int型数据的溢出） 
void init(SqStack *s);//栈的初始化 
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
		printf("内存分配失败，正在退出...");
		system("pause");
		exit(EXIT_FAILURE);
	}
	tips();
	while(1)
	{
		while((ch = getch('a','i'))!='i')
		{
			printf("你的选择是:%c\n",ch); 
			if(ch == 'a') init(s);
			else if(ch >= 'b' && ch <='h') option(s,ch);//此处因为除了初始化外均要判断是否初始化，所以用if,else语句 
			else flag = 1;
			if(flag)
			{
				flag = 0; 
				printf("输入错误，请重新输入\n");
				printf("输入你的选择：");
			}
			else break;
		}
		if(ch == 'i') break;
		system("pause");
		system("cls");//刷新界面 
		tips();
	}
	destroyStack(s);
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
	printf("输入你的选择:");
}
char getch(char from,char to)//用户选择输入（字符串读取后返回有效选择功能，范围从from到to） 
{
	char str[50];
	int i,len;
	gets(str);//字符串读取 
	len  = strlen(str);
	for(i = 0; i<len; i++) {
		if(str[i]>=from && str[i]<=to) return str[i];//遇到有效选项直接返回 
	}
	return str[i];//访问完之后查找不到有效数字直接返回最后数字 
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
void init(SqStack *s)
{
 	int size,times = 0;
 	printf("输入建立栈的大小：");
 	while(!get_data(&size))
	{
		printf("（按'y'继续输入，任意键退出）\n");
		if(getch('y','y') != 'y') return ; 
		printf("输入建立栈的大小：");
	} 
 	if(!initStack(s,size)) return ;
	 printf("初始化成功!\n");
 } 
void option(SqStack *s,char ch)//由于push与pop中data类型不同，所以不使用函数指针 
{
	int data,data_pop,data_top,stack_length;
	if(!s->elem)
	{
		printf("栈未初始化，请先初始化!\n");
		return ;
	}
	switch(ch)
	{
	case 'b':
	{
		if(isEmptyStack(s)) printf("这是一个空栈\n");
		else printf("这不是一个空栈\n");
		break;
	}
	case 'c'://option为1时执行入栈操作，为0时执行出栈操作 
	{
		printf("输入要入栈的数据:");
		while(!get_data(&data))
		{
			printf("输入'y'重新输入，任意键退出！\n");
			if(getch('y','y') != 'y') return;
			if(option) printf("输入要入栈的数据:");
	 	} 
	 	if(pushStack(s,data)) printf("入栈成功！\n");
	 	break;
	}
	case 'd':
	{
		if(popStack(s,&data_pop)) printf("%d 成功出栈！\n",data_pop);
		break;
	}
	case 'e':
	{
		if(getTopStack(s,&data_top)) printf("栈顶元素：%d\n",data_top);
		else printf("栈为空！无栈顶数据\n");
		break;	
	}
	case 'f':
	{
		if(stackLength(s,&stack_length)) printf("栈的长度为%d\n",stack_length);
		else printf("获取栈长度失败!\n");
		break;
	}
	case 'g':
	{
		if(clearStack(s)) printf("清空成功！\n");
		else printf("栈为空，不需要进行清空操作!\n");
		break;
	}
	case 'h':
	{
		if(s->top == -1) printf("栈为空！\n");
		else print(s);
	}
	}
}
