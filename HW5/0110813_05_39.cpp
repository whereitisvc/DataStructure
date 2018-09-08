#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node 
{
	    int*  datap;
	    struct node* link;
} NODE; 

typedef struct list
{
	    int   count; 
	    char* pos;
	    NODE* head; 
	    
} LIST; 

LIST* createList ( char name[] )
{
	LIST* list;

	list = (LIST*) malloc(sizeof (LIST));
	if (list)
    {
	       list->head    = NULL;
	       list->pos     = (char*)calloc(strlen(name)+1, sizeof(char));
	       for(int i=0;i<strlen(name);i++)
                   list->pos[i] = name[strlen(name)-1-i];
	       list->count   = 0;
    } 
	return list;
}
int addNode (NODE* rear, int* dataInPtr)
{
    NODE* newp = (NODE*)malloc(sizeof(NODE));
    newp->datap = dataInPtr;
    newp->link = NULL;

    rear->link = newp;
}	

int main()
{
    int num;
    char name[20];
    char path[50];
    char add1[] = "5-39 read files/";
    char add2[] = ".txt";
    int* datap = (int*)malloc(sizeof(int));
    NODE* pre;
    //LIST** listAry;
    FILE* fp;
    
    printf("Input numbers of file : ");
    scanf("%d",&num);
       
    //*listAry = (LIST*)calloc(num, sizeof(LIST));
    LIST* listAry[num];
    
    for(int i=0;i<num;i++)
    {
            printf("Input the name of file #%d : ",i+1);
            scanf("%s",name);
            
            listAry[i] = createList( name );
            //////////////////////// path name
            strcpy( path,add1 );
            strcat( path,name );
            strcat( path,add2 );
            ///////////////////////

            fp = fopen(path,"r");
            while( fscanf(fp,"%d",datap) != EOF )
            {
                   //printf("\n%d",*datap);
                   NODE* newp = (NODE*)malloc(sizeof(NODE));
                   newp->datap = datap;     
                   newp->link = NULL;
                   
                   if( listAry[i]->count == 0 )
                       listAry[i]->head = newp;
                   else
                       pre->link = newp;

                   pre = newp;
                   listAry[i]->count++;
                   datap = (int*)malloc(sizeof(int));
            }           
    }
    
    NODE* loc;
    for(int i=0;i<num;i++)
    {
            printf("\n%s : ",listAry[i]->pos);
            loc = listAry[i]->head;
            while( loc != NULL )
            {
                   printf("%d ",*(loc->datap));
                   loc = loc->link;
            }
            
    }
    
    fclose(fp);
    
    getch();
    return 0;
}
