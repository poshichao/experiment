#include<iostream>
#define maxSize 50
using namespace std;
typedef struct{    // 顺序表的定义
    int data[maxSize];		// 数据 
    int length;				// 表长 
}Sqlist;

void init(Sqlist &sl)    // 初始化顺序表
{
    int len=10;

    for(int i=1; i<=len; ++i)
    {
        sl.data[i]=i*3-2;
    }
    sl.length = len;
}

int locate(Sqlist sl, int num)    // 找到恰当的插入位置
{
    int i=1;
    for(; i<=sl.length; ++i)	// 比较插入数和表中数大小 
    {
        if(sl.data[i]>num)
        {
            return i;   // 返回位置 
        }
    }
    return i;   // 目前顺序表没有值较 num 大，返回最大下标
}

int insert(Sqlist &sl, int loc, int num)    // 往顺序表 sl 的 loc 位置插入值为 num 的元素
{
    int i=sl.length;

    if(loc<1 || loc>sl.length+1){   // 合法的位置应该在 1~sl.length+1 之间
        return 0;
    }

    for(;i>=loc;i--){				// 从后往前移，保证数据不被冲掉
    	sl.data[i+1]=sl.data[i];
	}
    sl.data[loc]=num;
    sl.length++;

    return 1;
}

void printSqlist(Sqlist sl)
{
    int len=sl.length;
    for(int i=1; i<=len; i++){
        cout<<sl.data[i]<<',';
    }
    cout<<";Length:"<<sl.length<<endl;
}

int main()
{
    Sqlist sl;
    int num;

    cout<<"输入一个数: ";
    cin>>num;

    init(sl);

    cout<<"插入前:"<<endl;
    printSqlist(sl);

    if(insert(sl, locate(sl, num), num) == 1)
    {
        cout<<"插入后："<<endl;
        printSqlist(sl);
    }

    return 0;
}
