#include "variables.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void lookup_variables(char** command) {
	int i = 0;
	while (command[i]) {
		// new char array to put it in the new command after looking up
		char* new_str = malloc(2 * strlen(command[0]));
		memset(new_str, 0, 2 * strlen(command[0]));

		int old_index = 0;
		for (old_index = 0; old_index < strlen(command[i]); old_index++) {
			char curr_char = command[i][old_index];

			// if there is '$' lookup and put the new value
			// else put the old char in the new char array
			if (curr_char == '$') {
				char* var = malloc(20);
				memset(var, 0, 20);

				if (old_index + 1 < strlen(command[i]))
					curr_char = command[i][++old_index];

				// if char is between [a-zA-Z0-9_] then put it in var
				while ((curr_char >= 'a' && curr_char <= 'z')
						|| (curr_char >= 'A' && curr_char <= 'Z')
						|| (curr_char >= '0' && curr_char <= '9')
						|| (curr_char == '_')) {

					var[strlen(var)] = curr_char;
					old_index++;

					if (old_index == strlen(command[i]))
						break;

					curr_char = command[i][old_index];
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

		command[i++] = new_str;
	}
}

