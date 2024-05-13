#include<stdio.h>
#include<stdlib.h>
#include<string.h>
constexpr auto MaxLen = 100;
//���������� 
typedef struct ThreadNode {
	int data;
	ThreadNode* lChild, * rChild;
	int lTag, rTag;
}ThreadNode, * ThreadTree;
typedef struct CThreadNode {
	char data;
	CThreadNode* lChild, * rChild;
}CThreadNode, * CThreadTree;
//����ʼ��
bool InitTree(ThreadTree& t) {
	t = (ThreadNode*)malloc(sizeof(ThreadNode));
	t->data = 1;
	t->lChild = NULL;
	t->lTag = 0;
	t->rChild = NULL;
	t->rTag = 0;
	return true;
}
//����ʼ��
bool InitCTree(CThreadTree& t,char data) {
	t = (CThreadNode*)malloc(sizeof(CThreadNode));
	t->data = data;
	t->lChild = NULL;
	t->rChild = NULL;
	return true;
}
//ָ���ڵ��������
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
//ָ���ڵ�����Һ���
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
//ָ���ڵ��������
bool CAddlChild(CThreadNode* q, int data) {
	CThreadNode* s = (CThreadNode*)malloc(sizeof(CThreadNode));
	s->data = data;
	s->lChild = NULL;
	s->rChild = NULL;
	q->lChild = s;
	return true;
}
//ָ���ڵ�����Һ���
bool CAddrChild(CThreadNode* q, int data) {
	CThreadNode* s = (CThreadNode*)malloc(sizeof(CThreadNode));
	s->data = data;
	s->lChild = NULL;
	s->rChild = NULL;
	q->rChild = s;
	return true;
}
//ջ
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
//����
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

//4.�������� ���µ��ϣ����ҵ���
void InvestLevel(ThreadTree &t) {
	Stack s ;//��ʼ��ջ�Ͷ���
	InitStack(s);
	Queue q;
	InitQueue(q);
	ThreadNode* p = t;
	EnQueue(q,p);//��ͷ������
	while (!IsEmptyQueue(q)) {//����Ϊ��ʱ��ʾ���нڵ㶼�Ѿ���ջ
		DeQueue(q, p);//����
		if (p->lChild) {//����Ԫ�����Һ��������ھ����
			EnQueue(q,p->lChild);
		}
		if (p->rChild) {//����Ԫ�����Һ��������ھ����
			EnQueue(q, p->rChild);
		}
		Push(s,p);//������Ԫ����ջ
	}//��ʱ���нڵ㶼�Ѿ��������������˳����ջ
	while (!IsEmptyStack(s)) {//���γ�ջֱ��ջ�գ���Ϊ���α���
		Pop(s, p);
		printf("%d", p->data);
	}
}
//5.��ȡ�������߶�
int  GetHeight(ThreadTree& t) {
	//����һ�����У�����һ��level��¼�㼶
	// ����ջ��Ԫ��front����lastʱ��level++��lastָ����һ�����һ��Ԫ�أ���ʱ��һ���Ѿ���ӣ�
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
//6.�ж��Ƿ�����ȫ������
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
//7.ӵ��˫�ӽڵ�ĸ���
int DoubleChildNodeNum(ThreadTree& t) {
	if (!t) { return 0; }
	if (t->lChild && t->rChild) {
		return DoubleChildNodeNum(t->lChild) + DoubleChildNodeNum(t->rChild) + 1;
	}
	else {
		return DoubleChildNodeNum(t->lChild) + DoubleChildNodeNum(t->rChild);
	}
}
//8.������������
void Exchange(ThreadTree& t) {
	if (!t) { return; }
	Exchange(t->lChild);
	Exchange(t->rChild);
	ThreadNode* temp = t->rChild;
	t->rChild = t->lChild;
	t->lChild = temp;
}
int i = 1;
//�����������Ϊx��ֵ
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
//9.����ɾ����tΪ���ڵ����
void DeleteTreeNode(ThreadTree t) {
	if (!t) { return; }
	DeleteTreeNode(t->lChild);
	DeleteTreeNode(t->rChild);
	free(t);
}
//10.ɾ����xΪ���ڵ������
void PostOrderX(ThreadTree t, int x) {
	if (!t) { return; }
	if (t->lChild && t->lChild->data == x) {//����һ��data==x����ַ��ʲ���Ҷ�ڵ㺢�ӵĴ���
		DeleteTreeNode(t->lChild);//���ú���ɾ������
		t->lChild = NULL;//ɾ����ɺ�Ҫ������ָ����ΪNULL
	}
	if (t->rChild && t->rChild->data == x) {
		DeleteTreeNode(t->rChild);
		t->rChild = NULL;
	} 
	PostOrderX(t->lChild,x);
	PostOrderX(t->rChild,x);
	
}
//11.��ӡx���������ȣ�ͬ�ǵݹ�������
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
//12.�����������
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
//13.����������
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
//15.���������������
void PreGetPost(char pre[],int l1,int h1,char post[],int l2,int h2) {
	int half;
	
	if (h1 >= l1) {
		post[h2] = pre[l1];
		half = (h1 - l1) / 2;
		PreGetPost(pre, l1 + 1, l1 + half, post, l2, l2 + half - 1);
		PreGetPost(pre, l1 + half + 1, h1, post, l2+half , h2-1);
	}
}
//16.Ҷ�ڵ����ɵ�����
void LeafLinkNode(ThreadTree t,ThreadTree &pre) {
	if (!t) { return; }
	LeafLinkNode(t->lChild, pre);
	LeafLinkNode(t->rChild, pre);
	if (!t->lChild && !t->rChild) {
		pre->rChild = t;
		pre = t;
	}
}

//18.�����ŵ���׺���ʽ
void BiTreeInExp(CThreadTree t, int deep) {//��������ж��Ƿ�Ҫ������
	if (!t) { return; }
	else if (!t->lChild && !t->rChild) { //���Ų����ܳ�����Ҷ�ӽ����
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
	//4�����
	//AddlChild(t->lChild->lChild, 8);
	//AddrChild(t->lChild->lChild, 9);
	//5����
	AddlChild(t->lChild->rChild, 10);
	AddlChild(t->lChild->rChild->lChild, 8);
	AddlChild(t->lChild->rChild->lChild->lChild, 9);
	AddrChild(t->lChild->rChild, 11);
	//6����
	//AddlChild(t->rChild->lChild, 12);
	//AddrChild(t->rChild->lChild, 13);
	//7����
	//AddlChild(t->rChild->rChild, 14);
	//AddrChild(t->rChild->rChild, 15);
	//���α���
	
	//InvestLevel(t);
	
	//��ӡָ���ڵ����������
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
