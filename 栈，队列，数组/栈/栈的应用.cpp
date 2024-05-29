#include<stdio.h>
#include<string.h>
#define MAXLENGTH 10

typedef struct Stack {
	int data[MAXLENGTH];
	int top;
}SqStack;
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
bool Pop(SqStack& s, int& x) {
	if (s.top == -1) {
		return false;
	}
	x = s.data[s.top--];
	//先自减再增值
	//x = S.data[--S.top];
	return true;
}
//利用栈进行括号检查
bool BracketCheck(char a[], int length) {
	//可以用栈实现，也可以用数组模仿栈实现
	//Stack s;
	//InitStack(s);
	char b[100] = {};
	int top = -1,x;
	for (int i = 0; i < length; i++)
	{
		if (a[i] == '(' || a[i] == '[' || a[i] == '{') {
			//Push(s, x);
			b[++top] = a[i];
			continue;
		}
		//出现这三种括号，而且队列为空直接返回错误，匹配失败
		else {
			//if (IsEmpty(s)){
				//return false;
			//}
			if (strlen(b) == 0) {
				return false;
			}
		}
		switch (a[i]) {
		case ')':
			//x = Pop(s, x);
			x = b[top--];
			if (x != '(') {
				return false;
			}continue;
		case ']':
			//x = Pop(s, x);
			x = b[top--];
			if (x != '[') {
				return false;
			}continue;
		case '}':
			//x = Pop(s, x); 
			x = b[top--];
			if (x != '{') {
				return false;
			}continue;
		}
	}
	//用栈实现
		//if (!IsEmpty(s)) {
			//return false;
		//}
	if (top!=-1){
		return false;
	}
	return true;
}
int main() {
	char a[100] = "{[((()())())]}";
	bool flag = BracketCheck(a, strlen(a));
		if (flag) {
			printf("匹配成功\n");
		}
		else {
			printf("匹配出现错误\n");
		}
	return 0;
}