#include<stdio.h>
#include<stdlib.h>
typedef struct DNode {
	int data;
	DNode* prior, * next;
}DNode,*DLinkList;
//�����ʼ��
bool DInit(DLinkList &L) {
	L = (DNode*)malloc(sizeof(DNode));
	if (L == NULL) {
		return false;
	}
	L->prior = NULL;
	L->next = NULL;
	return true;
}
//ָ���ڵ�����
bool DInsertAfter(DLinkList &L,DNode *p,int e) {//pΪָ���ڵ㣬eδ����Ԫ��
	if (p == NULL || L->next == NULL) {
		return false;
	}
	DNode *s = (DNode*)malloc(sizeof(DNode));
	s->data = e;
	s->next = p->next;
	//����pΪ���һ��Ԫ�ص����
	if (p->next != NULL) {
		p->next->prior = s;
	}
	s->prior = p;
	p->next = s;
	return true;
}
//ָ���ڵ�ǰ����
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
//ɾ��ָ���ڵ�p�ĺ�̽ڵ�
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
//ɾ��ָ���ڵ�p��ǰ���ڵ�
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
//ͷ�巨
DLinkList DHeadInsert(DLinkList& L) {
	L= (DNode*)malloc(sizeof(DNode));
	L->next = NULL; L->prior = NULL;
	int x;
	printf("˫����ͷ�巨��������\n");
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
		printf("��ӳɹ�������-1�˳�\n");
		scanf_s("%d", &x);
		
	}
	return L;
}
//β�巨 
DLinkList DTailInsert(DLinkList &L) {
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
		DNode *s=(DNode*)malloc(sizeof(DNode));
		s->data = x;
		s->next = R->next;
		s->prior = R;
		R->next = s;
		R = R->next;
		printf("��ӳɹ�������-1�˳�\n");
		scanf_s("%d", &x);
		
	}
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
int main() {
	DLinkList L;
	TailInsert(L);
	//��������
	PrintList(L);
	printf("����\n");
	DNode* q = L;
	for (int i = 0; i < 4; i++) {
		q = q->next;
	}
	InsertAfter(L, q, 100);
	PrintList(L);
	printf("ǰ��\n");
	InsertBefore(L, q, 100);
	PrintList(L);
	printf("ǰɾ\n");
	DeleteBeforeNode(L, q->prior);
	PrintList(L);
	printf("��ɾ\n");
	DeleteAfterNode(L, q->prior);
	PrintList(L);
	return 1;
}