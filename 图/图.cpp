#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct LNode {//��ʽ���
	int data;
	LNode* next;
}LNode;
typedef struct LQueue {//���У�������ͷβָ�룬�м����һ������ʵ�֣�ͷβֻ������ָ�롣
	LNode* front, * rear;
	//���������ҪƵ�����ʣ�������һ��length
	int length;
}LQueue;
//��ʼ��
bool InitLQueue(LQueue& q) {
	//�������Ϊͷβ����ָ��ָ��ͬһ�����
	//������ʽ�ڵ㣬��ʵ����������ѣ���������ͷβָ�룬���¶���Ϊһ���ṹ���Ϊ��ʽ����
	q.front = q.rear = (LNode*)malloc(sizeof(LNode));
	q.rear->next = q.front;//frontΪͷ��㣬ʹ����һ��ָ��NULL
	return true;
}
//�п�
bool IsEmpty(LQueue& q) {
	return q.front == q.rear;
}
//����
bool IsOverFlow(LQueue& q) {
	return q.rear->next == q.front;
}
//���
bool EnQueue(LQueue& q, int x) {
	if (IsOverFlow(q)) {//���Ϊ������Ϊ������
		//û�о�����һ���½ڵ㣬��x������ǰ��rear,�����������LNode���ӵ�rear���棬����rear���ƣ�
	//��Ҫ�ճ�һ���ڵ㣻
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		s->next = q.rear->next;
		q.rear->next = s;
		q.rear = s;
		return true;
	}
	//��ʼ��Ϊ����
		//���rear�����пյĽڵ��ֱ�Ӹ�ֵ���ƾ���
	//��ͷ���ʱ��rearָ��������һ��Ԫ�أ�����rear������һ���ڽ��и�ֵ
	q.rear = q.rear->next;
	q.rear->data = x;

	return true;
}
//����
bool DeLQueue(LQueue& q, int& x) {
	if (IsEmpty(q)) { return false; }//����Ϊ��
	//ͷ���ָ�����
	LNode* p = q.front->next;
	if (q.front->next == q.rear) {
		q.rear = q.front;
	}
	q.front->next = p->next;
	//�ҵ�rear����
	p->next = q.rear->next;
	q.rear->next = p;
	return true;
}
constexpr auto MAXSIZE = 100;
//�ڽӾ���
typedef struct MGraph {
	int edge[MAXSIZE][MAXSIZE];     //�ڽӾ�����߱�,��int�Ͳ������Դ�Ȩ
	char vex[MAXSIZE];              //�����ַ���
	int vexnum,arcnum;              //ͼ�����нڵ���,����
	bool IsToWards;                 //�Ƿ�Ϊ����ͼ������ͼ true������ͼ
};
//��ʼ���ڽӾ���
void InitMGraph(MGraph &m) {
	m.arcnum = 0; 
	m.vexnum =  0 ;
	memset(m.edge, 0, sizeof(m.edge));//ȫ����ʼ��Ϊ0
}
//���Ҷ���x��һ�������ӵ���һ���ڵ㣬���������±꣨�ڽӾ���
int FirstNeighborMG(MGraph m, int x) {//����xΪҪ��Ķ����λ���±�
	for (int i = 0; i < m.vexnum; i++)
	{
		if (m.edge[x][i] == 1) {
			return i;
		}
	}
	return -1;
}
//���ҵ�ǰ�������һ���ߣ��ڽӾ���
int NextNeighborMG(MGraph m, int x, int y) {
	for (int i = y; i < m.vexnum; i++)
	{
		if (m.edge[x][i] == 1) {
			return i;
		}
	}
	return -1;
}
//�ڽ�����ڵ�
typedef struct ArcNode {
	int adjvex;          //��ָ��Ķ����ڶ�����е�λ��
	int arclong;          //Ȩֵ
	ArcNode* nextarc;    //��һ���ߵ�ָ��
}ArcNode;
//�ڽӶ����ڵ�
typedef struct VNode {
	char vexNode;    //������Ϣ
	ArcNode* Firstarc;//��һ���ߵ�ָ��
}VNode,AdjList[MAXSIZE];//�����Ϊ����
//�ڽӱ�
typedef struct ALGraph {
	AdjList vertices;   //�����
	int vexnum, arcnum; //�ڵ���,����
	bool IsToWards;     //�Ƿ�Ϊ����ͼ������ͼ true������ͼ
}ALGraph;
//�ڽӱ��ʼ��
void InitALGraph(ALGraph &al,bool istowards) {
	al.arcnum = 0;
	al.vexnum = 0;
	al.IsToWards = istowards;
	memset(al.vertices, 0, sizeof(al.vertices));
}
//�ڽӱ�鵱ǰ��һ�������ŵĶ���
int FirstNeighborAL(ALGraph al, VNode x) {
	ArcNode* p = x.Firstarc;
	if (p) {
		return p->adjvex;
	}
	return -1;
}
//�ڽӱ�鵱ǰ��һ�������ŵĶ���
int NextNeighborAL(ALGraph al, VNode x, ArcNode* y) {
	ArcNode* p = y->nextarc;
	if (p) {
		return p->adjvex;
	}
	return -1;
}
//�ڽӱ�ת�ڽӾ���
bool ALGraphToMGraph(ALGraph al,MGraph &m) {
	InitMGraph(m);
	m.IsToWards = al.IsToWards;//�ڽӱ�
	for (int i = 0; i <al.vexnum; i++)
	{
		//���ڽӱ��ж����ĵ�i���������ݣ���ֵ���ڽӾ����ж����ĵ�i��
		m.vex[i] = al.vertices[i].vexNode;
		//����һ��p�ڵ���������ǰ��i���ڵ�ı߱�
		ArcNode* p = al.vertices[i].Firstarc;
		//�ڽӾ���ǰ�Ľڵ���+1
		m.vexnum++;
		//pΪ�����ʾ��ǰ����ı��Ѿ�ɨ���꣬������һ���������ѭ����
		while (p)
		{
			//iΪ��ǰ�ڵ㣬p->adjvex������߶�Ӧ����һ���ڵ�
			//���˴�˵����ǰ�����бߣ�ֻҪ��,i��p->adjvex��
			m.edge[i][p->adjvex] = 1;
			//����+1
			m.arcnum++;
			p = p->nextarc;
		}
	}
	//���������ͼ��ÿ���߱���������Ҫ/2������ͼ����
	if (!m.IsToWards) {//����ͼ��Ϊfalse
		m.arcnum /= 2;
	}
	return true;
}
//������ȱ���
//���ʼ�¼����
bool visited[MAXSIZE];
//��ʼ������
LQueue q; 
//���ʺ���
void visitMG(MGraph m,int i) {
	printf("%c",m.vex[i]);
}
//�ڽӾ���Ĺ������
void BFSMG(MGraph m, int i) {//iΪ��ĳ�����㿪ʼ
	visitMG(m, i);
	visited[i] = true;
	EnQueue(q, i);
	while (!IsEmpty(q)) {
		DeLQueue(q, i);
		for (int j = 0; j < m.vexnum; j++)
		{
			if (visited[i] == false && m.edge[i][j] != 0) {
				visitMG(m, j);
				visited[j] = true;
				EnQueue(q, j);
			}
		}
	}
}
void BFSTraverse(MGraph m) {
	for (int i = 0; i < m.vexnum; i++)
	{
		visited[i] = false;
	}
	InitLQueue(q);
	for (int i = 0; i < m.vexnum; i++)
	{
		if (!visited[i]) {
			BFSMG(m, i);
		}
	}
}
//�ڽӱ������ȱ���
void visitAL(ALGraph al, int i) {
	printf("%c", al.vertices[i].vexNode);
}
//�������
void BFSAL(ALGraph al, int i) {
	visitAL(al, i);
	visited[i] = true;
	EnQueue(q, i);
	while (!IsEmpty(q))
	{
		DeLQueue(q, i);
		for (ArcNode *p=al.vertices[i].Firstarc;p;p=p->nextarc)
		{
			int j = p->adjvex;
			if (visited[j] == false) {
				visitAL(al, j);
				visited[j] = true;
				EnQueue(q, j);
			}
		}
	}
}
//���forѭ��
void BFSALTraverse(ALGraph al) {
	for (int i = 0; i < al.vexnum; i++)
	{
		visited[i] = false;
	}
	InitLQueue(q);
	for (int i = 0; i < al.vexnum; i++)
	{
		if (!visited[i]) {
			BFSAL(al, i);
		}
	}
}
//������ȱ���
void DFSAL(ALGraph al, int i) {
	visitAL(al, i);
	visited[i] = true;
	for (ArcNode *p=al.vertices[i].Firstarc;p;p=p->nextarc)
	{
		int j = p->adjvex;
		if (!visited[j]) {
			DFSAL(al, j);
		}
	}
}
void DFSMG(MGraph m, int i) {
	visitMG(m, i);
	visited[i] = true;
	for (int j = 0; j < m.vexnum; j++)
	{
		if (!visited[j] && m.edge[i][j] != 0)
		{
			DFSMG(m, j);
		}
	}
}
//���
void DFSTraverse(MGraph m) {
	for (int i = 0; i < m.vexnum; i++)
	{
		visited[i] = false;
	}
	for (int i = 0; i <m.vexnum; i++)
	{
		if (!visited[i])
			DFSMG(m, i);
	}
}
//���
void DFSALTraverse(ALGraph al) {
	for (int i = 0; i < al.vexnum; i++)
	{
		visited[i] = false;
	}
	for (int i = 0; i < al.vexnum; i++)
	{
		if (!visited[i])
			DFSAL(al, i);
	}
}

//����
// 
//�ж�һ������ͼ�Ƿ�Ϊһ��������һ�����Ļ���n-1����
void DFS(MGraph g, int i, int& Vnum, int& Enum) {
	visited[i] = true; Vnum++;
	int j = FirstNeighborMG(g, i);
	while (j != -1)
	{
		Enum++;
		if (!visited[j]) {
			DFS(g, j, Vnum, Enum);
		}

		j = NextNeighborMG(g, i, j);
	}
}
//�ж�һ������ͼ�Ƿ�Ϊһ��������һ�����Ļ���n-1����
bool IsTree(MGraph g) {
	for (int i = 0; i < g.vexnum; i++)
	{
		visited[i] = false;
	}
	int Vnum = 0, Enum = 0;
	DFS(g, 1, Vnum, Enum);
	if (Vnum == g.vexnum && Enum == 2 * (g.vexnum - 1)) {
		return true;
	}
	else {
		return false;
	}
}

//����Ƿ��д�i��j��·��
bool CanSearch = false;
void DFSiToj(MGraph g, int i, int j, bool CanSearch) {
	if (i == j) {
		CanSearch = true;
		return;
	}
	visited[i] = true;
	for (int j = FirstNeighborMG(g, i); j != -1; j = NextNeighborMG(g, i, j))
	{
		if (!visited[j] && !CanSearch) {
			DFSiToj(g, j, i, CanSearch);
		}
	}
}
//ͼ��Ӧ��
//1.BFS�������·��
int d[MAXSIZE];
int path[MAXSIZE];
void EFSGetShortest(MGraph G, int u) {//uΪ��ʼ�Ľڵ�
	//׼������
	LQueue q;
	InitLQueue(q);
	for (int i = 0; i < G.vexnum; i++)
	{
		d[i] = INT_MAX; path[i] = -1;
		visited[i] = false;
	}
	d[u] = 0;
	visited[u] = true;
	EnQueue(q, u);
	while (!IsEmpty(q)) {
		DeLQueue(q, u);
		for (int i = FirstNeighborMG(G, u);i!=-1;i=NextNeighborMG(G,u,i))
		{
			if (!visited[i]) {
				d[i] = d[u] + 1;//·����һ
				path[i] =u;//�����Դ
				visited[i] = true;
				EnQueue(q, i);
			}
		}
	}
}
//�Ͻ�˹����
// final[];dist[];path[];
//��������
int Fpath[MAXSIZE][MAXSIZE];
void Floye(MGraph G) {
	for (int k = 0; k < G.vexnum; k++)//ÿ���ڵ�����һ�Σ��ۼӣ�
	{
		for (int i = 0; i < G.vexnum; i++)//���i��
		{
			for (int j = 0; j < G.vexnum; j++)//���j��
			{
				if (G.edge[i][j] > G.edge[i][k] + G.edge[k][j]) {//˵��������kʱ�и�����·��
					G.edge[i][j] = G.edge[i][k] + G.edge[k][j];//����
					Fpath[i][j] = k;//��¼��ת�ڵ�
				}
			}
		}
	}
}
//�����޻�ͼDGA�������ʽ
//���ǰ������������ʽ���������Ż����������ͬ������������Ժϲ�Ϊһ����

//��������AOV��(һ���������޻�ͼDAG�����������ˣ����ǰ������ִ��ѡ��˳���ţ�
int print[MAXSIZE];//��¼������˳��Ľڵ�����
int degree[MAXSIZE];//��¼����ĸ���������������
int s[MAXSIZE];//ģ��ջ
bool ToPuSort(ALGraph al) {
	int top = -1; 
	int i;
	for (i = 0; i < al.vexnum; i++)
	{
		//�������Ϊ0�ĵ㣬ȫ����ջ
		if (degree[i] == 0) {
			s[++top] = i;
		}
	}
	//���ڱ�ǽڵ����
		int count = 0;
	//ջ���գ����ڶ�Ϊ0�ĵ㣩��һֱѭ��
		while (top!=-1)
		{
			//��ջ
			i = s[top--];
			//�������¼����˳��
			print[count++] = i;
			//����ջ�ڵ�ָ��ڵ����ȼ�һ��˳�������Ϊ0��������ջ
			for (ArcNode *w =al.vertices[i].Firstarc; w ; w=w->nextarc)
			{
				int j = w->adjvex;
				//˳�������Ϊ0��������ջ
				if (!--degree[j]) {
					s[++top] = j;
				}
			}
		}//while
		//countС�ڽڵ���˵���л�·������ʧ��
		if (count < al.vexnum)return false;
		else return true;
}
//����������(����Ϊ0��
//print[]��¼������˳��
//degree��¼������
bool ReverseTopoSort(MGraph G) {
	int top = -1, i = 0;
	for (int i = 0; i < G.vexnum; i++)
	{
		if (degree[i] == 0) {
			s[++top] = i;
		}
	}
	int count = 0;
	while (top!=-1)
	{
		i = s[top--];
		print[count++] = i;
		for (int j = 0; j < G.vexnum; j++)
		{
			if (G.edge[j][i] != 0 && !--degree[G.edge[j][i]]) { s[++top] = j; }
		}
	}
	if (count < G.vexnum)return false;
	else return true;
}
//��ȱ���ʵ��������
void DFSReverseTopoSort(ALGraph al, int i) {
	visited[i] = true;
	for (ArcNode* w = al.vertices[i].Firstarc; w; w = w->nextarc)
	{
		if (!visited[w->adjvex]) {
			DFSReverseTopoSort(al, w->adjvex);
		}
	}
	//���������һ������β�����
	visitAL(al, i);
}
void DFSTreaver(ALGraph al) {
	for (int i = 0; i < al.vexnum; i++)
	{
		visited[i] = false;
	}
	for (int i = 0; i < al.vexnum; i++)
	{
		if (!visited[i]) {
			DFSReverseTopoSort(al, i);
		}
	}
}

//DFSʵ������
int finaltime[MAXSIZE];
int time;
void DFSTopoSort(ALGraph al, int i) {
	visited[i] = true;
	for (ArcNode* w = al.vertices[i].Firstarc; w; w = w->nextarc)
	{
		if (!visited[w->adjvex]) {
			DFSTopoSort(al, w->adjvex);
		}
	}
	finaltime[i] = ++time;
}
void DFSTopoSortTreaver(ALGraph al) {
	for (int i = 0; i < al.vexnum; ++i)
	{
		visited[i] = false;
	}
	time = 0;
	for (int i = 0; i < al.vexnum; ++i)
	{
		if (!visited[i]) {
			DFSTopoSort(al, i);
		}
	}
}

int main() {
	ALGraph al;
	InitALGraph(al, false);
	al.vertices[0].vexNode = 'a';
	ArcNode a1{};
	ArcNode a2{};
	ArcNode a3{};
	a3.adjvex = 3;
	a3.nextarc = NULL;
	a2.adjvex = 2;
	a2.nextarc = &a3;
	a1.adjvex = 1;
	a1.nextarc = &a2;
	al.vertices[0].Firstarc = &a1;

	al.vertices[1].vexNode = 'b';
	ArcNode b1{};
	b1.adjvex = 0;
	b1.nextarc = NULL;
	al.vertices[1].Firstarc = &b1;

	al.vertices[2].vexNode = 'c';
	ArcNode c1{};
	ArcNode c2{};
	c2.adjvex = 3;
	c2.nextarc = NULL;
	c1.adjvex = 0;
	c1.nextarc = &c2;
	al.vertices[2].Firstarc = &c1;

	al.vertices[3].vexNode = 'd';
	ArcNode d1{};
	ArcNode d2{};
	d2.adjvex = 2;
	d2.nextarc = NULL;
	d1.adjvex = 0;
	d1.nextarc = &d2;
	al.vertices[3].Firstarc = &d1;
	al.vertices[4].vexNode = 'e';
	al.vertices[5].vexNode = 'f';
	al.vertices[6].vexNode = 'g';

	al.arcnum = 7;
	al.vexnum = 7;
	MGraph m;
	ALGraphToMGraph(al, m);

	for (int i = 0; i < m.vexnum; i++)
	{
		printf("[");
		for (int j = 0; j < m.vexnum; j++)
		{
			printf(" %d ", m.edge[i][j]);
		}
		printf("]\n");
	}
	printf("��%d\n", m.vexnum);
	printf("��%d\n", m.arcnum);
	printf("����ڽӾ���:\n");
	BFSTraverse(m);
	printf("\n");
	printf("����ڽӱ�:\n");
	BFSALTraverse(al);
	printf("\n");
	printf("����ڽӾ���:\n");
	DFSTraverse(m);
	printf("\n");
	printf("����ڽӱ�:\n");
	DFSALTraverse(al);
	printf("\n");

	printf("----------------");
	ALGraph tal;
	InitALGraph(tal, true);
	for (int i = 0; i < 6; i++)
	{
		tal.vertices[i].vexNode = i+1 ;
	}
	tal.arcnum = 6;
	tal.vexnum = 6;

	ArcNode av2;
	av2.adjvex = 2;
	av2.nextarc = NULL;
	ArcNode av1;
	av1.adjvex = 1;
	av1.nextarc = &av2;
	tal.vertices[0].Firstarc = &av1;

	ArcNode bv2;
	bv2.adjvex = 3;
	bv2.nextarc = NULL;
	ArcNode bv1;
	bv1.adjvex = 2;
	bv1.nextarc = &bv2;
	tal.vertices[1].Firstarc = &bv1;
	
	ArcNode cv1;
	cv1.adjvex = 4;
	cv1.nextarc = NULL;
	tal.vertices[2].Firstarc = &cv1;

	ArcNode dv1;
	dv1.adjvex = 5;
	dv1.nextarc = NULL;
	tal.vertices[3].Firstarc = &dv1;

	ArcNode ev1;
	ev1.adjvex = 5;
	ev1.nextarc = NULL;
	tal.vertices[4].Firstarc = &ev1;

	DFSTopoSortTreaver(tal); printf("\nfinaltime:");
	for (int i = 0; i < tal.vexnum; i++)
	{
		printf("\n%d:[%d]", i, finaltime[i]);
	}
}                                         