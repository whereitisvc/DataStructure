#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"0110813_05_36.h"

typedef struct
{
        char place[50];
        char ppula[20];
        
}DATA;

void printOut( LIST* list20, LIST* list19 );

int main()
{
    FILE* fp;
    LIST* list20 = createList();
    LIST* list19 = createList();
    DATA* datap;
    char place[50];
    char year20[20];
    char year19[20];
    
    fp = fopen("5-36 read files/HW5_36.txt","r");
    while( fscanf( fp,"%s %s %s",place,year20,year19 ) != EOF )
    {  
           //printf("\n%s,  %s,  %s",place,year20,year19);
           datap = (DATA*)malloc( sizeof(DATA) );
           strcpy( datap->place, place );
           strcpy( datap->ppula, year19 ); 
           addNode( list19, datap );
           
           datap = (DATA*)malloc( sizeof(DATA) );
           strcpy( datap->place, place );
           strcpy( datap->ppula, year20 ); 
           addNode( list20, datap );
    }
    
    printOut( list20, list19 );
    
    fclose(fp);
    
    getch();
    return 0;
}

void printOut( LIST* list20, LIST* list19 )
{
    DATA* datap1;
    DATA* datap2;
    int count = 1;
    
    printf("\n  Censes Data for 1990              |  Population  "); 
    printf("\n-------------------------------------------------");
    traverse( list19, 0, (void**)&datap1 );//start from first node
    do
    {
              printf("\n %2d %-31s |  %-10s  ",count, datap1->place, datap1->ppula );
              count++;
              
    }while( traverse( list19, 1, (void**)&datap1 ) );
    retraverse( list19, 0, (void**)&datap1 );//start end first node
    do
    {
              count--;
              printf("\n %2d %-31s |  %-10s  ",count, datap1->place, datap1->ppula );
              
    }while( retraverse( list19, 1, (void**)&datap1 ) );
    
    
    printf("\n\n\n  Censes Data for 2000              |  Population  "); 
    printf("\n-------------------------------------------------");
    traverse( list20, 0, (void**)&datap2 );//start from first node
    do
    {
              printf("\n %2d %-31s |  %-10s  ",count, datap2->place, datap2->ppula );
              count++;
              
    }while( traverse( list20, 1, (void**)&datap2 ) );
    retraverse( list20, 0, (void**)&datap2 );//start end first node
    do
    {
              count--;
              printf("\n %2d %-31s |  %-10s  ",count, datap2->place, datap2->ppula );
              
    }while( retraverse( list20, 1, (void**)&datap2 ) );
            
}
