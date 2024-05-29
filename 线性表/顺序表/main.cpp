#include<iostream>
#include<string>
#define MaxSize 20
using namespace std;
typedef struct  {
	int data[MaxSize];
	int length;
}Sqlist;
//初始化
void InitSql(Sqlist &l) {
	l.length = 0;
}
//线性表打印
void PrintSql(Sqlist &l) {
	for (int i = 0; i < l.length; i++)
	{
		printf("l.data[%d]=%d\n", i, l.data[i]);
	}
}
//插入
bool SqlInsert(Sqlist &l,int e,int i) {
	if (i<1 || i>l.length||l.length==MaxSize) {
		return false;
	}
	for (int j = l.length; j >= i;j--) {
		l.data[j] = l.data[j - 1];
	}
	l.data[i - 1] = e;
	l.length++;
	return true;
}

//删除
bool SqlDelete(Sqlist& l, int e, int i) {
	if (i<1 || i>l.length) {
		return false;
	}
	 e= l.data[i - 1];
	for (int j = i; j <l.length; j++) {
		l.data[j-1] = l.data[j];
	}
	
	l.length--;
	return true;
}
//按值删除
int SqlSelectByNum(Sqlist& l, int e) {
	for (int j = 0; j < l.length; j++) {
		if (l.data[j]==e) {
			return j + 1;
		}
		
	}
return -1;
}
//查询
int SqlSelectBy(Sqlist& l, int i) {
	if (i<1 || i>l.length) {
		return -1;
	}
	return l.data[i - 1];

}
//核对？
int select(int s[], int k, int i) {
	if (i > 10) {
		return -1;
	}
	if (s[i] == k) {
		return i + 1;
	}
	return select(s, k, i + 1);
}

//大题
//1.最小删除
bool Min_Delete(Sqlist &l,int &e) {
	if (l.length == 0) {
		return false;
	}
	int q = 0;
	for (int i = 0; i < l.length; i++) {
		if (l.data[i] < l.data[q]) {
			q = i;
		}
	}
	e = l.data[q];
	l.data[q] = l.data[l.length - 1];
	l.length--;
	return true;

}

//2.反转
bool Reverse(Sqlist &l) {
	if (l.length == 0) {
		return false;
	}
	for (int i = 0; i < l.length/2; i++) {
		l.data[i] += l.data[l.length - 1 - i];
		l.data[l.length - 1 - i] = l.data[i] - l.data[l.length - 1 - i];
		l.data[i] -= l.data[l.length - 1 - i];
	}
}
bool DeleteX(Sqlist& l, int x) {
	int count = 0;
	for (int i = 0; i < l.length; i++) {
		if (l.data[i] != x) {
			l.data[count] = l.data[i];
			count++;
		}
	}
	l.length = count;
	return true;
}
Sqlist HeBing(Sqlist l1,Sqlist l2) {
	//if ()  ����˳�����󳤶ȷ���
	if (l1.length + l2.length > MaxSize) {
		//return NULL;
	}
	int i=0, j = 0;
	Sqlist A;
	while (i < l1.length && j < l2.length) {
		if (l1.data[i] <= l2.data[j]) {
			A.data[i+j] = l1.data[i++];
		}
		else {
			A.data[i+j] = l2.data[j++];
		}
	}
	while (i < l1.length) {
		A.data[i + j] = l1.data[i++];
	}
	while (j < l2.length) {
		A.data[i + j] = l2.data[j++];
	}
	A.length = i + j;
	return A;
}

//指定位置逆序
bool HalfReverse(int a[],int left,int right) {
	for (left, right; left < (right + left) / 2; left++, right--) {
		a[left] += a[right];
		a[right] = a[left] - a[right];
		a[left] = a[left] - a[right];
	}
	return true;
}
//
// 中位数
void Middle(int s1[], int s2[],int l1,int l2) {
	int i = 0, j = 0;
	while (i + j < l1-1) {
		if (s1[i] > s2[j]) {
			j++;
		}
		else {
			i++;
		}
	}
	if (s1[i] < s2[j]) {
		printf("----��λ����%d---\n",s1[i]);
	}
	else {
		printf("----��λ����%d---\n", s2[j]);
	}
}
//9
int Min(int a, int b) {
	return a < b ? a : b;
}
bool BothHave(int A[], int B[], int C[],int n) {
	int i=0 , j=0 , k = 0;
	while (i < n && j < n && k < n) {
		if (A[i] == B[j] && B[j] == C[k]) {
			printf("-----��ͬԪ�أ�%d----------\n", A[i]);
			i++; j++; k++;
		}
		int min = Min(A[i], Min(B[j], C[k]));
		if (min == A[i]) { i++; }
		else if (min == B[j]) { j++; }
		else { k++; }

	}
	return true;
}
//12众数
int Major(int A[],int n) {
	int i, c, count = 1;
	c = A[0];
	for ( i = 1; i < n; i++)
	{
		if (A[i] == c) {
			count++;
		}
		else {
			if (count > 0) {
				count--;
			}
			else {
				c = A[i];
				count = 1;
			}
		}
	}
	if (count > 0) {
		for ( i =count= 0; i < n; i++)
		{
			if (A[i] == c) {
				count++;
			}
		}
	}
	if (count > n / 2) {
		return c;
	}
	else {
		return -1;
	}
}
int main() {
	int BA[3] = { 1,2,3 }; int BB[3] = { -2,0,1 }; int BC[3] = { -1,1,4 };
	BothHave(BA, BB,BC, 3);
	Sqlist lx;
	InitSql(lx);
	for (int i = 0; i < 10; i++)
	{
		lx.data[i] = i;
	}
	lx.data[4] = 3;
	lx.data[5] = 3;
	lx.length = 10;
	DeleteX(lx, 3);
	printf("------------ɾ��x------------");
	PrintSql(lx);
	printf("------------ɾ��x------------");
	Sqlist l;
	InitSql(l);
	for (int i = 0; i < 10; i++)
	{
		l.data[i] = i;
	}
	l.length = 10;
	PrintSql(l);

	bool flag=SqlInsert(l, 100, 5);
	if (flag) {
		PrintSql(l);
	}
	printf("��λ��ɾ��\n");
	int e=0;
	flag=SqlDelete(l,e,3);
	if (flag) {
		PrintSql(l);
	}
	else {
		printf("error\n");
	}


	e = SqlSelectByNum(l, 7);
	printf("��λ��=%d\n",e);

	e= SqlSelectBy(l, 4);
	printf("���ҵ���ֵΪ=%d\n", e);

	//�ݹ���ã����������е�ֵ
	int s[10] = { 0,1,2,3,4,5,6,7,8,9 };
	int a=select(s,100,0);
	printf("a==%d", a);
	//l1
	Sqlist l1;
	InitSql(l1);
	for (int i = 0; i <5; i++)
	{
		l1.data[i] = 2*i+1;
	}
	l1.length = 5;
	PrintSql(l1);
	//l2
	Sqlist l2;
	InitSql(l2);
	for (int i = 0; i < 5; i++)
	{
		l2.data[i] = 2 * i ;
	}
	l2.length = 5;
	PrintSql(l2);
	Sqlist A = HeBing(l1, l2);
	printf("____________________________________________\n");
	PrintSql(A);

	printf("______________________��ת______________________\n");
	int arr[] = { 0,1,2,3,4,5,6,7,8,9 };
	bool haha=HalfReverse(arr, 0,9);
	for (int i = 0; i < 10; i++)
	{
		printf("a[%d]=%d\n", i,arr[i]);
	}
	int arr1[] = { 0,1,2,3,4,5,6,7,8,9,11,22,33,44,55 };
	printf("______________________ԭ����______________________\n");
	for (int i = 0; i < 15; i++)
	{
		printf("arr1[%d]=%d\n", i, arr1[i]);
	}
	printf("______________________�������鷴ת______________________\n");
	HalfReverse(arr1, 0, 14);
	for (int i = 0; i < 15; i++)
	{
		printf("a[%d]=%d\n", i, arr1[i]);
	}
	printf("______________________ǰ�벿�����鷴ת______________________\n");
	HalfReverse(arr1, 0, 4);
	for (int i = 0; i <15; i++)
	{
		printf("a[%d]=%d\n", i, arr1[i]);
	}
	printf("______________________��벿�����鷴ת______________________\n");

	HalfReverse(arr1, 5, 14);
	for (int i = 0; i < 15; i++)
	{
		printf("arr1[%d]=%d\n", i, arr1[i]);
	}
	int s1[5] = { 2,4,6,8,10 };
	int s2[5] = {1,3,5,7,9};
	Middle(s1, s2, 5, 5);
	printf("-----------------------\n");
	int m[9] = { 1,3,3,3,3,1,3,5,6};
	int result=Major(m,9);
	printf("result=%d\n",result);
	return 0;

}

