#include "../head/duLinkedList.h"

/**
 *  @name        : Status InitList_DuL(DuLinkedList *L)
 *	@description : initialize an empty linked list with only the head node
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList_DuL(DuLinkedList *L) {
	*L = (DuLinkedList)malloc(sizeof(DuLNode));
	if(!(*L)) return ERROR; 
	(*L)->data = 0;//头节点数据用于存储链表节点数量 
	(*L)->prior = (*L)->next = NULL;
	return SUCCESS;
}

/**
 *  @name        : void DestroyList_DuL(DuLinkedList *L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : status
 *  @notice      : None
 */
void DestroyList_DuL(DuLinkedList *L) {
	DuLinkedList p1,p2;
	p1 = p2 = *L;
	while(p1)
	{
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
}

/**
 *  @name        : Status InsertBeforeList_DuL(DuLNode *p, LNode *q)
 *	@description : insert node q before node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q) {
	if(!p || !q) 
	{
		printf("错误信息：空节点插入\n");
		return ERROR;
	} 
	if(p->prior)
	{
		p->prior->next = q;
		q->prior = p->prior;
	}
	else q->prior = NULL;
	q->next = p;
	p->prior = q;
	return SUCCESS;
}

/**
 *  @name        : Status InsertAfterList_DuL(DuLNode *p, DuLNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertAfterList_DuL(DuLNode *p, DuLNode *q) {
	if(!p || !q) 
	{
		printf("错误信息：空节点插入\n");
		return ERROR;
	} 
	if(p->next)
	{
		p->next->prior = q;
		q->next = p->next;
	}
	else q->next = NULL;
	p->next = q;
	q->prior = p;
	return SUCCESS;
}

/**
 *  @name        : Status DeleteList_DuL(DuLNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : status
 *  @notice      : None
 */
Status DeleteList_DuL(DuLNode *p, ElemType *e) {
	if(!p) 
	{
		printf("无法删除空节点\n");
		return ERROR; 
	} 
	//添加条件避免使用空指针的指针域造成程序崩溃 
	if(p->prior) p->prior->next = p->next;
	if(p->next) p->next->prior = p->prior;
	free(p);
}

/**
 *  @name        : void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : Status
 *  @notice      : None
 */
void print_int(ElemType e)
{
	printf("%d  ",e);
}
void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) {
	if(!L)
	{
		printf("这是一个空链表!\n");
	}
	while(L)
	{
		(*visit)(L->data);
		L = L->next;
	}
	printf("\n");
}
