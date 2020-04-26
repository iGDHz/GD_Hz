/***************************************************************************************
 *	FileName					:	main.c
 *	CopyRight					:
 *	ModuleName					:	
 *
 *	CPU							:
 *	RTOS						:
 *
 *	Create Data					:	2020/4/26
 *	Author/Corportation			:	Hz
 *
 *	Abstract Description		:	
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *	
 *
 ***************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tree.c"
/**************************************************************
*	Function Define Section
**************************************************************/

/**
 *  @name:void function_tips() 
 *	@description:种树操作选择 
 *	@param：None 
 *	@return:None	
 *  @notice:None
 */
void function_tips()
{
	printf("|————a.普通二叉树 ————|\n");
	printf("|————b.搜索二叉树 ————|\n");
	printf("|————c.表达式计算 ————|\n");
	printf("|————    d.退出   ————|\n");
	printf("请输入：");
}

/**
 *  @name:void Traverses() 
 *	@description:遍历方式选择 
 *	@param：None 
 *	@return:None	
 *  @notice:None
 */
 void Traverse()
 {
 	printf("|————a.先序遍历 ————|\n");
 	printf("|————b.中序遍历 ————|\n");
 	printf("|————c.后序遍历 ————|\n");
 	printf("|————d.层次遍历 ————|\n");
 	printf("|————  e.退出   ————|\n");
 	printf("请输入：");
 }
 
  /**
 *  @name:char getch(char from,char to)
 *	@description:获取正确输入选项 
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

int main()
{
	BiTree T;
	char ch,temp;
	while(1)
	{
		system("cls");
		function_tips();
		InitBiTree(&T);
		while((ch = getch('a','d'))<'a' || ch >'d') 
		{
			printf("请输入正确的字符！\n请输入：");
		}
		if(ch == 'd') break;
		switch(ch)
		{
			case 'a':{
				printf("请输入（如:AB#DF##G##C#E#H##）：") ;
				CreateBiTree(&T,"BiTree");
				getchar();//吸收多出来的回车 
				break;
			}
			case 'b':{
				printf("请输入（如:46283）:");
				CreateBiTree(&T,"BSTree");
				break;
			}
			case 'c':{
				printf("请输入(如：1 + 4 * 3 / 2 - 7)：");
				while(!CreateBiTree(&T,"BCTree"))
				{
					printf("输入错误，按‘Y’重新输入...    ");
					if(getch('Y','Y') == 'Y') break;
					getchar();
					printf("请输入(如：1+4*4-2)：");
				}
				break;
			}
		}
		while(ch=='a' || ch =='b')
		{
			system("cls");
			Traverse();
			while((temp = getch('a','e'))<'a' || temp >'e') 
			{
				
				printf("请输入正确的字符！\n请输入：");
			}
			if(temp == 'e') 
			{
				break;
			}
			else
			{
				switch(temp)
				{
					case 'a':{
					PreOrderTraverse(T,print);//先序遍历 
					putchar('\n');
					break;
					}
					case 'b':{
					InOrderTraverse(T,print);//中序遍历 
					putchar('\n');
					break;
						
					}
					case 'c':{
					PostOrderTraverse(T,print);//后序遍历 
					putchar('\n');
					break;
					}
					case 'd':{
					LevelOrderTraverse(T,print);//层次遍历 
					putchar('\n');	
					break;
					}
				}
				system("pause");
			}
		}
		if(ch == 'c')
		{
			PostOrderTraverse(T,print);
			printf("=%d\n",Value(T));
			system("pause"); 
		}
		DestroyBiTree(&T);
	}	
	DestroyBiTree(&T);
	return 0;
}
