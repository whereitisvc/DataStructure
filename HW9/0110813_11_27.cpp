#include <stdio.h>
#include <conio.h>
#include "0110813_11_27.h"

bool end = false;

int compare( void* p1, void* p2 )
{
    char x1 = *(char*)p1;
    char x2 = *(char*)p2;
    
    if((int)x1>(int)x2) return 1;
    else if((int)x1==(int)x2) return 0;
    else return -1;
}
void process( void* datap )
{
     printf("%c ",*(char*)datap);
}
void simulprocess( void* datap )
{
     if(!end)
     printf("%c ",*(char*)datap);
     if( *(char*)datap == 'O' ) end = true;
}

int main()
{
    GRAPH* graph = graphCreate(compare);
    char list[15] = { 'A','B','C','D','E', 'F','G','H','I','J', 'K','L','M','N','O' };
    //char list[9] = { 'A','X','H','P','E', 'Y','M','J','G'};
    char* datap;
    int length = 15;
    //int length = 9;
    
    for(int i=0;i<length;i++)
    {
            datap = (char*)malloc(sizeof(char));
            *datap = list[i];
            //printf("%c ",*datap);
            graphInsVrtx( graph, datap ); 
    }
    
    ///////////////////////////////////////////////////////////////////////////
    char* from;
    char* to;

    
    from = (char*)malloc(sizeof(char)); *from = 'A'; // A: B
    to = (char*)malloc(sizeof(char)); *to = 'B';
    graphInsArc(graph, from, to);
    
    from = (char*)malloc(sizeof(char)); *from = 'B'; // B: A,C,E
    to = (char*)malloc(sizeof(char)); *to = 'A';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'C';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'E';
    graphInsArc(graph, from, to);
    
    from = (char*)malloc(sizeof(char)); *from = 'C'; // C: B,D,G
    to = (char*)malloc(sizeof(char)); *to = 'B';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'D';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'G';
    graphInsArc(graph, from, to);
    
    from = (char*)malloc(sizeof(char)); *from = 'D'; // D: C
    to = (char*)malloc(sizeof(char)); *to = 'C';
    graphInsArc(graph, from, to);
    
    from = (char*)malloc(sizeof(char)); *from = 'E'; // E: B,F,G
    to = (char*)malloc(sizeof(char)); *to = 'B';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'F';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'G';
    graphInsArc(graph, from, to);
    
    from = (char*)malloc(sizeof(char)); *from = 'F'; // F: E,G,H
    to = (char*)malloc(sizeof(char)); *to = 'E';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'G';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'H';
    graphInsArc(graph, from, to);
    
    from = (char*)malloc(sizeof(char)); *from = 'G'; // G: E,F,C
    to = (char*)malloc(sizeof(char)); *to = 'E';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'F';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'C';
    graphInsArc(graph, from, to);
    
    from = (char*)malloc(sizeof(char)); *from = 'H'; // H: F,I,J
    to = (char*)malloc(sizeof(char)); *to = 'F';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'I';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'J';
    graphInsArc(graph, from, to);
    
    from = (char*)malloc(sizeof(char)); *from = 'I'; // I: H
    to = (char*)malloc(sizeof(char)); *to = 'H';
    graphInsArc(graph, from, to);
    
    from = (char*)malloc(sizeof(char)); *from = 'J'; // J: H,K,L
    to = (char*)malloc(sizeof(char)); *to = 'H';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'K';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'L';
    graphInsArc(graph, from, to);
    
    from = (char*)malloc(sizeof(char)); *from = 'K'; // K: J
    to = (char*)malloc(sizeof(char)); *to = 'J';
    graphInsArc(graph, from, to);
    
    from = (char*)malloc(sizeof(char)); *from = 'L'; // L: J,M,N,O
    to = (char*)malloc(sizeof(char)); *to = 'J';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'M';
    graphInsArc(graph, from, to);
    to = (char*)malloc(sizeof(char)); *to = 'N';
    graphInsArc(graph, from, to);
     to = (char*)malloc(sizeof(char)); *to = 'O';
    graphInsArc(graph, from, to);
    
    from = (char*)malloc(sizeof(char)); *from = 'M'; // M: L
    to = (char*)malloc(sizeof(char)); *to = 'L';
    graphInsArc(graph, from, to);
    
    from = (char*)malloc(sizeof(char)); *from = 'N'; // N: L
    to = (char*)malloc(sizeof(char)); *to = 'L';
    graphInsArc(graph, from, to);
    
    from = (char*)malloc(sizeof(char)); *from = 'O'; // O: L
    to = (char*)malloc(sizeof(char)); *to = 'L';
    graphInsArc(graph, from, to);
    
    //////////////////////////////////////////////////////////////////////////
    printf("\n\nsimulate path:  ");
    graphDpthFrst (graph, simulprocess);
    printf("\n\n(  DpthFrst:  ");
    graphDpthFrst (graph, process);
    printf("  )");
    printf("\n(  BrdthFrst: ");
    graphBrdthFrst (graph, process);
    printf("  )");
    
    
    getch();
    return 0;
}
