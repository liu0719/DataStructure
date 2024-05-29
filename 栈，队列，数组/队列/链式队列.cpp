#include<stdio.h>
#include<stdlib.h>
typedef struct LNode {//链式结点
	int data;
	LNode *next;
}LNode;
typedef struct LQueue {//队列，就是用头尾指针，中间包着一个链表实现；头尾只是两个指针。
	LNode* front, * rear;
	//如果长度需要频繁访问，不妨加一个length
	int length;
}LQueue;

////初始化
//bool InitLQueue(LQueue &q) {
//	//可以理解为头尾两个指针指向同一个结点
//	//申请链式节点，其实还是链表而已，加了两个头尾指针，重新定义为一个结构体称为链式队列
//	q.front = q.rear = (LNode*)malloc(sizeof(LNode));
//	q.front->next = NULL;//front为头结点，使其下一个指向NULL
//	return true;
//}
//判空，链表队列一般不会满，除非电脑没有内存了
bool IsEmpty(LQueue& q) {
	if (q.front == q.rear) {
		return true;
	}
	return false;
}
//入队
bool EnLQueue(LQueue& q,int x) {
	//申请一个新的节点存放要入队的元素x
	LNode *s = (LNode*)malloc(sizeof(LNode));
	s->data = x;
	s->next = q.rear->next;
	q.rear->next = s;
	q.rear = s;//rear一直要保持在最后一个
	return true;
}
//出队
bool DeQueue(LQueue& q, int& x) {
	if (q.rear == q.front) {//为空不能出队
		return false;
	}
	LNode *p = q.front->next;
	x = p->data;
	q.front->next = p->next;
	if (q.rear == p) {//处理只有一个节点的情况
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
	printf("出队:%d\n", e);
	DeQueue(Lq, e);
	printf("出队:%d\n", e);
	PrintLQueue(Lq);
	DeQueue(Lq, e);
	printf("出队:%d\n", e);
	DeQueue(Lq, e);
	printf("出队:%d\n", e);
	DeQueue(Lq, e);
	printf("出队:%d\n", e);
	PrintLQueue(Lq);
	return 0;
}