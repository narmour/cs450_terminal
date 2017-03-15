#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "constants.h"
#include "parse_cmd.h"
#include "string.h"


// function headers for executing commands passed from parse_cmd.h functions


// given cmd*c, fork and run the struct
void runCmd(struct cmd*c);


