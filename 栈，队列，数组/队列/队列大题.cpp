#include<stdio.h>
#include<stdlib.h>

//第五题
typedef struct LNode {//链式结点
	int data;
	LNode* next;
}LNode;
typedef struct LQueue {//队列，就是用头尾指针，中间包着一个链表实现；头尾只是两个指针。
	LNode* front, * rear;
	//如果长度需要频繁访问，不妨加一个length
	int length;
}LQueue;
//初始化
bool InitLQueue(LQueue& q) {
	//可以理解为头尾两个指针指向同一个结点
	//申请链式节点，其实还是链表而已，加了两个头尾指针，重新定义为一个结构体称为链式队列
	q.front = q.rear = (LNode*)malloc(sizeof(LNode));
	q.rear->next = q.front;//front为头结点，使其下一个指向NULL
	return true;
}
//判空
bool IsEmpty(LQueue& q) {
	return q.front == q.rear;
}
//判满
bool IsOverFlow(LQueue& q) {
	return q.rear->next == q.front;
}
//入队
bool EnQueue(LQueue& q,int x) {
	if (IsOverFlow(q)) {//如果为空则认为是满的
		//没有就申请一个新节点，将x赋给当前的rear,并将新申请的LNode链接到rear后面，并将rear后移；
	//需要空出一个节点；
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		s->next = q.rear->next;
		q.rear->next = s;
		q.rear = s;
		return true;
	}
	//初始视为不满
		//如果rear后面有空的节点就直接赋值后移就行
	//有头结点时，rear指向的是最后一个元素，先让rear向后遍历一个在进行赋值
	q.rear = q.rear->next;
	q.rear->data = x;
	
	return true;
}
//出队
bool DeLQueue(LQueue& q, int& x) {
	if (IsEmpty(q)) { return false; }//队列为空
	//头结点指向后移
	LNode* p = q.front->next;
	if (q.front->next == q.rear) {
		q.rear = q.front;
	}
	q.front->next = p->next;
	//挂到rear后面
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
	LQueue q;
	InitLQueue(q);
	printf("队列是否为空：%d\n", IsEmpty(q));
	printf("队列是否已满：%d\n", IsOverFlow(q));
	printf("----------------进6个------------\n");
	for (int i = 0; i < 2; i++)
	{
		EnQueue(q, i);
	PrintLQueue(q);
	printf("队列是否为空：%d\n", IsEmpty(q));
	printf("队列是否已满：%d\n", IsOverFlow(q));
	}
	printf("----------------出6个------------\n");
	for (int i = 0; i < 2; i++)
	{
		DeLQueue(q, i);
		PrintLQueue(q);
		printf("队列是否为空：%d\n", IsEmpty(q));
		printf("队列是否已满：%d\n", IsOverFlow(q));
	}
	printf("----------------进7个------------\n");
	for (int i = 0; i < 4; i++)
	{
		EnQueue(q, i);
		PrintLQueue(q);
		printf("队列是否为空：%d\n", IsEmpty(q));
		printf("队列是否已满：%d\n", IsOverFlow(q));
	}
	printf("----------------出6个------------\n");
	for (int i = 0; i < 4; i++)
	{
		DeLQueue(q, i);
		PrintLQueue(q);
		printf("队列是否为空：%d\n", IsEmpty(q));
		printf("队列是否已满：%d\n", IsOverFlow(q));
	}
	printf("----------------进4个------------\n");
	for (int i = 0; i < 5; i++)
	{
		EnQueue(q, i);
		PrintLQueue(q);
		printf("队列是否为空：%d\n", IsEmpty(q));
		printf("队列是否已满：%d\n", IsOverFlow(q));
	}
	return 0;
}