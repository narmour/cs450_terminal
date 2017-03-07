#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "parse_cmd.h"


void printCmd(struct cmd *c){
    // weird c. cant declare struct inside of switch? 
    struct exec *e;
    struct redir *r;
    switch(c->id){
        case ' ':
            e = (struct exec *)c;
            printf("CMD: %s\n",e->cmd);
            int i =0;
            printf("ARGS: ");
            while(e->args[i] !=NULL){
                printf("%s ",e->args[i]);
                i++;
            }
            printf("\n");
            break;
        case '>':
            r = (struct redir*)c;
            // print the redir exec cmd
            printCmd((struct cmd*)r->cmd);

            //print contents of redir
            printf("redir contents:  %c %s",r->r1,r->fd1);
            if(r->r2 !=NULL)
                printf(" %c %s\n",r->r2,r->fd2);
            puts("");
            //printf("redir exec: %s\n\n",r->cmd->cmd);
            break;

    }
}


/*
int readCmd(char **line,int num_words){

    char **command_text = (char **)malloc(num_words * sizeof(char**)+ 1);

    int i =0;
    while(i <num_words){
        if(*line[i] =='|'){
            break;
        }
        command_text[i] = line[i];
        i+=1;
    }

    printCmd(parseCmd(command_text,i));
    

    return i;


}
*/

struct redir* createRedir(char **command,int num_words){

	struct redir *r = (struct redir*)malloc(sizeof(struct redir));
    r->id = '>';
    // parse components of redir




	// get the exec command first
	int j =0;
	char **e = (char**)malloc(sizeof(char**) * num_words);
	while(j <num_words){
		if(*command[j] == '>' ||
			*command[j] == '<')
				break;
		    e[j] = command[j];
			j++;

		}
    struct exec *ex = (struct exec*)malloc(sizeof(struct exec));
    ex->id =' ';
    ex->cmd = e[0];
    ex->args = e;
    r->cmd = ex;
    
    // get rest of redir struct    
    //j = > or <   j+1 = filename
    r->r1 = *command[j++];
	r->fd1 = command[j++];
	// this means its an input redir into an output redir
	if(j < num_words){
		r->r2 = *command[j++];
		r->fd2 = command[j];
    }
    return r;



}

struct exec* createExec(char **command,int num_words){
    struct exec *ex = (struct exec*)malloc(sizeof(struct exec));
    ex->id =' ';
    ex->cmd = command[0];
    ex->args = command;

    return ex;




}


struct cmd* parseCmd(char **command,int num_words){
    int i =0;
    // bool for redir, 1 if redir, 0 if not == exec
    int redir =0;
    //bool for pipe, 1 if pipe, 0 if no pipe
    int pipe = 0;
    while (i < num_words){
        switch(*command[i]){
            case '>':
            case '<':
                redir =1;
                i++;
                break;
            case '|':
                pipe =1;
                i++;
                break;
            default: i++;
        }
    }
   
   if(pipe ==1){
       puts("its a pipe cmd");
       //struct pipe *p = (struct pipe*)malloc(sizeof(struct pipe));

   }
   
   else if(redir ==1){
        // set c as the redir
        return (struct cmd*)createRedir(command,num_words);
	}
	else{
        return (struct cmd*)createExec(command,num_words);
	}
}



/*
void parseLine(char *line[MAX_LINE_WORDS+1],int num_words){
    
    int i =0;
    while (i < num_words){
        switch(*line[i]){
            case '|':
                puts("found pipe");
                i+=1;
        }
        i += readCmd(&line[i],num_words -i);

        // switch on next character after a command
        //exec command c
    }

}
*/





