#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include "command_parser.h"
#include "constants.h"
#include "environment.h"
#include "variables.h"

typedef enum {
	false = 0, true = 1
} bool;

void start(bool read_from_file);

void shell_loop(bool input_from_file, char line[512]);

int main(int argc, char *argv[]) {
	bool input_from_file = false;
	char line[512];

	shell_loop(input_from_file, line);

	return 0;
}

void start(bool read_from_file) {
	cd(""); // let shell starts from home

	if (read_from_file) {
		// file processing functions should be called from here

//		shell_loop(true);
	} else {
//		shell_loop(false);
	}
}

void shell_loop(bool input_from_file, char line[512]) {

	bool from_file = input_from_file;

	while (true) {
		if (from_file) {
			//read next instruction from file

			// if end of file {from_file = false; continue;}
		} else {
			//read next instruction from console
			printf("shell : ");
			if (fgets(line, 512, stdin)) {
				line[strcspn(line, "\n")] = 0;
			}
		}

		// get command type
		int cmdType = get_cmd_type(line);

		if (cmdType == TYPE_EXIT) {
			// exit
			exit(0);
		} else if (cmdType == TYPE_COMMENT) {
			// do nothing
		} else if (cmdType == TYPE_HISTORY) {
			// print history
		} else {

			// do lookup
			char* new_line = command_lookup(line);

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
					// This is done by the child process

					// split the line by space
					char ** command = split(new_line, "\\s");

					if (cmdType == TYPE_CMD_PATH) {
						execv(command[0], command);
					} else if (cmdType == TYPE_CMD) {
						cmd_no_path(command);
					}

					printf("Unknown command\n");
					exit(0);
				} else {
					// This is run by the parent.  Wait for the child
					// to terminate

					pid_t tpid;
					do {
						tpid = wait(&child_status);
						//if(tpid != child_pid) process_terminated(tpid);
					} while (tpid != child_pid);

					printf("child has finished\n");
					//return child_status;
				}
			}
		}

	}
}
