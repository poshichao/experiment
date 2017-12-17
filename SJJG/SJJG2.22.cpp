#include <iostream>  
using namespace std;  
typedef struct node{		// 定义链表 
    int data;  
    node * next;  
}Node;

//创建单链表  
Node * CreateList()  
{  
    Node * now=new Node;  
    (*now).data=0;			// 将头节点的数据赋值为0 
    Node * p=now;  
    int j=5;  
    Node * q;  
	cout<<"请输入5个数"<<endl;
    while(j>0){   
        j--;  
        q=new Node;			// 每存入一个新的节点前，开辟一个新的空间
        cout<<"请输入第"<<5-j<<"个整数"<<endl;  
        int temp;  
        cin>>temp;  
        q->data=temp; 		// 赋值  
        p->next=q;			// 让当前节点指向新的节点 
        p=q;				// 指针p指向新的节点 
    }  
    p->next=NULL;			// 尾指针 
    return now;				// 返回表头结点 
}  

//使单链表变为原来的逆序  
Node * Reverse(Node * now)  
{  
    Node * pPre=now;  
    Node * pCur=pPre->next;  
    Node * pNext=NULL;  

    while(pCur){			// 将第二个节点插入到第一个前   
        pNext=pCur->next;  
        pCur->next=pPre;  
        pPre=pCur;  
        pCur=pNext;  
    }  
    now->next=NULL;
    return pPre;			// 返回新的表头节点  
}

int main()  
{  
    Node *CreateList();
    cout<<"开始创建链表"<<endl;  
    Node *now=CreateList();  
    Node *p=now;
	cout<<"逆置前的链表是："<<endl;
    while (p){    
        cout<<p->data<<' ';  
        p=p->next;  
    }  
    cout<<endl;
    Node * Reverse(Node * now);//声明函数  
    Node * r=Reverse(now);  
    cout<<"逆置后的链表是："<<endl; 
    while (r)  
    {  
        cout<<r->data<<' ';  
        r=r->next;  
    }
	cout<<endl; 
    return 0;  
}  
