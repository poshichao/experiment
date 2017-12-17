#include <iostream>
#include <stdlib.h>
using namespace std;
#define QUEUE_SIZE  10

// ѭ�����нṹ��
typedef struct {
 	int front;  			// ����ͷ 
 	int rear;       		// ����β 
 	int length;     		// ��¼����Ԫ�ظ���
 	int data[QUEUE_SIZE];  // ��Ŷ���Ԫ��ֵ������
} CirQueue;

// ��ʼ������
void initQueue(CirQueue *Q)
{
 	Q->front = Q->rear = 0;
 	Q->length = 0;
}

// �ж϶����Ƿ�Ϊ��
int QueueEmpty(CirQueue *Q)
{
 	return Q->length == 0;  
}

// �ж϶����� 
int QueueFull(CirQueue *Q)
{
 	return Q->length == QUEUE_SIZE;
}

// ����� 
void EnQueue(CirQueue *Q, int data)
{
 	if (QueueFull(Q))
  		cout<<"�����Ѿ����ˡ�"<<endl;
 	Q->length++; 				// ����Ԫ�ظ�����1
 	Q->data[Q->rear] = data;  	// ����Ԫ�ز����β
 	Q->rear = (Q->rear+1)%QUEUE_SIZE; 	// ����β��1
}

// ������
int Dequeue(CirQueue *Q)
{
 	int temp;
 	if (QueueEmpty(Q))
  		cout<<"�����Ѿ�Ϊ��!"<<endl;
 	temp = Q->data[Q->front];
 	Q->length--; 							// ����Ԫ�ظ�����1
 	Q->front = (Q->front+1)%QUEUE_SIZE;  	// ����ͷ��1
 	return temp;
}

int main()
{
 	CirQueue Q;
 	int input = 0;  // ������ݣ����û�����
 	
 	// ��ʼ������
 	initQueue(&Q);
 	cout<<"�������������:"<<endl;
 	// ��Ӳ���
 	while(!QueueFull(&Q))
 	{
  		cin>>input;
  		EnQueue(&Q, input);
 	}
 	cout<<"��������:"<<endl;

 	// ���Ӳ���
 	while(!QueueEmpty(&Q))
 	{
  		cout<<Dequeue(&Q)<<' ';
 	}
 	cout<<endl;
 	return 0;
}
