#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*+
constexpr auto MaxLen = 100;
//线索二叉树 
typedef struct ThreadNode {
	int data;
	ThreadNode* lChild, * rChild;
	int lTag, rTag;
}ThreadNode, * ThreadTree;
typedef struct CThreadNode {
	char data;
	CThreadNode* lChild, * rChild;
}CThreadNode, * CThreadTree;
//树初始化
bool InitTree(ThreadTree& t) {
	t = (ThreadNode*)malloc(sizeof(ThreadNode));
	t->data = 1;
	t->lChild = NULL;
	t->lTag = 0;
	t->rChild = NULL;
	t->rTag = 0;
	return true;
}
//树初始化
bool InitCTree(CThreadTree& t,char data) {
	t = (CThreadNode*)malloc(sizeof(CThreadNode));
	t->data = data;
	t->lChild = NULL;
	t->rChild = NULL;
	return true;
}
//指定节点添加左孩子
bool AddlChild(ThreadNode* q, int data) {
	ThreadNode* s = (ThreadNode*)malloc(sizeof(ThreadNode));
	s->data = data;
	s->lChild = NULL;
	s->lTag = 0;
	s->rChild = NULL;
	s->rTag = 0;
	q->lChild = s;
	return true;
}
//指定节点添加右孩子
bool AddrChild(ThreadNode* q, int data) {
	ThreadNode* s = (ThreadNode*)malloc(sizeof(ThreadNode));
	s->data = data;
	s->lChild = NULL;
	s->lTag = 0;
	s->rChild = NULL;
	s->rTag = 0;
	q->rChild = s;
	return true;
}
//指定节点添加左孩子
bool CAddlChild(CThreadNode* q, int data) {
	CThreadNode* s = (CThreadNode*)malloc(sizeof(CThreadNode));
	s->data = data;
	s->lChild = NULL;
	s->rChild = NULL;
	q->lChild = s;
	return true;
}
//指定节点添加右孩子
bool CAddrChild(CThreadNode* q, int data) {
	CThreadNode* s = (CThreadNode*)malloc(sizeof(CThreadNode));
	s->data = data;
	s->lChild = NULL;
	s->rChild = NULL;
	q->rChild = s;
	return true;
}
//栈
typedef struct StackNode {
	ThreadNode* data;
	StackNode* next;
}StackNode,*Stack;
void InitStack(Stack &s) {
	s = (StackNode*)malloc(sizeof(StackNode));
	s->data = NULL;
	s->next = NULL;
}
void Push(Stack &s, ThreadNode* data) {
	StackNode *p= (StackNode*)malloc(sizeof(StackNode));
	p->data = data;
	p->next = s->next;
	s->next = p;
}
void Pop(Stack &s, ThreadNode*&data) {
	StackNode* p=s->next;
	s->next = p->next;
	data = p->data;
	free(p);
}
void GetTop(Stack s, ThreadNode*& data) {
	data = s->next->data;
}
bool IsEmptyStack(Stack &s) {
	if (s->next) {
		return false;
	}
	return true;
}
//队列
typedef struct QueueNode {
	ThreadNode* data;
	QueueNode* next;
}QueueNode;
typedef struct Queue {
	QueueNode* rear, * front;
}LinkQueue;
void InitQueue(Queue &q) {
	q.rear=q.front = (QueueNode*)malloc(sizeof(QueueNode));
	q.front->next = NULL;
}
bool IsEmptyQueue(Queue &q) {
	if (q.rear == q.front) {
		return true;
	}
	return false;
}
void EnQueue(Queue &q, ThreadNode* data) {
	QueueNode* s = (QueueNode*)malloc(sizeof(QueueNode));
	s->data= data;
	s->next = q.rear->next;
	q.rear->next = s;
	q.rear = s;
}
void DeQueue(Queue &q, ThreadNode*& data) {
	QueueNode* p = q.front->next;
	if (p == q.rear) {
		q.rear = q.front;
	}
	q.front->next = p->next;
	data = p->data;
	free(p);
}

//4.逆层序遍历 从下到上，从右到左
void InvestLevel(ThreadTree &t) {
	Stack s ;//初始化栈和队列
	InitStack(s);
	Queue q;
	InitQueue(q);
	ThreadNode* p = t;
	EnQueue(q,p);//将头结点入队
	while (!IsEmptyQueue(q)) {//队列为空时表示所有节点都已经入栈
		DeQueue(q, p);//出队
		if (p->lChild) {//出队元素左右孩子若存在就入队
			EnQueue(q,p->lChild);
		}
		if (p->rChild) {//出队元素左右孩子若存在就入队
			EnQueue(q, p->rChild);
		}
		Push(s,p);//将出队元素入栈
	}//此时所有节点都已经按正常层序遍历顺序入栈
	while (!IsEmptyStack(s)) {//依次出栈直到栈空，即为逆层次遍历
		Pop(s, p);
		printf("%d", p->data);
	}
}
//5.获取二叉树高度
int  GetHeight(ThreadTree& t) {
	//制造一个队列，设置一个level记录层级
	// 当出栈的元素front超过last时，level++、last指向下一列最后一个元素（此时下一列已经入队）
	ThreadNode* q[100]{};
	int front = -1, rear = -1, level = 0, last = 0;
	ThreadNode* p = t;
	q[++rear] = p;
	while (front < rear) {
		p = q[++front];
		if (p->lChild) { q[++rear] = p->lChild; }
		if (p->rChild) { q[++rear] = p->rChild; }
		if (front == last) {
			level++;
			last = rear;
		}
	}
	return level;
}
//6.判断是否是完全二叉树
bool IsCompleteBiTree(ThreadTree& t) {
	Queue q; InitQueue(q);
	ThreadNode* p = t;
	EnQueue(q, p);
	while (!IsEmptyQueue(q))
	{
		DeQueue(q, p);
		if (p) {
			EnQueue(q, p->lChild);
			EnQueue(q, p->rChild);
		}
		else {
			while (!IsEmptyQueue(q)) {
				DeQueue(q, p);
				if (p) {
					return false;
				}
			}
		}
	}
	return true;
}
//7.拥有双子节点的个数
int DoubleChildNodeNum(ThreadTree& t) {
	if (!t) { return 0; }
	if (t->lChild && t->rChild) {
		return DoubleChildNodeNum(t->lChild) + DoubleChildNodeNum(t->rChild) + 1;
	}
	else {
		return DoubleChildNodeNum(t->lChild) + DoubleChildNodeNum(t->rChild);
	}
}
//8.交换左右子树
void Exchange(ThreadTree& t) {
	if (!t) { return; }
	Exchange(t->lChild);
	Exchange(t->rChild);
	ThreadNode* temp = t->rChild;
	t->rChild = t->lChild;
	t->lChild = temp;
}
int i = 1;
//先序遍历其中为x的值
int  SelectKValue(ThreadTree& t,int k) {
	if (t == NULL) {
		return'#';
	}
	if (i == k) {
		return t->data;
	}
	i++;
	int ch = SelectKValue(t->lChild, k);
	if (ch != '#') {
		return ch;
	}
	ch= SelectKValue(t->rChild, k);
	return ch;

}
//9.后序删除以t为根节点的树
void DeleteTreeNode(ThreadTree t) {
	if (!t) { return; }
	DeleteTreeNode(t->lChild);
	DeleteTreeNode(t->rChild);
	free(t);
}
//10.删除以x为根节点的子树
void PostOrderX(ThreadTree t, int x) {
	if (!t) { return; }
	if (t->lChild && t->lChild->data == x) {//单用一个data==x会出现访问不到叶节点孩子的错误
		DeleteTreeNode(t->lChild);//调用后序删除函数
		t->lChild = NULL;//删除完成后要将左孩子指针置为NULL
	}
	if (t->rChild && t->rChild->data == x) {
		DeleteTreeNode(t->rChild);
		t->rChild = NULL;
	} 
	PostOrderX(t->lChild,x);
	PostOrderX(t->rChild,x);
	
}
//11.打印x的所有祖先，同非递归后序遍历
void PrintXParents(ThreadTree t,int x) {
	ThreadNode* p = t, * r = NULL; Stack s; InitStack(s);
	while (p||!IsEmptyStack(s)) {
		if (p) {
			if (p->data == x) {
				break;
			}
			Push(s, p);
			p = p->lChild;
		}
		else {
			GetTop(s, p);
			if (p->rChild && p->rChild != r) {
				p = p->rChild;
			}
			else
			{
				Pop(s, p);
				r = p;
				p = NULL;
			}
		}//else
	}//while
	while (!IsEmptyStack(s)) {
		Pop(s, p);
		printf("%d", p->data);
	}
}
//12.最近公共祖先
int BothOrigin(ThreadTree root, ThreadNode* p, ThreadNode* q, ThreadNode* r) {
	r = root;
	int ch='#';
	if (!root) { return '#'; }
	
	BothOrigin(root->lChild, p, q, r);
	BothOrigin(root->rChild, p, q, r);	
	if (r->lChild == p || r->rChild == p) {
		ch = BothOrigin(root, r, q, r);
	}
	if (ch != '#') {
		return ch;
	}
	if (r->lChild == q || r->rChild == q) {
		ch = BothOrigin(root, p, r, r);
	}
	return ch;
	if (p == q) {
		r = q;
		return r->data;
	}
}
//13.求二叉树宽度
int GetWidth(ThreadTree t) {
	if (!t) { return 0; }
	ThreadNode* q[100]{};
	int rear = -1, front = -1, last = 0;
	int Width=1;
	ThreadNode *p = t;
	q[++rear] = p;
		while (front<rear) {
			p = q[++front];
			if(p->lChild){ q[++rear] = p->lChild; }
			if(p->rChild){ q[++rear] = p->rChild; }
			if (last == front) {
				Width = rear - front > Width ? rear - front : Width;
				last = rear;
			}
			
		}
		return Width;
}
//15.满二叉先序求后序
void PreGetPost(char pre[],int l1,int h1,char post[],int l2,int h2) {
	int half;
	
	if (h1 >= l1) {
		post[h2] = pre[l1];
		half = (h1 - l1) / 2;
		PreGetPost(pre, l1 + 1, l1 + half, post, l2, l2 + half - 1);
		PreGetPost(pre, l1 + half + 1, h1, post, l2+half , h2-1);
	}
}
//16.叶节点连成单链表
void LeafLinkNode(ThreadTree t,ThreadTree &pre) {
	if (!t) { return; }
	LeafLinkNode(t->lChild, pre);
	LeafLinkNode(t->rChild, pre);
	if (!t->lChild && !t->rChild) {
		pre->rChild = t;
		pre = t;
	}
}

//18.带括号的中缀表达式
void BiTreeInExp(CThreadTree t, int deep) {//用深度来判断是否要加括号
	if (!t) { return; }
	else if (!t->lChild && !t->rChild) { //符号不可能出现在叶子结点上
		printf("%c", t->data);
	}
	else {
		if (deep > 1) {
			printf("(");
		}
		BiTreeInExp(t->lChild, deep + 1);
		printf("%c", t->data);
		BiTreeInExp(t->rChild, deep + 1);
		if (deep > 1) {
			printf(")");
		}
	}
}
void BiTreeInExP(CThreadTree t) {
	BiTreeInExp(t, 1);
}
int Height(ThreadTree t) {
	int hc, hs;
	if (t == NULL) {
		return 0;
	}
	else {
		hc = Height(t->lChild);
		hs = Height(t->rChild);
		if (hc + 1 > hs) {
			return hc + 1;
		}
		else {
			return hs;
		}
	}
}
int main(){
	
	ThreadTree t;
	InitTree(t);
	AddlChild(t, 2);
	AddlChild(t->lChild, 4);
	AddrChild(t->lChild, 5);
	//AddrChild(t, 3);
	//AddlChild(t->rChild, 6);
	//AddrChild(t->rChild, 7);
	//4下面挂
	//AddlChild(t->lChild->lChild, 8);
	//AddrChild(t->lChild->lChild, 9);
	//5下面
	AddlChild(t->lChild->rChild, 10);
	AddlChild(t->lChild->rChild->lChild, 8);
	AddlChild(t->lChild->rChild->lChild->lChild, 9);
	AddrChild(t->lChild->rChild, 11);
	//6下面
	//AddlChild(t->rChild->lChild, 12);
	//AddrChild(t->rChild->lChild, 13);
	//7下面
	//AddlChild(t->rChild->rChild, 14);
	//AddrChild(t->rChild->rChild, 15);
	//逆层次遍历
	
	//InvestLevel(t);
	
	//打印指定节点的所有祖先
	//int height=GetHeight(t);
	//printf("%d", height);
	//PrintXParents(t, 8);
	//printf("%s",IsCompleteBiTree(t)?"true" : "false");
	//printf("%d",DoubleChildNodeNum(t));
	//Exchange(t);
	//InvestLevel(t);
	//9
	//int k = 5;
	//int value = SelectKValue(t, k);
	//printf("%d",value);
	//10
	//PostOrderX(t, 4);
	//InvestLevel(t);

	//12
	//ThreadNode* r = NULL;
	//BothOrigin(t, t->lChild->lChild, t->lChild->rChild, r);
	//printf("%d", r->data);

	//13
	//printf("%d", GetWidth(t));
	//15
	//char s[] = "1245367";
	//char result[7] = {};
	//PreGetPost(s,0,strlen(s)-1,result,0,strlen(s)-1);
	//for (int i = 0; i < strlen(s); i++)
	//{
	//	printf("%c", result[i]);
	//}
	//ThreadTree L; InitTree(L);
	//ThreadNode* p = L;
	//LeafLinkNode(t, p);
	//p = L;

	//16
	//printf("L");
	//while (p->rChild) {
	//	printf("-->%d",p->rChild->data);
	//	p = p->rChild;
	//}

	//18
	CThreadTree exp;
	InitCTree(exp,'*');
	CAddlChild(exp, '+');
	CAddlChild(exp->lChild, 'a');
	CAddrChild(exp->lChild, 'b');
	CAddrChild(exp, '*');
	CAddrChild(exp->rChild, '-');
	CAddlChild(exp->rChild, 'c');
	CAddrChild(exp->rChild->rChild, 'd');
	BiTreeInExP(exp);
	
	printf("%d",Height(t));
}
*/