#include "../head/linkedList.h"
#include<stdlib.h>
#include<stdio.h>
extern void print_int(ElemType e);//����"linkedList.c" �е�print_int���� 
extern Status get_data(ElemType *e);
extern get_ch();
void Search(LinkedList *L) {
	int data;

	LNode *q,*p;
	if(!(*L)->next) {
		printf("This is a empty list.\n");
		return ;
	}//�������޷������������� 
	TraverseList(*L,print_int);//��ʾ�������ݹ��û�ѡ�� 
	printf("Select the node by its data:");
	if(!get_data(&data)) return ;//������ҽڵ����� ,�����ʽ����ص���ʼ���� 
	while(!SearchList(*L,data)) {
		printf("The data isn't in the list.\nAgain ('1':break,'2'(else):continue):");//Ϊ���ҵ���Ӧ�ڵ�ʱ�������� 
		if(getch() == '1') return ;//����1ʱ�˳����� 
		printf("Select the node by its data:");
		get_data(&data);//������ҽڵ����� 
	}
	p = (*L)->next;//pΪ�������ݵĵ�һ���ڵ� 
	while(p) {
		if(p->data == data) break;
		p = p->next;
	}//���ҵ�p�ڵ� 
	printf("Enter the data to insert\n"); 
	/*�����½ڵ�q������p�ڵ����p�ڵ�֮��*/ 
	if(!LNodeCreat(&q)) exit(EXIT_FAILURE);
	InsertList(p,q);
}
