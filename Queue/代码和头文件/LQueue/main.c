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
#include"LQueue.c"

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
 	printf("|————b.队列是否为空  ————|\n");
 	printf("|————c.获取头结点数据————|\n");
 	printf("|————d.队列长度      ————|\n");
 	printf("|————e.入队          ————|\n");
 	printf("|————f.出队          ————|\n");
 	printf("|————g.清空队列      ————|\n");
 	printf("|————h.输出队列      ————|\n");
 	printf("|————i.退出          ————|\n");
 	printf("请输入：");
 }
 
 
int main()
{
	LQueue *Q;
	char ch,temp;
	void *e;
	int flag;
	Q = (LQueue*)malloc(sizeof(LQueue));
	Q->front = Q->rear = NULL;
	Q->length = 0;
	e = (void*)malloc(sizeof(void));
	flag = 0;
	tips();
	while(1)
	{
		while((ch = getch('a','i'))!='i')
		{
			printf("你的选择：%c\n",ch);
			switch(ch)
			{
				case 'a':InitLQueue(Q);break;//初始化队列 
				case 'b':{//判断队列是否为空	
					if(IsEmptyLQueue(Q)) printf("队列为空！\n");
					else
					{
						printf("队列为空！(若未初始化请先初始化)\n");
					}
					break;
				}
				case 'c':{//获取头节点数据 
					if(GetHeadLQueue(Q,e)) 
					{
						printf("队头元素:");
						LPrint(e);
						printf("\n");
					}
					break;
				}
				case 'd':{//获取队列长度 
					if(!Q->front || !Q->rear)
					{
						printf("队列未初始化！\n");
						break;
					}
					printf("队列长度为%d\n",LengthLQueue(Q));
					break;
				}
				case 'e':{//入队 
					choices();
					switch(temp = getch('a','d'))
					{
						case 'a':type = 'i';break;
						case 'b':type = 'd';break;
						case 'c':type = 'c';break;
						case 'd':type = 's';break;
						default:flag = 1;break;
					}
					if(flag)
					{
						system("cls");
						tips();
						break;
					}
					if(!get_data(e,type)) break;
					if(EnLQueue(Q,e)) printf("入队成功！\n");
					else printf("入队失败！\n");
					break;
				}
				case 'f':{//出队 
					if(DeLQueue(Q)) printf("出队成功！\n");
					else printf("无法出队\n");
					break;
				}
				case 'g':{//清空队列 
					ClearLQueue(Q);
					break;
				}
				case 'h':{//遍历队列 
					TraverseLQueue(Q,LPrint);
					break;
				}
				case 'i':break;
				default:flag = 1;break; 
			}
			if(flag)
			{
				flag = 0;
				printf("输入错误！\n请重新输入：");
			}
			else break;
		}
		if(ch == 'i') break;
		system("pause");
		system("cls");
		tips();
	}
	DestoryLQueue(Q);
	free(Q);
	return 0;
}

