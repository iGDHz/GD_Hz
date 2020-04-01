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
	/*��ʼ��ͷ�ڵ㣬�����κβ�������ͷ�ڵ����һ���ڵ㿪ʼ�������� 
	����ͷ�ڵ�Ҳ���Լ�ת�ò�����ͷ�ڵ�ı仯*/ 
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
	/*Lcur��ͷ��β��������Ltemp����ÿ��Lcur����һ���ڵ㣬
	��ֹLcur�ڵ��ͷź��޷��ҵ���һ���ڵ�*/ 
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
	if(!q) return ERROR;//��ֹ�սڵ����ʱ��������
	q->next = p->next;//�Ƚ�Ҫ����Ľڵ���ԭ�ڵ����һ�ڵ���������ֹ�ڵ㶪ʧ 
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
	/*Ltemp�洢Ҫɾ���Ľڵ㣬�Ƚ�Ҫɾ���ڵ����һ�ڵ�����һ�ڵ�����*/ 
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
}//������� 
void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
	L = L->next;//�Ӵ������ݵĵ�һ���ڵ㿪ʼ���� 
	if(!L)
	{
		printf("This is a empty list\n");
		return ;//���������ʧ����Ϣ��ʾ 
	}
	while(L) {
		(*visit)(L->data);
		L=L->next;
	}//����������� 
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
		L = L->next;//���η�������ֱ��NULL���������ʳɹ�����SUCCESS,ʧ�ܷ���ERROR
		 
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
	LinkedList Lrev,Lcur,Ltemp;//�����ת�� 
	Lrev = NULL , Lcur = (*L)->next;//��Lrev���δ洢ת�ú��Ϊ�ڵ㣬LcurΪ�������ݵ�ͷ��� 
	if(!Lcur) return ERROR;//�������ش�����Ϣ 
	while(Lcur) {
		Ltemp = Lcur;//Ltemp�������ڽڵ�ת�ú�ĺ�һ�ڵ� 
		Lcur = Lcur->next;// ÿ��ѭ��Lcur����ת�ú�ĵڶ��ڵ� 
		Ltemp->next = Lrev;//����һ��ڵ���ת��ͷ�ڵ����� 
		Lrev = Ltemp;//ת�ú��ͷ�ڵ㲻�ϴ��浽Lrev�� 
	}
	(*L)->next = Lrev;//ͷ�ڵ��������� 
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
	if(!L_slow || !L_slow->next) return ERROR;//������Ϊ��ʼ��������Ϊ��ʱֱ�ӷ��ش�����Ϣ 
	L_quick = L_slow->next->next;//��ָ�������� 
	while(L_slow!=L_quick) {
		if(!L_quick || !L_quick->next) return ERROR;//���ֿսڵ�ʱ���ֱ���жϸ������ǳɻ����� 
		L_slow = L_slow->next;//��ָ����һ�� 
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
	Ltemp = *L;//Lcur��Lpre���δ洢��ż�ڵ�,Ltemp��洢���ڵ����һ�ڵ㣬��Lcur��Lpreת�ú�����ϵ 
	while(Ltemp->next && Ltemp->next->next) {
		Lcur = Ltemp->next;
		Lpre = Lcur->next;//��ż�ڵ������ 
		Ltemp->next = Lpre;
		Ltemp = Lcur;
		Lcur->next = Lpre->next;
		Lpre->next = Lcur;//��ż�ڵ�Ľ��� 
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
	//�ڵ������п�ָ������������ָ����һ��ʱ������ָ�뵽��β��ʱ����ָ���ָ���м�ڵ� 
	while(L_quick && L_quick->next) {
		L_quick = L_quick->next->next;
		L_slow = L_slow->next;
	}
	return L_slow;
}

