//base class
struct cmd{
    int id;
};

// struct containing one command w/ args (if any)
struct exec{
    // identifies this type of command
    int id; // ' '
    char *cmd;
    char **args;
};

//struct containing exec cmd and filename of redir
//wc -l < inputfile > outputfile
struct redir{
    int id;// ' < or >'
    struct exec *cmd;
    // type of redir, < or >
    char r1;
    char *fd1;

    char r2;
    char *fd2;
};

struct pipecmd{
    int id;// '|'
    struct cmd *left;
    struct cmd *right;
};


// return a pointer to a redir cmd struct
struct redir* redir(char **command,int num_words);

// command is the command to be identified as exec or redir
struct cmd*  parseCmd(char **command,int num_words);

// print function for sanity checking
void printCmd(struct cmd *c);






//ls /usr/bin | head -10 | tail -5


// to parse arbitrary pipe:
// read in a command, if next word is a | read another command
