#include<stdio.h>
#include<string.h>
#define MAXLENGTH 10

typedef struct Stack {
	int data[MAXLENGTH];
	int top;
}SqStack;
//��ʼ��
bool InItShStack(SqStack& S) {
	S.top = -1;
	S.top = MAXLENGTH;
	return true;
}
//��ʼ��
bool InitStack(SqStack& S) {
	S.top = -1;
	//topҲ����ָ��0
	return true;
}
//�п�
bool IsEmpty(SqStack& S) {
	if (S.top == -1) {//S.top==0;
		return true;
	}
	return false;
}
//��ջ
bool Push(SqStack& S, int x) {
	if (S.top == MAXLENGTH - 1) {
		return false;
	}
	S.data[++S.top] = x;
	//top��ʼΪ0�Ļ�Ҫ�ȸ���������
	//S.data[S.top++] = x;
	return true;
}
//��ջ
bool Pop(SqStack& s, int& x) {
	if (s.top == -1) {
		return false;
	}
	x = s.data[s.top--];
	//���Լ�����ֵ
	//x = S.data[--S.top];
	return true;
}
//����ջ�������ż��
bool BracketCheck(char a[], int length) {
	//������ջʵ�֣�Ҳ����������ģ��ջʵ��
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
		//�������������ţ����Ҷ���Ϊ��ֱ�ӷ��ش���ƥ��ʧ��
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
	//��ջʵ��
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
			printf("ƥ��ɹ�\n");
		}
		else {
			printf("ƥ����ִ���\n");
		}
	return 0;
}