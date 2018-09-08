#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
        struct node* left;
        struct node* right;
        char* datap;
        char* code;
}NODE;

typedef struct
{
        int sum;
        NODE* root;
        int count;

}TREE;

TREE* createTree( int sum )
{
      TREE* tree = (TREE*)malloc( sizeof(TREE) );
      tree->sum = sum;
      tree->root = NULL;
      tree->count = 0;
      
      return tree;
}

bool insertNode( char* datainp, TREE* tree, NODE* root, int weight )
{
     NODE* newnode = (NODE*)malloc( sizeof(NODE) );
     newnode->datap = datainp;
     newnode->left = NULL;
     newnode->right = NULL;
     newnode->code = (char*)calloc(20,sizeof(char)); 
     
     if( tree->count==0 )
     {
         tree->root = newnode;
         tree->count++;
         return true;
     }
     
     if( root->left == NULL )
     {
         //strcat( newnode->code, "0" );
         root->left  = newnode;
         tree->sum  += weight;
         tree->count++;
         return true;
     }
     else if( root->right == NULL )
     {
         //strcat( newnode->code, "1" );
         root->right = newnode;
         tree->sum  += weight;
         tree->count++;
         return true;
     }    
     else return false;     
}
void appendCode( NODE* root, char* append )
{
      if( root!=NULL )
      {
          if( *(root->datap) != '+' )
          {    
               char temp[20];
               strcpy( temp, append );
               strcat( temp, root->code );
               strcpy( root->code, temp );
          }
          appendCode( root->left, append );
          appendCode( root->right, append );     

      }      
      return ;
}
bool insertTree( TREE* insert, TREE* tree, NODE* root, char LR )
{
     NODE* basep;
     bool found = false;
     if( LR=='R' )
     {
         root->right = insert->root;
         appendCode( insert->root, "1" );
     }
     else
     {
         root->left = insert->root;
         appendCode( insert->root, "0" );
     }
         
     tree->sum  += insert->sum;
     tree->count += insert->count;
}
bool traversal( NODE* root )
{
     if( root ==NULL )
     {
         printf("=");
         return true;
     }
     if( root!=NULL )
     {
         printf("%c",*(root->datap));
         traversal(root->left);
         traversal(root->right);
     }
     return true;
}
char* letter2code( NODE* root, char target, bool* foundp )
{
      char* code = (char*)calloc(20,sizeof(char)); 
      code = "***";
      if( root==NULL ) 
           return code;
           
      if( root!=NULL )
      {
          if( *(root->datap) == target )
          {
              code = root->code;
              *foundp = true;
              return code;
          }
          if(!*foundp)
                      code = letter2code( root->left, target, foundp );
          if(!*foundp)
                      code = letter2code( root->right, target, foundp );     

      }
      return code;
}
char code2letter( NODE* root, char* target, bool* foundp )
{
      char letter = '?'; 
      if( root==NULL ) 
           return letter;
           
      if( root!=NULL )
      {
          if( !strcmp(root->code, target) )
          {
              letter = *(root->datap);
              *foundp = true;
              return letter;
          }
          if(!*foundp)
                      letter = code2letter( root->left, target, foundp );
          if(!*foundp)
                      letter = code2letter( root->right, target, foundp );     

      }
      return letter;
}

int main()
{
    int length = 26;
    char list[30];// = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int weight[26];// = { 7,2,2,3,11, 2,2,6,6,1, 1,4,3,7,9, 2,1,6,6,8, 4,1,2,1,2, 1 };
    TREE** treelist;
    treelist = (TREE**)calloc( length, sizeof(TREE) );
    
    int a=0;
    char g;  
    FILE* fp;
    fp = fopen("HW6_readFile.txt","r");

    while( fscanf(fp,"%c %d%c",&list[a],&weight[a],&g) != EOF )  a++;
    
    //////////////////////////////////////////////////////////  sort weight
    for( int i=0; i<length-1; i++ )
         for( int j=i+1; j<length; j++ )
              if( weight[i] < weight[j] )
              {
                  int temp = weight[i];
                  weight[i] = weight[j];
                  weight[j] = temp;
                  
                  char tempc = list[i];
                  list[i] = list[j];
                  list[j] = tempc;
              }              
    for( int i=0; i<length; i++ )  printf("%2c ",list[i]);
    printf("\n");
    for( int i=0; i<length; i++ )  printf("%2d ",weight[i]);
    printf("\n");
    
    /////////////////////////////////////////////////////////  build treelist    
    char* datap;
    for( int i=0; i<length; i++ )  
    {
         treelist[i] = createTree( weight[i] );
         datap = (char*)malloc(sizeof(char));
         *datap = list[i];  //printf("%c ",*datap);
         insertNode( datap, treelist[i], treelist[i]->root, 0 ); 
    }

    /////////////////////////////////////////////////////////
    int treecount = length;
    int markA,markB;
    TREE* smallA;
    TREE* smallB;
    TREE* combineTree;
    bool keep;
    
    while( treecount > 1 )
    {         
              //printf("\n%2d. ",treecount);
              
              markA = 0; 
              while( treelist[markA]==NULL ) markA++;
              smallA = treelist[markA];
              for( int i=0; i<length; i++ )
              {
                   if( treelist[i]!=NULL )
                   {
                       if( treelist[i]->sum < smallA->sum )  
                       {    smallA = treelist[i];  markA = i;  }
                   }
              }
              
              markB = 0; 
              keep = true;
              while( treelist[markB]==NULL || keep ) 
              {      
                     markB++;
                     if(markB!=markA)  keep = false;
                     else keep = true;
              }
              smallB = treelist[markB]; 

              for( int i=0; i<length; i++ )
              {
                   if( treelist[i]!=NULL )
                   {
                       if( (treelist[i]->sum < smallB->sum) && i!=markA )  
                       {   smallB = treelist[i];   markB = i;  }
                   }
              }
    
              //////////////////////////////////////////////////////////
              combineTree = createTree(0);
              datap = (char*)malloc(sizeof(char));   *datap = '+';
              insertNode( datap, combineTree, combineTree->root, 0 );
              insertTree( smallA, combineTree, combineTree->root, 'L' );
              insertTree( smallB, combineTree, combineTree->root, 'R' );
              
              /////////////////////////////////////////////////////////
              treelist[markB] = combineTree;
              treelist[markA] = NULL;
              treecount--;
              
              //printf("\ncombineTree-weight = %2d\n",combineTree->sum);
              printf("\n");
              for( int i=0; i<length; i++ )
              {
                   if( treelist[i]!=NULL ) 
                   {    printf("%2d ",treelist[i]->sum); }
                        //printf("\n");
                        //traversal( treelist[i]->root );  }
                   else
                       printf("xx ");
              }
              //printf("\nsmallA = %2d, smallB = %2d\n", smallA->sum, smallB->sum);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    TREE* codeTree = combineTree; 
    char target;
    char* code; 
    bool found = false;

    printf("\n\n");
    for( int i=0;i<length;i++ )
    {
         code = (char*)calloc(20,sizeof(char)); found = false;
         target = list[i];
         printf("%c = ",target);
         code = letter2code( codeTree->root, target, &found );
         puts(code);
    }
    
    char word[20];
    printf("\n\n1.Input letters(Uppercase) : ");
    gets(word);
    printf("  %s --> ",word);
    for(int i=0;i<strlen(word);i++)
    {
           code = (char*)calloc(10,sizeof(char)); found = false; 
           code = letter2code( codeTree->root, word[i], &found );
           printf("%s ",code);
    }
    
    char codeline[100];
    char letter;
    int k = 0;
    printf("\n\n2.Input Codes(press Space to seperate) : ");
    gets(codeline);
    printf("  %s --> ",codeline);
    
    code = (char*)calloc(20,sizeof(char)); found = false; 
    for(int i=0;i<strlen(codeline);i++)
    {
           if( codeline[i]!=' ' )
           {
               *(code+i-k) = codeline[i];
               if( i==strlen(codeline)-1 )
               {
                  letter = code2letter( codeTree->root, code, &found );
                  //printf("%s,",code);
                  printf("%c",letter);
               }
           }
           else
           {
               letter = code2letter( codeTree->root, code, &found );
               //printf("%s,",code);
               printf("%c",letter);
               code = (char*)calloc(20,sizeof(char)); found = false; 
               k = i+1;
           }
    }
    
    
    getch();
    return 0;
}
    
