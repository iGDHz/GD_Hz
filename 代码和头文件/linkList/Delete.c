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
	TraverseList(*L,print_int);//��������û�ѡ�� 
	printf("Select the node by its data:");
	if(!get_data(&data)) return;//������ҽڵ����� ,�����ʽ����ص���ʼ���� 
	while(!SearchList(*L,data)) {
		printf("The data isn't in the list.\nAgain ('1':break,'2'(else):continue):");//Ϊ���ҵ���Ӧ�ڵ�ʱ�������� 
		if(getch() == '1') return ;//����1ʱ�˳����� 
		printf("Select the node by its data:");
		get_data(&data);//������ҽڵ����� 
	}
	p = *L;
	while(1) {
		if((p->next)->data == data) break;
		p = p->next;
	}
	DeleteList(p,&d_data);
	printf("Delete data:%d\n",d_data);
}
