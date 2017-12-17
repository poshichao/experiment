#include<iostream> 
#include<stdlib.h>
using namespace std; 
#define OVERFLOW   -2//����� 
#define OK          1//����ִ�гɹ� 
#define ERROR      -1//����ִ��ʧ�� 
typedef int datatype; 
typedef struct{ 
    char*  ch;//ָ����ָ���Ŵ�ֵ�Ĵ洢�ռ��ַ 
    int len;// �����򣺴�Ŵ��� 
}HString; 
//��ʼ��һ���մ� 
datatype InitHString(HString* s) 
{ 
    s->ch=(char*)malloc(sizeof(char));
	 
    if(NULL==s->ch) 
		return OVERFLOW;
		
    s->ch=NULL; 
    s->len=0; 
    return OK; 
} 
//Ϊ����ֵ 
datatype assigment_string(HString* s, const char* str) 
{ 
    if(s->ch) 
		free(s->ch);
		 
    int  length=0,i;
    
    while(str[length]!='\0') 
        length++;
        
    s->ch=(char*)malloc(length*sizeof(char));
    if(!s->ch) 
		return OVERFLOW;
		 
    for(i=0;i<length;i++) 
        *(s->ch+i)=*(str+i); 
    s->len=length; 
    *(s->ch+s->len)='\0'; 
    return OK; 
} 
//��ӡ 
void PrintString(const HString* s) 
{ 
    int i=0; 
    while(*(s->ch+i)!='\0') 
    { 
        printf("%c",*(s->ch+i)); 
        i++; 
    } 
    printf("\n"); 
}

//�������� 
datatype HSCat(HString* s,const HString* t) 
{ 
    int i=0; 
    char*  temp=(char*)malloc((s->len+t->len)*sizeof(char)); 
    if(!temp) 
		return  OVERFLOW; 
    for(i=0;i<s->len;i++) 
        *(temp+i)=*(s->ch+i); 
    free(s->ch);		//�ͷŷ�ֹ�ڴ�й© 
    for(i=0;i<t->len;i++) 
        *(temp+i+s->len)=*(t->ch+i); 
    s->len+=t->len; 
    s->ch=temp;			//ʹs->ch����ָ��temp 
    *(s->ch+s->len)='\0';       
    return OK; 
} 
int main() 
{ 
    // ������ 
    HString S; 
    InitHString(&S); 
    assigment_string(&S,"hello world!"); 
    PrintString(&S);  
 
    // ���Ӵ� 
    HString S3; 
    InitHString(&S3); 
    assigment_string(&S3,"////"); 
    HSCat(&S,&S3); 
    PrintString(&S); 
    free(S3.ch); 
    free(S.ch); 
   
    return 0; 
}
