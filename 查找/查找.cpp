#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
typedef struct SSTable {
	int *elem;
	int MAXLEN, length;//��󳤶ȣ�ʵ�ʳ���
}SSTable;
//��ʼ��
bool InitSSTable(SSTable &st) {
	st.elem = (int*)malloc(sizeof(int*));
	if (!st.elem)return false;
	st.MAXLEN = 1;
	st.length = 0;
	return true;
}
//malloc����
bool Increase_malloc(SSTable &st) {
	int* p = st.elem;
	//ÿ�η�����
	st.elem = (int*)malloc(2 * st.MAXLEN * sizeof(int));
	//����ʧ��
	if (!st.elem) {
		return false;
	}
	//���¸�ֵ����
	for (int i = 0; i < st.length; i++) {
		st.elem[i] = p[i];
	}
	st.MAXLEN *= 2;
	return true;
}
bool Increase_reallloc(SSTable &st) {
	st.elem = (int*)realloc(st.elem, st.MAXLEN * 2 * sizeof(int));
	st.MAXLEN *= 2;
	if (!st.elem) return false;
	return true;
}
//����
bool InSert(SSTable &st, int i, int key) {
	if (i<1 || i>st.length + 1) {
		return false;
	}
	//�������ݷ�ʽ
	//if (Increase_malloc(st)) {
	//	return false;
	//}
	bool err=true;
	if (st.length == st.MAXLEN) {
		err=Increase_reallloc(st);
	}

	if (!err) {
		return false;
	}
	//�������ĩβ����i-1����ֵ���Ų
	for (int  j = st.length; j >=i; j--)
	{
		st.elem[j] = st.elem[j - 1];
	}
	//��ֵ
	st.elem[i-1] = key;
	st.length++;
	return true;
}
bool IsEmpty(SSTable &st) {
	if (st.length = 0) {
		return false;
	}
	return true;
}
//��λ��ɾ��
bool Delete(SSTable &st,int i,int &e) {//iΪ�ڼ����ַ���
	if (st.length == 0 || i<1 || i>st.length) {
		return false;
	}
	e=st.elem[i - 1];
	for (int j = i-1; j < st.length-1; j++)
	{
		st.elem[j] = st.elem[j + 1];
	}
	st.length--;
	return true;
}
void Print(SSTable &st) {
	printf("��ǰ����:%d", st.MAXLEN);
	printf("\n��ǰ����:%d", st.length);
	printf("\n");
	for (int i = 0; i < st.length; i++)
	{
		printf("st.elem[%d]=%d\n", i, st.elem[i]);
	}
}

//˳�����,�����±�
int Search_Seq(SSTable &st, int e) {
	int i = 0;
	for (i; i < st.length && st.elem[i] != e; i++){}
	return i==st.length?-1:i;
}
//˳����ң��ڱ���0λ�ÿճ�����������Ԫ�أ�����
int Search_Seq_Soldier(SSTable &st,int e) {
	st.elem[0] = e;
	int i = st.length;
	for (i; st.elem[i] != e; i++) {}
	return i;
}
//˳���������
//���ʲ���ͬʱ�������ʽ����ţ�������߳ɹ����ҵĸ��ʣ�
// ʧ�ܵĸ��ʻή������ˮƽ���������Ż�ʧȥ˳��eg:�������)��

//�۰���ң����ֲ��ң�
//����ֻ�����������˳�����������
//�������ö���
int Binary_Search(SSTable st,int key) {
	int left = 0, right = st.length - 1,mid=0;
	while (left<= right) {
		mid = (left + right) / 2;
		if (st.elem[mid] == key) {
			return mid;
		}
		else if (key> st.elem[mid]) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return -1;
}
//�ݹ���ֲ���
int Binary_Search_DiGui(SSTable st, int key, int low, int high) {
	if (low > high)return 0;
	int mid = (low + high) / 2;
	if (st.elem[mid] > key) {
		Binary_Search_DiGui(st, key, low, mid - 1);
	}
	else if(st.elem[mid]<key){
		Binary_Search_DiGui(st, key, mid + 1, high);
	}
	else {
		return mid;
	}
}
//����
//6
bool Question6(int A[MAXSIZE][MAXSIZE], int n, int key) {
	int i = 0, j = n - 1;
	while (i < n && j >= 0) {
		if (A[i][j] == key) {
			return true;
		}
		else if (A[i][j] > key) {
			j--;
		}
		else {
			i--;
		}
	}
	return false;
}

//�ֿ����  ����˳�����
//���ǲ��ұ����Ԥ������Ϊ���飬ÿ��ѡ��һ����־���������
//����ʱ���Ȳ����������ٽ����Ӧ�Ŀ���в��ҡ�

//���������� ���������������
typedef struct BiNode {
	int data;
	BiNode* lchild, * rchild;
}BiNode,*BiTree;
//�����������ڵ�(�ǵݹ飩(���ԣ�
bool BiTree_Insert(BiTree t, int key) {
	if (!t) {
		BiNode *s = (BiNode*)malloc(sizeof(BiNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		t = s;
		return true;
	}
	BiNode* pre = NULL;
	while (t) {
		if (key == t->data) {
			return 0;
		}
		else if (key > t->data) {
			pre = t;
			t = t->rchild;
		}
		else {
			pre = t;
			t = t->lchild;
		}
	}
	BiNode *s= (BiTree)malloc(sizeof(BiNode));
	s->data = key;
	s->lchild = s->rchild = NULL;
	if (key > pre->data) {
		pre->rchild = s;
	}
	if (key < pre->data) {
		pre->lchild = s;
	}
	return true;
}
//�����������ڵ�(�ݹ�ʵ�֣�
bool BiTree_Insert_DIGUI(BiTree &t, int key) {
	if (!t) {
		t = (BiTree)malloc(sizeof(BiNode));
		t->data = key;
		t->lchild = NULL;
		t->rchild = NULL;
		return true;
	}
	if (key < t->data) {
		return BiTree_Insert(t->lchild, key);
	}
	else if(key>t->data){
		return BiTree_Insert(t->rchild, key);
	}
	else {
		return false;
	}
}
//�������������
bool Create_BiTree(BiTree &t, int a[],int length) {
	t = NULL;
	bool err = true;
	for (int i = 0; i < length; i++)
	{
		err= BiTree_Insert(t, a[i]);
		if (!err) {
			return err;
		}
	}
	return true;
}
//�����������������(��ӡ��
void Print(BiTree t) {
	BiNode *q[MAXSIZE] = { 0 };
	int front = -1,rear=-1,level=0,last=0;
	q[++rear] = t;
	int i = 0;
	while (front<rear)
	{
		t = q[++front];
		printf(" %d ", t->data);
		if (t->lchild) {
			q[++rear] = t->lchild;
		}
		if (t->rchild) {
			q[++rear] = t->rchild;
		}
		if (front == last) {
			printf("\n");
			level++;
			last = rear;
		}
	}
}
//�����������Ĳ���
BiNode* BSTSearch(BiTree t, int key) {
	while (t&&t->data!=key)
	{
		if (key < t->data) {
			t = t->lchild;
		}
		if (key > t->data) {
			t = t->rchild;
		}
	}
	return t;
}
//�����������Ĳ��ҵݹ�ʵ��
BiNode* BSTSearch_DIGUI(BiTree t, int key) {
	if (t == NULL) return NULL;
	if (key == t->data) {
		return 0;
	}
	else if(key<t->data){
		return BSTSearch_DIGUI(t->lchild,key);
	}
	else {
		return BSTSearch_DIGUI(t->rchild, key);
	}
}
int main() {
	SSTable st;
	InitSSTable(st);
	Print(st);
	for (int i = 1; i < 10; i++)
	{
		InSert(st, i, i);
	}
	Print(st);
	int e = 0;
	//Delete(st, 5, e);
	Print(st);
	printf("λ��Ϊ��%d\n", Search_Seq(st, 13));
	printf("λ��Ϊ��%d\n", Binary_Search(st,9));
	printf("λ��Ϊ��%d\n", Binary_Search_DiGui(st,9,0,st.length-1));
	BiTree t;
	//Create_BiTree(t, st.elem,st.length);
	//Print(t);
	int a[MAXSIZE] = { 10,3,4,2,1,0,6,7,8,9,11, };

	bool err=Create_BiTree(t, a, 11);
	if (!err) {
		printf("���ִ�������!\n");
	}
	Print(t);
	BiNode *Result=BSTSearch(t, 2);
	if (Result == NULL) {
		printf("û�ҵ�\n");
	}
	else {
		printf("�ҵ���ֵΪ:%d\n", Result->lchild->data);
	}
	

	return 0;
}