#include "exec_cmd.h"


void runCmd(struct cmd*c){
   // puts("run cmd called");
    // weird c. cant declare struct inside of switch? 
    struct exec *e;
    struct redir *r;
    struct pipecmd *p;
    int fd;
    if (c ==0){
        puts("found null");
        exit(1);
    }
    switch(c->id){

        case ' ':
            e = (struct exec *)c;
            //printf("EXEC CASE CMD %s\n",e->cmd);
            execvp(e->cmd,e->args);
            puts("didnt run cmd");
            break;
        case '>':
            r = (struct redir *)c;
            switch(r->r1){
            // switch output
            case '>':
                if(close(1) ==-1)
                    puts("couldnt close stdout");
                    // open output file
                    fd = open(r->fd1,O_WRONLY|O_CREAT|
                            O_TRUNC,0777);
                    // dup fd into stdout position
                    dup(fd);
                    execvp(r->cmd->cmd,r->cmd->args);
                    break;
                // switch input
             case '<':
                if(close(0) ==-1)
                    puts("couldnt close stdin");
                //open input file
                fd = open(r->fd1,O_RDONLY);
                //dup fd into stdin pos
                dup(fd);
                    
                //if theres an output file, redir stdout
                if(r->r2 =='>'){
                    if(close(1) ==-1)
                      puts("couldnt close stdout");
                    int fd2 = open(r->fd2,O_WRONLY|
                             O_CREAT|O_TRUNC,0777);
                    //dup fd2 into stdout
                    dup(fd2);
                 }
                 execvp(r->cmd->cmd,r->cmd->args);
                 break;


                }
       case '|':
            //puts("PIPE CASE");
            //printCmd(c);
            p = (struct pipecmd*)c;
            int pfd[2];
            pipe(pfd);


            // right side of pipe
            if(p->right !=NULL && fork() ==0){
                close(0);
                dup(pfd[0]);
                close(pfd[1]);
                runCmd(p->right);
            }
            // left side of pipe
            else{
                //puts("running left side!");
                if(p->right !=NULL){
                    close(1);
                    dup(pfd[1]);
                    close(pfd[1]);
                }
                runCmd(p->left);
            }
            break;



    }
}
