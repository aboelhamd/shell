#ifndef COMMAND_PARSER_H   /* Include guard */
#define COMMAND_PARSER_H

// method to return the type of command from the 8 types in constants
int get_cmd_type(char command[]);

// method to split an array by a specific delimiter
char** split(char str[], char delimiter[]);

// method to determine if a command is to be done
// in foreground or background
int is_foreground(char command[]);

#endif // COMMAND_PARSER_H
