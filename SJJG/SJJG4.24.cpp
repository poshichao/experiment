#include<iostream> 
#include<stdlib.h>
using namespace std; 
#define OVERFLOW   -2//堆溢出 
#define OK          1//函数执行成功 
#define ERROR      -1//函数执行失败 
typedef int datatype; 
typedef struct{ 
    char*  ch;//指针域，指向存放串值的存储空间基址 
    int len;// 整型域：存放串长 
}HString; 
//初始化一个空串 
datatype InitHString(HString* s) 
{ 
    s->ch=(char*)malloc(sizeof(char));
	 
    if(NULL==s->ch) 
		return OVERFLOW;
		
    s->ch=NULL; 
    s->len=0; 
    return OK; 
} 
//为串赋值 
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
//打印 
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

//串的连接 
datatype HSCat(HString* s,const HString* t) 
{ 
    int i=0; 
    char*  temp=(char*)malloc((s->len+t->len)*sizeof(char)); 
    if(!temp) 
		return  OVERFLOW; 
    for(i=0;i<s->len;i++) 
        *(temp+i)=*(s->ch+i); 
    free(s->ch);		//释放防止内存泄漏 
    for(i=0;i<t->len;i++) 
        *(temp+i+s->len)=*(t->ch+i); 
    s->len+=t->len; 
    s->ch=temp;			//使s->ch重新指向temp 
    *(s->ch+s->len)='\0';       
    return OK; 
} 
int main() 
{ 
    // 建立串 
    HString S; 
    InitHString(&S); 
    assigment_string(&S,"hello world!"); 
    PrintString(&S);  
 
    // 连接串 
    HString S3; 
    InitHString(&S3); 
    assigment_string(&S3,"////"); 
    HSCat(&S,&S3); 
    PrintString(&S); 
    free(S3.ch); 
    free(S.ch); 
   
    return 0; 
}
