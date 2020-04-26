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

#include"../头文件/BinaryTree.h"

/**************************************************************
*	Function Define Section
**************************************************************/

/**
 *  @name：Status InitBiTree(BiTree T) 
 *	@description:二叉树初始化 
 *	@param：T 
 *	@return	:Status	
 *  @notice:None
 */
Status InitBiTree(BiTree *T)
{
	*T = NULL;
	if(!*T) return ERROR;  
	return SUCCESS;
}
//操作结果：构造空二叉树T
Status DestroyBiTree(BiTree* T)
{
	if(!*T) return SUCCESS;
	DestroyBiTree(&((*T)->lchild));//左孩子 
	DestroyBiTree(&((*T)->rchild));//右孩子 
	free(*T);
}
/**
 *  @name:void InsertNode(BiTree *T,TElemtype e)
 *	@description:插入搜索二叉树 
 *	@param:T(节点)
 *	@return:None		
 *  @notice:None
 */
void InsertNode(BiTree *T,TElemType e)
{
	BiTNode *temp;
	if(e < (*T)->data)
	{
		if(!(*T)->lchild)//左孩子不存在时直接插入到左孩子 
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
		if(!(*T)->rchild)//右孩子不存在时直接插入到右孩子 
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
 *	@description:用中缀表达式建立二叉树 
 *	@param:字符串s，起始位置start, 终止位置end 
 *	@return:BiTNode*
 *  @notice:None
 */
 BiTNode* CTree(char *s,int start,int end)
 {
	BiTNode *p;
    int k,plus=0,posi,posj;
    if (start==end)    //只有一个字符，直接添加    
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
            posi = k;              //最后一个+或-的位置
        }
    }
	if (plus==0)   
	{              //没有+或-的情况，找到'*','/' 
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
        p->data = s[posi];                //节点值是s[posi]
        posj = posi;
        do
        {
        	posi--;
		}while(s[posi]==' ');
		do
		{
			posj++;
		}while(s[posj]==' ');
        p->lchild = CTree(s,start,posi);   //左子树由s[begin]至s[posi-1]构成
        p->rchild = CTree(s,posj,end);   //右子树由s[posi+1]到s[end]构成
        return p;
    }
    else  return NULL;
 }

/**
 *  @name:Status CreateBiTree(BiTree T,char* definition)
 *	@description:根据definition创建二叉树 
 *	@param:T，defintion 
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
			*T = (BiTree)malloc(sizeof(BiTNode));//节点建立 
			(*T)->lchild = (*T)->rchild = NULL; 
			if(!*T)
			{
				printf("内存分配失败!\n");
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
			*T = (BiTree)malloc(sizeof(BiTNode));//节点建立 
			(*T)->data = datas[i];
			(*T)->lchild = (*T)->rchild = NULL; 
			if(!*T)
			{
				printf("内存分配失败!\n");
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

//以下部分函数定义未指定参数类型
Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e))//先序遍历 
{
	if(!T) return SUCCESS;
	visit(T->data);
	PreOrderTraverse(T->lchild,visit);//左孩子 
	PreOrderTraverse(T->rchild,visit);//右孩子 
	return SUCCESS;
}
//初始条件：二叉树T存在，visit为对结点的操作的应用函数
//操作结果：先序遍历T，对每个结点调用visit函数一次且仅一次，一旦visit失败，则操作失败
Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e))	//中序遍历
{
	if(!T) return SUCCESS;
	InOrderTraverse(T->lchild,visit);//左孩子 
	visit(T->data);
	InOrderTraverse(T->rchild,visit);//右孩子 
	return SUCCESS;
}
Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e))	//后序遍历
{
	if(!T) return SUCCESS;
	PostOrderTraverse(T->lchild,visit);//左孩子 
	PostOrderTraverse(T->rchild,visit);//右孩子 	
	visit(T->data);	
	return SUCCESS;
}
Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e))//层序遍历
{
	BiTree temp;
	typedef struct TreeQueue
	{
		BiTree TQueue[MAXSIZE];
		int rear;
		int front;
	}Queue;//临时队列 
	Queue* Q = (Queue*)malloc(sizeof(Queue));
	Q->front = Q->rear = 0;
	Q->TQueue[Q->rear++] = T;
	while(Q->rear != Q->front)
	{
        temp = Q->TQueue[Q->front++];
        visit(temp->data);
        if (temp->lchild)     
            Q->TQueue[Q->rear++] = temp->lchild;//存在左孩子时入队 
        if (temp->rchild)    
            Q->TQueue[Q->rear++] = temp->rchild;//存在右孩子时入队	
	}
}
int Value(BiTNode* T)
{
	int v1,v2;
    if (!T) return 0;//空树直接返回0 
    if (!T->lchild && !T->rchild)  return T->data - '0';//返回数值 
    v1=Value(T->lchild); //先计算左子树
    v2=Value(T->rchild); //再计算右子树
    switch(T->data)     //将左、右子树运算的结果再进行运算，运用的是后序遍历的思路
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
