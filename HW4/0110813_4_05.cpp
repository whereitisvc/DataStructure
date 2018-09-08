#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include"0110813_4_04.h"

typedef struct
{
       int num;
       int time;
       
}CALL;
typedef struct
{
       int callNum;
       int arriveTime;
       int startTime;
       int svcTime;
       
}STATUS;
typedef struct
{
       int totCalls;
       int totIdleTime;
       int totWaitTime;
       float avgWaitTime;
       int totSvcTime;
       float avgSvcTime;
       int maxQueue;
       
}STATS;
void newCall( QUEUE* queue, int clock, int* CallNum );
void serverFree( QUEUE* queue, int clock, STATUS* status, STATS* stats, bool* moreCalls, int maxSrvtime );
void svcComplete( QUEUE* queue, int clock, STATUS* status, STATS* stats, bool* moreCalls );
void printStats( STATS* stats );

int main()
{
    int clock = 0, endTime = 120, maxSrvtime = 2;
    int callNum = 0;
    bool moreCalls = true;
    STATUS status;
    STATS runStats;
    QUEUE* queue = createQueue();
    
    status.startTime = 0;
    status.svcTime = 0;
    
    runStats.totCalls = 0;
    runStats.totSvcTime = 0;
    runStats.totWaitTime = 0;
    runStats.maxQueue = 0;
    runStats.totIdleTime = 0;
    
    srand(time(NULL));
    
    maxSrvtime = 2;   
    printf("\n Simulate 2 hours, maxmium srevice time of %d minutes :",maxSrvtime);
    printf("\n Clock   callNum  arriveTime  waitTime  startTime  serviceTime  queueSize ");

    while( clock <= endTime )//|| moreCalls )
    {      //printf("\nclock = %d",clock);
           newCall( queue, clock, &callNum );
           serverFree( queue, clock, &status, &runStats, &moreCalls, maxSrvtime );
           svcComplete( queue, clock, &status, &runStats, &moreCalls );
           
           if( !emptyQueue(queue) )
               moreCalls = true;
           
           clock++;
           
    }    
    printStats( &runStats );
   
    
    
    
    
    status.startTime = 0;
    status.svcTime = 0;
    
    runStats.totCalls = 0;
    runStats.totSvcTime = 0;
    runStats.totWaitTime = 0;
    runStats.maxQueue = 0;
    runStats.totIdleTime = 0;
    
    destroyQueue(queue);
    queue = createQueue();
    moreCalls = true;
    clock = 0;
    callNum = 0;
    
    maxSrvtime = 5;
    printf("\n\n\n Simulate 2 hours, maxmium srevice time of %d minutes :",maxSrvtime);
    printf("\n Clock   callNum  arriveTime  waitTime  startTime  serviceTime  queueSize ");
    while( clock <= endTime )//|| moreCalls )
    {      //printf("\nclock = %d",clock);
           newCall( queue, clock, &callNum );
           serverFree( queue, clock, &status, &runStats, &moreCalls, maxSrvtime );
           svcComplete( queue, clock, &status, &runStats, &moreCalls );
           
           if( !emptyQueue(queue) )
               moreCalls = true;
           
           clock++;
           
    }    
    printStats( &runStats );
    
    
    
    getch();
    return 0;
}

void newCall( QUEUE* queue, int clock, int* callNum )
{
     int r = (rand()%10)+1;
     int constance = 5;  //if maxSrvtime = 5 ,constance = 3 will be more proper 
     CALL* datap; 
     
     if( r <= constance )
     {
         (*callNum)++;
         datap = (CALL*)malloc( sizeof(CALL) );
         datap->num = *callNum;
         datap->time = clock;
         enqueue( queue, datap );
     }
}

void serverFree( QUEUE* queue, int clock, STATUS* status, STATS* stats, bool* moreCalls, int maxSrvtime )
{
     CALL* datap;
     
     if( clock > ( status->startTime + status->svcTime -1 ) )
     {
         if( !emptyQueue(queue) )
         {
             dequeue(queue,(void**)&datap);
             status->callNum = datap->num;
             status->arriveTime = datap->time;
             status->startTime = clock;
             status->svcTime = ( rand()%maxSrvtime )+1; 
             *moreCalls = true;
         }
         else
             stats->totIdleTime++;
     }

}

void svcComplete( QUEUE* queue, int clock, STATUS* status, STATS* stats, bool* moreCalls  )
{
     if( clock == ( status->startTime + status->svcTime -1 ) )
     {
         int waitTime = ( status->startTime - status->arriveTime );
         int size = queueCount(queue);
         
         (stats->totCalls)++;
         stats->totSvcTime += status->svcTime;
         stats->totWaitTime += waitTime; 
         
         if( stats->maxQueue < size )
             stats->maxQueue = size;
         
         *moreCalls = false;

         printf("\n| %4d  %8d  %10d  %8d  %9d  %10d  %10d  ", clock, status->callNum, status->arriveTime,
                                                           waitTime, status->startTime, status->svcTime, size);
                
     }
}
void printStats( STATS* stats )
{
     stats->avgWaitTime = (float)stats->totWaitTime / stats->totCalls;
     stats->avgSvcTime = (float)stats->totSvcTime / stats->totCalls;
     //printf("\n\n STATS : ");
     printf("\n\n Total Calls = %2d",stats->totCalls);
     printf("\n Total IdleTime = %2d",stats->totIdleTime);
     printf("\n Total WaitTime = %2d",stats->totWaitTime);
     printf("\n Total ServiceTime = %2d",stats->totSvcTime);
     printf("\n Average WaitTime = %f",stats->avgWaitTime);
     printf("\n Average ServiceTime = %f",stats->avgSvcTime);
     printf("\n Maximum QueueSize = %2d",stats->maxQueue);
     
     
}
