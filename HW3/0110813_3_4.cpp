#include <conio.h>
#include <stdio.h>
#include "0110813_3_4.h"
int main()
{
    int list[25] = { 1,2,3,4,5, -1,1,2,3,4, 5,6,7,8,9, 10,-2,11,12,-3, 1,2,3,4,5 };
    int* datap;
    int* pop;
    STACK* stack = createStack();
    //if( !createStack() ) printf("cannot creat stack.\n");
    
    for(int i=0;i<25;i++)
    {
            printf("%2d --> ",list[i]);
            datap = (int*) malloc( sizeof (int));
            *datap = list[i];          
            if( *datap >= 0 )
            {                      
                printf("push %2d",*datap);
                pushStack(stack,datap);
            }
            else if( *datap<0 )
            {                       
                 if( stackCount(stack)>=5 )
                 {   
                     printf("pop ");
                     for(int j=0;j<5;j++)
                     {       
                             pop = (int*)popStack(stack);
                             printf("%2d ",*pop);
                     }
                 }
                 else 
                 {
                      printf("stackCount less than 5,end program\n");
                      break;
                 }     
            }
            printf("\n");           
    }
                              
    destroyStack(stack);
    
    getch();
    return 0;
}
