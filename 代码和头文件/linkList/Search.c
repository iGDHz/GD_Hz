#include "../head/linkedList.h"
#include<stdlib.h>
#include<stdio.h>
extern void print_int(ElemType e);//调用"linkedList.c" 中的print_int函数 
extern Status get_data(ElemType *e);
extern get_ch();
void Search(LinkedList *L) {
	int data;

	LNode *q,*p;
	if(!(*L)->next) {
		printf("This is a empty list.\n");
		return ;
	}//空链表无法进行搜索操作 
	TraverseList(*L,print_int);//显示所有数据供用户选择 
	printf("Select the node by its data:");
	if(!get_data(&data)) return ;//输入查找节点数据 ,输入格式错误回到起始界面 
	while(!SearchList(*L,data)) {
		printf("The data isn't in the list.\nAgain ('1':break,'2'(else):continue):");//为查找到对应节点时反复查找 
		if(getch() == '1') return ;//输入1时退出查找 
		printf("Select the node by its data:");
		get_data(&data);//输入查找节点数据 
	}
	p = (*L)->next;//p为储存数据的第一个节点 
	while(p) {
		if(p->data == data) break;
		p = p->next;
	}//查找到p节点 
	printf("Enter the data to insert\n"); 
	/*建立新节点q，并把p节点插入p节点之后*/ 
	if(!LNodeCreat(&q)) exit(EXIT_FAILURE);
	InsertList(p,q);
}
