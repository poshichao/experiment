#include <iostream>  
using namespace std;  
typedef struct node{		// �������� 
    int data;  
    node * next;  
}Node;

//����������  
Node * CreateList()  
{  
    Node * now=new Node;  
    (*now).data=0;			// ��ͷ�ڵ�����ݸ�ֵΪ0 
    Node * p=now;  
    int j=5;  
    Node * q;  
	cout<<"������5����"<<endl;
    while(j>0){   
        j--;  
        q=new Node;			// ÿ����һ���µĽڵ�ǰ������һ���µĿռ�
        cout<<"�������"<<5-j<<"������"<<endl;  
        int temp;  
        cin>>temp;  
        q->data=temp; 		// ��ֵ  
        p->next=q;			// �õ�ǰ�ڵ�ָ���µĽڵ� 
        p=q;				// ָ��pָ���µĽڵ� 
    }  
    p->next=NULL;			// βָ�� 
    return now;				// ���ر�ͷ��� 
}  

//ʹ�������Ϊԭ��������  
Node * Reverse(Node * now)  
{  
    Node * pPre=now;  
    Node * pCur=pPre->next;  
    Node * pNext=NULL;  

    while(pCur){			// ���ڶ����ڵ���뵽��һ��ǰ   
        pNext=pCur->next;  
        pCur->next=pPre;  
        pPre=pCur;  
        pCur=pNext;  
    }  
    now->next=NULL;
    return pPre;			// �����µı�ͷ�ڵ�  
}

int main()  
{  
    Node *CreateList();
    cout<<"��ʼ��������"<<endl;  
    Node *now=CreateList();  
    Node *p=now;
	cout<<"����ǰ�������ǣ�"<<endl;
    while (p){    
        cout<<p->data<<' ';  
        p=p->next;  
    }  
    cout<<endl;
    Node * Reverse(Node * now);//��������  
    Node * r=Reverse(now);  
    cout<<"���ú�������ǣ�"<<endl; 
    while (r)  
    {  
        cout<<r->data<<' ';  
        r=r->next;  
    }
	cout<<endl; 
    return 0;  
}  
