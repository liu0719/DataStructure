#include<stdio.h>
#include<stdlib.h>
typedef struct LNode {
	int data;
	LNode* next;
}LNode, * LinkList;
typedef struct DNode {
	int data;
	int freq;
	DNode* prior, * next;
}DNode, * DLinkList;
//尾插法 
DLinkList DTailInsert(DLinkList& L) {
	L = (DNode*)malloc(sizeof(DNode));
	L->next = NULL; L->prior = NULL;
	DNode* R = L;//定义尾指针
	while (R->next != NULL) {//循环到最后一个数据
		R = R->next;
	}
	int x;
	printf("双链表尾插法，请输入\n");
	scanf_s("%d", &x);
	while (x != -1) {
		DNode* s = (DNode*)malloc(sizeof(DNode));
		s->data = x;
		s->freq = 0;
		s->next = R->next;
		s->prior = R;
		R->next = s;
		R = R->next;
		printf("添加成功，输入-1退出\n");
		scanf_s("%d", &x);
	}
	//L->prior = R;
	//R->next = L;
	return L;
}
//打印函数
void DPrintList(DLinkList& L) {
	DNode* p = L->next;
	while (p != NULL) {
		printf("<--->%d", p->data);
		p = p->next;
	}
	printf("\n");
	return;
}
//尾插
LinkList LTailInsert(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));
	LNode* s, * r = L; int x;
	printf("请输入尾插法建立的链表数字\n");
	scanf_s("%d", &x);
	while (x != -1) {
		s = (LNode*)malloc(sizeof(LNode));//要申请空间进行初始化
		s->data = x;
		s->next = r->next;
		r->next = s;
		r = r->next;
		printf("加入成功，输入-1退出\n");
		scanf_s("%d", &x);
	}
	r->next = NULL;
	return L;
}
//无头尾插
LinkList LTailInsertNoHead(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));
	LNode* s, * r = L; int x;
	printf("请输入尾插法建立的链表数字\n");
	scanf_s("%d", &x);
	L->data = x;
	printf("加入成功，输入-1退出\n");
	scanf_s("%d", &x);
	while (x != -1) {
		s = (LNode*)malloc(sizeof(LNode));//要申请空间进行初始化
		s->data = x;
		s->next = r->next;
		r->next = s;
		r = r->next;
		printf("加入成功，输入-1退出\n");
		scanf_s("%d", &x);
	}
	r->next = NULL;
	return L;
}
//单循环尾插
LinkList FTailInsert(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));
	LNode* s, * r = L; int x;
	printf("请输入尾插法建立的链表数字\n");
	scanf_s("%d", &x);
	while (x != -1) {
		s = (LNode*)malloc(sizeof(LNode));//要申请空间进行初始化
		s->data = x;
		s->next = r->next;
		r->next = s;
		r = r->next;       
		printf("加入成功，输入-1退出\n");
		scanf_s("%d", &x);
	}
	r->next = L;
	return L;
}
//打印函数
bool LPrintList(LinkList& L) {
	LNode* p = L->next;
	while (p!= NULL) {
		printf("-->%d", p->data);
		p = p->next;

	}
	printf("\n");
	return true;
}
//无头打印函数
bool LPrintListNoHead(LinkList& L) {
	LNode* p = L;
	while (p != NULL) {
		printf("-->%d", p->data);
		p = p->next;
	}
	printf("\n");
	return true;
}
//打印函数
bool FPrintList(LinkList& L) {
	LNode* p = L->next;
	while (p != L) {
		printf("-->%d", p->data);
		p = p->next;

	}
	printf("\n");
	return true;
}
//1
bool DeleteX(LinkList& L,int x) {
	LNode* p = L;
	while (p->next!= NULL) {
		if (p->next->data == x) {
			LNode* q = p->next;
			p->next = q->next;
			free(q);
		}
		p = p->next;
	}
	return true;
}
//2
bool DeleteMin(LinkList& L) {
	if (L->next == NULL) {
		return false;
	}
	LNode* p = L,*q=L;
	int min = p->next->data;
	while (p->next != NULL) {
		if (p->next->data<min) {
			q = p;
		}
		p = p->next;
	}
	p = q->next;
	q->next = p->next;
	free(p);
	return true;
}
//3
bool Reverse(LinkList &l) {
	LNode* p, * r;
	p= l->next;
	
	l->next = NULL;
	while (p!= NULL) {
		r = p->next;
		p->next = l->next;
		l->next = p;
		p = r;		
	}
	return true;
}
//4
bool DeleteInAAndB(LinkList &L,int a,int b) {
	LNode* p = L;
	while (p->next!= NULL) {
		if (p->next->data > a && p->next->data < b) {
			LNode* q = p->next;
			p->next = q->next;
			free(q);
		}
		else {
			p = p->next;
		}
	}
	return 0;
}
//6、
bool Divide(LinkList& L) {
	int count = 1;//和p指针同步，记录奇偶,从第一个节点开始
	LNode* p = L->next;
	LNode* B = (LNode*)malloc(sizeof(LNode));
	B->next = NULL;//初始化b链
	while (p != NULL) {
		LNode* r = p->next;//记录p的后一个节点，防止链断裂时后面消失
		if (count % 2 == 0) {//偶数时就前插到B链上；
			p->next = B->next;
			B->next = p;
		}
		else if(r != NULL){//处理最后r==NULL时无next的情况
			p->next = r->next;	//直接去链下一个奇数的节点
		}
		count++;//记录奇偶
		p = r;//p向后移
	}
	printf("A----\n");
	LPrintList(L);
	printf("B----\n");
	LPrintList(B);
	return 0;
}
//7
bool DeleteReplay(LinkList& L) {
	LNode* p = L;
	while (p->next != NULL) {
		LNode *q = p->next;
		if (p->data == q->data) {
			p->next = q->next;
			free(q);
		}
		else {
			p = p->next;
		}
	}
	return 0;
	
}
//8
LinkList CreateCFromAandB(LinkList &A, LinkList &B) {
	LNode* C = (LNode*)malloc(sizeof(LNode)),*p=A->next,*q=B->next,*R=C;
	C->next = NULL;
	while (q != NULL &&p != NULL) {
		if (q->data == p->data) {
			LNode* s = (LNode*)malloc(sizeof(LNode));
			s->data = q->data;
			s->next = R->next;
			R->next = s;
			R = R->next;
			q = q->next;
			p = p->next;
		}
		else if (q->data  < p->data) {
			q = q->next;
		}
		else {
			p = p->next;
		}
	}
	return C;
}
//9
bool BothHave(LinkList &A,LinkList &B) {
	LNode* pa = A->next, * pb = B->next,*pc=A,*u;
	while (pa&& pb) {
		if (pa->data < pb->data) {
			u = pa;
			pa = pa-> next;
			free(u);
		}else if (pa->data > pb->data){
			pb = pb->next;
		}
		else {
			pc->next = pa;
			pb = pb->next;
			pa = pa -> next;
			pc = pc->next;
		}
	}
	while (pa) {
		u = pa;
		pa = pa->next;
		free(u);
	}
	return 0;
}
//10
bool IsSon(LinkList& A, LinkList& B) {
	LNode* pa = A->next,*pb=B->next;
	bool flag = false;
	while (pa&&pb) {
		if (pa->data == pb->data) {
			pb = pb ->next;
			pa = pa->next;
			flag = true;
		}
		else if(flag){
			return !flag;
		}
		else {
			pa = pa->next;
		}
	}
	if (pb) {
		flag = false;
	}
	return flag;
}
//11
bool Symmetry(DLinkList &L) {
	DNode* p = L->next,* q = L->prior;
	while (p != q&&q->next!=p) {//处理pq相等和p超过q的可能 

		if (p->data == q->data) {
			p = p->next;
			q = q->prior;
		}
		else {
			return false;
		}
	}
	return true;
}
//12
bool Merge(LinkList& h1, LinkList& h2) {
	LNode* p = h1;
	while (p->next != h1) {
		p = p->next;
	}
	p->next = h2->next;
	p = p->next;
	while (p->next != h2) {
		p = p->next;
	}
	p->next = h1;
	return 0;
}
//13
DNode* Locate(DLinkList& L, int x)
 {
	DNode* p = L->next, * q = L;//p为工作指针，找到x之后将x在链上取下来
	while (p != NULL) {
		if (p->data == x) {
			p->freq++;//访问到x,freq++
			q = p->prior;//取出p
			q->next = p->next;
			if (p->next != NULL) {//处理p为最后一个节点的情况
				p->next->prior = q;
			}
			break;//找到后跳出循环
		}
		p=p->next;
	}
	if (p == NULL) {//找不到直接返回NULL
		return p;
	}
	while (q != L && q->freq <= p->freq) {//q节点向前寻找freq大于p的节点，找不到就在头结点后插入，使之成为第一个元素
		q = q->prior;
	}
	p->next = q->next;
	q->next->prior = p;
	q->next = p;
	p->prior = q;
		
	
	return p;
}
int GetLength(LinkList&L) {
	int count = 0;
	LNode* p = L;
	while (p != NULL) {
		count++;
		p = p->next;
	}
	return count; 
}
//14
bool RightMove(LinkList&L,int k) {
	int n=GetLength(L);//得到长度
	if (k >= n) {
		return false;
	}
	LNode* p = L,*q= L;//辅助指针
	for (int i = 0; i < n - k - 1; i++) {//找到应该移动的前一个元素
		p = p->next;
	}
	q = p->next;//把链表在这里断开
	p->next = NULL;//p将会作为最后一个元素
	LNode *r = q;//r当扫描指针，将扫到q链表的最后一个元素
	while (r->next) {
		r = r -> next;
	}
	//r此时为最后一个元素,链接到之前的头结点
	r->next = L;
	//把q当头结点
	L=q;
	return true;
}
int main() {
	LinkList lA;
	LTailInsert(lA);
	FTailInsert(lA);
	FPrintList(lA);
	LinkList lB;
	FTailInsert(lB);
	LTailInsert(lB);
	FPrintList(lB);


	DeleteX(l, 3);
	printf("删除\n");
	LPrintList(l);
	DeleteMin(l);
	printf("删除最小\n");
	LPrintList(l);
	printf("反转\n");
	Reverse(l);
	LPrintList(l);
	printf("删除A和B之间\n"); 
	DeleteInAAndB(l,4,6);
	LPrintList(l);
	Divide(l);
	DeleteReplay(lA);
	LinkList C=CreateCFromAandB(lA, lB);
	BothHave(lA, lB);
	bool flag=IsSon(lA, lB);
	printf("%d", flag);
	LPrintList(lA);
	Merge(lA, lB);
	FPrintList(lA);



	DLinkList DA;
	DTailInsert(DA);
	DPrintList(DA);
	DNode *i= Locate(DA,3);
	 i = Locate(DA, 2);
	printf("%d\n", i);
	DPrintList(DA);

	LinkList A;
	LTailInsertNoHead(A);
	LPrintListNoHead(A);
	int x = 0;
	printf("请输入你要移动的长度");
	scanf_s("%d", &x);
	RightMove(A, x);
	LPrintListNoHead(A);
	return 0;
}