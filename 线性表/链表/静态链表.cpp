#include<stdio.h>
#include<stdlib.h>
#define MaxSize 10
typedef struct SNode {
	int data;
	int next;
}SLinkList[MaxSize];//定义了长度就不可改变，容量固定，早起不支持指针的低级语言，
//容量需要固定的场景操作系统的FAT Fat就是静态链表
bool SInit(SLinkList& L) {
	L->next = -1;//表头为空，其他用-2表示空。
	L->data = 10;
	for (int i = 1; i < MaxSize; i++) {
		L[i].next = -2;//代表空的
	}
	return true;
}
bool SIsEmpty(SLinkList& L) {
	if (L->next == -1) {
		return true;
	}
	return false;
}
void SPrintList(SLinkList& L) {
	printf("---静态链表---\n");
	for (int i = 0; i < MaxSize; ++i) {
		printf("SNode[%d].data = %d, SNode[%d].next = %d\n", i, L[i].data, i, L[i].next);
	}
}
int SMalloc_S(SLinkList& L) {
	for (int i = 1; i < MaxSize; i++) {
		if (L[i].next == -2) {
			return i;
		}
	}
	return -1;
}
bool SInsert(SLinkList &L,int e) {
	int location = SMalloc_S(L);
	if (location == -1) {
		return false;
	}
	for (int i = 0; i < MaxSize; i++) {
		if (L[i].next == -1) {
			L[location].data = e;
			L[i].next = location;
			L[location].next = -1;
		}
	}
	return true;
	
}
//指定位置插入
bool InsertPoint(SLinkList &L,int i,int e) {
	int location = SMalloc_S(L);
	if (location == -1) {
		return false;
	}
	int index = 0;//第几个元素
	for (int j=0; j < i-1; j++) {//要修改元素的前一个，修改他的next
		index = L[index].next;//不断去找要删除的前一个的位置
	}
	int temp = L[index].next;//next赋给temp
	L[index].next = location;//next改为新增的元素位置
	L[location].data = e;//元素数据加入
	L[location].next = temp;//新增的元素的下一个为temp
	return true;
}
//指定删除，要按元素的链接删除，不能按序号删除
bool SDeletePoint(SLinkList& L, int i, int &e) {
	if (i<1||i>MaxSize) {
		return false;
	}
	int index = 0;//第几个元素
	for (int j = 0; j < i - 1; j++) {//要修改元素的前一个，修改他的next
		index = L[index].next;//不断去找要删除的前一个的位置
	}
	int q = L[index].next;//q即时要删除的元素
	L[index].next=L[q].next;//把q前一个的next由指向q变为指向q的下一个
	e = L[q].data;
	L[q].data = NULL;
	L[q].next = -2;//清空q
	return true;
}
int main() {
	SLinkList l;
	SInit(l);
	for (int i = 0; i < 5; i++)
	{
		SInsert(l, i);
	}
	SPrintList(l);
	InsertPoint(l, 3, 1000);
	InsertPoint(l, 1, 6000);
	SPrintList(l);
	int e;
	SDeletePoint(l, 3, e);
	SPrintList(l);
	InsertPoint(l, 4, 4000);
	SPrintList(l);
	InsertPoint(l, 1, 2000);
	InsertPoint(l, 1, 99999);

	SPrintList(l);
	SDeletePoint(l, 3, e);
	SPrintList(l);

//}