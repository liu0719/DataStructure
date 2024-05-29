#include<stdio.h>
#include<stdlib.h>
//ѭ��������
typedef struct LNode {
	int data;
	LNode* next;
}LNode, * LinkList;
//�п�
bool FIsEmpty(LinkList &L) {
	if (L->next = L) {
		return true;
	}
	return false;
}
//��β
bool FIsTail(LinkList& L,LNode *p) {
	if (p->next = L) {
		return true;
	}
	return false;
}
//���
bool FInsertAfter(LinkList& L, LNode* p,int e) {
	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}
//��װǰ��
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
//��ɾ
bool FDeleteAfter(LinkList& L, LNode* p, int e) {
	LNode* q = p->next;
	e= q->data ;
	q->next = p->next;
	free(q);
	return true;
}
//ɾ��ָ��
bool FDeleteAfter(LinkList& L, LNode* p) {
	LNode* q = p->next;
	p->data = q->data;
	p->next = q->next;
	free(q);
	return true;
}
//ѭ��˫��
typedef struct DNode {
	int data;
	DNode* prior, * next;
}DNode, * DLinkList;
//�п�
bool IsEmpty(DLinkList& L) {
	if (L->next = L) {
		return true;
	}
	return false;
}
//��β
bool FIsTail(DLinkList& L, DNode* p) {
	if (p->next == L) {
		return true;
	}
	return false;
}

//ָ���ڵ�����
bool FInsertAfter(DLinkList& L, DNode* p, int e) {//pΪָ���ڵ㣬eδ����Ԫ��
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
//ָ���ڵ�ǰ����
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
//ɾ��ָ���ڵ�p�ĺ�̽ڵ�
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
//ɾ��ָ���ڵ�p��ǰ���ڵ�
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