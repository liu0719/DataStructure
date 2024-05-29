#include<stdio.h>
#include<stdlib.h>
//循环单链表
typedef struct LNode {
	int data;
	LNode* next;
}LNode, * LinkList;
//判空
bool FIsEmpty(LinkList &L) {
	if (L->next = L) {
		return true;
	}
	return false;
}
//判尾
bool FIsTail(LinkList& L,LNode *p) {
	if (p->next = L) {
		return true;
	}
	return false;
}
//后插
bool FInsertAfter(LinkList& L, LNode* p,int e) {
	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}
//假装前插
bool FInsertBefore(LinkList& L, LNode* p, int e) {
	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	int temp = p->data;
	p->data=s->data;
	s->data = temp;
	return true;
}
//后删
bool FDeleteAfter(LinkList& L, LNode* p, int e) {
	LNode* q = p->next;
	e= q->data ;
	q->next = p->next;
	free(q);
	return true;
}
//删除指定
bool FDeleteAfter(LinkList& L, LNode* p) {
	LNode* q = p->next;
	p->data = q->data;
	p->next = q->next;
	free(q);
	return true;
}
//循环双链
typedef struct DNode {
	int data;
	DNode* prior, * next;
}DNode, * DLinkList;
//判空
bool IsEmpty(DLinkList& L) {
	if (L->next = L) {
		return true;
	}
	return false;
}
//判尾
bool FIsTail(DLinkList& L, DNode* p) {
	if (p->next == L) {
		return true;
	}
	return false;
}

//指定节点后插入
bool FInsertAfter(DLinkList& L, DNode* p, int e) {//p为指定节点，e未插入元素
	if (p == NULL) {
		return false;
	}
	DNode* s = (DNode*)malloc(sizeof(DNode));
	s->data = e;
	s->next = p->next;
	p->next->prior = s;
	s->prior = p;
	p->next = s;
	return true;
}
//指定节点前插入
bool FInsertBefore(DLinkList& L, DNode* p, int e) {
	if (p == NULL) {
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
bool FDeleteAfterNode(DLinkList& L, DNode* p) {
	if (p == NULL ) {
		return false;
	}
	DNode* q = p->next;
	p->next = q->next;
	q->next->prior = p;
	free(q);
	return true;
}
//删除指定节点p的前驱节点
bool FDeleteBeforeNode(DLinkList& L, DNode* p) {
	if ( p == NULL ) {
		return false;
	}
	DNode* q = (DNode*)malloc(sizeof(DNode));
	q = p->prior;
	p->prior = q->prior;
	q->prior->next = p;
	free(q);
	return true;
}