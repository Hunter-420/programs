#include<unistd.h>
#include<stdio.h>

int main(){
  char buffer[10];
  int count = read(0, buffer, 10);
  write(1, buffer, 10);
}
