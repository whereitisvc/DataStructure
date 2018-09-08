#include<stdio.h>
#include<conio.h>

long fibonacci( long n )
{
    if( n==0 || n==1 ) return n;
    else return ( fibonacci(n-1) + fibonacci(n-2) );
}
long fibonacci_iter( long n )
{
    int x=0,y=1,num;
    
    if( n==0 || n==1 ) return n;
    else{
         for(int i=0;i<n-1;i++){
                 num = x+y;
                 x = y;
                 y = num;
         }
    }
    return num;
}

int main()
{
    long a = 5, b = 20;
    
    //printf("a = %ld , b = %ld",a,b);
    //printf("\nfibonacci(%ld) = %ld",a,fibonacci(a));
    printf("\nfibonacci_iter(%d) = %d",a,fibonacci_iter(a));
    //printf("\nfibonacci(%ld) = %ld",b,fibonacci(b));
    printf("\nfibonacci_iter(%d) = %d",b,fibonacci_iter(b));
    
    getch();
    return 0;
}
