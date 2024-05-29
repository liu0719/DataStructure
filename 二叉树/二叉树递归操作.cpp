#include<stdio.h>
#include<stdlib.h>
typedef struct BiNode { 
	int data;
	BiNode* lChild, * rChild;
}BiNode,*BiTree;
//Init
void InitBiTree(BiTree &t) {
	t = (BiNode*)malloc(sizeof(BiNode));
	t->data = 1;
	t->lChild = NULL;
	t->rChild = NULL;
}
//指定节点添加右孩子
bool AddrChild(BiNode* q, int data) {
	BiNode* s = (BiNode*)malloc(sizeof(BiNode));
	s->data = data;
	s->lChild = NULL;
	s->rChild = NULL;
	q->rChild = s;
	return true;
}
//添加左孩子
bool AddlChild(BiNode* q, int data) {
	BiNode* s = (BiNode*)malloc(sizeof(BiNode));
	s->data = data;
	s->lChild = NULL;
	s->rChild = NULL;
	q->lChild = s;
	return true;
}
//统计度为1的节点数
int GetNumOfSingalChild(BiTree t) {
	int num=0;
	if (!t) {
		return 0;
	}
	else {
		num+= GetNumOfSingalChild(t->lChild);
		num+= GetNumOfSingalChild(t->rChild);
		if (t->lChild && t->rChild||!t->lChild &&!t->rChild) {
			return num;
		}
		else {
			return num + 1;
		}
	}
	
}
//统计度为2的节点数
int GetNumOfDoubleChild(BiTree t) {
	int num = 0;
	if (!t) {
		return 0;
	}
	else {
 		num += GetNumOfDoubleChild(t->lChild);
		num += GetNumOfDoubleChild(t->rChild);
		if (t->lChild && t->rChild ) {
			return num+1;
		}
		else {
			return num;
		}
	}

}
//统计度为0的点
int GetNumofZeroChild(BiTree t) {
	if (!t) { return 0; }
	int num=0;
	num+=GetNumofZeroChild(t->lChild);
	num+=GetNumofZeroChild(t->rChild);
	if (!t->lChild && !t->rChild) {
		return num + 1;
	}
	else {
		return num;
	}
}
//求高度
int GetHeight(BiTree t) {
	if (!t) { return 0; }
	int hl = GetHeight(t->lChild);
	int hr = GetHeight(t->rChild);
	if (hl >= hr) {
		return hl +1;
	}
	else {
		return hr;
	}
}
//二叉树递归求宽
int count[100]={};//数组标记每层的节点数
int WIDTH = -1;
void GetWidth(BiTree t,int k) {//k为层次，最开始是第一层
	if (!t) return ;
	count[k]++;
	if (WIDTH < count[k]) WIDTH = count[k];
	GetWidth(t->lChild, k + 1);
	GetWidth(t->rChild, k + 1);
}
//删除所有叶子,
void DeleteLeaf(BiTree t) {
	if (!t) { return; }
	if (t->lChild && !t->lChild->lChild && !t->lChild->rChild) {
		free(t->lChild);
		t->lChild = NULL;
	}
	if (t->rChild && !t->rChild->lChild && !t->rChild->rChild) {
		free(t->rChild);
		t->rChild = NULL;
	}
	DeleteLeaf(t->lChild);
	DeleteLeaf(t->rChild);
}
//先序遍历打印
void PrintPre(BiTree t) {
	if (!t)return;
	printf("%d", t->data);
	PrintPre(t->lChild);
	PrintPre(t->rChild);
}
//MAX即为所求宽度

//p节点所在层次
int GetpLevel(BiTree t, int  p) {
	if (!t || !p) { return 0; }
	int llevel = 0, rlevel = 0;
	llevel=GetpLevel(t->lChild,p);
	rlevel=GetpLevel(t->rChild,p);
	if (llevel != 0|| rlevel != 0 ||t->data == p) {
		if (llevel >= rlevel)return llevel + 1;
		else return rlevel + 1;
	}
	else {
		return 0;
	}
}
//找树中最大值
int GetMax(BiTree t) {
	if (!t) { return 0; }
	int lMax = 0, rMax = 0;
	lMax = GetMax(t->lChild);
	rMax = GetMax(t->rChild);
	if (t->data >= lMax && t->data >= rMax) {
		return t->data;
	}
	else {
		return lMax >= rMax ? lMax : rMax;
	}
}
//先序输出节点值和所在层次
void PrintDataAndLevel(BiTree t,int i) {//i为层次，初始为1
	if (!t)return ;
	printf("节点值:%d,节点所在层次:%d\n", t->data, i);
	PrintDataAndLevel(t->lChild,i+1);
	PrintDataAndLevel(t->rChild,i+1);
}
int main() {
	BiTree t;
	InitBiTree(t);
	AddlChild(t, 2);
	AddlChild(t->lChild, 4);
	AddrChild(t->lChild, 5);
	AddrChild(t, 3);
	AddlChild(t->rChild, 6);
	AddrChild(t->rChild, 7);
	//4下面挂
	AddlChild(t->lChild->lChild, 8);
	AddrChild(t->lChild->lChild, 9);
	//5下面
	AddlChild(t->lChild->rChild, 10);
	//AddlChild(t->lChild->rChild->lChild, 8);
	//AddlChild(t->lChild->rChild->lChild->lChild, 9);
	AddrChild(t->lChild->rChild, 11);
	//6下面
	AddlChild(t->rChild->lChild, 12);
	AddrChild(t->rChild->lChild, 13);
	//7下面
	AddlChild(t->rChild->rChild, 14);
	AddrChild(t->rChild->rChild, 15);

	printf("%d",GetNumOfSingalChild(t));
	printf("%d",GetNumOfDoubleChild(t));
	printf("%d", GetNumofZeroChild(t));
	printf("%d", GetHeight(t));
	GetWidth(t, 1);
	printf("\n%d", WIDTH);
	printf("\n删之前\n");
	PrintPre(t);
	//DeleteLeaf(t);
	printf("\n删除之后\n");
	PrintPre(t);
	printf("\n该节点所在层次为：%d\n", GetpLevel(t,4));
	printf("%d",GetMax(t));
	PrintDataAndLevel(t,1);
}