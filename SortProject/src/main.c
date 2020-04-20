#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"qgsort.c"
#include<time.h>
int get_data(int *e)//数据输入（防滚键盘） 
{
	char ch[30];
	int flag,i,len;
	long long int result;
	result = 0,i = 0,flag = 1;
	len = strlen(ch); 
	gets(ch);
	if(ch[i] == '-')//判断输入是否为负数 
	{
		flag = -1;
		i++; 
	}
	while(ch[i])
	{
		if(ch[i]<'0' || ch[i]>'9') 
		{
			printf("输入格式错误!\n");
			return 0;
		}
		else if(result < -2147483648LL || result > 2147483647LL)//判断是否会造成数据溢出 
		{  
			printf("数据溢出！\n");
			return 0;
		}
		result = result*10 + ch[i] - '0';
		i++;		
	}
	*e = (int)result * flag;//flag判断正负 
	return 1;
 } 
 
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

void data_choices()//数据选择 
{
	printf("|————a.大数据测试（10000）————|\n");
	printf("|————b.大数据测试（50000）————|\n");
	printf("|——— c.大数据测试（200000）————|\n");
	printf("|——————d.小数据测试 ——————|\n"); 
	printf("|——————  e.退出   ———————|\n");
}

void tips()//排序方式选择 
{
	printf("|————a.插入排序————|\n");
	printf("|————b.归并排序————|\n"); 
	printf("|————c.快速排序————|\n");
	printf("|————d.基数排序————|\n");
	printf("|————  e.退出  ————|\n");
}
void get_array(int **big,int ***small,int col,int row)//数组建立 
{
	int i;
	if(big) *big = (int*)malloc(sizeof(int)*col);
	else if(small) 
	{
		*small = (int**)malloc(sizeof(int*)*row);
		for(i = 0; i < row ; i++) *((*small)+i)= (int*)malloc(sizeof(int)*col);
	}
}
void function(char type)
{
	int i,j,col,row,flag,*big,**little,*temp;
	clock_t test_time;
	FILE *fp;
	char ch;
	big = NULL;
	little = NULL;
	flag = 0;
	srand((unsigned)time(NULL)); //随机数种子设置 
	while(1)
	{
		system("cls");
		data_choices();
		switch(ch = getch('a','e'))
		{
			case 'a':{
				col = 10000;
				get_array(&big,NULL,10000,0);//获取big[10000] 
				break;
			}
			case 'b':{
				col = 50000;
				get_array(&big,NULL,50000,0);//获取big[50000] 
				break;
			}
			case 'c':{
				col = 200000;
				get_array(&big,NULL,200000,0);//获取big[200000] 
				break;
			}
			case 'd':{
				printf("输入行：");
				while(!get_data(&row))//获取行 
				{
					printf("输入错误！按'Y'重新输入,任意键退出\n");
					if(getch('Y','Y') != 'Y') return ;
					printf("输入行："); 
				}
				printf("输入列: ");//获取列 
				while(!get_data(&col))
				{
					printf("输入错误！按'Y'重新输入,任意键退出\n");
					if(getch('Y','Y') != 'Y') return ;
					printf("输入列："); 
				}
				get_array(NULL,&little,col,row);//获取little[row][col] 
				break;
			}
			case 'e':return ;
			default:flag = 1;break;
		}
		if(flag)//错误输入 
		{
			printf("输入错误！\n");
			system("pause");
			break;
		}
		if(big) //大数组 
		{
			for(i = 0; i < col; i++)
			{
				big[i] = rand() % 100;
				
			}
			switch(type)
			{
				case 'a':{
					test_time = clock();//开始时间记录 
					insertSort(big,col);
					test_time = clock() - test_time;//获取排序时间 
					break;
				}
				case 'b':{
					get_array(&temp,NULL,col,0);
					test_time = clock();//开始时间记录 
					MergeSort(big,0,col,temp);
					test_time = clock() - test_time;//获取排序时间 
					free(temp);
					break;
				}
				case 'c':{
					test_time = clock();//开始时间记录	
					QuickSort_Recursion(big,0,col);
					test_time = clock() - test_time;//获取排序时间
					break;
				} 
				case 'd':{
					test_time = clock();//开始时间记录	
					RadixCountSort(big,col);
					test_time = clock() - test_time;//获取排序时间
					break;
				}
			}
			printf("运行时间:%dms\n",test_time);
			fp = fopen("date","w");
			for(i = 0; i < col; i++)
			{
				fprintf(fp,"%d ",big[i]);
			}
			system("pause");
			free(big);
			big = NULL;
		}
		else if(little)
		{
			for(i = 0; i < row; i++)
			{
				for(j = 0; j < col; j++)
				{
					little[i][j] = rand() % 100;
				}
			}
			switch(type)
			{
				case 'a':{
					test_time = clock();//开始时间记录 
					for(i = 0; i < row; i++)
						insertSort(*(little+i),col);
					test_time = clock() - test_time;//获取排序时间 
					break;
				}
				case 'b':{
					get_array(&temp,NULL,col,0);
					test_time = clock();//开始时间记录 
					for(i = 0; i < row; i++)
						MergeSort(*(little+i),0,col,temp);
					test_time = clock() - test_time;//获取排序时间 
					free(temp);
					break;
				}
				case 'c':{
					test_time = clock();//开始时间记录	
					for(i = 0; i < row; i++)
						QuickSort_Recursion(*(little+i),0,col);
					test_time = clock() - test_time;//获取排序时间
					break;
				} 
				case 'd':{
					test_time = clock();//开始时间记录	
					for(i = 0; i < row; i++)
						RadixCountSort(*(little+i),col);
					test_time = clock() - test_time;//获取排序时间
					break;
				}
			}
			printf("运行时间:%dms\n",test_time);
			fp = fopen("date","w");
			for(i = 0; i < row; i++)
			{
				for(j = 0; j < col; j++)
					fprintf(fp,"%d ",little[i][j]);
				fprintf(fp,"\n");
			}
			fclose(fp);
			system("pause");	
		} 
	}	
}
int main()
{
	int flag;
	char ch,type;
	flag = 0;
	while(1)
	{
		system("cls");
		tips();
		type = getch('a','e');
		if(type == 'e')  break;
		else if(type < 'a' || type > 'e')
		{
			printf("输入格式错误请重新输入！\n");
		}
		else
		{
			function(type);	
		}
	}
}
