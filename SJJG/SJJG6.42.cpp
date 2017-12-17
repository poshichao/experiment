#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct BiTNode {
	int data;
	struct BiTNode *lchild, *rchild;		// 左右子树 
}*BiTree;

// 初始化二叉树 
void InitBiTree(BiTree& T) {
	if(!(T = (BiTNode *)malloc(sizeof(BiTNode))))
		exit(-1);
}

// 按先序创建二叉树 
int CreateBiTree(BiTree& T) {
    char ch;  
    cin >> ch;		//输入数据
	
    if(ch == '#') {  
        T = NULL;  
    } else {  
        if(!(T = (BiTNode*)malloc(sizeof(BiTNode))))
			exit(-1);				//新建一个节点  
        T->data = ch;				//数据域为输入的内容  
        CreateBiTree(T->lchild);	//递归创建左子树  
        CreateBiTree(T->rchild);	//递归创建右子树  
    }
	return 1; 
}

// 求二叉树中叶子结点的数目  
int LeafNodeNum(int& i,BiTree& T) { 
	if (T) {
		if (!T->lchild && !T->rchild) 	// 既无左子树也无右子树，则为叶子 
			i++;   
		LeafNodeNum(i,T->lchild);  // 递归计算左子树的叶子数 
		LeafNodeNum(i,T->rchild);  // 递归计算右子树的叶子数
	}   
	return i;  
}  

int main() {
	BiTree T;
	int num = 0;		// 统计叶子节点数 
	InitBiTree(T);		// 初始化二叉树T 
	
	// 创建二叉树
	cout<<"按先序顺序输入各节点的值，'#'表示空树："<<endl; 
	CreateBiTree(T);
	
	// 求二叉树叶子结点数 
	num = LeafNodeNum(num, T);
	
	// 数出节点数 
	cout<<"该二叉树叶子节点数为:"<<endl; 
	cout<<num;
	return 0;
} 
