#include<stdio.h>
#define MAXSIZE 10
typedef struct Queue {
	int data[MAXSIZE];
	int front, rear;
	//要求不能剩最后一个空间时，可以用长度来判空和判满，q.length==0,q.length==10
	int length;
	//也可以用tag来标记最近一次操作，出队列为false，入队列为true;
	// 只有出队列会导致队列为空所以当  q.front==q.rear&&tag==false,
	//只有入队列会导致队列变满，所以当 q.front==q.rear&&tag==true,
	//这两种情况就可以区分了
	bool tag;
}Queue;
//初始化
bool InitQueue(Queue &q) {
	//也有可能队尾指针指向队尾元素，那么实现入队时要先让(rear=rear+1)%MAXSIZE(向后挪一位，在后再进行赋值
	//尾指针初始化时位置发生变化，那么判空操作也要发生变化
	q.front =q.rear =  0;//都指向0，入队rear++,出队front++
	return true;

}
//判空
bool IsEmpty(Queue& q) {
	if (q.front == q.rear) {
		return true;
	}
	return false;
}
//判满，这种判断方式最后一个必须是空的，必须要剩出最后一个空间判满
bool IsFull(Queue &q) {
	if ((q.rear + 1)%MAXSIZE == q.front) {
		return true;
	}
	return false;
}
//入队
bool EnQueue(Queue& q, int x) {
	if ((q.rear + 1) % MAXSIZE == q.front) {
		return false;
	}
	q.data[q.rear] = x;
	q.rear = (q.rear + 1) % MAXSIZE;
	return true;
}
//出队
bool DeQueue(Queue& q, int &x) {
	if (q.front == q.rear) {
		return false;//队空不能出队
	}
	
	x = q.data[q.front];
	q.data[q.front] = 0;
	q.front = (q.front + 1) % MAXSIZE;
	return true;
}
//队列元素个数
//(rear+size-front)%size
//队列中的元素个数
int QueueLength(Queue& q) {
	return (q.rear + MAXSIZE - q.front) % MAXSIZE;
}
bool PrintQueue(Queue& q) {
	for (int i = 0; i < MAXSIZE; i++) {
		printf("q.data[%d]=[%d]\n",i,q.data[i]);
	}
	printf("front=[%d],rear=[%d]\n", q.front, q.rear);
	return true;
}