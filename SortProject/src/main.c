#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"qgsort.c"
#include<time.h>
int get_data(int *e)//�������루�������̣� 
{
	char ch[30];
	int flag,i,len;
	long long int result;
	result = 0,i = 0,flag = 1;
	len = strlen(ch); 
	gets(ch);
	if(ch[i] == '-')//�ж������Ƿ�Ϊ���� 
	{
		flag = -1;
		i++; 
	}
	while(ch[i])
	{
		if(ch[i]<'0' || ch[i]>'9') 
		{
			printf("�����ʽ����!\n");
			return 0;
		}
		else if(result < -2147483648LL || result > 2147483647LL)//�ж��Ƿ������������ 
		{  
			printf("���������\n");
			return 0;
		}
		result = result*10 + ch[i] - '0';
		i++;		
	}
	*e = (int)result * flag;//flag�ж����� 
	return 1;
 } 
 
char getch(char from,char to)//�û�ѡ�����루�ַ�����ȡ�󷵻���Чѡ���ܣ���Χ��from��to�� 
{
	char str[50];
	int i,len;
	gets(str);//�ַ�����ȡ 
	len = strlen(str);
	for(i = 0; i<len; i++) { 
		if(str[i]>=from && str[i]<=to) return str[i];//������Чѡ��ֱ�ӷ��� 
	}
	return str[len-1];//������֮����Ҳ�����Ч����ֱ�ӷ���������� 
}

void data_choices()//����ѡ�� 
{
	printf("|��������a.�����ݲ��ԣ�10000����������|\n");
	printf("|��������b.�����ݲ��ԣ�50000����������|\n");
	printf("|������ c.�����ݲ��ԣ�200000����������|\n");
	printf("|������������d.С���ݲ��� ������������|\n"); 
	printf("|������������  e.�˳�   ��������������|\n");
}

void tips()//����ʽѡ�� 
{
	printf("|��������a.�������򡪡�����|\n");
	printf("|��������b.�鲢���򡪡�����|\n"); 
	printf("|��������c.�������򡪡�����|\n");
	printf("|��������d.�������򡪡�����|\n");
	printf("|��������  e.�˳�  ��������|\n");
}
void get_array(int **big,int ***small,int col,int row)//���齨�� 
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
	srand((unsigned)time(NULL)); //������������� 
	while(1)
	{
		system("cls");
		data_choices();
		switch(ch = getch('a','e'))
		{
			case 'a':{
				col = 10000;
				get_array(&big,NULL,10000,0);//��ȡbig[10000] 
				break;
			}
			case 'b':{
				col = 50000;
				get_array(&big,NULL,50000,0);//��ȡbig[50000] 
				break;
			}
			case 'c':{
				col = 200000;
				get_array(&big,NULL,200000,0);//��ȡbig[200000] 
				break;
			}
			case 'd':{
				printf("�����У�");
				while(!get_data(&row))//��ȡ�� 
				{
					printf("������󣡰�'Y'��������,������˳�\n");
					if(getch('Y','Y') != 'Y') return ;
					printf("�����У�"); 
				}
				printf("������: ");//��ȡ�� 
				while(!get_data(&col))
				{
					printf("������󣡰�'Y'��������,������˳�\n");
					if(getch('Y','Y') != 'Y') return ;
					printf("�����У�"); 
				}
				get_array(NULL,&little,col,row);//��ȡlittle[row][col] 
				break;
			}
			case 'e':return ;
			default:flag = 1;break;
		}
		if(flag)//�������� 
		{
			printf("�������\n");
			system("pause");
			break;
		}
		if(big) //������ 
		{
			for(i = 0; i < col; i++)
			{
				big[i] = rand() % 100;
				
			}
			switch(type)
			{
				case 'a':{
					test_time = clock();//��ʼʱ���¼ 
					insertSort(big,col);
					test_time = clock() - test_time;//��ȡ����ʱ�� 
					break;
				}
				case 'b':{
					get_array(&temp,NULL,col,0);
					test_time = clock();//��ʼʱ���¼ 
					MergeSort(big,0,col,temp);
					test_time = clock() - test_time;//��ȡ����ʱ�� 
					free(temp);
					break;
				}
				case 'c':{
					test_time = clock();//��ʼʱ���¼	
					QuickSort_Recursion(big,0,col);
					test_time = clock() - test_time;//��ȡ����ʱ��
					break;
				} 
				case 'd':{
					test_time = clock();//��ʼʱ���¼	
					RadixCountSort(big,col);
					test_time = clock() - test_time;//��ȡ����ʱ��
					break;
				}
			}
			printf("����ʱ��:%dms\n",test_time);
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
					test_time = clock();//��ʼʱ���¼ 
					for(i = 0; i < row; i++)
						insertSort(*(little+i),col);
					test_time = clock() - test_time;//��ȡ����ʱ�� 
					break;
				}
				case 'b':{
					get_array(&temp,NULL,col,0);
					test_time = clock();//��ʼʱ���¼ 
					for(i = 0; i < row; i++)
						MergeSort(*(little+i),0,col,temp);
					test_time = clock() - test_time;//��ȡ����ʱ�� 
					free(temp);
					break;
				}
				case 'c':{
					test_time = clock();//��ʼʱ���¼	
					for(i = 0; i < row; i++)
						QuickSort_Recursion(*(little+i),0,col);
					test_time = clock() - test_time;//��ȡ����ʱ��
					break;
				} 
				case 'd':{
					test_time = clock();//��ʼʱ���¼	
					for(i = 0; i < row; i++)
						RadixCountSort(*(little+i),col);
					test_time = clock() - test_time;//��ȡ����ʱ��
					break;
				}
			}
			printf("����ʱ��:%dms\n",test_time);
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
			printf("�����ʽ�������������룡\n");
		}
		else
		{
			function(type);	
		}
	}
}
