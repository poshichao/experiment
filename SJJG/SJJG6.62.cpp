#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct CSNode {
	char data;		// 数值 
	struct CSNode *firstchild, *nextsibling;	// 孩子节点，兄弟节点 
}CSNode, *CSTree;

// 初始化树的二叉链表 
void InitCSTree(CSTree& T) {
	if (!(T = (CSNode *)malloc(sizeof(CSNode))))
		exit(-1); 
}
 
// 按先序创建树的二叉链表 
int CreateCSTree(CSTree& T) {
    char da;  
    cin >> da;		//输入数据
	
    if(da == '#') {  
        T = NULL;  
    } else {  
        if(!(T = (CSNode*)malloc(sizeof(CSNode))))
			exit(-1);				//新建一个节点  
        T->data = da;				//数据域为输入的内容  
        CreateCSTree(T->firstchild);	//递归创建孩子节点  
        CreateCSTree(T->nextsibling);	//递归创建兄弟节点 
    }
	return 1; 
}

// 计算树的深度
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
	CSTree T;	// 树的二叉链表 
	int depth;	// 树的深度 
	
	InitCSTree(T);	// 初始化树的二叉链表 
	cout<<"按先序输入树对应的二叉链表，'#'表示空："<<endl; 
	CreateCSTree(T);	// 先序创建树的二叉链表，'#' 代表空 
	depth = Depth(T); 	// 计算树的深度 
	cout<<"该数的深度是："<<endl<<depth; 
	return 0;
}
