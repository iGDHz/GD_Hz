#include<stdio.h>
#include<stdlib.h>
#include"duLinkedList.c"
#include<string.h>
char getch(); 
Status get_data(); //�������루�����쳣����ʱ��ɵ����⣩
void tips();//˵��������� 
Status search(DuLinkedList L,ElemType e);//�����Ƿ���ҵ���Ӧ�ڵ� 

//�ú���ָ���ڲ�ͬ�Ĳ���������ò�ͬ�ĺ��� 
void qInsert(DuLinkedList L,Status (*insert)(DuLNode*, DuLNode* )); 

//�ڵ�ɾ������ 
void Delete(DuLinkedList L);

//�½ڵ�Ľ����˴�Ϊq�ڵ�Ľ��� 
Status DuLNode_creat(DuLinkedList *L);
int main()
 {	char ch;
 	int flag,data;
 	DuLinkedList L,q;
 	flag = data = 0;
	while(!InitList_DuL(&L))
	{
		printf("��ʼ��ʧ�ܣ�\n");
		printf("�������³�ʼ��...\n");
		if((data++) == 10) //��γ�ʼ��ʧ�ܺ�ֱ���˳����� 
		{
			printf("��ʼ��ʧ�ܣ������˳�����\n");
			system("pause");
		}
	 } 
	tips();
 	while(1)//ʹ�ö���ѭ��ˢ�½��� 
 	{
 		while((ch = getch())!='f')
 		{
 			printf("���ѡ��%c\n",ch);
 			switch(ch)
 			{
 				case 'a':{if(!DuLNode_creat(&q)) break;
 					else 
 					{
 						//ֱ�ӵ��� InsertAfterList_DuL����������������Ӳ��� 
					 	InsertAfterList_DuL(L,q);
					 	L->data++;//ͷ�ڵ��¼�ڵ���� 
					 	printf("����ɹ�!\n"); 
					 } 
					break;
				 }
				case 'b':qInsert(L,InsertBeforeList_DuL);L->data++;break;
				case 'c':qInsert(L,InsertAfterList_DuL);L->data++;break;
				case 'd':TraverseList_DuL(L->next,print_int);break;
				case 'e':Delete(L);L->data;break;
				case 'f':break;
				default:flag=1;break;
			 }
			if(flag)
		 	{
		 		flag = 0 ;
		 		printf("�����ʽ����\n����������:");
		 	}//�����ʽ����ʱ�������Ѳ��������� 
		 	else break;//��ȷ��ʽ�����ˢ�½��� 
		 }
		if(ch == 'f') break;
		system("pause");
		system("cls");
		tips();
	 }
	 DestroyList_DuL(&L);
 	return 0;
 }
 void tips()
{
	printf("|��������a.��ӽڵ�       ��������|\n");	
	printf("|��������b.p�ڵ�ǰ����ڵ㡪������|\n");	
	printf("|��������c.p�ڵ�����ڵ㡪������|\n");	
	printf("|��������d.�������       ��������|\n");	
	printf("|��������e.ɾ���ڵ�       ��������|\n");
	printf("|��������f.�˳�           ��������|\n\n");
	printf("����:");				
}
char getch()//�û�ѡ�����루�ַ�����ȡ�󷵻���Чѡ���ܣ� 
{
	char str[50];
	int i;
	gets(str);//�ַ�����ȡ 
	for(i = 0; i<strlen(str); i++) {
		if(str[i]>='a' &&str[i]<='f') return str[i];//������Ч����ֱ�ӷ��� 
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
			printf("�Ǹ�ʽ����!�˻�������...\n");
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
Status DuLNode_creat(DuLinkedList *L)
{
	*L = (DuLinkedList)malloc(sizeof(DuLNode));
	if(!(*L)) 
	{
		printf("�ڵ㽨��ʧ��!\n");
		return ERROR;
	 } 
	printf("�������ݣ�"); 
	while(!(get_data(&(*L)->data))) 
	{
		printf("����'a'�����������ݣ�����ֵ�˳���\n");
		if(getch() != 'a') return ERROR;
		printf("�������ݣ�"); 
	}
}
Status search(DuLinkedList L,ElemType e)
{
	while(L)
	{
		if(L->data == e) 	return SUCCESS;
		L=L->next;
	}
	return ERROR;
}
void qInsert(DuLinkedList L,Status (*insert)(DuLNode*, DuLNode* ))
{
	DuLinkedList q,p;
	int data;
	TraverseList_DuL(L->next,print_int);//�Ƚ����������������û�ѡ�� 
	if(!L->next) 
	{
		printf("������Ϊ�գ�����ӽڵ��ʹ��!\n");
		return ;
	}
	printf("ѡ��p�ڵ�...\n");
	printf("����p�ڵ㣺");
	if(!get_data(&data)) return; 
	while(!(search(L,data)))//�������ʱѭ�����룬Ҳ��ѡ���˳� 
	{
		printf("���Ҳ���p�ڵ㣬����'a'�������ң�����ֵ�˳�...\n");
		if((getch())!='a') return;
		printf("����p�ڵ㣺");
		if(!get_data(&data)) return; 	
	}	
	p = L->next;
	while(1)
	{
		if(p->data == data) break;
		p = p->next;
	}
	printf("��������ڵ�...\n");
	if(!DuLNode_creat(&q)) return ;
	(*insert)(p,q);
	TraverseList_DuL(L->next,print_int);
}
void Delete(DuLinkedList L)
{
	DuLinkedList temp;
	int data;
	temp = L = L->next;
	if(!L)//������ɾ������ 
	{
		printf("�������޷�����ɾ������!\n");
		return ;
	}
	TraverseList_DuL(L,print_int);//��ʾ�����нڵ���ѡ��ɾ���ڵ� 
	printf("����Ҫɾ���Ľڵ�\n");
	printf("�����룺");
	if(!get_data(&data)) return ; 
	while(!(search(L,data)))
	{
		printf("���Ҳ����ýڵ㣬����'a'�������ң�����ֵ�˳�...\n");
		if((getch())!='a') return;
		printf("�������룺");
		if(!get_data(&data)) return; 	
	}
	while(1)
	{
		if(L->data == data) break;
		L = L->next;
	}
	DeleteList_DuL(L,&data);
	printf("�ɹ�ɾ������:%d\n",data);
}
