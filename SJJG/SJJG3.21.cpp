#include<iostream>
using namespace std;
const int MAX=40;

int main(){
    char infix[MAX]={'#'};		// �ַ�����
    char oprator[MAX]={'@','#'};	// ������׺ջ��'@'ջ�� 
    int o=1;
    char postfix[12]={'#'};		// �����׺ջ 
    int p=0;				// '#'�����ж�ɨ��ջ�Ƿ���ɣ�ջ�� 
    int i,j,m=0,n;
    char c;

    cout<<"������ʽ���ԵȺű�ʾ������"<<endl; 
    cin.get(c);		// ������ʽ���ԵȺŽ���
    while(c!='='){		
        infix[m]=c;
        m++;
        cin.get(c);
    }
    n=m;

    for (i=0; i<m; i++) {
        switch(infix[i]) {
        // �����ž�ֱ����ջ
        case '(':
            n=n-2;
            oprator[o]=infix[i];
            o++;
            break;
        //������������ջ��ֱ��������һ��������
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
            //���ǰһ�������Ϊ*��/��������ջ,����ջ,����ֱ����ջ
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
            //�����һ�����������������Ҳ����ջ����������ջ����ջ
            if (oprator[o-1] != '(' && oprator[p-1] != '@') {            
                postfix[p] = oprator[o];
                oprator[o]='#';
            }
            oprator[o] = infix[i];
            o++;
            break;
        default :
            //�����������ֱ�ӽ����׺���ʽ����
            postfix[p] = infix[i];
            p++;
            break;
        }
    }

    //���ɨ����ɣ�����ջ
    for (j = o-1; j>0; j--) {
        if (oprator[j]!='@') {
            postfix[p]=oprator[j];
            oprator[j]='#';
        }
        else
            break;
    }

    //������
    for (i = 0; i<n; i++)
        cout << postfix[i];
    cout << endl;
    
    return 0;
}
