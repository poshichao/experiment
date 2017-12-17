#include<iostream>
#include<malloc.h>  
#define LIST_INIT_SIZE 100   //��ʼ����   
#define LISTINCREMENT 10    //�ռ�����   
using namespace std;
    
typedef int ElemType; 
typedef struct{  		// ����˳��� 
   ElemType *elem;   //�洢�ռ��ַ 
   int length;    	//��,Ԫ�ظ���  
   int listsize;   //������,�ռ��С  
}SqList;   
  
int InitList(SqList &L)  {  		//����һ���յ����Ա�L 
    L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType)) ;   
    if(!L.elem) exit(-1);   
    L.length=0;              
    L.listsize=LIST_INIT_SIZE;    
    return 1;   
}   
  
void Input(SqList &L) {  		//��������   
    int n,i,x;  
    cout<<"������˳�����:"<<endl;  
    cin>>n;  
    L.length=n;  
    for(i=0;i<n;i++)  
    {  
        cout<<"�������"<<i+1<<"��Ԫ�أ�"<<endl;  
        cin>>x;  
        L.elem[i]=x;  
    }  
}  
  
  
void Print(SqList L){  			// ������� 
    int i,n=L.length;  
    cout<<"���˳�����:"<<endl;  
    for(i=0;i<n;i++)  
        cout<<L.elem[i]<<' ';  
}  
  
void Reverse(SqList &L){  		//����ԭ��ռ�͵�����˳���L  
    int i,n;  
    ElemType temp;  
    n=L.length;  
    for(i=0;i<n/2;i++){  
        temp=L.elem[n-1-i];  
        L.elem[n-1-i]=L.elem[i];  
        L.elem[i]=temp;  
    }  
}  
  
int main(){  
    SqList L;  
    ElemType e;  
    InitList(L);  				// ��ʼ��˳��� 
    Input(L);					// Ϊ˳���ֵ 
    cout<<endl<<"����ǰ��";  
    Print(L);  
    Reverse( L);  				// �͵����� 
    cout<<endl<<"���ú�";  
    Print(L);  
    return 0;
}  
