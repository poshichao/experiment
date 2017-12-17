#include<iostream>
#define maxSize 50
using namespace std;
typedef struct{    // ˳���Ķ���
    int data[maxSize];		// ���� 
    int length;				// �� 
}Sqlist;

void init(Sqlist &sl)    // ��ʼ��˳���
{
    int len=10;

    for(int i=1; i<=len; ++i)
    {
        sl.data[i]=i*3-2;
    }
    sl.length = len;
}

int locate(Sqlist sl, int num)    // �ҵ�ǡ���Ĳ���λ��
{
    int i=1;
    for(; i<=sl.length; ++i)	// �Ƚϲ������ͱ�������С 
    {
        if(sl.data[i]>num)
        {
            return i;   // ����λ�� 
        }
    }
    return i;   // Ŀǰ˳���û��ֵ�� num �󣬷�������±�
}

int insert(Sqlist &sl, int loc, int num)    // ��˳��� sl �� loc λ�ò���ֵΪ num ��Ԫ��
{
    int i=sl.length;

    if(loc<1 || loc>sl.length+1){   // �Ϸ���λ��Ӧ���� 1~sl.length+1 ֮��
        return 0;
    }

    for(;i>=loc;i--){				// �Ӻ���ǰ�ƣ���֤���ݲ������
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

    cout<<"����һ����: ";
    cin>>num;

    init(sl);

    cout<<"����ǰ:"<<endl;
    printSqlist(sl);

    if(insert(sl, locate(sl, num), num) == 1)
    {
        cout<<"�����"<<endl;
        printSqlist(sl);
    }

    return 0;
}
