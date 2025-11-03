#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc,char*argv[]){
    if(argc!=2){
        fprintf(2,"sleep and second\n");
        exit(1);
    }
    int ticks=atoi(argv[1]);
    fprintf(1,"sleep for %d ticks...\n",ticks);
    sleep(ticks);
    fprintf(1,"Wake up\n");
    exit(0);
}