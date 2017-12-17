#include<iostream>
using namespace std;
const int MAX=40;

int main(){
    char infix[MAX]={'#'};		// 字符数组
    char oprator[MAX]={'@','#'};	// 代表中缀栈，'@'栈顶 
    int o=1;
    char postfix[12]={'#'};		// 代表后缀栈 
    int p=0;				// '#'用于判断扫描栈是否完成，栈底 
    int i,j,m=0,n;
    char c;

    cout<<"输入表达式，以等号表示结束："<<endl; 
    cin.get(c);		// 输入表达式，以等号结束
    while(c!='='){		
        infix[m]=c;
        m++;
        cin.get(c);
    }
    n=m;

    for (i=0; i<m; i++) {
        switch(infix[i]) {
        // 左括号就直接入栈
        case '(':
            n=n-2;
            oprator[o]=infix[i];
            o++;
            break;
        //右括号则先退栈，直到遇见第一个左括号
        case ')':
            for (j = o-1; j>0; j--) {
                if (oprator[j]!='(') {
                    postfix[p]=oprator[j];
                    oprator[j]='#';
                    p++;
                }
                else {
                    oprator[j] = '#';
                    break;
                }
            }
            o=j;
            break;
        case '*':
        case '/':
            //如果前一个运算符为*或/，则先退栈,再入栈,否则直接入栈
            if (oprator[o] == '*' || oprator[o] == '/') {
                postfix[p] = oprator[o];
                oprator[o]='#';
                p++;
            }
            oprator[o] = infix[i];
            o++;
            break;
        case '+' :
        case '-' :
            //如果上一个运算符不是左括号也不是栈顶，则先退栈再入栈
            if (oprator[o-1] != '(' && oprator[p-1] != '@') {            
                postfix[p] = oprator[o];
                oprator[o]='#';
            }
            oprator[o] = infix[i];
            o++;
            break;
        default :
            //如果是数字则直接进入后缀表达式数组
            postfix[p] = infix[i];
            p++;
            break;
        }
    }

    //如果扫描完成，则退栈
    for (j = o-1; j>0; j--) {
        if (oprator[j]!='@') {
            postfix[p]=oprator[j];
            oprator[j]='#';
        }
        else
            break;
    }

    //输出结果
    for (i = 0; i<n; i++)
        cout << postfix[i];
    cout << endl;
    
    return 0;
}
