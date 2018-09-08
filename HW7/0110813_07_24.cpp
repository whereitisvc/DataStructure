#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include"0110813_07_24.h" 
/*
      "0110813_07_24.h" was a BST ADT, and I edit some function which let BST ADT becomes a Threaded-BST ADT.
      edit the difinetion of NODE --> add int isthread variable;
      edit function BST_Insert
      edit function _insert
      edit function BST_treversal;
*/

typedef struct
{
        char c;
        int w;
}DATA;
int compare( void* p1 ,void* p2 )// compare NODE by DATA.w(weight)
{
    DATA a = *(DATA*)p1;
    DATA b = *(DATA*)p2;
    if( a.w > b.w ) return 1;
    if( a.w == b.w ) return 0;
    if( a.w < b.w ) return -1;
}
void process( void* p )
{
     printf("%c", ((DATA*)p)->c);
}

int main()
{
    char list[10] = "ABCDEFGHI";
    int  weight[9] = { 5,3,7,1,4,6,8,0,2 };
    DATA* datap;
    BST_TREE* tree = BST_Create(compare);
    
    for(int i=0;i<9;i++)
    {
            datap = (DATA*)malloc(sizeof(DATA));
            datap->c = list[i];
            datap->w = weight[i];
            //printf("\n%c, %d", datap->c, datap->w);
            BST_Insert(tree, datap);
            
    }
    printf("\n");
    BST_Traverse(tree,process);   
    
    getch();
    return 0;
}
