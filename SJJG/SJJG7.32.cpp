#include <cstdlib>
#include <iostream>
#include <string.h> 
#include <queue>
#define Maxsize 30
#define INFINITY 32767
using namespace std;
typedef struct ArcNode { //�ڽӱ����ڵ�
    int adjvex; //�����±�
    int info; //����
    struct ArcNode *nextarc;
}ArcNode;

typedef struct adjlist { //��ͷ�ڵ�
    char name[10]; //��������
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

int Locatecity(ALGraph G,char v[]);             //��λ����
void createGraph();                      		//��ͼ����
void MinSpanTree(ALGraph G);                    //����ķ�㷨����С���� 
int minimum(ALGraph G,Closedge closedge[]);		//ѡ����С�߼���С���ѵĺ���
void output(ALGraph G);                  		//����ڽӱ�ĺ���
int main() {
    createGraph();
    return 0;
}

//����ķ�㷨����С������
void MinSpanTree(ALGraph G)	{
    int k,i,j,w;
    char v[10];
    Closedge closedge[G.vexnum];
    for(int n=0;n<G.vexnum;n++)
    	closedge[n].lowcost=INFINITY; //��ʼ��
    cout<<"��������ʼ��:"<<endl;
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
    closedge[k].lowcost=0; //��ʼ��,U={v}
    for(i=1;i<G.vexnum;i++) { //��ʼѡ�����ඥ��
       ArcNode *p;
       w=minimum(G,closedge);
       cout<<G.ver[w].name<<"��Ӧ�Ļ���Ϊ:"<<closedge[w].lowcost<<endl;
       closedge[w].lowcost=0; //����w����U
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

// ������С���� 
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

// �����ڽӱ� 
void createGraph() {
    ALGraph G;
    cout<<"������ͼ�Ķ������:"<<endl;
    cin>>G.vexnum;
    cout<<"�����뻡��:"<<endl;
    cin>>G.arcnum;
    for(int i=0;i<G.vexnum;i++) {
       cout<<"��"<<i+1<<"�����������"<<endl;
       cin>>G.ver[i].name;
       G.ver[i].firstarc=NULL;
	}
    int n,m,cost;
    char v1[10],v2[10];
    for(int j=0;j<G.arcnum;j++) {
       	cout<<"�������"<<j+1<<"�����Ļ�β�뻡ͷ"<<endl;
       	cin>>v1>>v2;
       	n=Locatecity(G,v1); m=Locatecity(G,v2);
       	cout<<"�������Ӧ�Ļ���:"<<endl;
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

//������ڽӱ�ĺ���
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

//��λһ��v��G�е�λ�õĺ���
int Locatecity(ALGraph G,char v[]) {
    int i;
    for(i=0;i<G.vexnum;i++)
    	if(!strcmp(G.ver[i].name,v))
    		break;
    return i;
}
