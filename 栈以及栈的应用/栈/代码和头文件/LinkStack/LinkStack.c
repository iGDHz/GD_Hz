#include"../head/LinkStack.h"

Status initLStack(LinkStack *s)//初始化栈
{
	s->top = (LinkStackPtr)malloc(sizeof(StackNode));
	if(!s->top) return ERROR;
	s->top->next = NULL;
	return SUCCESS;		
 } 

Status isEmptyLStack(LinkStack *s)//判断栈是否为空
{
	if(s->count) return ERROR;
	return SUCCESS;
}

Status getTopLStack(LinkStack *s,ElemType *e)//得到栈顶元素
{
	if(s->count)
	{
		*e = s->top->data;
		return SUCCESS;
	}
	return ERROR;
}
Status clearLStack(LinkStack *s)//清空栈
{
	if(s->count)
	{
		destroyLStack(s);//将栈全部销毁后重新初始化 
		initLStack(s);
		return SUCCESS;
	}
	else return ERROR;
}
Status destroyLStack(LinkStack *s)//销毁栈
{
	LinkStackPtr S2,S1;
	if(!s) return ERROR; 
	S2=S1=s->top;//S1始终指向当前节点，S2指向下一节点，依次释放 
	while(S1)
	{
		S2 = S1->next;
		free(S1);
		S1 = S2;
	}
	return SUCCESS;
}
Status LStackLength(LinkStack *s,int *length)//检测栈长度
{
	if(s->count && length!=NULL)
	//由于前面已经对s进行过判断，所以此处只判断length是否为空与栈是否为空 
	{
		*length = s->count;
		return SUCCESS;
	}
	return ERROR;
}
Status pushLStack(LinkStack *s,ElemType data)//入栈
{
	LinkStackPtr new_Node,top = s->top;
	if(s->count == 0) 
	{
		top->data = data;
		return SUCCESS;
	}
	new_Node = (LinkStackPtr)malloc(sizeof(StackNode));//建立新节点 
	if(!new_Node)
	{
		printf("节点建立失败!\n");
		return ERROR;	
	}		
	new_Node->next = s->top;
	new_Node->data = data;
	s->top = new_Node;//以新节点作为头节点插入 
	return SUCCESS; 
}
Status popLStack(LinkStack *s,ElemType *data)//出栈
{
	LinkStackPtr top = s->top;
	if(!data) return ERROR;//由于前面已经对s是否为空进行了判定，所以此处data为唯一的可能出错的地方 
	*data = top->data;
	s->top = top->next;
	free(top);
	if(!s->top)//防止全部删除时回归未初始化的状态
	initLStack(s);
	return SUCCESS; 
}
