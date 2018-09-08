#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"largerADT.h"

int compare( void* ,void* );

int main()
{
    char a[] = "aaabaaaa";
    char b[] = "aaab";
    char* c;
    
    c = ( (char*)larger(a,b,compare) );            
    if( c == NULL )printf("a = %s ,b = %s ,same string.",a,b); 
    else printf("a = %s ,b = %s ,Larger = %s",a,b,c);
    
    getch();
    return 0;
}
int compare( void* p1 ,void* p2 )//compare two string
{
    return strcmp( (char*)p1 ,(char*)p2 );
}

