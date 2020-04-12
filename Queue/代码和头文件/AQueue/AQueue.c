/***************************************************************************************
 *	FileName					:	AQueue.c
 *	CopyRight					:	
 *	ModuleName					:	function 
 *
 *	CPU							:
 *	RTOS						:
 *
 *	Create Data					:	2020/4/11
 *	Author/Corportation			:	Hz
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

#include"AQueue.h"

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
		case 'd':for(i = (ch[0] == '-')?1:0;i<len;i++) if((ch[i]<'0' || ch[i]>'9') && ch[i]!='.') break;break;
		default:i = len;break;
	}
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
 *  @name        : void InitAQueue(AQueue *Q)
 *  @description : 初始化队列
 *  @param       : Q 队列指针Q
 *  @notice      : None
 */
void InitAQueue(AQueue *Q) 
{
	int i;
	if(!Q->length) DestoryAQueue(Q);//若队列已经初始化则格式化队列 
	for(i = 0;i < MAXQUEUE;i++) Q->data[i] = (void *)malloc(sizeof(void));
	Q->length = Q->front = Q->rear = 0;	
}


/**
 *  @name        : void DestoryAQueue(AQueue *Q)
 *  @description : 销毁队列
 *  @param       :  Q 队列指针Q
 *  @notice      : None
 */
void DestoryAQueue(AQueue *Q)
{
	int i;
	for(i = 0;i < MAXQUEUE;i++) free(Q->data[i]);
}

/**
 *  @name        : Status IsFullAQueue(const AQueue *Q)
 *  @description : 检查队列是否已满
 *  @param       : Q 队列指针Q
 *  @return      : 满-TRUE; 未满-FALSE
 *  @notice      : None
 */
Status IsFullAQueue(const AQueue *Q)
{
	if((Q->rear+1)%MAXQUEUE == Q->front) return TRUE;
	return FALSE;
}

/**
 *  @name        : Status IsEmptyAQueue(const AQueue *Q)
 *  @description : 检查队列是否为空
 *  @param       :  Q 队列指针Q
 *  @return      : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyAQueue(const AQueue *Q)
{
	if(Q->length) return FALSE;
	return TRUE; 
}


/**
 *  @name        : Status GetHeadAQueue(AQueue *Q, void *e)
 *  @description : 查看队头元素
 *  @param       : Q 队列指针Q，存放元素e
 *  @return      : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadAQueue(AQueue *Q, void *e)
{
	if(IsEmptyAQueue(Q)) return FALSE;
	switch(datatype[Q->front])//根据datatype找出对应元素的类型并输出 
	{
		case 'i':*(int*)e = *(int*)Q->data[Q->front];printf("队头元素：%d\n",*(int*)e);break;
		case 'f':*(float*)e = *(float*)Q->data[Q->front];printf("队头元素：%f\n",*(float*)e);break;
		case 'd':*(double*)e = *(double*)Q->data[Q->front];printf("队头元素：%lf\n",*(double*)e);break; 
		case 'c':*(char*)e = *(char*)Q->data[Q->front];printf("队头元素：%c\n",*(char*)e);break;
		case 's':*(char*)e = *(char*)Q->data[Q->front];printf("队头元素：%s\n",(char*)e);break;
	}
	return TRUE;
}		



/**
 *  @name        : int LengthAQueue(AQueue *Q)
 *  @description : 确定队列长度
 *  @param       : Q 队列指针Q
 *  @return      : 队列长度count
 *  @notice      : None
 */
int LengthAQueue(AQueue *Q)
{
	return Q->length;
}	
/**
 *  @name        : Status EnAQueue(AQueue *Q, void *data)
 *  @description : 入队操作
 *  @param       : Q 队列指针Q,入队数据指针data
 *  @return      : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否满了或为空
 */
Status EnAQueue(AQueue *Q, void *data)
{
	char d_type,temp;
	int i,len;
	if(!Q->data[0])
	{
		printf("队列未初始化！\n");
		return FALSE;
	}
	if(IsFullAQueue(Q))
	{
		printf("队列已满！\n");
		return FALSE;
	}
	data = (void*)malloc(sizeof(void));
	choices();//输出类型选项 
	switch((temp = getch('a','d')))//根据选项选择对应类型值 
	{
		case 'a':d_type = datatype[Q->rear] = 'i';break;//int
		case 'b':d_type = datatype[Q->rear] = 'd';break;//double
		case 'c':d_type = datatype[Q->rear] = 'c';break;//char
		case 'd':d_type = datatype[Q->rear] = 's';break;//string
		default:printf("输入错误！\n");return FALSE;
	}
	printf("请输入数据：");
	if(!get_data(data,d_type))
	{
		return FALSE;
	}
	Q->length++;
	switch(temp)
	{
		case 'a':*(int*)Q->data[Q->rear] = *(int *)data;break;
		case 'b':*(double*)Q->data[Q->rear] = *(double*)data;break;
		case 'c':*(char*)Q->data[Q->rear] = *(char *)data;break;
		case 'd':strcpy((char*)Q->data[Q->rear],(char*)data);break;
	}
	Q->rear = (Q->rear+1)%MAXQUEUE;//循环队列 
	return TRUE;
}



/**
 *  @name        : Status DeAQueue(AQueue *Q)
 *  @description : 出队操作
 *  @param       : Q 队列指针Q
 *  @return      : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeAQueue(AQueue *Q)
{
	if(IsEmptyAQueue(Q))
	{
		return FALSE;	
	}		
	Q->length--;
	Q->front = (Q->front+1)%MAXQUEUE;
	return TRUE;
}	



/**
 *  @name        : void ClearAQueue(Queue *Q)
 *  @description : 清空队列
 *  @param       : Q 队列指针Q
 *  @notice      : None
 */
void ClearAQueue(AQueue *Q)
{
	Q->length = Q->front = Q->rear = 0;
}	



/**
 *  @name        : Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
 *  @description : 遍历函数操作
 *  @param       : Q 队列指针Q，操作函数指针foo
 *  @return      : None
 *  @notice      : None
 */
Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
{
	int i;
	if(IsEmptyAQueue(Q))
	{
		return FALSE;
	}
	i = Q->front;
	do
	{
		type = datatype[i];
		foo(Q->data[i]);
		i = (i+1)%MAXQUEUE;
	}while(i != Q->rear);
	printf("\b\b\b    \n");//用空格将最后的“->”覆盖 
	return TRUE;		
}	


/**
 *  @name        : void APrint(void *q)
 *  @description : 操作函数
 *  @param       : q 指针q
 *  @notice      : None
 */
void APrint(void *q)
{
	switch(type)
	{
		case 'i':printf("%d -> ",*(int*)q);break;
		case 'd':printf("%lf -> ",*(double*)q);break;
		case 'c':printf("%c -> ",*(char*)q);break;
		case 's':printf("%s -> ",(char*)q);break;
	}
}
