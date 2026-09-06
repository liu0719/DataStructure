#include<stdio.h>
#include<malloc.h>
#include<windows.h>
//二叉树 
typedef struct BiNode {
	int data;
	BiNode* lChild, * rChild;
}BiNode, * BiTree;
//线索二叉树 
typedef struct ThreadNode {
	int data;
	ThreadNode* lChild, * rChild;
	int lTag, rTag;
}ThreadNode, * ThreadTree;
//树初始化
bool InitTree(ThreadTree& t) {
	t = (ThreadNode*)malloc(sizeof(ThreadNode));
	t->data = 1;
	t->lChild = NULL;
	t->lTag = 0;
	t->rChild = NULL;
	t->rTag = 0;
	return true;
}
//指定节点添加左孩子
bool AddlChild(ThreadNode* q, int data) {
	ThreadNode* s = (ThreadNode*)malloc(sizeof(ThreadNode));
	s->data = data;
	s->lChild = NULL;
	s->lTag = 0;
	s->rChild = NULL;
	s->rTag = 0;
	q->lChild = s;
	return true;
}
//指定节点添加右孩子
bool AddrChild(ThreadNode* q, int data) {
	ThreadNode* s = (ThreadNode*)malloc(sizeof(ThreadNode));
	s->data = data;
	s->lChild = NULL;
	s->lTag = 0;
	s->rChild = NULL;
	s->rTag = 0;
	q->rChild = s;
	return true;
}
//前序线索化，具体实现
void FrontThread(ThreadTree t, ThreadTree& pre) {
	if (t == NULL) {
		return;
	}
	// 线索化逻辑 
	if (t->lChild == NULL) {
		t->lChild = pre;
		t->lTag = 1;
		printf("%d->leftChild=%d\n", t->data, pre->data);
	}
	if (pre != NULL && pre->rChild == NULL) {
		pre->rChild = t;
		pre->rTag = 1;
		printf("%d->rightChild=%d\n", pre->data, t->data);
	}
	pre = t;
	//遍历逻辑 
	if (t->lTag == 0) {
		FrontThread(t->lChild, pre);
	}

	FrontThread(t->rChild, pre);
}
//前序线索化
void CreateFrontThread(ThreadTree t) {
	ThreadNode* pre = NULL;
	if (t == NULL) {
		return;
	}
	FrontThread(t, pre);
	if (pre->rChild == NULL) {
		pre->rTag = 1;
		printf("%d->rightChild=NULL\n", pre->data);
	}
}
//中序线索化，具体实现
void MiddleThread(ThreadTree t, ThreadTree& pre) {
	if (t == NULL) {
		return;
	}
	//遍历逻辑 
	MiddleThread(t->lChild, pre);
	// 线索化逻辑 
	if (t->lChild == NULL) {
		t->lChild = pre;
		t->lTag = 1;
		if (pre != NULL) {
			printf("%d->leftChild=%d\n", t->data, pre->data);
		}
		else {
			printf("%d->leftChild=NULL\n", t->data);
		}
		
	}
	if (pre != NULL && pre->rChild == NULL) {
		pre->rChild = t;
		pre->rTag = 1;
		printf("%d->rightChild=%d\n", pre->data, t->data);
	}
	pre = t;
	//遍历逻辑 
	MiddleThread(t->rChild, pre);
}
//中序线索化
void CreateMiddleThread(ThreadTree t) {
	ThreadNode* pre = NULL;
	if (t == NULL) {
		return;
	}
	MiddleThread(t, pre);
	if (pre->rChild == NULL) {
		pre->rTag = 1;
		printf("%d->rightChild=NULL\n", pre->data);
	}
}
//后序线索化，具体实现
void FinalThread(ThreadTree t, ThreadTree& pre) {
	if (t == NULL) {
		return;
	}
	//遍历逻辑 
	FinalThread(t->lChild, pre);
	FinalThread(t->rChild, pre);
	// 线索化逻辑 
	if (t->lChild == NULL) {
		t->lChild = pre;
		t->lTag = 1;
		if (pre != NULL) {
			printf("%d->leftChild=%d\n", t->data, pre->data);
		}
		else {
			printf("%d->leftChild=NULL\n", t->data);
		}

	}
	if (pre != NULL && pre->rChild == NULL) {
		pre->rChild = t;
		pre->rTag = 1;
		printf("%d->rightChild=%d\n", pre->data, t->data);
	}
	pre = t;
}
//后序线索化
void CreateFinalThread(ThreadTree t) {
	ThreadNode* pre = NULL;
	if (t == NULL) {
		return;
	}
	FinalThread(t, pre);
	if (pre->rChild == NULL) {
		pre->rTag = 1;
		printf("%d->rightChild=NULL\n", pre->data);
	}
}
//前序遍历
bool FrontPrint(ThreadTree t) {
	if (t != NULL) {
		printf("%d", t->data);
		FrontPrint(t->lChild);
		FrontPrint(t->rChild);
	}
	return true;
}
//中序遍历
bool MiddlePrint(ThreadTree t) {
	if (t != NULL) {
		MiddlePrint(t->lChild);
		printf("%d", t->data);
		MiddlePrint(t->rChild);
	}
	return true;
}
//后序遍历
bool FinalPrint(ThreadTree t) {
	if (t != NULL) {
		FinalPrint(t->lChild);
		FinalPrint(t->rChild);
		printf("%d", t->data);
	}
	return true;
}
//后序非递归遍历,这里用未线索化的二叉树
bool PostOrder(ThreadTree t) {
	ThreadNode* p = t, * r = NULL;
	ThreadNode* stack[100] = {};
	int top = -1;//用数组模拟栈
	while (p||top!=-1)
	{
		if (p) {                          //p不为空则，
			stack[++top] = p;       //将其入栈
			p = p->lChild;                //并p向左孩子移动
		}
		else {                                  //p为空时说明左孩子没了，或者刚将元素出完栈
			p = stack[top];                     //这里只访问，不出站，因为可能还有右节点没有遍历到
			if (p->rChild && p->rChild != r) {  //p右孩子不为空且不等于刚出站的元素，这里r是为了刚标记出栈的右孩子
				p = p->rChild;                  //没有遍历过的右节点在下次循环时会存入栈；
			}
			else {             //走到这里说明p已经没有左孩子和右孩子了，我们是先判断有没有左，没有做在判断右，走到这里只能是左右都没有了，而且p是最左分支的最左下节点，可以放心出栈
				p = stack[top--];//出栈
				printf("%d", p->data);//访问操作
				r = p;     //记录当前出栈的节点，下次访问栈顶的元素是其父节点，用r标记就不必再次遍历了
				p = NULL;   //出栈完，将p置为空，方便下次访问栈顶元素
			}
		}//else
	}//while
	return true;
}


int main() {
    // 设置控制台输出为UTF-8，解决中文乱码
    SetConsoleOutputCP(65001);
	ThreadTree t;
	InitTree(t);
	AddlChild(t, 2);
	AddlChild(t->lChild, 4);
	AddrChild(t->lChild, 5);
	AddrChild(t, 3);
	AddlChild(t->rChild, 6);
	AddrChild(t->rChild, 7);
	printf("%--------前序--------\n");
	FrontPrint(t);
	printf("\n");
	CreateFrontThread(t);
	printf("%--------中序--------\n");
	MiddlePrint(t);
	printf("\n");
	CreateMiddleThread(t);
	printf("%--------后序--------\n");
	FinalPrint(t);
	printf("\n");
	CreateFinalThread(t);
	PostOrder(t);
	return 0;
 }
