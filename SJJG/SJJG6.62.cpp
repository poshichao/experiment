#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct CSNode {
	char data;		// ��ֵ 
	struct CSNode *firstchild, *nextsibling;	// ���ӽڵ㣬�ֵܽڵ� 
}CSNode, *CSTree;

// ��ʼ�����Ķ������� 
void InitCSTree(CSTree& T) {
	if (!(T = (CSNode *)malloc(sizeof(CSNode))))
		exit(-1); 
}
 
// �����򴴽����Ķ������� 
int CreateCSTree(CSTree& T) {
    char da;  
    cin >> da;		//��������
	
    if(da == '#') {  
        T = NULL;  
    } else {  
        if(!(T = (CSNode*)malloc(sizeof(CSNode))))
			exit(-1);				//�½�һ���ڵ�  
        T->data = da;				//������Ϊ���������  
        CreateCSTree(T->firstchild);	//�ݹ鴴�����ӽڵ�  
        CreateCSTree(T->nextsibling);	//�ݹ鴴���ֵܽڵ� 
    }
	return 1; 
}

// �����������
int Depth(CSTree& T) {
	int d1,d2;  
	if (T) {
		d1 = 1+Depth(T->firstchild);   
		d2 = Depth(T->nextsibling);   
	return d1>d2?d1:d2;  
	}   
	else return 0;
} 

int main() {
	CSTree T;	// ���Ķ������� 
	int depth;	// ������� 
	
	InitCSTree(T);	// ��ʼ�����Ķ������� 
	cout<<"��������������Ӧ�Ķ�������'#'��ʾ�գ�"<<endl; 
	CreateCSTree(T);	// ���򴴽����Ķ�������'#' ����� 
	depth = Depth(T); 	// ����������� 
	cout<<"����������ǣ�"<<endl<<depth; 
	return 0;
}
