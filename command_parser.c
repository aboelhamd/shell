//#include "main.h"
#include "command_parser.h"
#include "constants.h"
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

char** split(char str[], char delimiter[]) {
	char ** res = malloc((size_t) 100);
	memset(res, 0, (size_t) 100);

	char * p = strtok(str, delimiter);

	int i = 0;
	// split string and append tokens to 'res'
	while (p) {
		res[i] = p;
		i++;

		p = strtok(NULL, delimiter);
	}

	return res;
}

int matches(char* regex_str, char* command) {
	int error;
	regex_t regex;

	error = regcomp(&regex, regex_str, REG_EXTENDED);

	if (!error) {
		error = regexec(&regex, command, (size_t) 0, NULL, 0);
	}

	regfree(&regex);

	return !error;
}

int is_foreground(char command[]) {
	char* regex_str = "&\\s*$";

	return !matches(regex_str, command);
}

int is_exp(char command[]) {
	char* regex_str = "^[a-zA-Z_][a-zA-Z0-9_]*=[a-zA-Z0-9_]+(\\s+&)?$";

	return matches(regex_str, command);
}

int is_comment(char command[]) {
	char* regex_str = "^\\s*#";

	return matches(regex_str, command);
}

int is_cd(char command[]) {
	char* regex_str = "^\\s*cd";

	return matches(regex_str, command);
}

int is_echo(char command[]) {
	char* regex_str = "^\\s*echo";

	return matches(regex_str, command);
}

int is_history(char command[]) {
	char* regex_str = "^\\s*history\\s*$";

	return matches(regex_str, command);
}

int is_exit(char command[]) {
	char* regex_str = "^\\s*exit\\s*$";

	return matches(regex_str, command);
}

int is_command_path(char command[]) {
	char* regex_str = "^\\s*/";

	return matches(regex_str, command);
}

int get_cmd_type(char command[]) {
	if (is_comment(command)) {
		return TYPE_COMMENT;
	} else if (is_exp(command)) {
		return TYPE_EXPRESSION;
	} else if (is_history(command)) {
		return TYPE_HISTORY;
	} else if (is_exit(command)) {
		return TYPE_EXIT;
	} else if (is_command_path(command)) {
		return TYPE_CMD_PATH;
	} else if (is_cd(command)) {
		return TYPE_CD;
	} else if (is_echo(command)) {
		return TYPE_ECHO;
	} else {
		return TYPE_CMD;
	}
}

//char** clean_command(char command[], int cmdType, int foreground) {
//
//	char** res = split(command, " ");
//
//	// if & found , remove it
//	if (!foreground) {
//		// make the last string null
//		res[sizeof res * 4 / sizeof res[0] - 2] = '\0';
//	}
//
//	if ((cmdType == TYPE_CD) | (cmdType == TYPE_ECHO)) {
//		res++;
//	}
//
//	return res;
//}

