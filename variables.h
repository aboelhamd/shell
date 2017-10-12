#ifndef VARIABLES_H_   /* Include guard */
#define VARIABLES_H_

// This method takes an array of strings (which was parsed earlier)
// and lookup for every variable in it and replace them with their values
void lookup_variables(char** command);


void print_all_variables(void);

#endif // VARIABLES_H_
