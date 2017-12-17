#include<iostream>
#include<malloc.h>
using namespace std;

typedef int ElemType;
typedef struct node{	// 定义链表 
	ElemType data;
	struct node *next;
}*LinkList;

// 初始化头结点 
void InitLink(LinkList L)
{
	L->data = 0;
	L->next = L;
}

// 用长度为n的数组创建链表
void CreateLink(LinkList L, ElemType *arr, int n)
{
	node * now = NULL;
	node * r = L;
	int i;
	r->data = arr[0];
	for (i = 1; i < n; i++){
		now = (node *)malloc(sizeof(node)); 
		now->data = arr[i];
		now->next = r->next;
		r->next = now;
		r = r->next;
	}
}

// 输出指定节点之后的所有节点
void ShowList(LinkList L)
{
	int i;
	node *r = L;
	while (r->next != L){
		cout<<r->data<<" ";
		r = r->next;
	}
	cout<<r->data<<endl;
}

//返回L后第n个节点（n可超过L的总节点个数）
node * CreLNodePoint(LinkList L, int n)
{
	node *s = L;
	while (n--){		// n不为0，一直向后移 
		s = s->next;
	}
	return s;
}

//删除s的前驱节点
void DetelePre(node *s)
{
	node *p = s;
	node *r = p;
	while (p->next != s){	// 根据地址比较，是否为s节点的前一节点 
		r = p;
		p = p->next;
	}
	
	r->next = s;		// 将s节点的前前节点指向s节点 
	free(p);			// 释放s前一节点的内存空间 
}

int main()
{
	ElemType data[6] = {1, 2, 3, 8, 4, 5 };			// 给数组一组值，用来为创建链表 
	int length = sizeof(data) / sizeof(ElemType);	// 计算应该有几个节点 
	LinkList L = (LinkList)malloc(sizeof(LinkList));
	node *s;

	InitLink(L);	// 初始化头结点	
	CreateLink(L, data, length);	// 创建链表，无头结点、头指针 
	cout<<"原链表:";
	ShowList(L);

	s = CreLNodePoint(L,4);		// 制作指向循环链表某节点的指针
	DetelePre(s);				// 删除s的前驱节点
	cout<<"s指向的数据为:"<<s->data<<endl;
	cout<<"删除其前驱节点:";
	ShowList(L);
	
	return 0;
}
