#include<stdio.h>
#include<conio.h>
//#include "0110849_9_33.h"
#include "0110813_09_33.h"


typedef struct data{
        char *name;
        
        int priority;
        } ;
        

int compare( void* p1, void* p2  ){   
    
    
    if(((data*)p1)->priority>((data*)p2)->priority) 
        return 1;
    else if(((data*)p1)->priority==((data*)p2)->priority) 
        return 0;
    else 
        return -1;
    
    
        }


HEAP* readfile(){
      
      HEAP* heap = heapCreate(100,compare);
      FILE* file;
      data* datap;
      char* temp;
      char c;
      int i=0,millage,years,sequence;      
      
      file = fopen("9_33.txt","r");
      temp = new char[17];
      
      
      
      while(!feof(file))
      {
          
          if(i<16)
          {
              fscanf(file,"%c",&c);
              if(c!='\n')
              {
              temp[i] = c;
              i++;
          	  }
          }
          else
          {
          	  temp[16] = '\0';
              fscanf(file,"%d %d %d",&millage,&years,&sequence);
              
              printf("%s  %d  %d  %d  \n",temp,millage,years,sequence);
              
              datap = (data*)(malloc(sizeof(data)));
              datap->name = temp;
              datap->priority = millage/1000+years-sequence;
              
              heapInsert(heap,datap);
              
              temp = new char[17];
              
              i = 0;
          }
          
          
      }
      
        
      return heap;
      
      }



int main()
{
    int count=1;
    int last;
    HEAP* heap;
    data* datap;
    bool end = false;
	
    heap = readfile();

	printf("\n");

    last = heap->last;
    
    
    while(!end)
    { 
           if(last<=0)
           		end = true;
           else
           {
		   		datap = (data*)(heap->heapAry[0]);
           
           		printf("%d  %s  %d  \n",count, datap->name, datap->priority);
           
           		last = heap->last;
           		
           		heap->heapAry[0] = (data*)(heap->heapAry[last]);
				heap->heapAry[last] = datap;
				heap->last--;
           		
				_reheapDown (heap, 0);
           		
           		
           		
				count++;
           
       	   }
    }
    
    
    getch();
    return 0;
}
