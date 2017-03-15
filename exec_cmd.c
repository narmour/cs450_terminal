#include "exec_cmd.h"


void runCmd(struct cmd*c){
    puts("run cmd called");
    // weird c. cant declare struct inside of switch? 
    struct exec *e;
    struct redir *r;
    struct pipecmd *p;

    pid_t pid;
    switch(c->id){
        case ' ':
            e = (struct exec *)c;
            pid = fork();
            if(pid ==-1){
                puts("ERROR");
                break;
            }
            if(pid ==0){
                execvp(e->cmd,e->args);
                puts("didnt run cmd");
            }
            break;





    }



}
