#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"qgsort.c"

/**
 *  @name:void tips()
 *	@description:�����㷨ѡ�� 
 *	@param:None			
 *	@return	:None	
 *  @notice:None
 */
void tips()//����ʽѡ�� 
{
	printf("|��������a.�������򡪡�����|\n");
	printf("|��������b.�鲢���򡪡�����|\n"); 
	printf("|��������c.�������򡪡�����|\n");
	printf("|��������d.�������򡪡�����|\n");
}

 /**
 *  @name:char getch(char from,char to)
 *	@description:��ȡ��ȷ����ѡ�� 
 *	@param:from,to			
 *	@return:char	
 *  @notice:None
 */
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

int main()
{
	int i,a[50000],*temp;
	FILE *fp;
	char ch;
	i = 0;
	fp = fopen("test_data","r");
	;
	while(!feof(fp))
	{
		fscanf(fp,"%d",&a[i]);
		i++;
	 } 
	temp = (int*)malloc(sizeof(int)*5000);
	fclose(fp);
	tips();
	while(1)
	{
		ch = getch('a','e');
		switch(ch)
		{
			case 'a':{
				insertSort(a,5000);
				break;
			}
			case 'b':{
				MergeSort(a,0,5000,temp);
				break;
			}
			case 'c':{
				QuickSort_Recursion(a,0,5000);
				break;
			}
			case 'd':{
				RadixCountSort(a,5000); 
				break;
			}
			default:{
				printf("����������������룡\n"); 
				break;
			}
		}
		if(ch >= 'a' && ch <= 'd') break;
	}
	if(ch != 'e')
	{
		fp = fopen("test_data","w");
		for(i = 0; i <= 5000; i++)
		{
			fprintf(fp,"%d ",a[i]);
		}
		fclose(fp);
	}
	return 0;
}
