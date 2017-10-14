#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include "command_parser.h"
#include "constants.h"
#include "environment.h"
#include "variables.h"
#include "commands.h"
#include "file_processing.h"

typedef enum {
	false = 0, true = 1
} bool;

void shell_loop(bool input_from_file, char line[512]);

void write_in_log(int sig);

int main(int argc, char *argv[]) {
	setup_environment();
	// receive child signal to write to log
	signal(SIGCHLD, write_in_log);

	bool input_from_file = argc > 1;
	char* batch_path = "";
	if (input_from_file) {
		batch_path = argv[1];
	}

	shell_loop(input_from_file, batch_path);
}

void write_in_log(int sig) {
	// reset signal
	signal(SIGCHLD, write_in_log);
	write_to_log("Child process is terminated");
}

void shell_loop(bool input_from_file, char* batch_path) {
	// let shell starts from home
	cd("");

	bool from_file = input_from_file;

	// command line
	char line[512];

	// batch file
	FILE* batch = get_commands_batch_file(batch_path);
	// if batch file is not found
	if (!batch) {
		printf("There is no batch file in the given path\n");
		from_file = false;
	}

	while (true) {
		if (from_file) {
			//read next instruction from file
			//if there is no more lines , close the file
			if (fgets(line, 512, batch)) {
				// remove the '\n' from the line
				if (line[strlen(line) - 1] == '\n')
					line[strlen(line) - 1] = '\0';

				printf("%s\n", line);
			} else {
				fclose(batch);
				from_file = false;
				continue;
			}
		} else {
			//read next instruction from console
			printf("shell> ");
			if (fgets(line, 512, stdin)) {
				line[strcspn(line, "\n")] = 0;
			} else {
				exit(0);
			}
		}

		// if input is blank , ignore and start again
		if (strlen(line) == 0) {
			continue;
		}
		// add command to history
		write_to_history(line);

		// do lookup
		char* new_line = command_lookup(line);

		// get command type
		int cmdType = get_cmd_type(new_line);
		// is the command in foreground or background
		int foreground = is_foreground(new_line);

		// remove '&' if background
		if (!foreground)
			remove_and(new_line);

		if (cmdType == TYPE_EXIT) {
			// exit
			exit(0);
		} else if (cmdType == TYPE_COMMENT) {
			// do nothing
		} else if (cmdType == TYPE_HISTORY) {
			print_history();
		} else {

			if (cmdType == TYPE_EXPRESSION) {
				set_variable(new_line);
			} else if (cmdType == TYPE_CD) {
				cd(new_line);
			} else if (cmdType == TYPE_ECHO) {
				echo(new_line);
			} else {
				// execute in a child process
				pid_t child_pid;
				int child_status;

				child_pid = fork();
				if (child_pid == 0) {
					// writing to log
					write_to_log("Child process is created");

					//split the line by space
					char ** command = split(new_line, " \t");

					if (cmdType == TYPE_CMD_PATH) {
						execv(command[0], command);
					} else if (cmdType == TYPE_CMD) {
						cmd_no_path(command);
					}
				} else {
					if (foreground) {
						pid_t tpid;
						do {
							tpid = wait(&child_status);
						} while (tpid != child_pid);
					}
				}
			}
		}

	}
}
