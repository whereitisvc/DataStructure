#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"0110813_05_30.h"

int main()
{
    LIST* list1 = createList();
    LIST* list2 = createList();
    char num[100];
    char* rnum;
    int* datap;
    int* datap2;
    
    ////////////////////////////////////////////////////////////// Input number
    printf("Input first number : ");
    scanf("%s",num); 
    //reverse num string
    rnum = (char*)calloc(strlen(num)+1, sizeof(char));
    for(int i=0;i<strlen(num);i++)
            rnum[i] = num[strlen(num)-1-i];    
    
    for( int i=0;i<strlen(rnum);i++ )
    {
         datap = (int*)malloc(sizeof(int));
         *datap = rnum[i]-'0';  
         addNode( list1,datap );   printf(" %d->",*datap);
    }
    
    printf("\nInput second number : ");
    scanf("%s",num);
    //reverse num string
    free(rnum);
    rnum = (char*)calloc(strlen(num)+1, sizeof(char));
    for(int i=0;i<strlen(num);i++)
            rnum[i] = num[strlen(num)-1-i];
    for( int i=0;i<strlen(num);i++ )
    {
         datap = (int*)malloc(sizeof(int));
         *datap = rnum[i]-'0';
         addNode( list2,datap );    printf(" %d->",*datap);
    }

    ////////////////////////////////////////////////////////////// Caculate sum
    int carry = 0;
    int* sum;
    bool check1 = true, check2 = true;
    LIST* sumlist = createList();
    traverse( list1, 0, (void**)&datap );//start from first node
    traverse( list2, 0, (void**)&datap2 );
    do
    {
        sum = (int*)malloc( sizeof(int) );
        
        if( check1 && check2 )*sum = carry + *datap + *datap2;            
        else if( check1 )     *sum = carry + *datap;
        else                  *sum = carry + *datap2;
       
        if( *sum > 9 )
        {
                 *sum = *sum - 10;
                 carry = 1;
        }
        else carry = 0;     
           
        addNode( sumlist, sum );   
        
        check1 = traverse( list1, 1, (void**)&datap ); 
        check2 = traverse( list2, 1, (void**)&datap2 );    
 
    }while( check1 || check2 );
    
    ////////////////////////////////////////////////////////////// print sum
    int i=0;
    int* out;
    out = (int*)calloc(sumlist->count, sizeof(int));
    printf("\n\nsum = ");
    traverse( sumlist, 0, (void**)&sum );
    do
    {
              out[i] = *sum; i++;              
    }while( traverse( sumlist, 1, (void**)&sum ) ) ;   
    for(int i=0;i<sumlist->count;i++)
            printf("%d",out[ sumlist->count-1-i ]);
            
    free(rnum);
    destroyList(list1);
    destroyList(list2);
    destroyList(sumlist);
    
    getch();
    return 0;
}
