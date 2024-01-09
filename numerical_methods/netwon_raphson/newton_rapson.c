#include<stdio.h>
#include<math.h>
#define E 0.0001


float f(float x){
    return x*x + x - 2;
}

float df(float x){
    return 2*x + 1;
}

int main(){
    
    float x0=0, x1=0;

    int i=0;
    printf("Enter initial guess: ");
    scanf("%f", &x0);
    do
    {
        x1=x0-(f(x0)/df(x0));
        printf("\n i=%d x0=%f x1=%f f(x1)=%f", i++, x0, x1, f(x1));
        x0=x1;
        if (i>100)
        {
            printf("\n\nSolution does not converge");
            break;
        }
        i++;

    } while ((fabs(f(x1)) > E));
    
    return 0;
}