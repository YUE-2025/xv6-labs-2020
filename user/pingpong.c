#include "kernel/types.h"
#include"user/user.h"
int main(){
    int pipe1[2];
    int pipe2[2];
    char buffer[10];
    if(pipe(pipe1)<0||pipe(pipe2)<0){
        fprintf(2,"no pipe");
        exit(1);
    }
    int pid=fork();
    if(pid<0){
        fprintf(2,"no pipes");
        exit(1);
    }else if(pid==0){
        close(pipe1[1]);
        close(pipe2[0]);
        read(pipe1[0],buffer,4);
        printf("%d:reeceived %s\n",getpid(),buffer);
        write(pipe2[1],"pong",4);
        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    }else{
        close(pipe1[0]);
        close(pipe2[1]);
        write(pipe1[1],"ping",4);
        read(pipe2[0],buffer,4);
        printf("%d:reeceived %s\n",getpid(),buffer);
        wait(0);
        close(pipe1[1]);
        close(pipe2[0]);
        exit(0);
    }
}