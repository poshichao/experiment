#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct LNode{  
    int data;  
    struct LNode *next;  
} LNode, *LinkList;  
typedef LinkList CLQueue;
int InitCLQueue(CLQueue &rear)//队列初始化  
{   
   rear = (CLQueue)malloc(sizeof(LNode));  
   if(!rear) return 0;  
   rear -> next = rear;  
   return 1;     
}  
  
int EnCLQueue(CLQueue &rear, int x)//入队列  
{   
    CLQueue head,p;  
    head = rear -> next;  
    p = (CLQueue)malloc(sizeof(LNode));  
    if(!p)return 0;    //储存分配失败  
    p -> data = x;  
    p -> next = head;  
    rear -> next = p;     //把拥有元素e的新节点p赋值给原队尾的后继  
    rear = p;             //将当前的p设置为队尾节点  
    return 1;  
}  
  
int DeCLQueue(CLQueue &rear, int &x)//出队列  
{   
    CLQueue head,p;  
    head = rear -> next;  
    if(head == rear)return 0;  
    p = head -> next;     //将欲删除的队头结点暂存给p  
    x = p -> data;        //将欲删除的队头结点的值赋给x  
    head -> next = p -> next;//将原队头结点的后继p->next赋值给头结点后继  
    free(p);  
    return 1;  
}
int main()
{
	CLQueue Q;
	InitCLQueue(Q);		// 初始化队列
	
	int a[10];
	cout<<"输入10个数进入队列："<<endl;
	for (int i=0; i<10; i++)		// 入队列 
	{
		cin>>a[i];
		EnCLQueue(Q, a[i]);
	}
	Q = Q->next;
	 
	cout<<"队列结果："<<endl;
	for(int i=0; i<10; i++, Q = Q->next)	// 显示队列 
	{
		cout<<Q->next->data<<' ';
	}
	Q = Q->next;
	
	cout<<endl<<"2出队列："<<endl;
	DeCLQueue(Q, a[1]);		// 指定2出队列 
	for(int i = 0; i<9; i++, Q = Q->next)	// 显示出队列后队列 
	{
		cout<<Q->next->data<<' ';
	}
	cout<<endl;
	
	return 0;
} 
