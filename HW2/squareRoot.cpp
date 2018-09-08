#include<stdio.h>
#include<conio.h>
#include<math.h>

float squareRoot(int num ,float ans ,float tol)
{
      if( fabs(ans*ans-num) <= tol )
          return ans;
      else 
           return squareRoot( num ,( (ans*ans+num)/(2*ans) ) ,tol );
}
int main()
{
    int num;
    num = 125;
    printf("\n squareRoot( %d,2,0.01 ) = %f  ",num,squareRoot( num,2,0.01 ));
    num = 763;
    printf("\n squareRoot( %d,2,0.01 ) = %f  ",num,squareRoot( num,2,0.01 ));
    num = 997;
    printf("\n squareRoot( %d,2,0.01 ) = %f  ",num,squareRoot( num,2,0.01 ));
    
    getch();
    return 0;
}
