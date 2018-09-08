#include<stdio.h>
#include<conio.h>
#include"0110813_4_04.h"

QUEUE* scanQueue( QUEUE* queue );
QUEUE* printQueue( QUEUE* queue );
QUEUE* checkQueueop( QUEUE* queue ,bool* claer );

int main()
{
    char c;
    char* cp;
    int*  np;
    char* datap;
    FILE *fp;
    QUEUE* queue = createQueue(); 
    bool opclear = false;
    
    fp = fopen("HW4_20.txt","r");
    while( fscanf(fp,"%c",&c) != EOF )
    {    
         cp = (char*)malloc(sizeof(char));  *cp = c;
        if( c=='+' || c=='-' || c=='*' || c=='/' )  //operator
            enqueue(queue,cp);
    
        else //number
        {   
            np = (int*)malloc(sizeof(int));
            *np = (int)(*cp) - (int)'0';  
            enqueue(queue,np);  
        }
    }
    queue = printQueue( queue );
    printf("\n");
    
    while( !opclear )
    {
           queue = scanQueue( queue );
           queue = printQueue( queue );
           printf("\n");
           
           queue = checkQueueop( queue, &opclear );
    }
    
    getch();
    return 0;
}

QUEUE* scanQueue( QUEUE* queue )
{
     QUEUE* new_queue = createQueue();
     QUEUE* tri_queue = createQueue();
     char* datacp;
     int*  datanp;
     char  op;
     bool  check = false;
     int   count = 0,num[2],x;
     
     while( !emptyQueue(queue) )
     {
           if( queueCount(tri_queue)==3 )
            {
                    dequeue( tri_queue,(void**)&datacp );     
                    enqueue( new_queue,datacp );
            }           
            
            dequeue( queue,(void**)&datacp ); 
            
            if( *datacp=='+' || *datacp=='-' || *datacp=='*' || *datacp=='/' )  //operator
            { 
                op = *datacp;  count = 0; check = true; 
                enqueue( tri_queue,datacp );              
            }
            else //number
            {
                  datanp = (int*)datacp;
                  num[count] = *datanp; 
               
                  count++;                                                
                  if( check && count==2 )
                  {
                            if( op=='+' )x = num[0] + num[1]; 
                            if( op=='-' )x = num[0] - num[1];
                            if( op=='*' )x = num[0] * num[1];
                            if( op=='/' )x = num[0] / num[1];

                            destroyQueue( tri_queue );
                            tri_queue = createQueue();
                            *datanp = x;
                            check = false; count = 0;
                   }
                  
                  enqueue( tri_queue,datanp );            
            }
            
            
            if( emptyQueue(queue) )  //dequeue last data in tri_queue
            {
                while( !emptyQueue(tri_queue) )
                {
                       dequeue( tri_queue,(void**)&datacp ); 
                       enqueue( new_queue,datacp );
                }
            }
            
     }     
     
     return new_queue;    
}

QUEUE* printQueue( QUEUE* queue )
{
     QUEUE* trans = createQueue();
     char* datap;
     while( !emptyQueue(queue) )
     {
         dequeue( queue,(void**)&datap );
         if( *datap=='+' || *datap=='-' || *datap=='*' || *datap=='/' ) //operator
             printf("%c ",*(char*)datap);
         else   //number
             printf("%d ",*(int*)datap);
         enqueue( trans,datap );
     }
     return trans;
}
QUEUE* checkQueueop( QUEUE* queue ,bool* clear )
{
     QUEUE* trans = createQueue();
     char* datap;
     *clear = true;
     while( !emptyQueue(queue) )
     {
         dequeue( queue,(void**)&datap );
         if( *datap=='+' || *datap=='-' || *datap=='*' || *datap=='/' ) //operator
            *clear = false;
         enqueue( trans,datap );
     }
     
     return trans;
}
