#include<iostream>
using namespace std;
int visited[20];        // 访问标志

// 邻接表
typedef struct ArcNode {
    int adjvex;                 //邻接点域
    struct ArcNode * nextarc;  //指向下一个邻接点的指针域
};

// 表头节点
typedef struct VNode {
    int data;               //顶点信息
    ArcNode *firstarc;      //指向第一条依附该顶点的弧的指针
}VNode, AdjList[20];

// 图
typedef struct {
    AdjList vertices;       // 一张图的所有节点
    int vexnum, arcnum;     // 节点数,边数
}ALGraph;

// 生成树边集
typedef struct {
    int start;
    int end;
}Arc;

// 队列,用来实现广度优先遍历
typedef struct QNode{
    int data;               // 数据
    struct QNode* next;     // 指向队列中下一个元素
}QNode, *QuePtr;

typedef  struct {
    QuePtr front;       // 队头
    QuePtr rear;        // 队尾
}LinkQue;

Arc BSet[20];               // 广度优先搜索生成的边的边集
Arc DSet[20];               // 深度优先搜索生成的边的边集
int b = 0;                  // 广度优先搜索边集的index
int d = 0;                  // 深度优先搜索边集的index

/**
 * 创建无向图
 * @param G 图
 */
void createGraph(ALGraph &G){
    cout<<"请输入图的顶点的个数。"<<endl;
    cin>>G.vexnum;
    cout<<"请输入图的边的个数。"<<endl;
    cin>>G.arcnum;
    cout<<"请输入顶点的信息。"<<endl;
    for (int i = 0; i<G.vexnum; i++){
        cin>>G.vertices[i].data;
        G.vertices[i].firstarc = NULL;
    }
    cout<<"请输入边的信息:"<<endl;

    int a, b;                           // 每一条边的两个节点
    for (int j = 0; j<G.arcnum; j++){
        cin>>a>>b;                      // 输入一条边的两个节点
        ArcNode* s = (ArcNode*)malloc(sizeof(ArcNode)); // 为节点开辟空间
        s->adjvex = a;
        s->nextarc = G.vertices[b].firstarc;
        G.vertices[b].firstarc = s;             // 边的第一个节点赋为a
        s = (ArcNode*)malloc(sizeof(ArcNode));
        s->adjvex = b;
        s->nextarc = G.vertices[a].firstarc;
        G.vertices[a].firstarc = s;             // 边的第二个节点赋为b
    }
    cout<<"邻接表创建完成。"<<endl;
}

/**
 * 深度优先遍历
 * @param G 图
 * @param i 遍历开始节点位置
 */
void DFS(ALGraph G, int i){
    //以i为开始开始遍历
    cout<<i<<" ";
    ArcNode *p;
    visited[i] = 1;                 //0为假，1为真
    p = G.vertices[i].firstarc;

    // 循环遍历,如果该节点没有被访问过,将从该节点向下进行深度优先遍历
    while (p){
        if (!visited[p->adjvex]){
            DSet[d].start = i;          // 设置边的两个节点
            DSet[d].end = p->adjvex;
            d++;                        // 访问下一个节点,节点下标自增
            DFS(G, p->adjvex);          // 从该节点开始继续进行深度优先遍历
        }
        p = p->nextarc;                 // 节点已经被访问过,找下一个没有被访问过的节点
    }
}

/**
 * 调用深度优先遍历
 * @param G 图
 */
void DFSTraverse(ALGraph G){
    int j, i;       // i 循环控制变量; j 深度优先遍历的开始节点
    cout<<"请输入从哪个点开始进行深度优先搜索。"<<endl;
    cin>>j;
    cout<<"深度优先搜索遍历顺序为："<<endl;

    // 将所有节点的访问标志重置
    for (i = 0; i<G.vexnum; i++){
        visited[i] = 0;
    }

    // 从开始节点开始,没有被访问过就调用深度优先遍历
    for (i = j; i<G.vexnum; i++){
        if (!visited[i]){
            DFS(G, i);
        }
    }

    // 由于上一次的遍历还没有访问过 0--j 之间的节点,所以还要将他们进行遍历
    for (i = 0; i<j; i++){
        if (!visited[i]){
            DFS(G, i);
        }
    }
    cout<<endl;
}

/**
 * 打印深度优先生成树
 * @param G 图
 */
void PrintDFTree(ALGraph G){
    int i = 0;
    cout<<"深度生成树的边集为：";

    // 从头开始,输出深度优先生成树边集.输出方式是打印开始节点和结束节点
    for (; i < G.vexnum - 1; i++){
        cout<<"("<<DSet[i].start<<","<<DSet[i].end<<")";
    }
    cout<<endl;
}

/**
 * 初始化队列,用来实现广度优先遍历
 * @param Q 队列
 * @return
 */
int Init(LinkQue &Q){
    Q.front = Q.rear = (QuePtr)malloc(sizeof(QNode));   // 为队头队尾开辟空间
    if (!Q.front)
        return -1;
    Q.front->next = NULL;               //不要忘了把头结点的next手动定义为null
    return 0;
}

/**
 * 进队
 * @param Q 队列
 * @param e 进队元素
 * @return
 */
int enQue(LinkQue &Q, int e){
    QNode *p = (QNode*)malloc(sizeof(QNode));   // 为进队元素开辟一段空间
    if (!p)
        return -1;

    // 将元素的信息都赋给队列的节点
    p->data = e;
    p->next = NULL;     // 该节点的下一个节点为空
    Q.rear->next = p;   // 将节点插入到队尾
    Q.rear = p;
    return 0;
}

/**
 * 出队
 * @param Q
 * @param e
 * @return
 */
int deQue(LinkQue &Q, int &e){
    // 队列为空
    if (Q.front == Q.rear){
        cout<<"队列为空"<<endl;
        return -1;
    }

    QNode* p = Q.front->next;           //Q.front 是一个没有存放任何东西的头结点
    e = p->data;
    Q.front->next = p->next;            // 没有节点指向p节点,p也就相当于从队列中删除出去

    //队列中只有一个元素的情况 先把rear挪到前面来 要不然删的话把rear也一起删掉了
    if (Q.rear == p)
        Q.rear = Q.front;

    free(p);            // 释放掉删除节点的空间
    return 0;
}

/**
 * 广度优先遍历
 * @param G 图
 * @param i 从第i的节点开始遍历
 */
void BFS(ALGraph G, int i) {
    cout<<i<<" ";           // 从i开始遍历
    visited[i] = 1;         // 节点已经访问过

    LinkQue Q;              // 队列
    Init(Q);                // 初始化队列
    enQue(Q, i);            // 将遍历的节点插入队列
    deQue(Q, i);            // 由于是开始节点,直接出队

    ArcNode *p = G.vertices[i].firstarc;    // 然后找当前节点的下一个邻接点

    // 找到邻接点
    while (p){

        // 如果邻接点没有被访问过,输出邻接点
        if (!visited[p->adjvex]){
            cout<<p->adjvex<<" ";
            visited[p->adjvex] = 1;
            enQue(Q, p->adjvex);        // 节点进队
            BSet[b].start = i;
            BSet[b].end = p->adjvex;
            b++;
        }
        p = p->nextarc;                 // 被访问过,继续找下一个邻接点
    }
}


/**
 * 调用广度优先遍历
 * @param G 图
 */
void BFSTraverse(ALGraph G){
    int i, j;       // i:循环控制变量; j:从节点j开始遍历
    cout<<"请输入从哪个点开始进行广度优先搜索。"<<endl;
    cin>>j;
    cout<<"广度优先搜索遍历顺序为："<<endl;

    // 将所有节点的访问标志重置
    for (i = 0; i<G.vexnum; i++){
        visited[i] = 0;
    }

    // 从j开始,如果没有被访问过就进行广度优先遍历
    for (i = j; i<G.vexnum; i++){
        if (!visited[i]){
            BFS(G, i);
        }
    }
    for (i = 0; i<j; i++){
        if (!visited[i]){
            BFS(G, i);
        }
    }
    cout<<endl;
}

/**
 * 打印广度优先生成树
 * @param G 图
 */
void PrintBFTree(ALGraph G){
    int i = 0;
    cout<<"广度生成树的边集为："<<endl;

    // 打印广度优先生成树边集,以开始节点和结束节点的形式
    for (; i < G.vexnum - 1; i++){
        cout<<"("<<BSet[i].start<<","<<BSet[i].end<<")";
    }
    cout<<endl;
}

/**
 * 测试主函数
 * @return
 */
int main() {
    ALGraph G;          // 无向图
    createGraph(G);     // 初始化创建图
    DFSTraverse(G);     // 开始调用深度优先遍历
    PrintDFTree(G);     // 打印深度优先生成树
    BFSTraverse(G);     // 开始调用广度优先遍历
    PrintBFTree(G);     // 打印广度优先生成树
    return 0;
}