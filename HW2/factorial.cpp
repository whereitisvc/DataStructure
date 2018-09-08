#include<stdio.h>
#include<conio.h>

int factorial( int n )
{
    if(n==1) return 1;
    else return n*factorial(n-1);
}
int factorial_iter( int n )
{
    int sum = 1;
    for(int i=1;i<=n;i++)
        sum = sum*i;
    return sum;
}

int main()
{
    int a = 5, b = 7;
    
    printf("a = %d , b = %d",a,b);
    printf("\nfactorial(%d) = %d",a,factorial(a));
    printf("\nfactorial_iter(%d) = %d",a,factorial_iter(a));
    printf("\nfactorial(%d) = %d",b,factorial(b));
    printf("\nfactorial_iter(%d) = %d",b,factorial_iter(b));
    
    getch();
    return 0;
}
