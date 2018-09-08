#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"0110813_05_26.h"

typedef struct
	   {
	    int   count; 
	    LIST* pos;
	    LIST* head; 
	    LIST* rear;
	    int    (*compare) (void* argu1, void* argu2); 
	   } LISTHEAD; 
LISTHEAD* createListhead (int (*compare) (void* argu1, void* argu2))
{
	LISTHEAD* listhead;

	listhead = (LISTHEAD*) malloc(sizeof (LISTHEAD));
	if (listhead)
	   {
	    listhead->head    = NULL;
	    listhead->pos     = NULL;
	    listhead->rear    = NULL;
	    listhead->count   = 0;
	    listhead->compare = compare;
	   } 
	return listhead;
}
int addList (LISTHEAD* listhead, LIST* list)
{
    if( listhead->rear == NULL )
    {
        listhead->head = list;
        listhead->pos  = list;
        listhead->rear = list;
        listhead->count++;
    }    
    else
    {
        listhead->rear->link = list;
        listhead->pos  = list;
        listhead->rear = list;
        listhead->count++;
    }
    
}	// addNode 


int comparestu( void* p1 ,void* p2 )//compare two string
{
    return strcmp( (char*)p1 ,(char*)p2 );
}
int compare( void* p1 ,void* p2 )//compare two integer
{
    if( *(int*)p1 < *(int*)p2 ) return -1;
    else if( *(int*)p1 > *(int*)p2 ) return 1;
    else return 0;
}

int main()
{
    LISTHEAD* student = createListhead( comparestu );
    LIST* list;
    char* name;
    FILE* fp;
    fp = fopen("5-26 read files/HW5_26.txt","r");
    //fp = fopen("5-26 read files/test.txt","r");

    ////////////////////////////////////////////////// initialize student list by reading text file
    name = (char*)calloc(50, sizeof(char) );
    while( fgets(name, 50, fp) != NULL )
    {
           if (name[strlen(name) - 1] == '\n')  //trauncate '\n'
               name[strlen(name) - 1] = '\0';
          
           list = createList( compare );
           list->dataPtr = name;
           addList( student, list );
           name = (char*)calloc(50, sizeof(char) );
    }
    
    //////////////////////////////////////////////////  input student scores
    student->pos = student->head;
    int* score;
    int count = 0;
    printf("Input each student's scores (up to four subjects), input '-1' to stop.");
    for(int i=0; i < student->count; i++)
    {
            printf("\n%s : \n",student->pos->dataPtr);
            do
            {
                  score = (int*)malloc( sizeof(int) );
                  scanf("%d",score);
                  if( *score>0 ) addNode( student->pos, score);
                  count++;
            }while( *score != -1 && count != 4 );
            
            count = 0;
            student->pos = student->pos->link;
    }
    
    /////////////////////////////////////////////////  show student's score
    student->pos = student->head;
    int* datap;
    int sum = 0;
    printf("\n\n");

    for(int i=0; i < student->count; i++)
    {
           printf("\n%s : ",student->pos->dataPtr);
           
           traverse( student->pos, 0, (void**)&datap );//start from first node
           do
           {
                  printf("%2d, ",*datap);
                  sum += *datap;
 
           }while( traverse( student->pos, 1, (void**)&datap ) );
           
           printf("sum = %d, avg = %f",sum,(float)sum/(student->pos->count));
           sum = 0;
           student->pos = student->pos->link;
    }
    
    fclose(fp);
    free(name);
    destroyList(list);

    getch();
    return 0;
}

