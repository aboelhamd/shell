#ifndef VARIABLES_H_   /* Include guard */
#define VARIABLES_H_

// This method takes a string and look up for variables in it
char* command_lookup(char old_str[]);

// This method takes the expression string "x=$HOME"
// and save the variable with the new value
void set_variable(char expression[]);

void print_all_variables(void);

#endif // VARIABLES_H_
