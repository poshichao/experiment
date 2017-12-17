#include<iostream>
#include<malloc.h>  
#define LIST_INIT_SIZE 100   //初始容量   
#define LISTINCREMENT 10    //空间增量   
using namespace std;
    
typedef int ElemType; 
typedef struct{  		// 定义顺序表 
   ElemType *elem;   //存储空间基址 
   int length;    	//表长,元素个数  
   int listsize;   //表容量,空间大小  
}SqList;   
  
int InitList(SqList &L)  {  		//构造一个空的线性表L 
    L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType)) ;   
    if(!L.elem) exit(-1);   
    L.length=0;              
    L.listsize=LIST_INIT_SIZE;    
    return 1;   
}   
  
void Input(SqList &L) {  		//输入数据   
    int n,i,x;  
    cout<<"请输入顺序表长度:"<<endl;  
    cin>>n;  
    L.length=n;  
    for(i=0;i<n;i++)  
    {  
        cout<<"请输入第"<<i+1<<"个元素："<<endl;  
        cin>>x;  
        L.elem[i]=x;  
    }  
}  
  
  
void Print(SqList L){  			// 输出数据 
    int i,n=L.length;  
    cout<<"这个顺序表是:"<<endl;  
    for(i=0;i<n;i++)  
        cout<<L.elem[i]<<' ';  
}  
  
void Reverse(SqList &L){  		//利用原表空间就地逆置顺序表L  
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
    InitList(L);  				// 初始化顺序表 
    Input(L);					// 为顺序表赋值 
    cout<<endl<<"逆置前，";  
    Print(L);  
    Reverse( L);  				// 就地逆置 
    cout<<endl<<"逆置后，";  
    Print(L);  
    return 0;
}  
