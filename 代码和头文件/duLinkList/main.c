#include<stdio.h>
#include<stdlib.h>
#include"duLinkedList.c"
#include<string.h>
char getch(); 
Status get_data(); //自制输入（减少异常输入时造成的问题）
void tips();//说明事项输出 
Status search(DuLinkedList L,ElemType e);//返回是否查找到对应节点 

//用函数指针在不同的插入情况调用不同的函数 
void qInsert(DuLinkedList L,Status (*insert)(DuLNode*, DuLNode* )); 

//节点删除操作 
void Delete(DuLinkedList L);

//新节点的建立此处为q节点的建立 
Status DuLNode_creat(DuLinkedList *L);
int main()
 {	char ch;
 	int flag,data;
 	DuLinkedList L,q;
 	flag = data = 0;
	while(!InitList_DuL(&L))
	{
		printf("初始化失败！\n");
		printf("尝试重新初始化...\n");
		if((data++) == 10) //多次初始化失败后直接退出程序 
		{
			printf("初始化失败！正在退出程序！\n");
			system("pause");
		}
	 } 
	tips();
 	while(1)//使用二重循环刷新界面 
 	{
 		while((ch = getch())!='f')
 		{
 			printf("你的选择：%c\n",ch);
 			switch(ch)
 			{
 				case 'a':{if(!DuLNode_creat(&q)) break;
 					else 
 					{
 						//直接调用 InsertAfterList_DuL函数减少再设置添加操作 
					 	InsertAfterList_DuL(L,q);
					 	L->data++;//头节点记录节点个数 
					 	printf("输入成功!\n"); 
					 } 
					break;
				 }
				case 'b':qInsert(L,InsertBeforeList_DuL);L->data++;break;
				case 'c':qInsert(L,InsertAfterList_DuL);L->data++;break;
				case 'd':TraverseList_DuL(L->next,print_int);break;
				case 'e':Delete(L);L->data;break;
				case 'f':break;
				default:flag=1;break;
			 }
			if(flag)
		 	{
		 		flag = 0 ;
		 		printf("输入格式错误\n请重新输入:");
		 	}//输入格式错误时发出提醒并重新输入 
		 	else break;//正确格式输入后刷新界面 
		 }
		if(ch == 'f') break;
		system("pause");
		system("cls");
		tips();
	 }
	 DestroyList_DuL(&L);
 	return 0;
 }
 void tips()
{
	printf("|————a.添加节点       ————|\n");	
	printf("|————b.p节点前插入节点————|\n");	
	printf("|————c.p节点后插入节点————|\n");	
	printf("|————d.输出链表       ————|\n");	
	printf("|————e.删除节点       ————|\n");
	printf("|————f.退出           ————|\n\n");
	printf("输入:");				
}
char getch()//用户选择输入（字符串读取后返回有效选择功能） 
{
	char str[50];
	int i;
	gets(str);//字符串读取 
	for(i = 0; i<strlen(str); i++) {
		if(str[i]>='a' &&str[i]<='f') return str[i];//遇到有效数字直接返回 
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
			printf("非格式输入!退回主界面...\n");
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
Status DuLNode_creat(DuLinkedList *L)
{
	*L = (DuLinkedList)malloc(sizeof(DuLNode));
	if(!(*L)) 
	{
		printf("节点建立失败!\n");
		return ERROR;
	 } 
	printf("输入数据："); 
	while(!(get_data(&(*L)->data))) 
	{
		printf("输入'a'重新输入数据（任意值退出）\n");
		if(getch() != 'a') return ERROR;
		printf("输入数据："); 
	}
}
Status search(DuLinkedList L,ElemType e)
{
	while(L)
	{
		if(L->data == e) 	return SUCCESS;
		L=L->next;
	}
	return ERROR;
}
void qInsert(DuLinkedList L,Status (*insert)(DuLNode*, DuLNode* ))
{
	DuLinkedList q,p;
	int data;
	TraverseList_DuL(L->next,print_int);//先将链表遍历后输出供用户选择 
	if(!L->next) 
	{
		printf("该链表为空，请添加节点后使用!\n");
		return ;
	}
	printf("选择p节点...\n");
	printf("输入p节点：");
	if(!get_data(&data)) return; 
	while(!(search(L,data)))//输入错误时循环输入，也可选择退出 
	{
		printf("查找不到p节点，输入'a'继续查找，任意值退出...\n");
		if((getch())!='a') return;
		printf("输入p节点：");
		if(!get_data(&data)) return; 	
	}	
	p = L->next;
	while(1)
	{
		if(p->data == data) break;
		p = p->next;
	}
	printf("建立插入节点...\n");
	if(!DuLNode_creat(&q)) return ;
	(*insert)(p,q);
	TraverseList_DuL(L->next,print_int);
}
void Delete(DuLinkedList L)
{
	DuLinkedList temp;
	int data;
	temp = L = L->next;
	if(!L)//空链表删除警告 
	{
		printf("空链表无法进行删除操作!\n");
		return ;
	}
	TraverseList_DuL(L,print_int);//显示出所有节点再选择删除节点 
	printf("输入要删除的节点\n");
	printf("请输入：");
	if(!get_data(&data)) return ; 
	while(!(search(L,data)))
	{
		printf("查找不到该节点，输入'a'继续查找，任意值退出...\n");
		if((getch())!='a') return;
		printf("重新输入：");
		if(!get_data(&data)) return; 	
	}
	while(1)
	{
		if(L->data == data) break;
		L = L->next;
	}
	DeleteList_DuL(L,&data);
	printf("成功删除数据:%d\n",data);
}
