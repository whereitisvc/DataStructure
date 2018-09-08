#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"0110813_05_29.h"

typedef struct
{
       int coef;
       int exp;
       
}POLY;

int compare( void* p1 ,void* p2 )//compare two integer
{
    if( ((POLY*)p1)->exp < ((POLY*)p2)->exp ) return -1;
    else if( ((POLY*)p1)->exp > ((POLY*)p2)->exp ) return 1;
    else return 0;
}

int main()
{
    LIST* list1  = createList( compare );
    LIST* list2 = createList( compare );
    POLY* poly = (POLY*)malloc( sizeof(POLY) );
    FILE* fp;
    
    ////////////////////////////////////////////////////////////////// read file
    fp = fopen("5-29 read files/HW5_29_p1.txt","r");
    while( fscanf(fp,"%d %d", &(poly->coef),&(poly->exp)  ) != EOF )
    {
           addNode( list1,poly );
           poly = (POLY*)malloc( sizeof(POLY) );
    }
    fp = fopen("5-29 read files/HW5_29_p2.txt","r");
    while( fscanf(fp,"%d %d", &(poly->coef),&(poly->exp)  ) != EOF )
    {
           addNode( list2,poly );
           poly = (POLY*)malloc( sizeof(POLY) );
    }
    
    ////////////////////////////////////////////////////////////////// print list1&2
    printf("list1 :");
    traverse( list1, 0, (void**)&poly );
    printf(" %2dx^%d ", poly->coef, poly->exp);
    while(traverse( list1, 1, (void**)&poly ))
            printf("+ %2dx^%d ", poly->coef, poly->exp);
            
    printf("\nlist2 :");
    traverse( list2, 0, (void**)&poly );
    printf(" %2dx^%d ", poly->coef, poly->exp);
    while(traverse( list2, 1, (void**)&poly ))
            printf("+ %2dx^%d ", poly->coef, poly->exp);
    
    ////////////////////////////////////////////////////////////////// add two list        
    LIST* sumlist = createList( compare );
    POLY* poly2;
    POLY* sum = (POLY*)malloc( sizeof(POLY) );
    traverse( list1, 0, (void**)&poly );
    do
    {
         if( searchList( list2, poly, (void**)&poly2 ) ) //found 
         {
             sum->coef = poly->coef + poly2->coef;
             sum->exp = poly->exp;
             if( sum->coef != 0 )  
             {
                 addNode( sumlist, sum );
                 sum = (POLY*)malloc( sizeof(POLY) );
             }
         }
         else
         {
             sum->coef = poly->coef;
             sum->exp = poly->exp;
             addNode( sumlist, sum );
             sum = (POLY*)malloc( sizeof(POLY) );
         }
              
    }while( traverse( list1, 1, (void**)&poly ) );
    
    traverse( list2, 0, (void**)&poly );
    do
    {
          if( !searchList( list1, poly, (void**)&poly2 ) )
         {
             sum->coef = poly->coef;
             sum->exp = poly->exp;
             addNode( sumlist, sum );
             sum = (POLY*)malloc( sizeof(POLY) );
         }
              
    }while( traverse( list2, 1, (void**)&poly ) );
    
    ////////////////////////////////////////////////////////////////// print sumlist
    printf("\nsum   :");
    sum = (POLY*)malloc( sizeof(POLY) );
    traverse( sumlist, 0, (void**)&sum );
    printf(" %2dx^%d ", sum->coef, sum->exp);
    while(traverse( sumlist, 1, (void**)&sum ))
            printf("+ %2dx^%d ", sum->coef, sum->exp);
            
    
    fclose(fp);
    free(poly);
    free(sum);
    destroyList(list1);
    destroyList(list2);
    destroyList(sumlist);
    
    getch();
    return 0;
}
