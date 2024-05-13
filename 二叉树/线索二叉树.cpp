#include<stdio.h>
#include<malloc.h>
/*
//������ 
typedef struct BiNode {
	int data;
	BiNode* lChild, * rChild;
}BiNode, * BiTree;
//���������� 
typedef struct ThreadNode {
	int data;
	ThreadNode* lChild, * rChild;
	int lTag, rTag;
}ThreadNode, * ThreadTree;
//����ʼ��
bool InitTree(ThreadTree& t) {
	t = (ThreadNode*)malloc(sizeof(ThreadNode));
	t->data = 1;
	t->lChild = NULL;
	t->lTag = 0;
	t->rChild = NULL;
	t->rTag = 0;
	return true;
}
//ָ���ڵ��������
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
//ָ���ڵ�����Һ���
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
//ǰ��������������ʵ��
void FrontThread(ThreadTree t, ThreadTree& pre) {
	if (t == NULL) {
		return;
	}
	// �������߼� 
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
	//�����߼� 
	if (t->lTag == 0) {
		FrontThread(t->lChild, pre);
	}

	FrontThread(t->rChild, pre);
}
//ǰ��������
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
//����������������ʵ��
void MiddleThread(ThreadTree t, ThreadTree& pre) {
	if (t == NULL) {
		return;
	}
	//�����߼� 
	MiddleThread(t->lChild, pre);
	// �������߼� 
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
	//�����߼� 
	MiddleThread(t->rChild, pre);
}
//����������
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
//����������������ʵ��
void FinalThread(ThreadTree t, ThreadTree& pre) {
	if (t == NULL) {
		return;
	}
	//�����߼� 
	FinalThread(t->lChild, pre);
	FinalThread(t->rChild, pre);
	// �������߼� 
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
//����������
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
//ǰ�����
bool FrontPrint(ThreadTree t) {
	if (t != NULL) {
		printf("%d", t->data);
		FrontPrint(t->lChild);
		FrontPrint(t->rChild);
	}
	return true;
}
//�������
bool MiddlePrint(ThreadTree t) {
	if (t != NULL) {
		MiddlePrint(t->lChild);
		printf("%d", t->data);
		MiddlePrint(t->rChild);
	}
	return true;
}
//�������
bool FinalPrint(ThreadTree t) {
	if (t != NULL) {
		FinalPrint(t->lChild);
		FinalPrint(t->rChild);
		printf("%d", t->data);
	}
	return true;
}
//����ǵݹ����,������δ�������Ķ�����
bool PostOrder(ThreadTree t) {
	ThreadNode* p = t, * r = NULL;
	ThreadNode* stack[100] = {};
	int top = -1;//������ģ��ջ
	while (p||top!=-1)
	{
		if (p) {                          //p��Ϊ����
			stack[++top] = p;       //������ջ
			p = p->lChild;                //��p�������ƶ�
		}
		else {                                  //pΪ��ʱ˵������û�ˣ����߸ս�Ԫ�س���ջ
			p = stack[top];                     //����ֻ���ʣ�����վ����Ϊ���ܻ����ҽڵ�û�б�����
			if (p->rChild && p->rChild != r) {  //p�Һ��Ӳ�Ϊ���Ҳ����ڸճ�վ��Ԫ�أ�����r��Ϊ�˸ձ�ǳ�ջ���Һ���
				p = p->rChild;                  //û�б��������ҽڵ����´�ѭ��ʱ�����ջ��
			}
			else {             //�ߵ�����˵��p�Ѿ�û�����Ӻ��Һ����ˣ����������ж���û����û�������ж��ң��ߵ�����ֻ�������Ҷ�û���ˣ�����p�������֧�������½ڵ㣬���Է��ĳ�ջ
				p = stack[top--];//��ջ
				printf("%d", p->data);//���ʲ���
				r = p;     //��¼��ǰ��ջ�Ľڵ㣬�´η���ջ����Ԫ�����丸�ڵ㣬��r��ǾͲ����ٴα�����
				p = NULL;   //��ջ�꣬��p��Ϊ�գ������´η���ջ��Ԫ��
			}
		}//else
	}//while
	return true;
}


int main() {
	ThreadTree t;
	InitTree(t);
	AddlChild(t, 2);
	AddlChild(t->lChild, 4);
	AddrChild(t->lChild, 5);
	AddrChild(t, 3);
	AddlChild(t->rChild, 6);
	AddrChild(t->rChild, 7);
	printf("%--------ǰ��--------\n");
	//FrontPrint(t);
	//printf("\n");
	//CreateFrontThread(t);
	printf("%--------����--------\n");
	//MiddlePrint(t);
	//printf("\n");
	//CreateMiddleThread(t);
	printf("%--------����--------\n");
	//FinalPrint(t);
	//printf("\n");
	//CreateFinalThread(t);
	PostOrder(t);
	return 0;
 }
*/
