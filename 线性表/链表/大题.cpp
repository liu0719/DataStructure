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
//β�巨 
DLinkList DTailInsert(DLinkList& L) {
	L = (DNode*)malloc(sizeof(DNode));
	L->next = NULL; L->prior = NULL;
	DNode* R = L;//����βָ��
	while (R->next != NULL) {//ѭ�������һ������
		R = R->next;
	}
	int x;
	printf("˫����β�巨��������\n");
	scanf_s("%d", &x);
	while (x != -1) {
		DNode* s = (DNode*)malloc(sizeof(DNode));
		s->data = x;
		s->freq = 0;
		s->next = R->next;
		s->prior = R;
		R->next = s;
		R = R->next;
		printf("��ӳɹ�������-1�˳�\n");
		scanf_s("%d", &x);
	}
	//L->prior = R;
	//R->next = L;
	return L;
}
//��ӡ����
void DPrintList(DLinkList& L) {
	DNode* p = L->next;
	while (p != NULL) {
		printf("<--->%d", p->data);
		p = p->next;
	}
	printf("\n");
	return;
}
//β��
LinkList LTailInsert(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));
	LNode* s, * r = L; int x;
	printf("������β�巨��������������\n");
	scanf_s("%d", &x);
	while (x != -1) {
		s = (LNode*)malloc(sizeof(LNode));//Ҫ����ռ���г�ʼ��
		s->data = x;
		s->next = r->next;
		r->next = s;
		r = r->next;
		printf("����ɹ�������-1�˳�\n");
		scanf_s("%d", &x);
	}
	r->next = NULL;
	return L;
}
//��ͷβ��
LinkList LTailInsertNoHead(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));
	LNode* s, * r = L; int x;
	printf("������β�巨��������������\n");
	scanf_s("%d", &x);
	L->data = x;
	printf("����ɹ�������-1�˳�\n");
	scanf_s("%d", &x);
	while (x != -1) {
		s = (LNode*)malloc(sizeof(LNode));//Ҫ����ռ���г�ʼ��
		s->data = x;
		s->next = r->next;
		r->next = s;
		r = r->next;
		printf("����ɹ�������-1�˳�\n");
		scanf_s("%d", &x);
	}
	r->next = NULL;
	return L;
}
//��ѭ��β��
LinkList FTailInsert(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));
	LNode* s, * r = L; int x;
	printf("������β�巨��������������\n");
	scanf_s("%d", &x);
	while (x != -1) {
		s = (LNode*)malloc(sizeof(LNode));//Ҫ����ռ���г�ʼ��
		s->data = x;
		s->next = r->next;
		r->next = s;
		r = r->next;       
		printf("����ɹ�������-1�˳�\n");
		scanf_s("%d", &x);
	}
	r->next = L;
	return L;
}
//��ӡ����
bool LPrintList(LinkList& L) {
	LNode* p = L->next;
	while (p!= NULL) {
		printf("-->%d", p->data);
		p = p->next;

	}
	printf("\n");
	return true;
}
//��ͷ��ӡ����
bool LPrintListNoHead(LinkList& L) {
	LNode* p = L;
	while (p != NULL) {
		printf("-->%d", p->data);
		p = p->next;
	}
	printf("\n");
	return true;
}
//��ӡ����
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
//6��
bool Divide(LinkList& L) {
	int count = 1;//��pָ��ͬ������¼��ż,�ӵ�һ���ڵ㿪ʼ
	LNode* p = L->next;
	LNode* B = (LNode*)malloc(sizeof(LNode));
	B->next = NULL;//��ʼ��b��
	while (p != NULL) {
		LNode* r = p->next;//��¼p�ĺ�һ���ڵ㣬��ֹ������ʱ������ʧ
		if (count % 2 == 0) {//ż��ʱ��ǰ�嵽B���ϣ�
			p->next = B->next;
			B->next = p;
		}
		else if(r != NULL){//�������r==NULLʱ��next�����
			p->next = r->next;	//ֱ��ȥ����һ�������Ľڵ�
		}
		count++;//��¼��ż
		p = r;//p�����
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
	while (p != q&&q->next!=p) {//����pq��Ⱥ�p����q�Ŀ��� 

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
	DNode* p = L->next, * q = L;//pΪ����ָ�룬�ҵ�x֮��x������ȡ����
	while (p != NULL) {
		if (p->data == x) {
			p->freq++;//���ʵ�x,freq++
			q = p->prior;//ȡ��p
			q->next = p->next;
			if (p->next != NULL) {//����pΪ���һ���ڵ�����
				p->next->prior = q;
			}
			break;//�ҵ�������ѭ��
		}
		p=p->next;
	}
	if (p == NULL) {//�Ҳ���ֱ�ӷ���NULL
		return p;
	}
	while (q != L && q->freq <= p->freq) {//q�ڵ���ǰѰ��freq����p�Ľڵ㣬�Ҳ�������ͷ������룬ʹ֮��Ϊ��һ��Ԫ��
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
	int n=GetLength(L);//�õ�����
	if (k >= n) {
		return false;
	}
	LNode* p = L,*q= L;//����ָ��
	for (int i = 0; i < n - k - 1; i++) {//�ҵ�Ӧ���ƶ���ǰһ��Ԫ��
		p = p->next;
	}
	q = p->next;//������������Ͽ�
	p->next = NULL;//p������Ϊ���һ��Ԫ��
	LNode *r = q;//r��ɨ��ָ�룬��ɨ��q��������һ��Ԫ��
	while (r->next) {
		r = r -> next;
	}
	//r��ʱΪ���һ��Ԫ��,���ӵ�֮ǰ��ͷ���
	r->next = L;
	//��q��ͷ���
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
	printf("ɾ��\n");
	LPrintList(l);
	DeleteMin(l);
	printf("ɾ����С\n");
	LPrintList(l);
	printf("��ת\n");
	Reverse(l);
	LPrintList(l);
	printf("ɾ��A��B֮��\n"); 
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
	printf("��������Ҫ�ƶ��ĳ���");
	scanf_s("%d", &x);
	RightMove(A, x);
	LPrintListNoHead(A);
	return 0;
}