/***************************************************************************************
 *	FileName					:	main.c
 *	CopyRight					:	
 *	ModuleName					:	主函数 
 *
 *	CPU							:	
 *	RTOS						:
 *
 *	Create Data					:	2020/4/11
 *	Author/Corportation			:	
 *
 *	Abstract Description		:	
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *	
 *
 ***************************************************************************************/

/**************************************************************
*	Include File Section
**************************************************************/

#include"LQueue.h"

/**************************************************************
*	Function Define Section
**************************************************************/

  /**
 *  @name:void choices()
 *	@description:输出类型选择 
 *	@param:None
 *	@return:None	
 *  @notice:None
 */
 void choices()
 {
 	system("cls");
 	printf("\t*****选择输入类型*****\n");
	printf("|————     a.int型      ————|\n");
	printf("|————    b.double型    ————|\n");
	printf("|————     c.char型     ————|\n");
	printf("|————d.string(20字符内)————|\n");
	printf("请输入：");
 }
 
/**
 *  @name:char getch(char from,char to)
 *	@description:获取用户输入的有效选项 
 *	@param:from,to
 *	@return:char	
 *  @notice:None
 */
char getch(char from,char to)//用户选择输入（字符串读取后返回有效选择功能，范围从from到to） 
{
	char str[50];
	int i,len;
	gets(str);//字符串读取 
	len = strlen(str);
	for(i = 0; i<len; i++) { 
		if(str[i]>=from && str[i]<=to) return str[i];//遇到有效选项直接返回 
	}
	return str[len-1];//访问完之后查找不到有效数字直接返回最后数字 
}
/**
 *  @name:Status get_data(void *e,char d_type)
 *	@description:整型数据输入 
 *	@param:e
 *	@return:Status	
 *  @notice:None
 */
Status get_data(void *e,char d_type)//数据输入（防滚键盘） 
{
	char ch[30];
	int len,i;
	long long int result_int;
	double result_double;
	printf("输入数据：");
	gets(ch);
	len = strlen(ch); 
	if(len>20) 
	{
		printf("输入字符过长！\n");
		return FALSE;
	}
	switch(d_type)// 根据选项判断输入是否正确 
	{
		case 'i':for(i = (ch[0] == '-')?1:0;i<len;i++) if(ch[i]<'0' || ch[i]>'9') break;break;
		case 'f':
		case 'd':for(i=0;i<len;i++) if((ch[i]<'0' || ch[i]>'9') && ch[i]!='.') break;break;
		default:i = len;break;
	}
	type = d_type;
	if(i!=len)
	{
		printf("输入格式错误！\n");
		return FALSE;
	}
	switch(d_type)
	{
		case 'i':{
			if((result_int = strtol(ch,NULL,0)) < -2147483648LL || result_int > 2147483647LL)
			{
				printf("数据溢出！\n");
				return FALSE;
			}//对整型添加溢出处理 
			break;
		}
		case 'f':
		case 'd': result_double = atof(ch);break;//float与double为同类型转化函数 
		case 'c':{
			*(char*)e = ch[0];
			return TRUE;
		}
		case 's':{
			strcpy((char*)e,ch);//讲ch复制给e指针所指向的内容 
			return TRUE;
		}
	}
	if(d_type == 'i')
	{
		*(int*)e = (int)result_int;
	}
	else if(d_type == 'f')
	{
		*(float*)e = (float)result_double;
	}
	else *(double*)e = result_double;
	return TRUE;
 } 
 
 /**
 *  @name        : void InitLQueue(LQueue *Q)
 *  @description : 初始化队列
 *  @param       : Q 队列指针Q
 *  @notice      : None
 */
void InitLQueue(LQueue *Q)
{
	if(!Q->front || !Q->rear) DestoryLQueue(Q);
	Q->rear = Q->front = (Node*)malloc(sizeof(Node));
	Q->front->next = NULL;
	Q->length = 0;
	Q->front->data = malloc(sizeof(void));
	data_head = 0;//数据类型的头位置 
	data_rear = 0;//数据类型的尾位置 
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *  @description : 销毁队列
 *  @param       : Q 队列指针Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q)
{
	Node *p1,*p2;
	p1 = p2 =Q->front;
	while(p1)
	{
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *  @description : 检查队列是否为空
 *  @param       : Q 队列指针Q
 *  @return      : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q)
{
	if(Q->length) return FALSE;
	return TRUE;
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *  @description : 查看队头元素
 *  @param       : Q e 队列指针Q,返回数据指针e
 *  @return      : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadLQueue(LQueue *Q, void *e)
{
	if(IsEmptyLQueue(Q))
	{
		return FALSE;
	}
	switch(type = datatype[data_head])
	{
		case 'i':type = 'i';*(int*)e = *(int*)Q->front->data;break;
		case 'd':type = 'd';*(double*)e = *(double*)Q->front->data;break;
		case 'c':type = 'c';*(char*)e = *(char*)Q->front->data;break;
		case 's':type = 's';strcpy((char*)e,(char*)Q->front->data);break;
	}
	return TRUE;
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *  @description : 确定队列长度
 *  @param       : Q 队列指针Q
 *  @return      : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q)
{
	return Q->length;
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *  @description : 入队操作
 *  @param       :  Q 队列指针Q,入队数据指针data
 *  @return      : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否为空
 */
Status EnLQueue(LQueue *Q, void *data)
{
	Node *new_node;
	if(!Q->front || !Q->rear) 
	{
		printf("队列未初始化！\n");
		return FALSE;
	}
	datatype[data_head] = type;
	if(!Q->length)//刚初始化时直接利用初始化的头节点继续赋值 
	{
		switch(type)
		{
			case 'i':*(int*)Q->front->data = *(int*)data;break;
			case 'd':*(double*)Q->front->data = *(double*)data;break;
			case 'c':*(char*)Q->front->data = *(char*)data;break;
			case 's':strcpy((char*)Q->front->data,(char*)data);break;
		}
		Q->length++; 
		return TRUE;
	}
	new_node = (Node*)malloc(sizeof(Node));
	new_node->data = (void*)malloc(sizeof(void));
	if(!new_node || !new_node->data)
	{
		printf("节点内存分配失败！\n");
		return FALSE;
	 } 
	switch(type)
	{
		case 'i':*(int*)new_node->data = *(int*)data;break;
		case 'd':*(double*)new_node->data = *(double*)data;break;
		case 'c':*(char*)new_node->data = *(char*)data;break;
		case 's':strcpy((char*)new_node->data,(char*)data);break;
	}
	new_node->next = NULL;//新节点后接空节点 
	new_node = Q->rear->next;//新节点接于原队列的尾节点 
	Q->rear = new_node;//尾节点重新设置
	Q->length++; 
	data_rear = (data_rear+1)%30;//数据类型尾位置向后移一位 
	return TRUE;
}

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *  @description : 出队操作
 *  @param       : Q 队列指针Q
 *  @return      : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q)
{
	Node *free_Q;
	if(IsEmptyLQueue(Q))
	{
		return FALSE;
	}
	if(Q->front == Q->rear) InitLQueue(Q);//只有一个节点时直接格式化 
	free_Q = Q->front;
	Q->front = Q->front->next;
	free(free_Q);
	Q->length--;
	data_head = (data_head+1)%30;//数据类型头位置向后移一位 
	return TRUE;
}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *  @description : 清空队列
 *  @param       : Q 队列指针Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q)
{
	if(!Q->length) return ;
	DestoryLQueue(Q);
	InitLQueue(Q);
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *  @description : 遍历函数操作
 *  @param       : Q 队列指针Q，操作函数指针foo
 *  @return      : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
{
	Node *p;
	int i;
	if(!Q->front || !Q->rear)
	{
		printf("队列未初始化！");
		return FALSE;
	}
	if(!Q->length)
	{
		printf("队列为空！");
		return FALSE;
	}
	i = data_head;
	p = Q->front;
	while(p)
	{
		type = datatype[i];//类型声明 
		foo(p->data);//输出对应数据 
		p = p->next;
		i = (i+1)%30;
		printf(" -> ");
	}	
	printf("\b\b\b   \n");
	return TRUE;
}
/**
 *  @name        : void LPrint(void *q)
 *  @description : 操作函数
 *  @param       : q 指针q
 
 *  @notice      : None
 */
void LPrint(void *q)
{
	switch(type)
	{
		case 'i':printf("%d",*(int*)q);break;
		case 'd':printf("%lf",*(double*)q);break;
		case 'c':printf("%c",*(char*)q);break;
		case 's':printf("%s",(char*)q);break; 
	}
}
