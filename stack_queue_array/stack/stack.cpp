#include<stdio.h>
#include<windows.h>
#define MAXLENGTH 10
typedef struct Stack {
	int data[MAXLENGTH];
	int top;
}SqStack;	

//共享栈
//初始化
bool InItShStack(SqStack& S) {
	S.top = -1;
	S.top = MAXLENGTH;
	return true;
}
//初始化
bool InitStack(SqStack& S) {
	S.top = -1;
	//top也可以指向0
	return true;
}
//判空
bool IsEmpty(SqStack& S) {
	if (S.top == -1) {//S.top==0;
		return true;
	}
	return false;
}
//入栈
bool Push(SqStack& S, int x) {
	if (S.top == MAXLENGTH - 1) {
		return false;
	}
	S.data[++S.top] = x;
	//top初始为0的话要先复制在自增
	//S.data[S.top++] = x;
	return true;
}
//出栈
bool Pop(SqStack& S, int& x) {
	if (S.top == -1) {
		return false;
	}
	x = S.data[S.top--];
	//先自减再增值
	//x = S.data[--S.top];
	return true;
}
//返回头元素
int FindTop(SqStack& S) {
	if (S.top == -1) {
		return -1;
	}
	return S.data[S.top];
}
