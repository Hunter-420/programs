/*

  author: Nischal Khanal
  date: 02 jan 2024
  title: curve fitting

  algorithm:
  1. start 
  2. read n no of data 
  3. read the value of Xi and Yi and constant variable a and b
  4. initialize:
                sumx=0,sumy=0,

*/

#include <stdio.h>
#define E 0.001

int main(){
  int i,n;
  float x[20],y[20],sumx=0,sumy=0,a,b;
  printf("Enter the value of n: ");
  scanf("%d",&n);

  for (i=0;i<n;i++) {
    printf("The value of x[%d]\n",i);
    scanf("%d",x[i]);
    printf("The value of y[%d]\n",i);
    scanf("%d",y[i]);

  }

  for (i=0;i<n;i++) {
    sumx=sumx+x[i];
    sumy=sumy+y[i];
    sumxx=sumxx+x[i]*x[i];
    sumxy=sumxy+x[i]*y[i];
  }

  printf("i=%d\t sumx=%f\t sumy=%f\t sumxx=%f\t sumxy=%f\n",i,sumx,sumy,sumxx,sumxy);
  b=(n*sumxy-sumx*sumy)/(n*sumxx-sumx*sumx);
  a=(sumy-b*sumx)/n;
  printf("\n The curve on straight line y=%fx+%f\n",a,b);

  getch();
  return 0;
(
