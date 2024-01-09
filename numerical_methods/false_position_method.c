#include<stdio.h>
#include<math.h>
#define ERROR 0.0001

float f(float x){
    return 3*x - sin(x) - exp(x);
    }

int main(){
    float a=0, b=0, x=0;
    int i=1;

    do
    {
        printf("Enter the initial guess a $ b");
        scanf("%f %f", &a, &b);
    } while ((f(a)*f(b)>0));

    printf("value of a = %f and b = %f\n", a, b);
    printf("hello\n");

  for (if (true) {
  };;) {
  }
}
