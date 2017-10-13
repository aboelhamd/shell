#ifndef COMMANDS_H_   /* Include guard */
#define COMMANDS_H_

/*
 - This function should be responsible for implementing the "cd" shell command
 */
int cd(char command[]);

/*
 - This function should be responsible for implementing the "echo" shell command
 - the command will be ready for printing , should handle with/out quotes messages
 */
void echo(char command[]);

/*
 - This function should be responsible for implementing shell commands without
 - their path
 */
void cmd_no_path(char** command);

#endif // COMMANDS_H_
