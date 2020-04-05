#include"../head/SqStack.h"

Status initStack(SqStack *s,int sizes)//初始化栈
{
	if(!s->elem) clearStack(s);//栈存在时对栈进行格式化 
	if(sizes <= 0 )
	{
		printf("无法建立一个长度小于等于0的栈\n");
		return ERROR;
	}
	s->elem = (int*)malloc(sizeof(int)*sizes);
	if(!s->elem) return ERROR;
	s->top = -1;//初始化为空栈 
	s->size = sizes;
	return SUCCESS;
}


Status isEmptyStack(SqStack *s)//判断栈是否为空
{
	if(s->top == -1) return SUCCESS;//直接按照按栈的长度判断 
	return ERROR;
}
Status getTopStack(SqStack *s,ElemType *e) //得到栈顶元素
{
	if(s->top == -1) return ERROR;//栈为空无法获取栈顶元素 
	*e = *(s->elem + s->top);
	return SUCCESS;
}
Status clearStack(SqStack *s)//清空栈
{
	if(s->top == -1) return ERROR; 
	s->top = -1;//直接用top赋值为-1作为空栈的操作 
	return SUCCESS;
}
Status destroyStack(SqStack *s)//销毁栈
{
	if(!s) return ERROR;//由于主函数中已经确保s不为空指针，所以此函数只能返回SUCCESS 
	free(s);
	return SUCCESS;
}
Status stackLength(SqStack *s,int *length)//检测栈长度
{
	if(!length) return ERROR;
	*length = s->size;
	return SUCCESS;
}
Status pushStack(SqStack *s,ElemType data)//入栈
{
	if(s->top == s->size-1)
	{
		printf("栈已满，入栈失败!\n");
		return ERROR;
	}
	s->top++;
	*(s->elem + s->top) = data;
	return SUCCESS;
}
Status popStack(SqStack *s,ElemType *data)//出栈
{
	if(s->top == -1)
	{
		printf("栈为空，出栈失败!\n");
		return ERROR; 
	}
	*data = *(s->elem + s->top);
	s->top--;
	return SUCCESS;
}

