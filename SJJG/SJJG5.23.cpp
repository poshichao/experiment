#include<iostream> 
#include<stdlib.h>
using namespace std; 
#define Max 128   

typedef struct{  
	int col;  
	int e; 
}Twin;
   
class CSparseMat
{
	public:    
		CSparseMat(int r,int c,int n);	
		void ShowSparse(int i,int j);    
		Twin* m_pt; // 指向非零元的指针  
		int rpos[Max];  
		int m_nCol;  // 矩阵列数  
		int m_nRow;  // 矩阵行数  
		int m_nTws;    // 非零元个数  
}; 

CSparseMat::CSparseMat(int r, int c, int n) 
{
	m_nRow=r;  
	m_nCol=c;  
	m_nTws=n;   
	m_pt=new Twin[m_nTws];  
	if(!m_pt) 
		return;   // 输入矩阵的所有二元组  
	int i;   
	for(i=0;i<m_nTws;i++)
	{   
		cout<<"请输入非零元二元组的列标和值：";   
		cin>>m_pt[i].col>>m_pt[i].e;  
	}   
	for(i=0;i<m_nRow;i++)
	{   
		cout<<"请输入每行第一个非零元在二元组中的序号(没有输入-1)：";   
		cin>>rpos[i]; // 该行没有非零元输入-1  
	}  
}

void CSparseMat::ShowSparse(int i,int j) 
{  
	if(i>m_nRow||j>m_nCol)		// 超出矩阵范畴 
		return;   
	int x=0;  
	int s,d;  
	if(i==m_nRow)			 
	{
	   s=rpos[i-1];   
	   d=m_nTws;   
	}   
	else
	{
		s=rpos[i-1];   
		int m=1;   
		d=rpos[i+m-1];   
		while(d<0)
		{
		    if(i+m<m_nRow)
			{
			    m++;      
				d=rpos[i+m-1];     
			}    
			else      
			d=m_nTws;   
		}   
	}
	if(s>=0)
	{
	   int k=s;   
	   while(k<d)
	   {
	      	if(m_pt[k].col==j)      
				x=m_pt[k].e;    
			k++;   
		}   
	}
	cout<<x<<endl;  
} 

int main() 
{  
	CSparseMat A(3,3,5); 		// 3x3的矩阵，5个非零元 
	A.ShowSparse(2,1);  		// 查找第二行第一列的元素 
	return 0; 
}


