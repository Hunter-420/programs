#include<unistd.h>
#include<stdio.h>

int main(){
  int count = write(1,"Hello",5);
  printf("writing %d char",count);
}
