#include "../head/linkedList.h"
#include<stdio.h>
extern void print_int(ElemType e);
extern void TraverseList(LinkedList L, void (*visit)(ElemType e));
void Delete(LinkedList *L) {
	int data,d_data;
	LNode *p;
	if(!(*L)->next) {
		printf("This is a empty list.\n");
		return ;
	}
	TraverseList(*L,print_int);//输出链表供用户选择 
	printf("Select the node by its data:");
	if(!get_data(&data)) return;//输入查找节点数据 ,输入格式错误回到起始界面 
	while(!SearchList(*L,data)) {
		printf("The data isn't in the list.\nAgain ('1':break,'2'(else):continue):");//为查找到对应节点时反复查找 
		if(getch() == '1') return ;//输入1时退出查找 
		printf("Select the node by its data:");
		get_data(&data);//输入查找节点数据 
	}
	p = *L;
	while(1) {
		if((p->next)->data == data) break;
		p = p->next;
	}
	DeleteList(p,&d_data);
	printf("Delete data:%d\n",d_data);
}
