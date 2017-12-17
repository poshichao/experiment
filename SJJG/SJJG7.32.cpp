#include <cstdlib>
#include <iostream>
#include <string.h> 
#include <queue>
#define Maxsize 30
#define INFINITY 32767
using namespace std;
typedef struct ArcNode { //邻接表链节点
    int adjvex; //顶点下标
    int info; //花费
    struct ArcNode *nextarc;
}ArcNode;

typedef struct adjlist { //表头节点
    char name[10]; //顶点名称
    ArcNode *firstarc;
}adjlist;

typedef struct {
    int vexnum,arcnum;
    adjlist ver[Maxsize];
}ALGraph;

typedef struct{
    int adjvex;
    int lowcost;
}Closedge;

int Locatecity(ALGraph G,char v[]);             //定位函数
void createGraph();                      		//建图函数
void MinSpanTree(ALGraph G);                    //普里姆算法求最小生树 
int minimum(ALGraph G,Closedge closedge[]);		//选择最小边即最小花费的函数
void output(ALGraph G);                  		//输出邻接表的函数
int main() {
    createGraph();
    return 0;
}

//普里姆算法求最小生成树
void MinSpanTree(ALGraph G)	{
    int k,i,j,w;
    char v[10];
    Closedge closedge[G.vexnum];
    for(int n=0;n<G.vexnum;n++)
    	closedge[n].lowcost=INFINITY; //初始化
    cout<<"请输入起始点:"<<endl;
    cin>>v;
    k=Locatecity(G,v);
    for(j=0;j<G.vexnum;j++) {
       ArcNode *p;
       if(j!=k) {
          p=G.ver[j].firstarc;
          while(p->adjvex!=k&&p->nextarc)
          p=p->nextarc;
          if(p&&p->adjvex==k) {
              closedge[j].lowcost=p->info;
              closedge[j].adjvex=k;
		  }
	   }
	}
    cout<<G.ver[k].name<<endl;
    closedge[k].lowcost=0; //初始化,U={v}
    for(i=1;i<G.vexnum;i++) { //开始选择其余顶点
       ArcNode *p;
       w=minimum(G,closedge);
       cout<<G.ver[w].name<<"对应的花费为:"<<closedge[w].lowcost<<endl;
       closedge[w].lowcost=0; //顶点w加入U
       for(j=0;j<G.vexnum;j++) {
          ArcNode *p;
          if(j!=w) {
            p=G.ver[j].firstarc;
            while(p->adjvex!=w&&p->nextarc)
            	p=p->nextarc;
            if(p&&p->info<closedge[j].lowcost&&p->adjvex==w) {
            	closedge[j].lowcost=p->info;
                closedge[j].adjvex=w;
			}
		  }
	   }
	}
}

// 计算最小数字 
int minimum(ALGraph G,Closedge closedge[]) {
    int i,vex=-1,min=INFINITY;
    for(i=0;i<G.vexnum;i++) {
       if(closedge[i].lowcost!=0&&closedge[i].lowcost<min) {
          min=closedge[i].lowcost;
          vex=i;
	   }
	}
    return vex;
}

// 创建邻接表 
void createGraph() {
    ALGraph G;
    cout<<"请输入图的顶点个数:"<<endl;
    cin>>G.vexnum;
    cout<<"请输入弧数:"<<endl;
    cin>>G.arcnum;
    for(int i=0;i<G.vexnum;i++) {
       cout<<"第"<<i+1<<"个顶点的名称"<<endl;
       cin>>G.ver[i].name;
       G.ver[i].firstarc=NULL;
	}
    int n,m,cost;
    char v1[10],v2[10];
    for(int j=0;j<G.arcnum;j++) {
       	cout<<"请输入第"<<j+1<<"条弧的弧尾与弧头"<<endl;
       	cin>>v1>>v2;
       	n=Locatecity(G,v1); m=Locatecity(G,v2);
       	cout<<"请输入对应的花费:"<<endl;
       	cin>>cost;
       	ArcNode *p,*q,*t;
       	p=(ArcNode*)malloc(sizeof(ArcNode));
       	p->adjvex=m;
       	p->info=cost;
       	p->nextarc=NULL;
       	if(G.ver[n].firstarc==NULL)
       		G.ver[n].firstarc=p;
       	else {
          	q=G.ver[n].firstarc;
          	while(q->nextarc)
          		q=q->nextarc;
          	q->nextarc=p;
	   	}
       	t=(ArcNode*)malloc(sizeof(ArcNode));
       	t->adjvex=n;
       	t->info=cost;
       	t->nextarc=NULL;
       	if(G.ver[m].firstarc==NULL)
       		G.ver[m].firstarc=t;
       	else {
          	q=G.ver[m].firstarc;
          	while(q->nextarc)
          		q=q->nextarc;
          	q->nextarc=t;
	   }
	}
    output(G);
    MinSpanTree(G);
}

//输出弧邻接表的函数
void output(ALGraph G) {
    int i,j;
    ArcNode *p;
    for(i=0;i<G.vexnum;i++) {
       if(G.ver[i].firstarc!=NULL) {
          	p=G.ver[i].firstarc;
          	while(p) {
             	cout<<p->adjvex<<' '<<p->info<<' ';
             	p=p->nextarc;
		  	}
	   	}
       	cout<<endl;
	}
}

//定位一点v在G中的位置的函数
int Locatecity(ALGraph G,char v[]) {
    int i;
    for(i=0;i<G.vexnum;i++)
    	if(!strcmp(G.ver[i].name,v))
    		break;
    return i;
}
