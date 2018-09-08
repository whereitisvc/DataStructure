#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "0110813_09_33.h"

typedef struct data
{
        char name[100];
        int priority;
}DATA;

int compare( void* p1, void* p2  )
{
    int x1,x2;
    x1 = ((DATA*)p1)->priority;
    x2 = ((DATA*)p2)->priority;
    
    if(x1>x2) return 1;
    else if(x1==x2) return 0;
    else return -1;
}

int main()
{
    char name1[50],name2[50];
    int A,B,C;
    DATA* datap;
    HEAP* heap = heapCreate(100,compare);
    FILE* fp;
    
    /////////////////////////////////////////////////////////////////////////// build heap
    fp = fopen("9_33.txt","r");
    while( fscanf( fp,"%s %s %d %d %d", &name1, &name2, &A, &B, &C ) != EOF )
    {
           strcat(name1," ");
           strcat(name1,name2);
           printf("%-20s %-5d %d %2d -->  ",name1,A,B,C);
           datap = (DATA*)malloc( sizeof(DATA) );
           strcpy( datap->name, name1 );
           datap->priority = A/1000+B-C;
           heapInsert(heap, datap);
           printf("%d\n", datap->priority);
    }
    
    ////////////////////////////////////////////////////////////////////////// heap sort
    int last = heap->last;
    int count = 1;
    printf("\n\n");
    while( last > 0 )
    { 
           datap = (DATA*)(heap->heapAry[0]);
           printf("%2d. %-20s    %d\n",count, datap->name, datap->priority);
           
           last = heap->last;
           heap->heapAry[0] = (DATA*)(heap->heapAry[last]);
           heap->heapAry[last] = datap;
           heap->last--;
           _reheapDown (heap, 0);
           count++;
    }
    
    
    getch();
    return 0;
}
