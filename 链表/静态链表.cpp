#include<stdio.h>
#include<stdlib.h>
#define MaxSize 10
typedef struct SNode {
	int data;
	int next;
}SLinkList[MaxSize];//�����˳��ȾͲ��ɸı䣬�����̶�������֧��ָ��ĵͼ����ԣ�
//������Ҫ�̶��ĳ�������ϵͳ��FAT Fat���Ǿ�̬����
bool SInit(SLinkList& L) {
	L->next = -1;//��ͷΪ�գ�������-2��ʾ�ա�
	L->data = 10;
	for (int i = 1; i < MaxSize; i++) {
		L[i].next = -2;//����յ�
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
	printf("---��̬����---\n");
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
//ָ��λ�ò���
bool InsertPoint(SLinkList &L,int i,int e) {
	int location = SMalloc_S(L);
	if (location == -1) {
		return false;
	}
	int index = 0;//�ڼ���Ԫ��
	for (int j=0; j < i-1; j++) {//Ҫ�޸�Ԫ�ص�ǰһ�����޸�����next
		index = L[index].next;//����ȥ��Ҫɾ����ǰһ����λ��
	}
	int temp = L[index].next;//next����temp
	L[index].next = location;//next��Ϊ������Ԫ��λ��
	L[location].data = e;//Ԫ�����ݼ���
	L[location].next = temp;//������Ԫ�ص���һ��Ϊtemp
	return true;
}
//ָ��ɾ����Ҫ��Ԫ�ص�����ɾ�������ܰ����ɾ��
bool SDeletePoint(SLinkList& L, int i, int &e) {
	if (i<1||i>MaxSize) {
		return false;
	}
	int index = 0;//�ڼ���Ԫ��
	for (int j = 0; j < i - 1; j++) {//Ҫ�޸�Ԫ�ص�ǰһ�����޸�����next
		index = L[index].next;//����ȥ��Ҫɾ����ǰһ����λ��
	}
	int q = L[index].next;//q��ʱҪɾ����Ԫ��
	L[index].next=L[q].next;//��qǰһ����next��ָ��q��Ϊָ��q����һ��
	e = L[q].data;
	L[q].data = NULL;
	L[q].next = -2;//���q
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