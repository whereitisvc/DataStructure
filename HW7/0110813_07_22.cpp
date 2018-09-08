#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include"0110813_07_22.h"//BST ADT

typedef struct
{
        char name[50];
        char num[50];
}DATA;

int compare( void* p1 ,void* p2 );
void process( void* p );
void process2( void* p );
char getop();
void search( BST_TREE* tree );
void insert( BST_TREE* tree );
void deleting( BST_TREE* tree );
void print( BST_TREE* tree );

FILE* fp;

int main()
{
    char name[50];
    char num[50];
    DATA* datap;
    BST_TREE* tree = BST_Create( compare );
    
    fp = fopen("HW7_22.txt","r");
    while( fscanf(fp,"%s %s",&name,&num) != EOF )
    {       
            datap = (DATA*)malloc( sizeof(DATA) );
            strcpy(datap->name, name);
            strcpy(datap->num, num);
            BST_Insert( tree, datap );  
    }
    ///////////////////////////////////////////////////////////
    
    char op;
    while( (op = getop()) != 'q' )
    {
           switch(op)
           {
                     case's':
                             search(tree);
                             break;
                     case'i':
                             insert(tree);
                             break;
                     case'd':
                             deleting(tree);
                             break;
                     case'p':
                             print(tree);
                             break;
           }
           printf("\n");
    }
    
    //fp = fopen("HW7_22@.txt","w");
    fp = fopen("HW7_22.txt","w");
    BST_Traverse( tree, process2 );
    
    fclose(fp);
    tree = BST_Destroy(tree);
    
    //getch();
    return 0;
}

int compare( void* p1 ,void* p2 )//compare two string
{
    return strcmp( ((DATA*)p1)->name ,((DATA*)p2)->name );
}
void process( void* p )
{
     DATA d = *(DATA*)p;
     printf("\n%-10s, %s",d.name,d.num);
}
void process2( void* p )
{
     DATA d = *(DATA*)p;
     fprintf(fp,"%s %s\n",d.name,d.num);
}
char getop()
{
     char op;
     bool error;
     printf("\n-------- MENU ----------------------------------------");
     printf("\npress 's' --> search the list for a specified name");
     printf("\npress 'i' --> insert a new name");
     printf("\npress 'd' --> deleting an exiting name");
     printf("\npress 'p' --> print list");
     printf("\npress 'q' --> save and exit");
     do
     {
         printf("\nEnter Option : ");
         scanf(" %c",&op);  // " %c" instead of "%c" to ignore \n or space 
         if( op=='s' || op=='i' || op=='d' || op=='p' || op=='q' ) error = false;
         else 
         {
              printf("Invalid input !");
              error = true;
         }
     }while( error );
     
     return op;
}
void search( BST_TREE* tree )
{
     char target[50];
     DATA* get;
     printf("\nInput a specified name : ");
     scanf("%s",&target);
     
     if( ( get = (DATA*)BST_Retrieve(tree, &target) ) != NULL )   
          printf("found ! --> %s, %s",get->name, get->num );
     else
         printf("Not found");
}
void insert( BST_TREE* tree )
{
     DATA* datap = (DATA*)malloc( sizeof(DATA) );
     printf("Enter new name : ");
     scanf("%s",&(datap->name));
     printf("Enter phone number : ");
     scanf("%s",&(datap->num));
     BST_Insert(tree,datap);
     printf("insert!");
}
void deleting( BST_TREE* tree )
{
     char d[50];
     printf("Enter deleting name : ");
     scanf("%s",&d);
     if( BST_Delete(tree, &d) ) printf("delete!");
     else printf("error!");
}
void print( BST_TREE* tree )
{
     BST_Traverse( tree, process );
}

