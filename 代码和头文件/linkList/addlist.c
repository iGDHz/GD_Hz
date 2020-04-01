#include "../head/linkedList.h"
#include<stdlib.h>
#include<stdio.h>
extern char getch();
extern Status get_data(ElemType *e);
Status LNodeCreat(LinkedList *node) {
	char ch;
	*node = (LinkedList)malloc(sizeof(LNode));
	if(!(*node)) return ERROR;
	printf("data:");
	while(!get_data(&(*node)->data))
	{
		printf("Whether to add node('1' to continue):");
		ch = getch();
		if(ch != '1') return ERROR;
		printf("data:");
	}
	(*node)->next = NULL;
	return SUCCESS;
}
Status LNode_add(LinkedList L) {
	LinkedList node;
	if(!LNodeCreat(&node)) return ERROR;
	node->next = L->next;
	L->next = node;
	return SUCCESS;
}
