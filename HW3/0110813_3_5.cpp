#include <conio.h>
#include <stdio.h>
#include "0110813_3_4.h"
int map[10][12]={ {1,1,1,1,1,1,1,1,1,1,1,1}, 
                      {1,0,0,0,1,1,0,1,0,1,0,1},
                      {1,1,1,0,1,0,0,0,0,0,0,1},
                      {1,1,0,0,0,0,1,1,1,1,0,1},
                      {1,1,0,1,1,1,1,1,1,1,0,0},
                      {1,1,0,1,0,1,1,1,1,1,1,1},
                      {1,1,0,0,0,1,1,1,1,1,1,1},
                      {1,1,1,1,0,1,0,1,0,1,0,1},
                      {1,1,0,0,0,0,0,1,0,0,0,1},
                      {1,1,1,1,1,1,1,1,1,1,1,1}, };
typedef struct
{
       int x;
       int y;
}Point;

int neighbors( Point past,Point p ,STACK* stack ) //count available neighbors
{
    int count = 0;
    Point* datap;
    if( map[p.y][p.x-1]==0 && (p.x-1)!= past.x )
    { 
        count++;
        datap = (Point*) malloc( sizeof (Point));
        datap->x = p.x-1; datap->y = p.y; 
        pushStack(stack,datap); 
    }
    if( map[p.y][p.x+1]==0 && (p.x+1)!= past.x )
    { 
        count++;
        datap = (Point*) malloc( sizeof (Point));
        datap->x = p.x+1; datap->y = p.y; 
        pushStack(stack,datap); 
    }
    if( map[p.y-1][p.x]==0 && (p.y-1)!= past.y )
    { 
        count++;
        datap = (Point*) malloc( sizeof (Point));
        datap->x = p.x; datap->y = p.y-1; 
        pushStack(stack,datap); 
    }
    if( map[p.y+1][p.x]==0 && (p.y+1)!= past.y )
    { 
        count++;
        datap = (Point*) malloc( sizeof (Point));
        datap->x = p.x; datap->y = p.y+1; 
        pushStack(stack,datap); 
    }
    
    return count;
}

int main()
{
    int startx,starty,endx = 11,endy = 4;     //set end point
    Point currentSpot,pastSpot,branchSpot;
    Point* datap;
    STACK* path_stack = createStack(); 
    STACK* temp_stack = createStack();       //temperary record the available neighbors point
    STACK* choice_stack = createStack();
    bool succeed = true;
    
    printf("  ");                               //draw map & coordinate
    for(int i=0;i<12;i++) printf("%3d",i);
    printf("\n");
    for(int i=0;i<10;i++){
        printf("%2d",i);
        for(int j=0;j<12;j++)
             if(map[i][j]==1)printf("  *");
             else printf("   ");
        printf("\n");
    }

    
    while(1)    // repeat progess
    {
            
    
               //user input startx, starty
    while(1){
             printf("\ninput stratx(0~11), starty(0~9) : ");
             scanf("%d %d",&startx,&starty);
             if( startx<12 && startx>0 && starty<10 && starty>0 )
                 if( map[starty][startx]==0 ) break;
    };

                                                    //initialize
    currentSpot.x = startx; currentSpot.y = starty;
    pastSpot.x = -1; pastSpot.y = -1;
    branchSpot.x = -1; branchSpot.y = -1;
    succeed = true;
    printf("\nwhole path:\n(%2d ,%2d)->",currentSpot.x,currentSpot.y);
    
    while(1)
    {
            if( currentSpot.x == endx && currentSpot.y == endy ) //end point
            {
                succeed = true; break;
            }
            else
            {
                datap = (Point*) malloc( sizeof (Point));
                datap->x = currentSpot.x; datap->y = currentSpot.y;
                pushStack( path_stack,datap );
                
                int count = neighbors( pastSpot,currentSpot,temp_stack  );
                
                if( count >= 2 )//alternative
                {         
                           pushStack( path_stack,&branchSpot );
                           
                           Point* q;
                           while( !emptyStack(temp_stack) ) //push tempStack to choiceStack
                           {
                                  q = (Point*) malloc( sizeof (Point));
                                  *q = *(Point*)popStack( temp_stack );
                                  pushStack( choice_stack,q );
                           }
                           
                           pastSpot = currentSpot;
                           currentSpot = *(Point*)popStack( choice_stack ); 
                           printf("(%2d ,%2d)->",currentSpot.x,currentSpot.y);
                          
                }
                
                if( count == 1 )//continue
                {
                    pastSpot = currentSpot;
                    currentSpot = *(Point*)popStack( temp_stack );
                     printf("(%2d ,%2d)->",currentSpot.x,currentSpot.y);
                }
                
                if( count == 0 )//deadend
                { 
                    Point* p2;
                    printf(" * ");
                    while(1)
                    {
                          if( emptyStack(path_stack) ) 
                          { succeed = false; break; }
                          
                          p2 = (Point*)popStack( path_stack );
                          
                          if( p2->x==branchSpot.x && p2->y==branchSpot.y )break; //deadend and no other branchspot --> fail
                          else printf("(%2d ,%2d)->",p2->x,p2->y);
                          
                    }
                    if(!succeed) break;
                    
                    printf("(%2d ,%2d)->",pastSpot.x,pastSpot.y);
                    pastSpot = *(Point*)stackTop( path_stack );
                    currentSpot = *(Point*)popStack( choice_stack );
                     printf("(%2d ,%2d)->",currentSpot.x,currentSpot.y);
                }
                
            }
    }
    
    if(succeed)
    {
               printf("(%2d, %2d)",endx,endy);
               
               printf("\n\nperfect path :\n");
               Point* p3;
               STACK* reverse_stack = createStack();
               while( !emptyStack(path_stack) )
               {
                      p3 = (Point*)popStack( path_stack );
                      if( p3->x!=branchSpot.x && p3->y!=branchSpot.y )
                          pushStack( reverse_stack,p3 );
               }
               while( !emptyStack(reverse_stack) )
               {
                      p3 = (Point*)popStack( reverse_stack );
                      printf("(%2d, %2d) -> ",p3->x,p3->y);
               }
               printf("(%2d, %2d)",endx,endy);
    }
    else if(!succeed)
    {
        printf("cannot escape the maze .");
    }
    
    char c;
    printf("\n\nPress 'y' to continue 'n' to exit. ");
    c = getch();
    if(c=='n')break;
    
    
    }
    
    return 0;
}
