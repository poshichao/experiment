#include <iostream>
#include <stdlib.h>
using namespace std;
#define QUEUE_SIZE  10

// 循环队列结构体
typedef struct {
 	int front;  			// 队列头 
 	int rear;       		// 队列尾 
 	int length;     		// 记录队列元素个数
 	int data[QUEUE_SIZE];  // 存放队列元素值的数组
} CirQueue;

// 初始化队列
void initQueue(CirQueue *Q)
{
 	Q->front = Q->rear = 0;
 	Q->length = 0;
}

// 判断队列是否为空
int QueueEmpty(CirQueue *Q)
{
 	return Q->length == 0;  
}

// 判断队列满 
int QueueFull(CirQueue *Q)
{
 	return Q->length == QUEUE_SIZE;
}

// 入队列 
void EnQueue(CirQueue *Q, int data)
{
 	if (QueueFull(Q))
  		cout<<"队列已经满了。"<<endl;
 	Q->length++; 				// 队列元素个数加1
 	Q->data[Q->rear] = data;  	// 将新元素插入队尾
 	Q->rear = (Q->rear+1)%QUEUE_SIZE; 	// 将队尾加1
}

// 出队列
int Dequeue(CirQueue *Q)
{
 	int temp;
 	if (QueueEmpty(Q))
  		cout<<"队列已经为空!"<<endl;
 	temp = Q->data[Q->front];
 	Q->length--; 							// 队列元素个数减1
 	Q->front = (Q->front+1)%QUEUE_SIZE;  	// 队列头加1
 	return temp;
}

int main()
{
 	CirQueue Q;
 	int input = 0;  // 入队数据，由用户输入
 	
 	// 初始化队列
 	initQueue(&Q);
 	cout<<"请输入入队数据:"<<endl;
 	// 入队操作
 	while(!QueueFull(&Q))
 	{
  		cin>>input;
  		EnQueue(&Q, input);
 	}
 	cout<<"出队数据:"<<endl;

 	// 出队操作
 	while(!QueueEmpty(&Q))
 	{
  		cout<<Dequeue(&Q)<<' ';
 	}
 	cout<<endl;
 	return 0;
}
