/***************************************************************************************
 *	FileName					:	Pstring_2.c
 *	CopyRight					:	
 *	ModuleName					:	get the longest palindrome string
 *
 *	CPU							:
 *	RTOS						:
 *
 *	Create Data					:	2020/4/7
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
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../head/input.h"

/**************************************************************
*	Function Define Section
**************************************************************/

/**
 *  @name:int** Matrix_Create(int n)
 *	@description:Creat a n*n matrix filled with zero
 *	@param:n		
 *	@return	:int **	
 *  @notice:None
 */
 int** Matrix_Create(int n)
 {
 	int **matrix;
 	int i,j;
 	matrix = (int **)malloc(sizeof(int*)*n);
 	for(i=0;i<n;i++) *(matrix+i) = (int *)malloc(sizeof(int)*n);
 	for(i=0;i<n;i++)
 	{
 		for(j=0;j<n;j++)
 		{
 			*(*(matrix+i)+j)= 0;
		 }
	 }
	return matrix;
 }
 
 /**
 *  @name:char* Plongest(char *s,int *max)
 *	@description:retrun the head of the longest palindrome string and return the max_length to max
 *	@param:s,max	
 *	@return:char *	
 *  @notice:None
 */
 
 char* Plongest(char *s,int *max)
 {
 	int **matrix,max_start,max_len,cur_len,i,j,n;
	max_start = max_len = 0;
  	n = strlen(s);
 	matrix = Matrix_Create(n);//����һ��n*n��0���󣬵�λ����Ҳ�� 
 	for(j=0;j<n;j++)//matrix[i][j]Ϊ��s[i]��s[j]�Ƿ�Ϊ�����ַ��� 
 	{
 		for(i=0;i<=j;i++)
 		{
 			if(j - i < 2)	*(*(matrix+i)+j) = (s[i] == s[j]);//��s[i]��s[j]����ʱ���ж������Ƿ���� 
			else	*(*(matrix+i)+j) = ((s[i] == s[j]) && *(*(matrix+i+1)+j-1));//����i+1��j-1Ϊ�����ַ������ж�s[i]��s[j]�ܷ�����������ǰ�����ַ��� 
			cur_len = j + 1 - i;
			if(*(*(matrix+i)+j) && cur_len > max_len)
			{
				max_start = i;
				max_len = cur_len;
			}
		 }
	 }
	*max = max_len;
	return &s[max_start];
 } 
 
 /**
 *  @name:char getch(char from,char to)
 *	@description:get a correct character from a string
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
 	int n,i,j,max;
 	char s[1001],*str;
 	printf("����:");
	while(1)
 	{
 		gets(s);
 		str = Plongest(s,&max);
 		*(str+max) = '\0';
		printf("���:%s\n",str);
		printf("����'y'�˳��������������...   ");
		if((getch('y','y'))=='y') break;
		printf("����:");
	}
 	return 0;
 }
