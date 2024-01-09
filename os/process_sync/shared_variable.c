#include<stdio.h>
#include<unistd.h>

/* shared variable */
int g = 5;

int main(){
    /* process id */
    int pid;

    /* creating parent and child process */
    pid = fork();

    /* executed by parent process */
    if(pid > 0){
        int x =g;
        x++;
        sleep(1);
        g =x;
        printf("Parent Process: %d",g);
    }

    /* executed by child process */
    else if(pid == 0){
        int y =g;
        y--;
        sleep(1);
        g = y;
        printf("\nChild Process: %d",g);
    }

    /* executed by both and child process */
    printf("\n Last g: %d",g);

    return 0;
}