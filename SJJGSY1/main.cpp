#include<iostream>
int num;	// 总人数
int m;		// m值
using namespace std;

//结点类
class JLink {
public:
    int password;
    int number;
    JLink *next;
};

// 单向循环链表类
class CircularLinkList {

public:

    // 首元节点
    JLink *head;
    // 构造函数
    CircularLinkList() {
        head = new JLink;
        head->password = 0;
        head->number = 0;
        head->next = head;
    }

    ~CircularLinkList() {
        delete head;
    }

    void createLinkList(int n);                 //创建单向循环链表
    bool IsEmpty();                             //判断链表是否为空
    JLink* findNode(int position, JLink *jtemp);          // 查找节点位置
    JLink* deleteNode(JLink *jtemp);            //删除指定位置结点
};

// 创建单向循环链表
void CircularLinkList::createLinkList(int n) {
    if (n < 0) {
        cout<<"输入节点数错误！"<<endl;
    }
    else {
        JLink *jnew, *jtemp = head;

        // 输入第一个节点
        cout << "第" << 1 << "个结点值：";
//        cin>>head->password;            // 手动输入新节点密码
        head->password = (rand() % (1000-0+1))+ 0;  // 随机生成新节点的密码
        head->number = 1;   // 新节点的编号
        head->next = head;      // 将新节点指向下一节点
        n--;
        cout<<head->password<<endl;

        int i = n;
        while (n-- > 0) {
            cout << "第" << i - n + 1<< "个结点值：";
            jnew = new JLink;
//            cin>>jnew->password;            // 手动生成新节点密码
            jnew->password = (rand() % (1000-0+1))+ 0;  // 随机生成新节点的密码
            jnew->number = i - n + 1;   // 新节点的编号
            jnew->next = head;      // 将新节点指向下一节点
            jtemp->next = jnew;
            jtemp = jnew;
            cout<<jnew->password<<endl;
        }
    }
}

// 查找
JLink* CircularLinkList::findNode(int position, JLink *jtemp) {
    while (position-- > 2)
        jtemp = jtemp->next;
    return jtemp;
}

// 删除
JLink* CircularLinkList::deleteNode(JLink *jtemp) {

    JLink *jdelete;

    jdelete = jtemp->next;
    cout<<jdelete->number<<' ';
    m = jdelete->password;
    num--;
    jtemp->next = jdelete->next;
    delete jdelete;
    jdelete = NULL;
    return jtemp->next;
}

// 判空
bool CircularLinkList::IsEmpty() {
    if (num > 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    CircularLinkList JO;    // 单向循环链表对象
    cout<<"请输入总人数(建议人数小于30)：";
    cin>>num;
    JO.createLinkList(num);
    cout<<"m的初始值：";
//    cin>>m;         // 手动为m赋初值
    m = (rand() % (1000-0+1))+ 0;       // 随机生成m初值
    cout<<m<<endl;
    JLink *jtemp = JO.head;
    cout<<"输出序列为：";
    while (JO.IsEmpty() == true) {
        jtemp = JO.findNode(m, jtemp);
        jtemp = JO.deleteNode(jtemp);
    }

   return 0;
}
