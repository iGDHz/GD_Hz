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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"AQueue.c"

/**************************************************************
*	Function Define Section
**************************************************************/

/**
 *  @name:void tips()
 *	@description:输出操作指南 
 *	@param:None
 *	@return:None	
 *  @notice:None
 */
 void tips()
 {
 	printf("|————a.初始化队列    ————|\n");
 	printf("|————b.队列是否已满  ————|\n");
 	printf("|————c.队列是否为空  ————|\n");
 	printf("|————d.获取头结点数据————|\n");
 	printf("|————e.队列长度      ————|\n");
 	printf("|————f.入队          ————|\n");
 	printf("|————g.出队          ————|\n");
 	printf("|————h.清空队列      ————|\n");
 	printf("|————i.输出队列      ————|\n");
 	printf("|————j.退出          ————|\n");
 	printf("请输入：");
 }

int main()
{
	AQueue *Q;
	void *e,*data;
	int flag;
	char ch;
	Q = (AQueue*)malloc(sizeof(AQueue));
	Q->data[0] = NULL;
	e = (void*)malloc(sizeof(void));
	flag = 0;
	InitAQueue(Q);
	tips();
	while(1)
	{
		while((ch = getch('a','j'))!='j')
		{
			printf("你的选择：%c\n",ch);
			switch(ch)
			{
				case 'a':InitAQueue(Q);break;
				case 'b':{
					if(IsFullAQueue(Q)) printf("队列已满！\n");
					else printf("队列未满！\n");
					break;
				}
				case 'c':{	
					if(IsEmptyAQueue(Q)) printf("队列为空！\n");
					else printf("队列不为空！\n");
					break;
				}
				case 'd':{
					if(GetHeadAQueue(Q,e)) ;
					else printf("队列为空！\n");
					break;
				}
				case 'e':{
					printf("队列长度为%d\n",LengthAQueue(Q));
					break;
				}
				case 'f':{
					if(EnAQueue(Q,data)) printf("入队成功！\n");
					else printf("入队失败！\n");
					break;
				}
				case 'g':{
					if(DeAQueue(Q)) printf("出队成功！\n");
					else printf("队列为空！无法出队\n");
					break;
				}
				case 'h':{
					ClearAQueue(Q);
					break;
				}
				case 'i':{
					if(TraverseAQueue(Q,APrint));
					else printf("队列为空！\n");
					break;
				}
				default:flag = 1;break; 
			}
			if(flag)
			{
				flag = 0;
				printf("输入错误！\n请重新输入：");
			}
			else break;
		}
		if(ch == 'j') break;
		system("pause");
		system("cls");
		tips();
	}
	DestoryAQueue(Q);
	free(Q);
	return 0;
}

