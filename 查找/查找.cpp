#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
typedef struct SSTable {
	int *elem;
	int MAXLEN, length;//最大长度，实际长度
}SSTable;
//初始化
bool InitSSTable(SSTable &st) {
	st.elem = (int*)malloc(sizeof(int*));
	if (!st.elem)return false;
	st.MAXLEN = 1;
	st.length = 0;
	return true;
}
//malloc扩容
bool Increase_malloc(SSTable &st) {
	int* p = st.elem;
	//每次翻两倍
	st.elem = (int*)malloc(2 * st.MAXLEN * sizeof(int));
	//扩容失败
	if (!st.elem) {
		return false;
	}
	//重新赋值回来
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
//插入
bool InSert(SSTable &st, int i, int key) {
	if (i<1 || i>st.length + 1) {
		return false;
	}
	//两种扩容方式
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
	//将数组从末尾到第i-1个数值向后挪
	for (int  j = st.length; j >=i; j--)
	{
		st.elem[j] = st.elem[j - 1];
	}
	//赋值
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
//按位置删除
bool Delete(SSTable &st,int i,int &e) {//i为第几个字符，
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
	printf("当前容量:%d", st.MAXLEN);
	printf("\n当前长度:%d", st.length);
	printf("\n");
	for (int i = 0; i < st.length; i++)
	{
		printf("st.elem[%d]=%d\n", i, st.elem[i]);
	}
}

//顺序查找,返回下标
int Search_Seq(SSTable &st, int e) {
	int i = 0;
	for (i; i < st.length && st.elem[i] != e; i++){}
	return i==st.length?-1:i;
}
//顺序查找（哨兵）0位置空出来留给查找元素，倒着
int Search_Seq_Soldier(SSTable &st,int e) {
	st.elem[0] = e;
	int i = st.length;
	for (i; st.elem[i] != e; i++) {}
	return i;
}
//顺序查找树，
//概率不相同时，按概率降序排，可以提高成功查找的概率，
// 失败的概率会降到正常水平（按概率排会失去顺序，eg:升序降序等)。

//折半查找（二分查找）
//二分只适用于有序的顺序表、，升序降序。
//链表不能用二分
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
//递归二分查找
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
//大题
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

//分块查找  索引顺序查找
//就是查找表进行预处理，分为几块，每块选出一个标志组成索引表，
//查找时，先查找索引表，再进入对应的块进行查找。

//二叉排序树 ，（二叉查找树）
typedef struct BiNode {
	int data;
	BiNode* lchild, * rchild;
}BiNode,*BiTree;
//二叉树新增节点(非递归）(不对）
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
//二叉树新增节点(递归实现）
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
//构造二叉排序树
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
//层序遍历二叉排序树(打印）
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
//二叉排序树的查找
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
//二叉排序树的查找递归实现
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
	printf("位置为：%d\n", Search_Seq(st, 13));
	printf("位置为：%d\n", Binary_Search(st,9));
	printf("位置为：%d\n", Binary_Search_DiGui(st,9,0,st.length-1));
	BiTree t;
	//Create_BiTree(t, st.elem,st.length);
	//Print(t);
	int a[MAXSIZE] = { 10,3,4,2,1,0,6,7,8,9,11, };

	bool err=Create_BiTree(t, a, 11);
	if (!err) {
		printf("出现创建错误!\n");
	}
	Print(t);
	BiNode *Result=BSTSearch(t, 2);
	if (Result == NULL) {
		printf("没找到\n");
	}
	else {
		printf("找到的值为:%d\n", Result->lchild->data);
	}
	

	return 0;
}