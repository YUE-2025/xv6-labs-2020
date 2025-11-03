#include"kernel/types.h"
#include"user/user.h"
#include"kernel/param.h"
#define MAX_LINE 512
int main(int argc,char *argv[]){
    if(argc<3){
        fprintf(2,"Usage: xargs<command><args_0>\n");
        exit(1);
    }
    char line[MAX_LINE];
    char *new_argv[MAXARG];
    for(int i=0;i<MAXARG;i++){
        new_argv[i]=0;
    }
    new_argv[0]=argv[1];
    new_argv[1]=argv[2];
    while(gets(line,sizeof(line))>0){
        if(line[0]=='\0'||line[0]=='\n'){
            continue;
        }
    char *newline=strchr(line,'\n');
    if(newline){
         *newline='\0';
    }
    if(strcmp(line,"exit")==0){
        break;
    }
    new_argv[2]=line;
    int pid=fork();
    if(pid<0){
        fprintf(2,"xargs:fork failed\n");
        exit(1);
    }else if(pid==0){
        exec(new_argv[0],new_argv);
        fprintf(2,"xargs:exec %s failed\n",new_argv[0]);
        exit(1);
    }else{
        wait(0);
    }
}
return 0;
}
