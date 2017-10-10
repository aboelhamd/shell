#include "variables.h"

char table[1000];
int length = 0;

const char* lookup_variable(const char* key) {
	// if key is found , return its value
	// if not return an empty string
	char* value = "";
	for (int i = 0; i < length; i += 2) {
		if (!strcmp(key, table[i])) {
			value = table[i + 1];
		}
	}
	return value;
}

void set_variable(const char* key, const char* value) {
	// if the key is found , update its value
	for (int i = 0; i < length; i += 2) {
		if (!strcmp(key, table[i])) {
			table[i + 1] = value;
			return;
		}
	}

	// if key is not found , add it to table
	table[length++] = key;
	table[length++] = value;
}

void print_all_variables(void) {
	for (int i = 0; i < length; i += 2) {
		printf("key : %s  ,  value : %s\n", table[i], table[i + 1]);
	}
}
