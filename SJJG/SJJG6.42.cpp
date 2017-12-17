#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct BiTNode {
	int data;
	struct BiTNode *lchild, *rchild;		// �������� 
}*BiTree;

// ��ʼ�������� 
void InitBiTree(BiTree& T) {
	if(!(T = (BiTNode *)malloc(sizeof(BiTNode))))
		exit(-1);
}

// �����򴴽������� 
int CreateBiTree(BiTree& T) {
    char ch;  
    cin >> ch;		//��������
	
    if(ch == '#') {  
        T = NULL;  
    } else {  
        if(!(T = (BiTNode*)malloc(sizeof(BiTNode))))
			exit(-1);				//�½�һ���ڵ�  
        T->data = ch;				//������Ϊ���������  
        CreateBiTree(T->lchild);	//�ݹ鴴��������  
        CreateBiTree(T->rchild);	//�ݹ鴴��������  
    }
	return 1; 
}

// ���������Ҷ�ӽ�����Ŀ  
int LeafNodeNum(int& i,BiTree& T) { 
	if (T) {
		if (!T->lchild && !T->rchild) 	// ����������Ҳ������������ΪҶ�� 
			i++;   
		LeafNodeNum(i,T->lchild);  // �ݹ������������Ҷ���� 
		LeafNodeNum(i,T->rchild);  // �ݹ������������Ҷ����
	}   
	return i;  
}  

int main() {
	BiTree T;
	int num = 0;		// ͳ��Ҷ�ӽڵ��� 
	InitBiTree(T);		// ��ʼ��������T 
	
	// ����������
	cout<<"������˳��������ڵ��ֵ��'#'��ʾ������"<<endl; 
	CreateBiTree(T);
	
	// �������Ҷ�ӽ���� 
	num = LeafNodeNum(num, T);
	
	// �����ڵ��� 
	cout<<"�ö�����Ҷ�ӽڵ���Ϊ:"<<endl; 
	cout<<num;
	return 0;
} 
