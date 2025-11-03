#include"kernel/types.h"
#include"user/user.h"
void sieve(int read_fd){
    int prime,num;
    int p[2];
    int pid;
    if(read(read_fd,&prime,sizeof(prime))<=0){
        close(read_fd);
        exit(0);
    }
    printf("prime %d\n",prime);
    if(pipe(p)<0){
        fprintf(2,"pipe failed");
        exit(1);
    }
    pid=fork();
    if(pid<0){
        fprintf(2,"fork failed\n");
        exit(1);
    }else if(pid==0){
        close(p[1]);
        close(read_fd);
        sieve(p[0]);
    }else{
        close(p[0]);
        while(read(read_fd,&num,sizeof(num))>0){
            if(num%prime!=0){
                write(p[1],&num,sizeof(num));
            }
        }
        close(read_fd);
        close(p[1]);
        wait(0);
        exit(0);
    }
}
int main(){
    int p[2];
    int pid;
    if(pipe(p)<0){
        fprintf(2,"pipe failed\n");
        exit(1);
    }
    pid=fork();
    if(pid<0){
        fprintf(2,"fork failed\n");
        exit(1);
    }else if(pid==0){
        close(p[1]);
        sieve(p[0]);
    }else{
        close(p[0]);
        for(int i=2;i<=35;i++){
            write(p[1],&i,sizeof(i));
        }
        close(p[1]);
        wait(0);
        exit(0);
    }
    return 0;

}