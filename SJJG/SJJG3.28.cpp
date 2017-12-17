#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct LNode{  
    int data;  
    struct LNode *next;  
} LNode, *LinkList;  
typedef LinkList CLQueue;
int InitCLQueue(CLQueue &rear)//���г�ʼ��  
{   
   rear = (CLQueue)malloc(sizeof(LNode));  
   if(!rear) return 0;  
   rear -> next = rear;  
   return 1;     
}  
  
int EnCLQueue(CLQueue &rear, int x)//�����  
{   
    CLQueue head,p;  
    head = rear -> next;  
    p = (CLQueue)malloc(sizeof(LNode));  
    if(!p)return 0;    //�������ʧ��  
    p -> data = x;  
    p -> next = head;  
    rear -> next = p;     //��ӵ��Ԫ��e���½ڵ�p��ֵ��ԭ��β�ĺ��  
    rear = p;             //����ǰ��p����Ϊ��β�ڵ�  
    return 1;  
}  
  
int DeCLQueue(CLQueue &rear, int &x)//������  
{   
    CLQueue head,p;  
    head = rear -> next;  
    if(head == rear)return 0;  
    p = head -> next;     //����ɾ���Ķ�ͷ����ݴ��p  
    x = p -> data;        //����ɾ���Ķ�ͷ����ֵ����x  
    head -> next = p -> next;//��ԭ��ͷ���ĺ��p->next��ֵ��ͷ�����  
    free(p);  
    return 1;  
}
int main()
{
	CLQueue Q;
	InitCLQueue(Q);		// ��ʼ������
	
	int a[10];
	cout<<"����10����������У�"<<endl;
	for (int i=0; i<10; i++)		// ����� 
	{
		cin>>a[i];
		EnCLQueue(Q, a[i]);
	}
	Q = Q->next;
	 
	cout<<"���н����"<<endl;
	for(int i=0; i<10; i++, Q = Q->next)	// ��ʾ���� 
	{
		cout<<Q->next->data<<' ';
	}
	Q = Q->next;
	
	cout<<endl<<"2�����У�"<<endl;
	DeCLQueue(Q, a[1]);		// ָ��2������ 
	for(int i = 0; i<9; i++, Q = Q->next)	// ��ʾ�����к���� 
	{
		cout<<Q->next->data<<' ';
	}
	cout<<endl;
	
	return 0;
} 
