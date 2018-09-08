#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include"largerADT.h"
#include"nodeADT.h"

typedef struct 
{
        int id;
        float avg;
}DATA;
int compare ( void* p1 ,void* p2 );

int main()
{
    DATA* newdata;
    NODE* node;
    NODE* temp;
    int index = 0;
    int id;
    float avg;
    
    FILE *fp;
    fp = fopen("list.txt","r");
    while( fscanf(fp,"%d %f",&id,&avg) != EOF )
    {
           printf("\n %d %f",id,avg);
        newdata = (DATA*)malloc( sizeof(DATA) );
        newdata->id = id;
        newdata->avg = avg;
        if(index==0) {     
                 node = creatNode(newdata);
                 temp = node;
         }
         else {
              temp->link = creatNode(newdata);  
              temp = temp->link;
         }
         index++;   
    }
    fclose(fp);
    
    
    DATA* large = (DATA*)malloc( sizeof(DATA) );
    temp = node;
    large->id = 0; large->avg = 0;
    while( temp!=NULL )
    {
           DATA* a = (DATA*)temp->datap;
           printf("\nStudent id : %d ,avg = %f",a->id,a->avg);
           if( a->avg > large->avg )
           {
               large->id = a->id;
               large->avg = a->avg;
           }
           //large = (DATA*)larger(large,a,compare);
           temp = temp->link;
    }
    printf("\n  Best Grade Student:\nStudent id : %d ,avg = %f",large->id,large->avg);
    
    getch();
    return 0;
}
/*
int compare ( void* p1 ,void* p2 )
(
    if( (DATA*)p1->avg) > (DATA*)p2->avg )
       return 1;
    else
       return -1;
}*/

