#include "exec_cmd.h"


void runCmd(struct cmd*c){
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
            //printf("ARGS: %s\n",e->args[2]);
            if(execvp(e->cmd,e->args) ==-1)
                exit(1);
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
                    if(fd ==-1){
                        puts("error opening");
                        exit(1);
                    }

                    // dup fd into stdout position
                    dup(fd);
                    if(execvp(r->cmd->cmd,r->cmd->args) ==-1){
                        puts("error executing");
                        exit(1);
                    }
                    if(close(fd) == -1){
                        puts("error closing");
                        exit(1);
                    }
                    break;
                // switch input
             case '<':
                if(close(0) ==-1)
                    puts("couldnt close stdin");
                //open input file
                fd = open(r->fd1,O_RDONLY);
                if(fd ==-1){
                    puts("error opening");
                    exit(1);
                }
                //dup fd into stdin pos
                dup(fd);
                    
                //if theres an output file, redir stdout
                if(r->r2 =='>'){
                    if(close(1) ==-1){
                      puts("couldnt close stdout");
                      exit(1);
                    }
                    int fd2 = open(r->fd2,O_WRONLY|
                             O_CREAT|O_TRUNC,0777);
                    if(fd2 ==-1){
                        puts("error opening");
                        exit(1);
                    }
                    //dup fd2 into stdout
                    dup(fd2);
                 }
                 if(execvp(r->cmd->cmd,r->cmd->args) ==-1)
                     exit(1);
                 break;


                }
       case '|':
            p = (struct pipecmd*)c;
            int pfd[2];
            if(pipe(pfd) ==-1){
                puts("error creating pipes");
                exit(1);
            }


            // right side of pipe
            if(p->right !=NULL && fork() ==0){
               if(close(0) ==-1)
                   exit(1);
                dup(pfd[0]);
                if(close(pfd[1]) ==-1)
                    exit(1);
                runCmd(p->right);
            }
            // left side of pipe
            else{
                if(p->right !=NULL){
                    if(close(1) ==-1)
                        exit(1);
                    dup(pfd[1]);
                    if(close(pfd[1]) ==-1)
                        exit(1);
                }
                runCmd(p->left);
            }
            break;



    }
}
