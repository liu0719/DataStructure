#include<stdio.h>
#include<stdlib.h>
/*
typedef struct LNode{
    int data;
	LNode *next;
}LNode,*LinkList;
//带头节点
//判空函数
//p为指针，p->指向的就是p指向元素的位置，*p=a（p->data)==(a.data)
bool LEmpty(LinkList L) {
	if (L->next == NULL) {
		return true;
	}
	else {
		return false;
	}
}
//带头节点初始化
void LInitLinkListHead(LinkList &L) {
	L = (LNode *)malloc(sizeof(LNode));
	L->next = NULL;
}
//长度，就按下标算，头结点为零
int LLengthOfList(LinkList &L) {
	int i = 0; LNode* p = L;
	while (p->next != NULL) {
		p = p->next;
		i++;
	}
	return i;
}
//打印函数
void LPrintList(LinkList &L) {
	LNode *p = L->next;
	while (p != NULL) {
		printf("-->%d", p->data);
		p = p->next;
		
	}
	printf("\n");
	return;
}
//按位置查找
LNode* LSelectByLocation(LinkList& L, int i) {//i为插入的位置，
	LNode* p = L; int j = 0;//同打印按下标来
	while (p != NULL && j < i) {
		p = p->next;
		j++;
	}
	return p;
}
//按值查找
LNode* LSelectByValue(LinkList& L, int e) {//e是查找的元素
	LNode* p = L;
	while (p != NULL && p->data != e) {//找到就停止，为空也停止
		p = p->next;
	}
	return p;
}
//按位置添加节点
bool LInsertLNode(LinkList& L, int i, LNode* s) {
	LNode* p = L; int j = 0;
	while (p != NULL && j < i - 1) {//找到目标节点的前一个，按下标来，所以i-1
		p = p->next;
		j++;
	}
	if (p == NULL) {//若是最后一个节点为null说明i值不合法，可以是null前一个
		return false;
	}
	s->next = p->next;//添加节点先把后面挂上
	p->next = s;
	return true;

}
//按位置删除节点
bool LDeleteLNode(LinkList& L, int i) {
	LNode *p = L; int j = 0;
	while (p != NULL && j < i - 1) {//找到要删除的前一个位置
		p = p->next;
		j++;
	}
	if (p == NULL || p->next == NULL) {//tc
		return false;
	}
	LNode* q = p->next;
	p->next = q->next;
	//free(q);
	return true;
}
//修改链表
bool LUpdataList(LinkList& L, int i, int e) {
	LNode* p = L; int j = 0;
	while (p != NULL && i < j) {
		p = p->next;
		j++;
	}
	if (p == NULL) {
		return false;
	}
	p->data = e;
	return true;
}
//删除节点*P
bool LDeletePointNode(LinkList &L,LNode *p) {
	if (p->next == NULL) {
		return false;
	}
	LNode* s=p->next;
	p->data = s->data;
	p->next = s->next;
	free(s);
	return true;
}
//在p节点前插入
bool LInsertbefore(LinkList& L, LNode* p,LNode *s) {
	s->next = p->next;//在p后新建一个结点，当做后插，然后交换p和s的值
	p->next = s;
	int temp = p->data;
	p->data = s->data;
	s->data = temp;
	return true;
}
//不带头结点
void LInitLinkList(LinkList& L) {
	L = NULL;
}
//头插实现原链表倒置
LinkList LHeadInsert(LinkList &L) {
	LNode* s; int x;
	L = (LNode*)malloc(sizeof(LNode));//指针变量要申请空间进行初始化
	printf("请输入头插法建立的链表数字\n");
	scanf_s("%d", &x);
	while (x != -1) {
		s = (LNode*)malloc(sizeof(LNode));//要申请空间进行初始化
		s->data = x;
		s->next = L->next;
		L->next = s;
		printf("加入成功，输入-1退出\n");
		scanf_s("%d", &x);
	}
	return L;

}
//尾插
LinkList LTailInsert(LinkList &L) {
	L = (LNode*)malloc(sizeof(LNode));
	LNode* s , * r = L; int x;
	printf("请输入尾插法建立的链表数字\n");
	scanf_s("%d", &x);
	while (x != -1) {
		s = (LNode*)malloc(sizeof(LNode));//要申请空间进行初始化
		s->data = x;
		s->next = r->next;
		r->next = s;
		r = r->next;
		printf("加入成功，输入-1退出\n");
		scanf_s("%d", &x);
	}
	return L;
}
int main() {
	LinkList L1;
	//InitLinkListHead(L1);
	L1=TailInsert(L1);
	PrintList(L1);
	LinkList l ;
	InitLinkListHead(l);
	if (Empty(l)) {
		printf("链表为空\n");
	}
	LNode n3 = {3,NULL};
	LNode n2 = { 2,&n3 };
	LNode n1 = { 1,&n2 };
	l->next = &n1;
	int length = LengthOfList(l);
	printf("链表长度=%d\n", length);
	PrintList(l);
	//查找
	printf("查到的元素为%d\n", SelectByLocation(l, 1)->data);
	printf("查到的元素为%d\n", SelectByValue(l,2)->data);
	//添加
	LNode n4 = { 4,NULL };
	InsertLNode(l, 1, &n4);
	printf("添加后\n");
	PrintList(l);
	//删除
	DeleteLNode(l, 3);
	printf("删除后\n");
	PrintList(l);
	printf("--------------双链表-----------");
	testDNode();
	return 0;
}*/