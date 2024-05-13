#include<stdio.h>
#include<stdlib.h>
typedef struct LNode {//��ʽ���
	int data;
	LNode *next;
}LNode;
typedef struct LQueue {//���У�������ͷβָ�룬�м����һ������ʵ�֣�ͷβֻ������ָ�롣
	LNode* front, * rear;
	//���������ҪƵ�����ʣ�������һ��length
	int length;
}LQueue;

////��ʼ��
//bool InitLQueue(LQueue &q) {
//	//�������Ϊͷβ����ָ��ָ��ͬһ�����
//	//������ʽ�ڵ㣬��ʵ����������ѣ���������ͷβָ�룬���¶���Ϊһ���ṹ���Ϊ��ʽ����
//	q.front = q.rear = (LNode*)malloc(sizeof(LNode));
//	q.front->next = NULL;//frontΪͷ��㣬ʹ����һ��ָ��NULL
//	return true;
//}
//�пգ��������һ�㲻���������ǵ���û���ڴ���
bool IsEmpty(LQueue& q) {
	if (q.front == q.rear) {
		return true;
	}
	return false;
}
//���
bool EnLQueue(LQueue& q,int x) {
	//����һ���µĽڵ���Ҫ��ӵ�Ԫ��x
	LNode *s = (LNode*)malloc(sizeof(LNode));
	s->data = x;
	s->next = q.rear->next;
	q.rear->next = s;
	q.rear = s;//rearһֱҪ���������һ��
	return true;
}
//����
bool DeQueue(LQueue& q, int& x) {
	if (q.rear == q.front) {//Ϊ�ղ��ܳ���
		return false;
	}
	LNode *p = q.front->next;
	x = p->data;
	q.front->next = p->next;
	if (q.rear == p) {//����ֻ��һ���ڵ�����
		q.rear = q.front;
	}
	free(p);
	return true;
}
bool PrintLQueue(LQueue &q) {
	LNode* p = q.front->next;
	while (p != NULL) {
		printf("--->%d", p->data);
		p = p->next;
	}
	printf("\n");
	return 0;
}

int main() {
	LQueue Lq;
	InitLQueue(Lq);
	for (int i = 0; i < 5; i++)
	{
		EnLQueue(Lq, i);
	}
	PrintLQueue(Lq);
	int e = 0;
	DeQueue(Lq,e);
	printf("����:%d\n", e);
	DeQueue(Lq, e);
	printf("����:%d\n", e);
	PrintLQueue(Lq);
	DeQueue(Lq, e);
	printf("����:%d\n", e);
	DeQueue(Lq, e);
	printf("����:%d\n", e);
	DeQueue(Lq, e);
	printf("����:%d\n", e);
	PrintLQueue(Lq);
	return 0;
}