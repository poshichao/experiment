#include<iostream>
#include<malloc.h>
using namespace std;

typedef int ElemType;
typedef struct node{	// �������� 
	ElemType data;
	struct node *next;
}*LinkList;

// ��ʼ��ͷ��� 
void InitLink(LinkList L)
{
	L->data = 0;
	L->next = L;
}

// �ó���Ϊn�����鴴������
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

// ���ָ���ڵ�֮������нڵ�
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

//����L���n���ڵ㣨n�ɳ���L���ܽڵ������
node * CreLNodePoint(LinkList L, int n)
{
	node *s = L;
	while (n--){		// n��Ϊ0��һֱ����� 
		s = s->next;
	}
	return s;
}

//ɾ��s��ǰ���ڵ�
void DetelePre(node *s)
{
	node *p = s;
	node *r = p;
	while (p->next != s){	// ���ݵ�ַ�Ƚϣ��Ƿ�Ϊs�ڵ��ǰһ�ڵ� 
		r = p;
		p = p->next;
	}
	
	r->next = s;		// ��s�ڵ��ǰǰ�ڵ�ָ��s�ڵ� 
	free(p);			// �ͷ�sǰһ�ڵ���ڴ�ռ� 
}

int main()
{
	ElemType data[6] = {1, 2, 3, 8, 4, 5 };			// ������һ��ֵ������Ϊ�������� 
	int length = sizeof(data) / sizeof(ElemType);	// ����Ӧ���м����ڵ� 
	LinkList L = (LinkList)malloc(sizeof(LinkList));
	node *s;

	InitLink(L);	// ��ʼ��ͷ���	
	CreateLink(L, data, length);	// ����������ͷ��㡢ͷָ�� 
	cout<<"ԭ����:";
	ShowList(L);

	s = CreLNodePoint(L,4);		// ����ָ��ѭ������ĳ�ڵ��ָ��
	DetelePre(s);				// ɾ��s��ǰ���ڵ�
	cout<<"sָ�������Ϊ:"<<s->data<<endl;
	cout<<"ɾ����ǰ���ڵ�:";
	ShowList(L);
	
	return 0;
}
