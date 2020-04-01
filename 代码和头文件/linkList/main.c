#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../head/linkedList.h"
extern void print_int(ElemType e);
void tip()//�������չʾ 
{
	printf("|��������1.Add node           ��������|\n");
	printf("|��������2.Traverse list      ��������|\n");
	printf("|��������3.Reverse list       ��������|\n");
	printf("|��������4.ReverseEvenList    ��������|\n");
	printf("|��������5.Insert list        ��������|\n");
	printf("|��������6.Delete list        ��������|\n");
	printf("|��������7.IsLoopList         ��������|\n");
	printf("|��������8.Retrun middle node ��������|\n");
	printf("|��������9.EXIT               ��������|\n\n");
	printf("input:");
}
char getch()//�û�ѡ�����루�ַ�����ȡ�󷵻���Чѡ���ܣ� 
{
	char str[50];
	int i;
	gets(str);//�ַ�����ȡ 
	for(i = 0; i<strlen(str); i++) {
		if(str[i]>='1' &&str[i]<='9') return str[i];//������Ч����ֱ�ӷ��� 
	}
	return str[i];//������֮����Ҳ�����Ч����ֱ�ӷ���������� 
}
Status get_data(ElemType *e)//�������루�������̣� 
{
	char ch[30];
	int flag,i;
	*e = 0;
	flag = i = 0;
	gets(ch);
	while(ch[i]!='\0')
	{
		if((flag ||ch[i]!='-')&&(ch[i]<'0' || ch[i]>'9'))
		{
			printf("Unformatted input!\n");
			return ERROR;
		} 
		else if(ch[i] == '-' && (ch[i]>='0' || ch[i]<='9')) flag = 1; 
		else
		{
			(*e) =(*e)*10+ch[i]-'0';
		}
		i++;
	 } 
	if(flag)  *e = (*e) * (-1);
	 return SUCCESS;
 } 
int main() {
	LinkedList L;
	char ch;
	int flag = 1;
	if(!InitList(&L)) exit(EXIT_FAILURE);//����ĳ�ʼ�� 
	tip();
	while(1) {
		while((ch = getch())!='9') 
		{
			printf("Your choice:%c\n",ch);//�����Ч���� 
			switch(ch) {		
				case '1': {
					if(!LNode_add(L)) printf("Add failure!\n");//���ʧ�ܷ��ش�����Ϣ 
					else printf("Successfully added!\n");//���سɹ���ӵ���Ϣ 
					break;
				}
				case '2': {
					TraverseList(L,print_int);//����������print_int�ķ�ʽ����������� 
					break;
				}
				case '3': {
					if(!ReverseList(&L)) printf("Reverse error!\n");//����ת��ʧ�ܷ��ش�����Ϣ 
					else printf("Reverse success!\n");//����ת�óɹ���Ϣ 
					break;
				}
				case '4': {
					L = ReverseEvenList(&L);//ʵ���������ż����ת�� 
					printf("ReverseEven success!\n");//ת�óɹ� 
					break;
				}
				case '5': {
					Search(&L);//���Ҳ��ڽڵ������½ڵ� 
					break;
				}
				case '6': {
					Delete(&L);//���Ҳ�ɾ���ڵ� 
					break;
				}
				case '7': {
					if(IsLoopList(L->next)) printf("This is a loop list.\n"); 
					else printf("This is not a loop list.\n");
					break;//�����Ƿ�Ϊ�ɻ�������Ϣ 
				}
				case '8': {
					TraverseList(L,print_int);//��ʾ������������ 
					printf("%d\n",(FindMidNode(&L))->data);//��������м����� 
					break;
				}
				case '9':break;//����β��� 
				default:flag = 0;//�ж��Ƿ�Ϊ�������� 
				break; 
			}
			if(!flag) {
				flag = 1;
				printf("Error format input��\n");//����������ʾ 
				printf("input:");
			} else break;//��������ʱ����ѭ��ˢ�½��� 
		}
		if(ch == '9') break;//����ѭ���������� 
		system("pause");
		system("cls");
		tip();
	}
	DestroyList(&L);//�������� 
	return 0;
}
