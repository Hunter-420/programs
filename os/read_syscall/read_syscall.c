#include<unistd.h>
#include<stdio.h>
int main(){
  char buffer[10];
  read(0, buffer, 8);
  int count = write(1, buffer,9);
  printf("%d char written",count);

}
