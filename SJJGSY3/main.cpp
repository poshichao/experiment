#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;
#define MAX  100        // 定义字符的最大数量
int n;

// 哈夫曼树
typedef struct {
    int weight;                     // 权重
    int parent, lchild, rchild;     // 根节点；左孩子；右孩子
    char word;                      // 字符
}HTNode, *HuffmanTree;

typedef char **HuffmanCode;     // 动态分配数组存储哈夫曼编码表

/**
 * 求最小值
 * @param HT 哈夫曼树
 * @param k  循环变量i
 * @return   最小数的位置
 */
int min(HuffmanTree &HT,int k) {
    int i = 0;
    int min;        // 用来存放weight最小且parent为0的元素的序号
    int min_weight; // 用来存放weight最小且parent为0的元素的weight值

    //先将第一个parent为0的元素的weight值赋给min_weight,留作以后比较用。
    while(HT[i].parent != 0)
        i++;
    min_weight = HT[i].weight;
    min = i;

    //选出weight最小且parent为0的元素，并将其序号赋给min
    for(;i<k;i++) {
        if(HT[i].weight < min_weight && HT[i].parent == 0) {
            min_weight = HT[i].weight;
            min = i;
        }
    }

    HT[min].parent = 1;         // 选出weight最小的元素后，将其parent置1，使得下一次比较时将其排除在外。

    return min;
}

/**
 * 选取最小的两个节点
 * @param HT    哈夫曼树
 * @param k     循环数i
 * @param min1  最小数
 * @param min2  最小数
 */
void selectMinium(HuffmanTree &HT,int k,int &min1,int &min2) {
    min1 = min(HT, k);
    min2 = min(HT, k);
}

/**
 * 初始化哈夫曼树
 * @param HT 哈夫曼树
 * @param w 权重
 * @param n 字符数
 * @param wo 字符
 */
void InitHuffman(HuffmanTree &HT, int *w, int n, char *wo) {
    if (n <= 1)
        return;

    int m = 2*n -1;             // 节点数，为叶子数（n）的二倍减一
    HuffmanTree p;              // 辅助哈夫曼树
    int i;                      // 循环控制量
    HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));   // 0号单元不使用

    // 初始化哈夫曼树
    for (p = HT, i = 0; i < n; ++i, ++p, ++w, ++wo)
        *p = {*w, 0, 0, 0, *wo};
    for(; i < m; ++i, ++p)
        *p = {0, 0, 0, 0, 0};

    // 建立哈夫曼树
    for(i = n; i < m; ++i) {
        // 在HT[0...i-1]选择parent为0且weight最小的两个节点，其序号分别为m1和m2
        int m1, m2;
        m1 = m2 = 0;
        selectMinium(HT,i,m1,m2);

        HT[m1].parent = i;
        HT[m2].parent = i;
        HT[i].lchild = m1;
        HT[i].rchild = m2;
        HT[i].weight = HT[m1].weight + HT[m2].weight;
    }

    // 将哈夫曼树存入文件中
    ofstream file;
    file.open("hfmTree.txt");       // 打开文件
    for (int i = 0; i < m; i++) {   // 写入文件
        file<<HT[i].weight<<' ';
        if (i%5 == 4)               // 每行5个
            file<<endl;
    }
    file.close();                   // 关闭文件

}

/**
 * 打印哈夫曼树
 * @param HT 要打印的哈夫曼树
 * @param n 叶子节点数
 */
void printHuffTree(HuffmanTree &HT, int n) {
    cout<<"哈夫曼树为："<<endl;
    ofstream outfile;
    outfile.open("treePrint.txt");

    // 文件打开错误
    if (!outfile) {
        cerr<<"不能打开文件: "<<"treePrint.txt"<<endl;
        exit(-1);
    }

    int m = 2 * n -1;           // 节点数

    // 按序将文件中的内容进行输出
    for (int i = 0; i < m; i++) {
        cout<<"节点"<<i + 1<<"的权重："<<HT[i].weight<<' '<<"父节点的位置："<<HT[i].parent<<' '<<"左孩子的位置："<<HT[i].lchild<<' '<<"右孩子的位置："<<HT[i].rchild<<endl;

        // 非叶子结点的字符用其权重代替
        if (!(HT[i].rchild == 0 && HT[i].lchild == 0))
            outfile<<HT[i].weight<<" ";
        else
            outfile<<HT[i].word<<" ";
        outfile<<HT[i].weight<<" "<<HT[i].parent<<" "<<HT[i].lchild<<" "<<HT[i].rchild<<endl;
    }

    cout<<"哈夫曼树已经存入文件中"<<endl;
    outfile.close();        // 关闭文件
}

/**
 * 编码
 * @param HT 哈夫曼树
 * @param HC 哈夫曼编码表
 * @param n  字符数
 * @param wo 将编码的字符
 */
void encodingHuff(HuffmanTree &HT, HuffmanCode &HC, int num, char wo[]) {
    HC = new char*[n + 1];          // 分配储存n个字符编码的编码表空间
    char *cd = new char[n];         // 分配临时存储字符编码的动态空间
    cd[n - 1] = '\0';               // 编码结束符

    // 逐个求字符编码
    for (int i = 0; i < n; i++) {
        int start = n - 1;          // start 开始指向最后，即编码结束符位置
        int c = i;
        int f = HT[c].parent;       // f指向结点c的双亲

        // 从叶子结点开始回溯，直到根结点
        while (f != 0) {
            --start;                // 回溯一次，start向前指向一个位置
            if (HT[f].lchild == c)
                cd[start] = '0';    // 结点c是f的左孩子，则cd[start] = 0;
            else
                cd[start] = '1';    // 否则c是f的右孩子，cd[start] = 1
            c = f;
            f = HT[f].parent;       // 继续向上回溯
        }

        HC[i] = new char[n - start];// 为第i个字符编码分配空间
        strcpy(HC[i], &cd[start]);  // 把求得编码的首地址从cd[start]复制到HC的当前行中
    }

    delete cd;                      // 释放空间

    // 将编码结果存入文件
    ofstream file;
    file.open("codeFile.txt");
    for (int i = 0; i < n; i++) {
        file<<HC[i];                // 紧凑格式
    }
    file.close();
}

/**
 * 译码
 * @param HT 哈夫曼树
 * @param a  要译的编码
 * @param zf 字符
 * @param b  译码结果
 * @param n  字符数
 */
void decoding(HuffmanTree &HT, char a[],char zf[],char b[],int n) {
    int q = 2*n-2;          // q初始化为根结点的下标
    int k = 0;              // 记录存储译出字符数组的下标
    int i = 0;
    for (i = 0; a[i] != '\0';i++) {     // for循环结束条件是读入的字符是结束符（二进制编码）

        // 判断读入的二进制字符是0还是1
        if (a[i] == '0') {              // 读入0，把根结点(HT[q])的左孩子的下标值赋给q,下次循环的时候把HT[q]的左孩子作为新的根结点
            q = HT[q].lchild;
        } else if (a[i] == '1') {
            q = HT[q].rchild;
        }

        // 判断HT[q]是否为叶子结点
        if (HT[q].lchild == 0 && HT[q].rchild == 0) {   // 是叶子结点，说明已经译出一个字符该字符的下标就是找到的叶子结点的下标
            b[k++] = zf[q];                             // 把下标为q的字符赋给字符数组b[]
            q = 2 * n - 2;                              // 初始化q为根结点的下标,继续译下一个字符的时候从哈夫曼树的根结点开始
        }
    }

    b[k] = '\0';            // 将结束符添加到末尾

    // 将译码结果存入文件
    ofstream file;
    file.open("textFile.txt");
    for (int i = 0; i < n; i++) {
        file<<b[i];
    }
    file.close();

}

/**
 * 打印代码文件
 * @param HC 编码
 */
void print(HuffmanCode &HC) {
    ifstream outfile;
    outfile.open("codeFile.txt");
    string str;                 // 用来存放从文件中取出的内容,以便再次存入文件

    // 将文件中的内容取出,然后放入到字符串中进行输出
    while( outfile >> str ) {
        cout << "编码后的代码是: " << str << endl;
    }

    outfile.close();        // 关闭文件

    // 将输出的内容存入文件
    ofstream infile;
    infile.open("codePrint.txt");
    infile << str;
    infile.close();
}

/**
 * 测试主函数
 * @return
 */
int main() {
    char com, word[26], chin[MAX], chout[MAX];     // 指令, 字符, 译码代码
    int weight[26];         // 权值
    HuffmanTree HT;         // 哈夫曼树
    HuffmanCode HC;         // 哈夫曼编码表

    // 菜单循环打印,知道用户输入退出指令
    do {
        cout<<"请输入指令： (I：初始化哈夫曼树 E：编码 D：译码 P：打印代码文件 T：打印哈夫曼树 Q：退出)";
        cin>>com;

        // 根据指令来判断应该执行的操作
        switch(com){

            // 创建哈夫曼树
            case 'I':
                cout<<"输入字符集的长度：";
                cin>>n;
                for (int i = 0; i < n; i++) {
                    cout<<"输入第"<<i + 1<<"个字符以及其对应的权值：";
                    cin>>word[i]>>weight[i];
                }
                InitHuffman(HT, weight, n, word);
                break;

            // 编码
            case 'E':
                encodingHuff(HT, HC, n, word);
                cout<<"编码完成!"<<endl;
                break;

            // 译码
            case 'D':
                cout<<"译码";
                cout<<"输入要译码的代号:";
                for (int i = 0; i < 1; i++) {
                    cin>>chin;
                }
                decoding(HT, chin, word, chout, n); //调用译码的函数
                cout<<"译码结果为: "<<chout<<endl;
                break;

            // 打印编码结果
            case 'P':
                print(HC);
                break;

            // 打印哈夫曼树
            case 'T':
                printHuffTree(HT, n);
                break;

            // 退出循化
            case 'Q':
                cout<<"感谢使用!";
                break;

            // 错误指令处理
            default:
                cout<<"输入指令错误！请重新输入.";
                break;
        }

    } while(com != 'Q');
    return 0;
}