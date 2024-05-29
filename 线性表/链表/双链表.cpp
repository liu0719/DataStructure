#include<stdio.h>
#include<stdlib.h>
typedef struct DNode {
	int data;
	DNode* prior, * next;
}DNode,*DLinkList;
//链表初始化
bool DInit(DLinkList &L) {
	L = (DNode*)malloc(sizeof(DNode));
	if (L == NULL) {
		return false;
	}
	L->prior = NULL;
	L->next = NULL;
	return true;
}
//指定节点后插入
bool DInsertAfter(DLinkList &L,DNode *p,int e) {//p为指定节点，e未插入元素
	if (p == NULL || L->next == NULL) {
		return false;
	}
	DNode *s = (DNode*)malloc(sizeof(DNode));
	s->data = e;
	s->next = p->next;
	//处理p为最后一个元素的情况
	if (p->next != NULL) {
		p->next->prior = s;
	}
	s->prior = p;
	p->next = s;
	return true;
}
//指定节点前插入
bool DInsertBefore(DLinkList& L, DNode* p, int e) {
	if (p == L || p == NULL) {
		return false;
	}
	DNode* s = (DNode*)malloc(sizeof(DNode));
	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return true;
}
//删除指定节点p的后继节点
bool DDeleteAfterNode(DLinkList& L, DNode* p) {
	if (p == NULL || p->next == NULL) {
		return false; 
	}
	DNode* q = p->next;
	p->next = q->next;
	if (q->next != NULL) {
		q->next->prior = p;
	}
	free(q);
	return true;
}
//删除指定节点p的前驱节点
bool DDeleteBeforeNode(DLinkList& L, DNode* p) {
	if (p == L || p == NULL||p->prior==L) {
		return false;
	}
	DNode* q = (DNode*)malloc(sizeof(DNode));
	q = p->prior;
	p->prior=q->prior ;
	q->prior->next = p;
	free(q);
	return true;
}
//头插法
DLinkList DHeadInsert(DLinkList& L) {
	L= (DNode*)malloc(sizeof(DNode));
	L->next = NULL; L->prior = NULL;
	int x;
	printf("双链表头插法，请输入\n");
	scanf_s(" %d", &x);
	while (x != -1) {
		DNode *s= (DNode*)malloc(sizeof(DNode));
		s->data = x;
		s->next = L->next;
		if (s->next != NULL) {
			L->next->prior = s;
		}
		s->prior = L;
		L->next = s;
		printf("添加成功，输入-1退出\n");
		scanf_s("%d", &x);
		
	}
	return L;
}
//尾插法 
DLinkList DTailInsert(DLinkList &L) {
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
		DNode *s=(DNode*)malloc(sizeof(DNode));
		s->data = x;
		s->next = R->next;
		s->prior = R;
		R->next = s;
		R = R->next;
		printf("添加成功，输入-1退出\n");
		scanf_s("%d", &x);
		
	}
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
int main() {
	DLinkList L;
	TailInsert(L);
	//生成链表
	PrintList(L);
	printf("后增\n");
	DNode* q = L;
	for (int i = 0; i < 4; i++) {
		q = q->next;
	}
	InsertAfter(L, q, 100);
	PrintList(L);
	printf("前增\n");
	InsertBefore(L, q, 100);
	PrintList(L);
	printf("前删\n");
	DeleteBeforeNode(L, q->prior);
	PrintList(L);
	printf("后删\n");
	DeleteAfterNode(L, q->prior);
	PrintList(L);
	return 1;
}