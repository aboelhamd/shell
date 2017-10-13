#include "commands.h"
#include "command_parser.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"

int cd(char command[]) {
	// split into 2 strings by space
	char** str = split(command, " ");

	printf("%s\n", str[1]);

	if (str[1])
		return chdir(str[1]);

	return -1;
}

void echo(char command[]) {
	char handled_msg[512];
	memset(handled_msg, 0, 512);

	// split the message by double quotes
	char** arr = split(command, "\"");

	// split the first part by space
	char** no_quotes = split(arr[0], " ");

	// append the first part (without quotes) to handled message without echo
	int i = 1;
	while (no_quotes[i]) {
		strcat(handled_msg, no_quotes[i++]);
		strcat(handled_msg, " ");
	}

	// if there is 2 elements in the splitted array ,
	// then there is (")
	if (arr[1]) {
		strcat(handled_msg, arr[1]);
	}

	printf("%s\n", handled_msg);
}
