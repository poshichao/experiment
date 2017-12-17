// 迪杰斯特拉算法求最短路径
#include <iostream>
using namespace std;
#define MAX_VERtEX_NUM 20                   //顶点的最大个数
#define VRType int                          //表示弧的权值的类型
#define VertexType int                      //图中顶点的数据类型
#define INFINITY 65535
typedef struct {
    VertexType vexs[MAX_VERtEX_NUM];        //存储图中顶点数据
    VRType arcs[MAX_VERtEX_NUM][MAX_VERtEX_NUM];                         //二维数组，记录顶点之间的关系
    int vexnum,arcnum;                      //记录图的顶点数和弧（边）数
}MGraph;

typedef int PathMatrix[MAX_VERtEX_NUM];     //用于存储最短路径中经过的顶点的下标
typedef int ShortPathTable[MAX_VERtEX_NUM]; //用于存储各个最短路径的权值和

//根据顶点本身数据，判断出顶点在二维数组中的位置
int LocateVex(MGraph * G,VertexType v) {
    int i = 0;
    //遍历一维数组，找到变量v
    for (; i < G->vexnum; i++) {
        if (G->vexs[i] == v) {
            break;
        }
    }
    //如果找不到，输出提示语句，返回-1
    if (i > G->vexnum) {
        cout<<"no such vertex."<<endl;
        return -1;
    }
    return i;
}
//构造有向网
void CreateUDG(MGraph *G) {
	cout<<"输入节点数和边数："; 
    cin>>G->vexnum>>G->arcnum;
    cout<<"输入各节点："<<endl;
    for (int i = 0; i < G->vexnum; i++) {
        cin>>G->vexs[i];
    }
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            G->arcs[i][j] = INFINITY;
        }
    }
    
    cout<<"输入各边的起点和终点，以及相应权重："<<endl; 
    for (int i = 0; i < G->arcnum; i++) {
        int v1,v2,w;
        cin>>v1>>v2>>w;
        int n = LocateVex(G, v1);
        int m = LocateVex(G, v2);
        if (m == -1 || n == -1) {
            cout<<"no this vertex"<<endl;
            return;
        }
        G->arcs[n][m] = w;
    }
}

//迪杰斯特拉算法，v0表示有向网中起始点所在数组中的下标
void ShortestPath_Dijkstra(MGraph G, int v0, PathMatrix *p, ShortPathTable *D) {
    int final[MAX_VERtEX_NUM];//用于存储各顶点是否已经确定最短路径的数组
    
    //对各数组进行初始化
    for (int v = 0; v < G.vexnum; v++) {
        final[v] = 0;
        (*D)[v] = G.arcs[v0][v];
        (*p)[v] = 0;
    }
    
    //由于以v0位下标的顶点为起始点，所以不用再判断
    (*D)[v0] = 0;
    final[v0] = 1;
    int k = 0;
    for (int i = 0; i < G.vexnum; i++) {
        int min = INFINITY;
        
        //选择到各顶点权值最小的顶点，即为本次能确定最短路径的顶点
        for (int w = 0; w < G.vexnum; w++) {
            if (!final[w]) {
                if ((*D)[w] < min) {
                    k = w;
                    min = (*D)[w];
                }
            }
        }
        final[k] = 1;		//设置该顶点的标志位为1，避免下次重复判断
        
        //对v0到各顶点的权值进行更新
        for (int w = 0; w < G.vexnum; w++) {
            if (!final[w] && (min+G.arcs[k][w] < (*D)[w])) {
                (*D)[w] = min+G.arcs[k][w];
                (*p)[w] = k;//记录各个最短路径上存在的顶点
            }
        }
    }
}
int main() {
    MGraph G;
    CreateUDG(&G);
    PathMatrix P;
    ShortPathTable D;
    ShortestPath_Dijkstra(G, 0, &P, &D);
    for (int i=1; i<G.vexnum; i++) {
        cout<<"V"<<0<<"- V"<<i<<"的最短路径中的顶点有(逆序)：";
        cout<<" V"<<i;
        int j = i;
        //由于每一段最短路径上都记录着经过的顶点，所以采用嵌套的方式输出即可得到各个最短路径上的所有顶点
        while (P[j] != 0) {
            cout<<" V"<<P[j];
            j = P[j];
        }
        cout<<" V0"<<endl;
    }
    cout<<"源点到各顶点的最短路径长度为:"<<endl;
    for (int i = 1; i < G.vexnum; i++) {
        cout<<"V"<<G.vexs[0]<<" - V"<<G.vexs[i]<<" : "<<D[i]<<endl;
    }
    return 0;
}
