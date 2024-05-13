#include<stdio.h>
#define MAXSIZE 10
typedef struct Queue {
	int data[MAXSIZE];
	int front, rear;
	//Ҫ����ʣ���һ���ռ�ʱ�������ó������пպ�������q.length==0,q.length==10
	int length;
	//Ҳ������tag��������һ�β�����������Ϊfalse�������Ϊtrue;
	// ֻ�г����лᵼ�¶���Ϊ�����Ե�  q.front==q.rear&&tag==false,
	//ֻ������лᵼ�¶��б��������Ե� q.front==q.rear&&tag==true,
	//����������Ϳ���������
	bool tag;
}Queue;
//��ʼ��
bool InitQueue(Queue &q) {
	//Ҳ�п��ܶ�βָ��ָ���βԪ�أ���ôʵ�����ʱҪ����(rear=rear+1)%MAXSIZE(���Ųһλ���ں��ٽ��и�ֵ
	//βָ���ʼ��ʱλ�÷����仯����ô�пղ���ҲҪ�����仯
	q.front =q.rear =  0;//��ָ��0�����rear++,����front++
	return true;

}
//�п�
bool IsEmpty(Queue& q) {
	if (q.front == q.rear) {
		return true;
	}
	return false;
}
//�����������жϷ�ʽ���һ�������ǿյģ�����Ҫʣ�����һ���ռ�����
bool IsFull(Queue &q) {
	if ((q.rear + 1)%MAXSIZE == q.front) {
		return true;
	}
	return false;
}
//���
bool EnQueue(Queue& q, int x) {
	if ((q.rear + 1) % MAXSIZE == q.front) {
		return false;
	}
	q.data[q.rear] = x;
	q.rear = (q.rear + 1) % MAXSIZE;
	return true;
}
//����
bool DeQueue(Queue& q, int &x) {
	if (q.front == q.rear) {
		return false;//�ӿղ��ܳ���
	}
	
	x = q.data[q.front];
	q.data[q.front] = 0;
	q.front = (q.front + 1) % MAXSIZE;
	return true;
}
//����Ԫ�ظ���
//(rear+size-front)%size
//�����е�Ԫ�ظ���
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