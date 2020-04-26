/***************************************************************************************
 *	FileName					:	
 *	CopyRight					:
 *	ModuleName					:	
 *
 *	CPU							:
 *	RTOS						:
 *
 *	Create Data					:	
 *	Author/Corportation			:	
 *
 *	Abstract Description		:	
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *	
 *
 ***************************************************************************************/

#include"../ͷ�ļ�/BinaryTree.h"

/**************************************************************
*	Function Define Section
**************************************************************/

/**
 *  @name��Status InitBiTree(BiTree T) 
 *	@description:��������ʼ�� 
 *	@param��T 
 *	@return	:Status	
 *  @notice:None
 */
Status InitBiTree(BiTree *T)
{
	*T = NULL;
	if(!*T) return ERROR;  
	return SUCCESS;
}
//�������������ն�����T
Status DestroyBiTree(BiTree* T)
{
	if(!*T) return SUCCESS;
	DestroyBiTree(&((*T)->lchild));//���� 
	DestroyBiTree(&((*T)->rchild));//�Һ��� 
	free(*T);
}
/**
 *  @name:void InsertNode(BiTree *T,TElemtype e)
 *	@description:�������������� 
 *	@param:T(�ڵ�)
 *	@return:None		
 *  @notice:None
 */
void InsertNode(BiTree *T,TElemType e)
{
	BiTNode *temp;
	if(e < (*T)->data)
	{
		if(!(*T)->lchild)//���Ӳ�����ʱֱ�Ӳ��뵽���� 
		{
			(*T)->lchild = (BiTree)malloc(sizeof(BiTNode));
			temp = (*T)->lchild;
			temp->lchild = temp->rchild = NULL;
			temp->data = e;
		}
		else
		{
			InsertNode(&((*T)->lchild),e);
		}
	}
	else if(e > (*T)->data)
	{
		if(!(*T)->rchild)//�Һ��Ӳ�����ʱֱ�Ӳ��뵽�Һ��� 
		{
			(*T)->rchild = (BiTree)malloc(sizeof(BiTNode));
			temp = (*T)->rchild;
			temp->lchild = temp->rchild = NULL;
			temp->data = e;
		}
		else
		{
			InsertNode(&((*T)->rchild),e);
		}
	}
	else
	{
		temp = (BiTree)malloc(sizeof(BiTNode));
		temp->data = e;
		temp->lchild = (*T)->lchild;
		(*T)->lchild = temp;
		temp->rchild = NULL;	
	}
}
/**
 *  @name:BiTNode* CTree(char *s,int start,int end)
 *	@description:����׺���ʽ���������� 
 *	@param:�ַ���s����ʼλ��start, ��ֹλ��end 
 *	@return:BiTNode*
 *  @notice:None
 */
 BiTNode* CTree(char *s,int start,int end)
 {
	BiTNode *p;
    int k,plus=0,posi,posj;
    if (start==end)    //ֻ��һ���ַ���ֱ�����    
    {
        p = (BiTNode *)malloc(sizeof(BiTNode));   
        p->data = s[start];                      
        p->lchild = NULL;
        p->rchild = NULL;
        return p;
    }
    for (k = start; k <= end; k++)
    { 
        if (s[k]=='+' || s[k]=='-')
        {
            plus++;
            posi = k;              //���һ��+��-��λ��
        }
    }
	if (plus==0)   
	{              //û��+��-��������ҵ�'*','/' 
        for (k = start; k <= end; k++)
        {
		    if (s[k]=='*' || s[k]=='/')
            {
                plus++;
                posi = k;
            }
    	} 
	}
    if (plus!=0)
    {
        p=(BiTNode *)malloc(sizeof(BiTNode));
        p->data = s[posi];                //�ڵ�ֵ��s[posi]
        posj = posi;
        do
        {
        	posi--;
		}while(s[posi]==' ');
		do
		{
			posj++;
		}while(s[posj]==' ');
        p->lchild = CTree(s,start,posi);   //��������s[begin]��s[posi-1]����
        p->rchild = CTree(s,posj,end);   //��������s[posi+1]��s[end]����
        return p;
    }
    else  return NULL;
 }

/**
 *  @name:Status CreateBiTree(BiTree T,char* definition)
 *	@description:����definition���������� 
 *	@param:T��defintion 
 *	@return:Status 
 *  @notice:None
 */
Status CreateBiTree(BiTree* T, char* definition)
{
	char data,datas[50];
	int i,len;
	if(!strcmp(definition,"BiTree"))
	{
		while((data = getchar())=='\n' || data == ' ') ;
		if(data == '#')
		{
			*T = NULL;
			return SUCCESS;
		}
		if(!*T) 
		{
			*T = (BiTree)malloc(sizeof(BiTNode));//�ڵ㽨�� 
			(*T)->lchild = (*T)->rchild = NULL; 
			if(!*T)
			{
				printf("�ڴ����ʧ��!\n");
				return ERROR;
			}
		}
		(*T)->data = data;
		if(!CreateBiTree(&((*T)->lchild),definition)) return ERROR;
		if(!CreateBiTree(&((*T)->rchild),definition)) return ERROR;
	}
	else if(!strcmp(definition,"BSTree")) 
	{
		gets(datas);
		i = 0;
		while(datas[i]==' ') i++;
		if(!*T) 
		{
			*T = (BiTree)malloc(sizeof(BiTNode));//�ڵ㽨�� 
			(*T)->data = datas[i];
			(*T)->lchild = (*T)->rchild = NULL; 
			if(!*T)
			{
				printf("�ڴ����ʧ��!\n");
				return ERROR;
			}
		}
		len = strlen(datas);
		for(; i < len; i++)
		{
			if(datas[i] == ' ') continue;
			InsertNode(T,datas[i]);
		} 
	}
	else if(!strcmp(definition,"BCTree"))
	{
		gets(datas);
		i = 0;
		while((datas[i]>='0' && datas[i]<='9') || datas[i] == ' ' || datas[i] == '+' || datas[i] == '-' || datas[i] == '/' || datas[i] == '*') i++;
		if(i != strlen(datas)) return ERROR;
		*T = CTree(datas,0,strlen(datas)-1);
	 } 
	return SUCCESS;
}

Status print(TElemType e)
{
	printf("%c ",e);
}

//���²��ֺ�������δָ����������
Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e))//������� 
{
	if(!T) return SUCCESS;
	visit(T->data);
	PreOrderTraverse(T->lchild,visit);//���� 
	PreOrderTraverse(T->rchild,visit);//�Һ��� 
	return SUCCESS;
}
//��ʼ������������T���ڣ�visitΪ�Խ��Ĳ�����Ӧ�ú���
//����������������T����ÿ��������visit����һ���ҽ�һ�Σ�һ��visitʧ�ܣ������ʧ��
Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e))	//�������
{
	if(!T) return SUCCESS;
	InOrderTraverse(T->lchild,visit);//���� 
	visit(T->data);
	InOrderTraverse(T->rchild,visit);//�Һ��� 
	return SUCCESS;
}
Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e))	//�������
{
	if(!T) return SUCCESS;
	PostOrderTraverse(T->lchild,visit);//���� 
	PostOrderTraverse(T->rchild,visit);//�Һ��� 	
	visit(T->data);	
	return SUCCESS;
}
Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e))//�������
{
	BiTree temp;
	typedef struct TreeQueue
	{
		BiTree TQueue[MAXSIZE];
		int rear;
		int front;
	}Queue;//��ʱ���� 
	Queue* Q = (Queue*)malloc(sizeof(Queue));
	Q->front = Q->rear = 0;
	Q->TQueue[Q->rear++] = T;
	while(Q->rear != Q->front)
	{
        temp = Q->TQueue[Q->front++];
        visit(temp->data);
        if (temp->lchild)     
            Q->TQueue[Q->rear++] = temp->lchild;//��������ʱ��� 
        if (temp->rchild)    
            Q->TQueue[Q->rear++] = temp->rchild;//�����Һ���ʱ���	
	}
}
int Value(BiTNode* T)
{
	int v1,v2;
    if (!T) return 0;//����ֱ�ӷ���0 
    if (!T->lchild && !T->rchild)  return T->data - '0';//������ֵ 
    v1=Value(T->lchild); //�ȼ���������
    v2=Value(T->rchild); //�ټ���������
    switch(T->data)     //��������������Ľ���ٽ������㣬���õ��Ǻ��������˼·
    {
    	case '+':return v1+v2;
    	case '-':return v1-v2;
   		case '*': return v1*v2;
   		case '/':
        if (v2!=0)
            return v1/v2;
        else
            abort();
    }
}
