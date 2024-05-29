#include<stdio.h>
#include<stdlib.h>

//������
typedef struct LNode {//��ʽ���
	int data;
	LNode* next;
}LNode;
typedef struct LQueue {//���У�������ͷβָ�룬�м����һ������ʵ�֣�ͷβֻ������ָ�롣
	LNode* front, * rear;
	//���������ҪƵ�����ʣ�������һ��length
	int length;
}LQueue;
//��ʼ��
bool InitLQueue(LQueue& q) {
	//�������Ϊͷβ����ָ��ָ��ͬһ�����
	//������ʽ�ڵ㣬��ʵ����������ѣ���������ͷβָ�룬���¶���Ϊһ���ṹ���Ϊ��ʽ����
	q.front = q.rear = (LNode*)malloc(sizeof(LNode));
	q.rear->next = q.front;//frontΪͷ��㣬ʹ����һ��ָ��NULL
	return true;
}
//�п�
bool IsEmpty(LQueue& q) {
	return q.front == q.rear;
}
//����
bool IsOverFlow(LQueue& q) {
	return q.rear->next == q.front;
}
//���
bool EnQueue(LQueue& q,int x) {
	if (IsOverFlow(q)) {//���Ϊ������Ϊ������
		//û�о�����һ���½ڵ㣬��x������ǰ��rear,�����������LNode���ӵ�rear���棬����rear���ƣ�
	//��Ҫ�ճ�һ���ڵ㣻
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		s->next = q.rear->next;
		q.rear->next = s;
		q.rear = s;
		return true;
	}
	//��ʼ��Ϊ����
		//���rear�����пյĽڵ��ֱ�Ӹ�ֵ���ƾ���
	//��ͷ���ʱ��rearָ��������һ��Ԫ�أ�����rear������һ���ڽ��и�ֵ
	q.rear = q.rear->next;
	q.rear->data = x;
	
	return true;
}
//����
bool DeLQueue(LQueue& q, int& x) {
	if (IsEmpty(q)) { return false; }//����Ϊ��
	//ͷ���ָ�����
	LNode* p = q.front->next;
	if (q.front->next == q.rear) {
		q.rear = q.front;
	}
	q.front->next = p->next;
	//�ҵ�rear����
	p->next = q.rear->next;
	q.rear->next = p;
	return true;
}
bool PrintLQueue(LQueue &q) {
	LNode* p = q.front->next;
	while (p != q.rear) {
		printf("--->%d", p->data);
		p = p->next;
	}
	printf("\n");
	printf("q.front=%d,q.rear=%d\n", q.front->data, q.rear->data);
	return 0;
}
int main() {
	system("color 80");
	LQueue q;
	InitLQueue(q);
	printf("�����Ƿ�Ϊ�գ�%d\n", IsEmpty(q));
	printf("�����Ƿ�������%d\n", IsOverFlow(q));
	printf("----------------��6��------------\n");
	for (int i = 0; i < 2; i++)
	{
		EnQueue(q, i);
	PrintLQueue(q);
	printf("�����Ƿ�Ϊ�գ�%d\n", IsEmpty(q));
	printf("�����Ƿ�������%d\n", IsOverFlow(q));
	}
	printf("----------------��6��------------\n");
	for (int i = 0; i < 2; i++)
	{
		DeLQueue(q, i);
		PrintLQueue(q);
		printf("�����Ƿ�Ϊ�գ�%d\n", IsEmpty(q));
		printf("�����Ƿ�������%d\n", IsOverFlow(q));
	}
	printf("----------------��7��------------\n");
	for (int i = 0; i < 4; i++)
	{
		EnQueue(q, i);
		PrintLQueue(q);
		printf("�����Ƿ�Ϊ�գ�%d\n", IsEmpty(q));
		printf("�����Ƿ�������%d\n", IsOverFlow(q));
	}
	printf("----------------��6��------------\n");
	for (int i = 0; i < 4; i++)
	{
		DeLQueue(q, i);
		PrintLQueue(q);
		printf("�����Ƿ�Ϊ�գ�%d\n", IsEmpty(q));
		printf("�����Ƿ�������%d\n", IsOverFlow(q));
	}
	printf("----------------��4��------------\n");
	for (int i = 0; i < 5; i++)
	{
		EnQueue(q, i);
		PrintLQueue(q);
		printf("�����Ƿ�Ϊ�գ�%d\n", IsEmpty(q));
		printf("�����Ƿ�������%d\n", IsOverFlow(q));
	}
	return 0;
}