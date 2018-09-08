/*
    Application of queue: phone call
    Written by: 01107003 ´¿­§­× 
    Date: 2014/10/31
*/
#include<stdio.h>
#include<stdbool.h>
#include<iostream>
#include<time.h>
//#include "0110703_4_22.h"
#include"0110813_4_04.h"

using namespace std;

typedef struct data
{
    int custNum;
    int totSvcTime;
    int totWaitTime;
    int maxQueueSize;
    
    int arrivalTime;
    int startTime;
    int svcTime;
    int waitTime;
    
    
}PHONE;


PHONE* constructPhone();
void newCustomer(QUEUE*,int,int,int);
void serverFree(QUEUE*,int,PHONE*,bool);
void svcComplete(QUEUE*,int,PHONE*,PHONE*,bool);
void printStats(PHONE*);
void start(int,int);

int main()
{
    int maxtime;
    int maxservicetime;
    
    cout<<"Input the length of time:";
    cin>>maxtime;
    cout<<"Input the max service time:";
    cin>>maxservicetime;
    
    start(maxtime,maxservicetime);
    
    
    system("pause");
    return 0;
}

void start(int maxtime,int maxservicetime)
{
    QUEUE* queue;
    PHONE* custStatus;
    PHONE* runStats;
    int clock=1;
    bool moreCusts=false;
    
    //initialize
    queue=createQueue();
    custStatus=constructPhone();
    runStats=constructPhone();
    
    //timing loop
    while(clock<=maxtime || moreCusts)
    {
        //call simulator
        newCustomer(queue,clock,custStatus->custNum,maxservicetime);
        //process active call
        serverFree(queue,clock,custStatus,moreCusts);
        //start new call
        svcComplete(queue,clock,custStatus,runStats,moreCusts);
        
        if(!emptyQueue(queue))moreCusts=true;
        
        clock++;
    }
    //gathered statistic
    printStats(runStats);
}

PHONE* constructPhone()
{
    PHONE* phone;
    phone->custNum=1;
    phone->totSvcTime=0;
    phone->totWaitTime=0;
    phone->maxQueueSize=0;
    
    phone->arrivalTime=0;
    phone->startTime=0;
    phone->svcTime=0;
    phone->waitTime=0;
    
    return phone;
}
//Determined whether a new customer has arrived
void newCustomer(QUEUE* queue,int clock,int custNum,int maxservicetime)
{
    cout<<"in newCustomer\n";
    //the new  customer's data
    PHONE* custData;
    
    //random simulate
    bool newcustomer=false;
    int number;
    srand (time(NULL));
    number=rand()%maxservicetime+1;
    if(number<=maxservicetime/2)newcustomer=true;
    
    //successfully generate
    if(newcustomer)
    {
        cout<<"_new customer: servicetime="<<number<<endl;
        //the number of people not served
        custNum++;
        //store custNum in custData
        custData->custNum=custNum;
        //store arrival time in custData
        custData->arrivalTime=clock;
        enqueue(queue,custData);
        
        //test
        PHONE* temp;
        queueFront(queue,(void**)temp);
        cout<<"---original---\n"
            <<"custNum="<<custNum<<endl
            <<"clock="<<clock<<endl;
        cout<<"---temp output---\n"
            <<"custNum="<<temp->custNum<<endl
            <<"arrivalTime="<<temp->arrivalTime<<endl
            <<"---end output---\n";
    }
}
//determined whether the server is idle. If so then starts serving a new customer
void serverFree(QUEUE* queue,int clock,PHONE* status,bool moreCusts)
{
    cout<<"in serverFree\n";
    PHONE* custData;
    if(clock > (status->startTime + status->svcTime - 1))
    {
        //server is idle
        if(!emptyQueue(queue))
        {
            cout<<"_idle\n";
            dequeue(queue,(void**)&custData);
            status->custNum=custData->custNum;
            status->arrivalTime=custData->arrivalTime;
            status->startTime=clock;
            status->svcTime=custData->arrivalTime;
            moreCusts=true;
        }
    }
}
//determined whether the current cumstomer's processing is complete
void svcComplete(QUEUE* queue,int clock,PHONE* status,PHONE* stats,bool moreCusts)
{
    cout<<"in svcComplete\n";
    int queueSize;
    if(clock==(status->startTime + status->svcTime - 1))
    {
        //current call complete
        cout<<"_current call complete\n";
        status->waitTime=status->startTime - status->arrivalTime;
        stats->custNum++;
        stats->totSvcTime=stats->totSvcTime + status->svcTime;
        stats->totWaitTime=stats->totWaitTime + status->waitTime;
        queueSize=queueCount(queue);
        
        if((stats->maxQueueSize) < queueSize)stats->maxQueueSize=queueSize;
        
        //print
        cout<<"status custNum:"<<status->custNum<<endl
            <<"status arriveTime:"<<status->arrivalTime<<endl
            <<"status startTime:"<<status->startTime<<endl
            <<"status svcTime:"<<status->svcTime<<endl
            <<"waitTime:"<<status->waitTime<<endl
            <<"queueCount(queue):"<<queueCount(queue)<<endl;
        
        moreCusts=false;
    }
}
//print out the statistics for the simulation
void printStats(PHONE* stats)
{
    double avgSvcTime,avgWaitTime;
    
    cout<<"--------Simulation Statistics--------\n";
    cout<<"Total customers:"<<stats->custNum<<endl;
    cout<<"Total service time:"<<stats->totSvcTime<<endl;
    
    avgSvcTime=stats->totSvcTime/stats->custNum;
    cout<<"Average service time:"<<avgSvcTime<<endl;
    
    avgWaitTime=stats->totWaitTime/stats->custNum;
    cout<<"Average wait time:"<<avgWaitTime<<endl;
    
    cout<<"Max queue size:"<<stats->maxQueueSize<<endl;
}




