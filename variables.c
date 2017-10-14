#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "variables.h"
#include "command_parser.h"

char* command_lookup(char command[]) {
	char* new_str = malloc(256);
	memset(new_str, 0, 256);

	int old_index = 0;
	for (old_index = 0; old_index < strlen(command); old_index++) {
		char curr_char = command[old_index];

		// if there is '~' , then replace it by $HOME
		if (curr_char == '~') {
			char* value = getenv("HOME");
			// append the new value to the new str
			if (value) {
				strcat(new_str, value);
			}
		}
		// if there is '$' , then lookup and put the new value
		// else put the old char in the new char array
		else if (curr_char == '$') {
			char* var = malloc(20);
			memset(var, 0, 20);

			if (old_index + 1 < strlen(command))
				curr_char = command[++old_index];

			// if char is between [a-zA-Z0-9_] then put it in var
			while ((curr_char >= 'a' && curr_char <= 'z')
					|| (curr_char >= 'A' && curr_char <= 'Z')
					|| (curr_char >= '0' && curr_char <= '9')
					|| (curr_char == '_')) {

				var[strlen(var)] = curr_char;
				old_index++;

				if (old_index == strlen(command))
					break;

				curr_char = command[old_index];
			}

			// decrement it because it will increment again in the for loop
			old_index--;

			char* value = getenv(var);
			// append the new value to the new str
			if (value) {
				strcat(new_str, value);
			}

		} else {
			new_str[strlen(new_str)] = curr_char;
		}
	}
	return new_str;
}

void set_variable(char expression[]) {
	// split the command by '='
	char** arr = split(expression, "=");

	char* value = arr[1];
	// remove double quotes from value
	if (value[0] == '\"')
		value++;
	if (value[strlen(value) - 1] == '\"')
		value[strlen(value) - 1] = '\0';

	// split the command before '=' by space to get "export" (if found) and the key
	arr = split(arr[0], " \t");

	char* key;

	// "export" is found
	if (arr[1]) {
		key = arr[1];
	} else {
		key = arr[0];
	}

	// set the key with the new value
	setenv(key, value, 1);
}
