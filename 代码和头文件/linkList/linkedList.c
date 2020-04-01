#include "../head/linkedList.h"
#include<stdlib.h>
#include<stdio.h>
/**
 *  @name        : Status InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList(LinkedList *L) {
	*L = (LinkedList)malloc(sizeof(LNode));
	/*初始化头节点，不做任何操作，从头节点的下一个节点开始储存数据 
	保留头节点也可以简化转置操作中头节点的变化*/ 
	if(!(*L))	return ERROR;
	(*L)->next = NULL;
	return SUCCESS;
}

/**
 *  @name        : void DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
void DestroyList(LinkedList *L) {
	LinkedList Ltemp,Lcur = *L;
	/*Lcur从头到尾遍历链表，Ltemp储存每次Lcur的下一个节点，
	防止Lcur节点释放后无法找到下一个节点*/ 
	while(Lcur) {
		Ltemp = Lcur->next;
		free(Lcur);
		Lcur = Ltemp;
	}
}

/**
 *  @name        : Status InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : Status
 *  @notice      : None
 */
Status InsertList(LNode *p, LNode *q) {
	if(!q) return ERROR;//防止空节点插入时发生错误
	q->next = p->next;//先将要插入的节点与原节点的下一节点相连，防止节点丢失 
	p->next = q;
	return SUCCESS;
}
/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : Status
 *  @notice      : None
 */
Status DeleteList(LNode *p, ElemType *e) {
	LNode *Ltemp;
	/*Ltemp存储要删除的节点，先讲要删除节点的上一节点与下一节点相连*/ 
	Ltemp = p->next; 
	p->next = Ltemp->next;
	*e = Ltemp->data;
	free(Ltemp);
}

/**
 *  @name        : void TraverseList(LinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : None
 *  @notice      : None
 */
void print_int(ElemType e) {
	printf("%d  ",e);
}//整型输出 
void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
	L = L->next;//从储存数据的第一个节点开始访问 
	if(!L)
	{
		printf("This is a empty list\n");
		return ;//空量表访问失败信息提示 
	}
	while(L) {
		(*visit)(L->data);
		L=L->next;
	}//遍历输出链表 
	printf("\n");
}

/**
 *  @name        : Status SearchList(LinkedList L, ElemType e)
 *	@description : find the first node in the linked list according to e
 *	@param		 : L(the head node), e
 *	@return		 : Status
 *  @notice      : None
 */
Status SearchList(LinkedList L, ElemType e) {
	while(L) {
		if(L->data == e) return SUCCESS;
		L = L->next;//依次访问链表直到NULL结束，访问成功返回SUCCESS,失败返回ERROR
		 
	}
	return ERROR;
}

/**
 *  @name        : Status ReverseList(LinkedList *L)
 *	@description : reverse the linked list
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status ReverseList(LinkedList *L) {
	LinkedList Lrev,Lcur,Ltemp;//链表的转置 
	Lrev = NULL , Lcur = (*L)->next;//用Lrev依次存储转置后的为节点，Lcur为储存数据的头结点 
	if(!Lcur) return ERROR;//空量表返回错误信息 
	while(Lcur) {
		Ltemp = Lcur;//Ltemp储存相邻节点转置后的后一节点 
		Lcur = Lcur->next;// 每次循环Lcur储存转置后的第二节点 
		Ltemp->next = Lrev;//讲上一后节点与转置头节点连接 
		Lrev = Ltemp;//转置后的头节点不断储存到Lrev中 
	}
	(*L)->next = Lrev;//头节点重新设置 
	return SUCCESS;
}

/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L) {
	LinkedList L_slow,L_quick;
	L_slow = L;
	if(!L_slow || !L_slow->next) return ERROR;//当函数为初始化或链表为空时直接返回错误信息 
	L_quick = L_slow->next->next;//快指针走两次 
	while(L_slow!=L_quick) {
		if(!L_quick || !L_quick->next) return ERROR;//发现空节点时则可直接判断该链表不是成环链表 
		L_slow = L_slow->next;//慢指针走一次 
		L_quick = L_quick->next->next;
	}
	return SUCCESS;
}

/**
 *  @name        : LNode* ReverseEvenList(LinkedList *L)
 *	@description : reverse the nodes which value is an even number in the linked list, input: 1 -> 2 -> 3 -> 4  output: 2 -> 1 -> 4 -> 3
 *	@param		 : L(the head node)
 *	@return		 : LNode(the new head node)
 *  @notice      : choose to finish
 */
LNode* ReverseEvenList(LinkedList *L) {
	LinkedList 	Ltemp,Lcur,Lpre,L_head;
	Ltemp = *L;//Lcur和Lpre依次存储奇偶节点,Ltemp则存储两节点的上一节点，与Lcur，Lpre转置后建立联系 
	while(Ltemp->next && Ltemp->next->next) {
		Lcur = Ltemp->next;
		Lpre = Lcur->next;//奇偶节点的设置 
		Ltemp->next = Lpre;
		Ltemp = Lcur;
		Lcur->next = Lpre->next;
		Lpre->next = Lcur;//奇偶节点的交换 
	}
	return *L;
}

/**
 *  @name        : LNode* FindMidNode(LinkedList *L)
 *	@description : find the middle node in the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : choose to finish
 */
LNode* FindMidNode(LinkedList *L) {
	LNode *L_slow,*L_quick;
	L_slow = L_quick = *L;
	//在单链表中快指针走两步，慢指针走一步时，当快指针到达尾部时，慢指针就指向中间节点 
	while(L_quick && L_quick->next) {
		L_quick = L_quick->next->next;
		L_slow = L_slow->next;
	}
	return L_slow;
}

