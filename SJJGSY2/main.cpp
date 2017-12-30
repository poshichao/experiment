#include <iostream>
#include <malloc.h>
using namespace std;
#define N 10                    // 停车场内最多的停车数
#define M 10                    // 候车场内最多的停车数
#define price 1                 // 单位时间价钱
typedef struct {
    int carNo[N];           // 车牌号
    int carTime[N];         // 进场时间
    int top;                // 栈指针
} SqStack;                  // 定义顺序栈类型，用于描述停车场

typedef struct {
    int carNo[M];           // 车牌号
    int front,rear;         // 队首和队尾指针
} SqQueue;                  // 定义循环队类型，用于描述候车场

/**
 * 初始化栈
 * @param s 栈
 */
void InitStack(SqStack *&s) {
    s = (SqStack *)malloc(sizeof(SqStack));
    s->top = -1;
}

/**
 * 栈的判空
 * @param s 栈
 * @return  true或false(是否为空)
 */
int StackEmpty(SqStack *s) {
    return (s->top == -1);  // 栈空
}

/**
 * 栈的判满
 * @param s 栈
 * @return  true或false(是否满栈)
 */
int StackFull(SqStack *s) {
    return (s->top == N - 1);   // 栈满
}

/**
 * 进栈
 * @param no 车牌号
 * @param time 到达时刻
 */
void Push(SqStack *&s,int no,int time) {
    if (StackFull(s)) {
        cout<<"栈满"<<endl;
    } else {
        s->top++;
        s->carNo[s->top] = no;
        s->carTime[s->top] = time;
    }
}

/**
 * 出栈
 * @param no 车牌号
 * @param time 离去时刻
 */
void Pop(SqStack *&s,int &no,int &time) {
    if (StackEmpty(s)) {
        cout<<"栈空"<<endl;
    } else {
        no = s->carNo[s->top];
        time = s->carTime[s->top];
        s->top--;
    }
}

/**
 * 显示整个栈
 * @param s 栈
 */
void display(SqStack *s) {
    int i;
    for (i = s->top; i >= 0; i--) {
        cout<<s->carNo[i]<<' ';
    }
    cout<<endl;
}

/**
 * 队列的初始化
 * @param q 队列
 */
void InitQueue(SqQueue *&q) {
    q = (SqQueue *)malloc(sizeof(SqQueue));
    q->front = q->rear = 0;
}

/**
 * 队列的判空
 * @param q 队列
 * @return  true或false(队列是否为空)
 */
int QueueEmpty(SqQueue *q) {
    return(q->front==q->rear);
}

/**
 * 队列判满
 * @param q 队列
 * @return  true或false(队列是否为满)
 */
int QueueFull(SqQueue *q) {
    return ((q->rear+1)%M==q->front);
}

/**
 * 进队列
 * @param q 队列
 * @param e 进队列的元素
 * @return
 */
int enQueue(SqQueue *&q,int e) {
    if ((q->rear+1)%M==q->front)    /*队满*/
        return 0;
    q->rear=(q->rear+1)%M;
    q->carNo[q->rear]=e;
    return 1;
}

/**
 * 出队列
 * @param q 队列
 * @param e 出队的元素
 * @return
 */
int deQueue(SqQueue *&q,int &e) {
    if (q->front==q->rear)          /*队空的情况*/
        return 0;
    q->front=(q->front+1)%M;
    e=q->carNo[q->front];
    return 1;
}

/**
 * 输出出队
 * @param q 队列
 */
void DispQueue(SqQueue *q) {
    int i;
    i=(q->front+1)%M;
    cout<<q->carNo[i]<<' ';
    while ((q->rear-i+M)%M>0)
    {
        i=(i+1)%M;
        cout<<q->carNo[i]<<' ';
    }
    cout<<endl;
}

/**
 * 测试主函数
 * @return
 */
int main()
{
    int comm;   // 命令,用于判断执行那个操作
    int no,e1,time,e2;      // 车牌号, 临时车牌号 , 时间, 临时时间
    int i,j,t;              // 循环控制变量
    SqStack *St,*St1;       //St是停车场，St1是在有车离开时，记录为该车移开位置的车辆
    SqQueue *Qu;            //Qu是候车场
    InitStack(St);          // 初始化栈
    InitStack(St1);         // 初始化栈
    InitQueue(Qu);          // 初始化队列

    // 用户输入命令，根据不同的指令对停车场执行不同的操作
    do {
        cout<<"输入指令(1:到达 2:离开 3:显示停车场 4:显示候车场 0:退出):";
        cin>>comm;
        switch(comm) {
            case 1:     // 汽车到达
                cout<<"输入车牌号和时间(设车牌号和时间均为整数): ";
                cin>>no>>time;

                // 停车场不满,进入停车场
                if (!StackFull(St)) {
                    Push(St,no,time);
                    cout<<"  >>停车场位置:"<<St->top+1<<endl;
                }

                else {                       // 停车场满
                    // 候车场不满，进入候车场
                    if (!QueueFull(Qu)) {
                        enQueue(Qu,no);
                        cout<<"  >>候车场位置:"<<Qu->rear<<endl;
                    }
                    else
                        cout<<"  >>候车场已满,不能停车"<<endl;
                }
                break;
            case 2:     // 汽车离开
                cout<<"输入车牌号和离开时间(设车牌号和时间均为整数): ";
                cin>>no>>time;
                for (i = 0; i <= St->top && St->carNo[i] != no; i++);  // 遍历栈，查找是否有出栈的车辆
                if (i>St->top)
                    cout<<"  >>未找到该车牌号的汽车"<<endl;
                else {
                    t = St->top - i;        // 需要出栈的车辆数目,全进入临时栈

                    // 从要出停车场的车辆往后，先出栈进入临时栈
                    for (j=0; j<t; j++) {
                        Pop(St,e1,e2);
                        Push(St1,e1,e2);
                    }
                    Pop(St,e1,e2);              // 该汽车离开
                    cout<<"  >>"<<no<<"汽车停车时间:"<<time - e2<<endl;
                    cout<<"  >>"<<no<<"汽车停车费用:"<<(time - e2) * price<<endl;

                    // 将临时栈中的车辆重新进栈到停车场中
                    while (!StackEmpty(St1)) {
                        Pop(St1,e1,e2);
                        Push(St,e1,e2);
                    }

                    // 队不空时,将队头进栈停车场
                    if (!QueueEmpty(Qu)) {
                        deQueue(Qu,e1);
                        Push(St,e1,time);       // 以当前时间开始计费
                    }
                }
                break;
            case 3:     // 显示停车场情况
                if (!StackEmpty(St)) {
                    cout<<"  >>停车场中的车辆:";
                    display(St);        // 输出停车场中的车辆
                }
                else
                    cout<<"  >>停车场中无车辆"<<endl;
                break;
            case 4:     /*显示候车场情况*/
                if (!QueueEmpty(Qu)) {
                    cout<<"  >>候车场中的车辆:";
                    DispQueue(Qu);      // 输出候车场中的车辆
                }
                else
                    cout<<"  >>候车场中无车辆"<<endl;
                break;
            case 0:     // 结束循环
                if (!StackEmpty(St)) {
                    cout<<"  >>停车场中的车辆:";   // 输出停车场中的车辆
                    display(St);
                }
                if (!QueueEmpty(Qu)) {
                    printf("  >>候车场中的车辆:"); // 输出候车场中的车辆
                    DispQueue(Qu);
                }
                break;
            default:    // 其他情况
                cout<<"  >>输入的命令错误"<<endl;
                break;
        }
    }
    while(comm!=0);
    return 0;
}