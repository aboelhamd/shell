#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "commands.h"
#include "command_parser.h"
#include "file_processing.h"

int cd(char command[]) {
	// split into 2 strings by space
	char** str = split(command, " \t");

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
	char** no_quotes = split(arr[0], " \t");

	// append the first part (without quotes) to handled message without "echo"
	int i = 1;
	while (no_quotes[i]) {
		strcat(handled_msg, no_quotes[i++]);
		strcat(handled_msg, " ");
	}

	// if there is 2 elements in the splitted array ,
	// then there is ("")
	if (arr[1]) {
		strcat(handled_msg, arr[1]);
	}

	// if there is 2 elements in the splitted array ,
	// then there is another part after the quotes
	if (arr[2]) {
		// split the last part by space
		char** no_quotes = split(arr[2], " \t");
		// append the last part (without quotes) to handled message
		i = 0;
		while (no_quotes[i]) {
			strcat(handled_msg, " ");
			strcat(handled_msg, no_quotes[i++]);
		}
	}

	printf("%s\n", handled_msg);
}

void cmd_no_path(char** command) {
	// get the PATH
	char* path = getenv("PATH");

	// make a copy
	char path_copy[512];
	memset(path_copy, 0, 512);
	strcat(path_copy, path);

	// and split it into directories
	char** dirs = split(path_copy, ":");

	// for each directory , try to execute the command
	int i = 0;
	while (dirs[i]) {
		// make copy of the directory
		char dir_copy[512];
		memset(dir_copy, 0, 512);
		strcat(dir_copy, dirs[i++]);

		// append the command to the directory
		strcat(dir_copy, "/");
		strcat(dir_copy, command[0]);

		// execute the command with current directory
		execv(dir_copy, command);
	}
//	perror("There is no such command\n");
}

void print_history() {
	FILE* file = get_history_file();

	char* str = malloc(512);

	while (fgets(str, 512, file)) {
		printf("%s", str);
	}

	fclose(file);
	if (str)
		free(str);
}
