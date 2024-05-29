#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct LNode {//链式结点
	int data;
	LNode* next;
}LNode;
typedef struct LQueue {//队列，就是用头尾指针，中间包着一个链表实现；头尾只是两个指针。
	LNode* front, * rear;
	//如果长度需要频繁访问，不妨加一个length
	int length;
}LQueue;
//初始化
bool InitLQueue(LQueue& q) {
	//可以理解为头尾两个指针指向同一个结点
	//申请链式节点，其实还是链表而已，加了两个头尾指针，重新定义为一个结构体称为链式队列
	q.front = q.rear = (LNode*)malloc(sizeof(LNode));
	q.rear->next = q.front;//front为头结点，使其下一个指向NULL
	return true;
}
//判空
bool IsEmpty(LQueue& q) {
	return q.front == q.rear;
}
//判满
bool IsOverFlow(LQueue& q) {
	return q.rear->next == q.front;
}
//入队
bool EnQueue(LQueue& q, int x) {
	if (IsOverFlow(q)) {//如果为空则认为是满的
		//没有就申请一个新节点，将x赋给当前的rear,并将新申请的LNode链接到rear后面，并将rear后移；
	//需要空出一个节点；
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		s->next = q.rear->next;
		q.rear->next = s;
		q.rear = s;
		return true;
	}
	//初始视为不满
		//如果rear后面有空的节点就直接赋值后移就行
	//有头结点时，rear指向的是最后一个元素，先让rear向后遍历一个在进行赋值
	q.rear = q.rear->next;
	q.rear->data = x;

	return true;
}
//出队
bool DeLQueue(LQueue& q, int& x) {
	if (IsEmpty(q)) { return false; }//队列为空
	//头结点指向后移
	LNode* p = q.front->next;
	if (q.front->next == q.rear) {
		q.rear = q.front;
	}
	q.front->next = p->next;
	//挂到rear后面
	p->next = q.rear->next;
	q.rear->next = p;
	return true;
}
constexpr auto MAXSIZE = 100;
//邻接矩阵
typedef struct MGraph {
	int edge[MAXSIZE][MAXSIZE];     //邻接矩阵表，边表,用int型参数可以带权
	char vex[MAXSIZE];              //顶点字符表
	int vexnum,arcnum;              //图中现有节点数,边数
	bool IsToWards;                 //是否为有向图或无向图 true则有向图
};
//初始化邻接矩阵
void InitMGraph(MGraph &m) {
	m.arcnum = 0; 
	m.vexnum =  0 ;
	memset(m.edge, 0, sizeof(m.edge));//全部初始化为0
}
//查找顶点x第一个边连接的另一个节点，返回数组下标（邻接矩阵）
int FirstNeighborMG(MGraph m, int x) {//传入x为要查的顶点的位置下标
	for (int i = 0; i < m.vexnum; i++)
	{
		if (m.edge[x][i] == 1) {
			return i;
		}
	}
	return -1;
}
//查找当前顶点的下一个边（邻接矩阵）
int NextNeighborMG(MGraph m, int x, int y) {
	for (int i = y; i < m.vexnum; i++)
	{
		if (m.edge[x][i] == 1) {
			return i;
		}
	}
	return -1;
}
//邻接链表节点
typedef struct ArcNode {
	int adjvex;          //边指向的顶点在顶点表中的位置
	int arclong;          //权值
	ArcNode* nextarc;    //下一个边的指针
}ArcNode;
//邻接顶点表节点
typedef struct VNode {
	char vexNode;    //顶点信息
	ArcNode* Firstarc;//第一个边的指针
}VNode,AdjList[MAXSIZE];//起别名为数组
//邻接表
typedef struct ALGraph {
	AdjList vertices;   //顶点表
	int vexnum, arcnum; //节点数,边数
	bool IsToWards;     //是否为有向图或无向图 true则有向图
}ALGraph;
//邻接表初始化
void InitALGraph(ALGraph &al,bool istowards) {
	al.arcnum = 0;
	al.vexnum = 0;
	al.IsToWards = istowards;
	memset(al.vertices, 0, sizeof(al.vertices));
}
//邻接表查当前第一个边连着的顶点
int FirstNeighborAL(ALGraph al, VNode x) {
	ArcNode* p = x.Firstarc;
	if (p) {
		return p->adjvex;
	}
	return -1;
}
//邻接表查当前下一个边连着的顶点
int NextNeighborAL(ALGraph al, VNode x, ArcNode* y) {
	ArcNode* p = y->nextarc;
	if (p) {
		return p->adjvex;
	}
	return -1;
}
//邻接表转邻接矩阵
bool ALGraphToMGraph(ALGraph al,MGraph &m) {
	InitMGraph(m);
	m.IsToWards = al.IsToWards;//邻接表
	for (int i = 0; i <al.vexnum; i++)
	{
		//将邻接表中顶点表的第i个顶点内容，赋值给邻接矩阵中顶点表的第i个
		m.vex[i] = al.vertices[i].vexNode;
		//建立一个p节点来遍历当前第i个节点的边表
		ArcNode* p = al.vertices[i].Firstarc;
		//邻接矩阵当前的节点数+1
		m.vexnum++;
		//p为空则表示当前顶点的边已经扫描完，进入下一个顶点进行循环。
		while (p)
		{
			//i为当前节点，p->adjvex是这个边对应的另一个节点
			//到此处说明当前顶点有边，只要将,i行p->adjvex列
			m.edge[i][p->adjvex] = 1;
			//边数+1
			m.arcnum++;
			p = p->nextarc;
		}
	}
	//如果是无向图，每个边被算了两次要/2，有向图则不用
	if (!m.IsToWards) {//无向图则为false
		m.arcnum /= 2;
	}
	return true;
}
//广度优先遍历
//访问记录数组
bool visited[MAXSIZE];
//初始化队列
LQueue q; 
//访问函数
void visitMG(MGraph m,int i) {
	printf("%c",m.vex[i]);
}
//邻接矩阵的广度优先
void BFSMG(MGraph m, int i) {//i为从某个顶点开始
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
//邻接表广度优先遍历
void visitAL(ALGraph al, int i) {
	printf("%c", al.vertices[i].vexNode);
}
//具体遍历
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
//外层for循环
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
//深度优先遍历
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
//深度
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
//深度
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

//大题
// 
//判断一个无向图是否为一棵树，是一棵树的话有n-1个边
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
//判断一个无向图是否为一棵树，是一棵树的话有n-1个边
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

//检查是否有从i到j的路径
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
//图的应用
//1.BFS方法最短路径
int d[MAXSIZE];
int path[MAXSIZE];
void EFSGetShortest(MGraph G, int u) {//u为开始的节点
	//准备工作
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
				d[i] = d[u] + 1;//路径加一
				path[i] =u;//标记来源
				visited[i] = true;
				EnQueue(q, i);
			}
		}
	}
}
//迪杰斯特拉
// final[];dist[];path[];
//弗洛伊德
int Fpath[MAXSIZE][MAXSIZE];
void Floye(MGraph G) {
	for (int k = 0; k < G.vexnum; k++)//每个节点允许一次（累加）
	{
		for (int i = 0; i < G.vexnum; i++)//检查i行
		{
			for (int j = 0; j < G.vexnum; j++)//检查j列
			{
				if (G.edge[i][j] > G.edge[i][k] + G.edge[k][j]) {//说明允许经过k时有更近的路径
					G.edge[i][j] = G.edge[i][k] + G.edge[k][j];//更新
					Fpath[i][j] = k;//记录中转节点
				}
			}
		}
	}
}
//有向无环图DGA描述表达式
//就是把描述算术表达式的树进行优化，如果有相同的子树，则可以合并为一个；

//拓扑排序AOV网(一定是有向无环图DAG，否则不能拓扑，就是按事情的执行选后顺序排）
int print[MAXSIZE];//记录按拓扑顺序的节点数组
int degree[MAXSIZE];//记录最初的各个顶点的入度数；
int s[MAXSIZE];//模拟栈
bool ToPuSort(ALGraph al) {
	int top = -1; 
	int i;
	for (i = 0; i < al.vexnum; i++)
	{
		//先找入度为0的点，全部入栈
		if (degree[i] == 0) {
			s[++top] = i;
		}
	}
	//用于标记节点个数
		int count = 0;
	//栈不空（存在度为0的点）就一直循环
		while (top!=-1)
		{
			//出栈
			i = s[top--];
			//用数组记录拓扑顺序
			print[count++] = i;
			//将出栈节点指向节点的入度减一，顺便检测如果为0，则将其入栈
			for (ArcNode *w =al.vertices[i].Firstarc; w ; w=w->nextarc)
			{
				int j = w->adjvex;
				//顺便检测如果为0，则将其入栈
				if (!--degree[j]) {
					s[++top] = j;
				}
			}
		}//while
		//count小于节点数说明有回路，拓扑失败
		if (count < al.vexnum)return false;
		else return true;
}
//逆拓扑排序(出度为0）
//print[]记录逆拓扑顺序
//degree记录出度数
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
//深度遍历实现逆拓扑
void DFSReverseTopoSort(ALGraph al, int i) {
	visited[i] = true;
	for (ArcNode* w = al.vertices[i].Firstarc; w; w = w->nextarc)
	{
		if (!visited[w->adjvex]) {
			DFSReverseTopoSort(al, w->adjvex);
		}
	}
	//跟后序遍历一样，在尾部输出
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

//DFS实现拓扑
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
	printf("点%d\n", m.vexnum);
	printf("边%d\n", m.arcnum);
	printf("广度邻接矩阵:\n");
	BFSTraverse(m);
	printf("\n");
	printf("广度邻接表:\n");
	BFSALTraverse(al);
	printf("\n");
	printf("深度邻接矩阵:\n");
	DFSTraverse(m);
	printf("\n");
	printf("深度邻接表:\n");
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