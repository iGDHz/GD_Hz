#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../head/linkedList.h"
extern void print_int(ElemType e);
void tip()//功能面板展示 
{
	printf("|————1.Add node           ————|\n");
	printf("|————2.Traverse list      ————|\n");
	printf("|————3.Reverse list       ————|\n");
	printf("|————4.ReverseEvenList    ————|\n");
	printf("|————5.Insert list        ————|\n");
	printf("|————6.Delete list        ————|\n");
	printf("|————7.IsLoopList         ————|\n");
	printf("|————8.Retrun middle node ————|\n");
	printf("|————9.EXIT               ————|\n\n");
	printf("input:");
}
char getch()//用户选择输入（字符串读取后返回有效选择功能） 
{
	char str[50];
	int i;
	gets(str);//字符串读取 
	for(i = 0; i<strlen(str); i++) {
		if(str[i]>='1' &&str[i]<='9') return str[i];//遇到有效数字直接返回 
	}
	return str[i];//访问完之后查找不到有效数字直接返回最后数字 
}
Status get_data(ElemType *e)//数据输入（防滚键盘） 
{
	char ch[30];
	int flag,i;
	*e = 0;
	flag = i = 0;
	gets(ch);
	while(ch[i]!='\0')
	{
		if((flag ||ch[i]!='-')&&(ch[i]<'0' || ch[i]>'9'))
		{
			printf("Unformatted input!\n");
			return ERROR;
		} 
		else if(ch[i] == '-' && (ch[i]>='0' || ch[i]<='9')) flag = 1; 
		else
		{
			(*e) =(*e)*10+ch[i]-'0';
		}
		i++;
	 } 
	if(flag)  *e = (*e) * (-1);
	 return SUCCESS;
 } 
int main() {
	LinkedList L;
	char ch;
	int flag = 1;
	if(!InitList(&L)) exit(EXIT_FAILURE);//链表的初始化 
	tip();
	while(1) {
		while((ch = getch())!='9') 
		{
			printf("Your choice:%c\n",ch);//输出有效输入 
			switch(ch) {		
				case '1': {
					if(!LNode_add(L)) printf("Add failure!\n");//添加失败返回错误信息 
					else printf("Successfully added!\n");//返回成功添加的信息 
					break;
				}
				case '2': {
					TraverseList(L,print_int);//遍历链表用print_int的方式输出链表数据 
					break;
				}
				case '3': {
					if(!ReverseList(&L)) printf("Reverse error!\n");//链表转置失败返回错误信息 
					else printf("Reverse success!\n");//返回转置成功信息 
					break;
				}
				case '4': {
					L = ReverseEvenList(&L);//实现链表的奇偶数的转置 
					printf("ReverseEven success!\n");//转置成功 
					break;
				}
				case '5': {
					Search(&L);//查找并在节点后插入新节点 
					break;
				}
				case '6': {
					Delete(&L);//查找并删除节点 
					break;
				}
				case '7': {
					if(IsLoopList(L->next)) printf("This is a loop list.\n"); 
					else printf("This is not a loop list.\n");
					break;//返回是否为成环链表信息 
				}
				case '8': {
					TraverseList(L,print_int);//显示链表所有数据 
					printf("%d\n",(FindMidNode(&L))->data);//输出链表中间数据 
					break;
				}
				case '9':break;//无如何操作 
				default:flag = 0;//判断是否为正常输入 
				break; 
			}
			if(!flag) {
				flag = 1;
				printf("Error format input！\n");//错误输入提示 
				printf("input:");
			} else break;//正常输入时跳出循环刷新界面 
		}
		if(ch == '9') break;//跳出循环结束程序 
		system("pause");
		system("cls");
		tip();
	}
	DestroyList(&L);//销毁链表 
	return 0;
}
