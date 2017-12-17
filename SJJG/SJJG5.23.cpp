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
		Twin* m_pt; // ָ�����Ԫ��ָ��  
		int rpos[Max];  
		int m_nCol;  // ��������  
		int m_nRow;  // ��������  
		int m_nTws;    // ����Ԫ����  
}; 

CSparseMat::CSparseMat(int r, int c, int n) 
{
	m_nRow=r;  
	m_nCol=c;  
	m_nTws=n;   
	m_pt=new Twin[m_nTws];  
	if(!m_pt) 
		return;   // �����������ж�Ԫ��  
	int i;   
	for(i=0;i<m_nTws;i++)
	{   
		cout<<"���������Ԫ��Ԫ����б��ֵ��";   
		cin>>m_pt[i].col>>m_pt[i].e;  
	}   
	for(i=0;i<m_nRow;i++)
	{   
		cout<<"������ÿ�е�һ������Ԫ�ڶ�Ԫ���е����(û������-1)��";   
		cin>>rpos[i]; // ����û�з���Ԫ����-1  
	}  
}

void CSparseMat::ShowSparse(int i,int j) 
{  
	if(i>m_nRow||j>m_nCol)		// �������󷶳� 
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
	CSparseMat A(3,3,5); 		// 3x3�ľ���5������Ԫ 
	A.ShowSparse(2,1);  		// ���ҵڶ��е�һ�е�Ԫ�� 
	return 0; 
}


