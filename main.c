#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include "command_parser.h"

typedef enum {
	false = 0, true = 1
} bool;

void start(bool read_from_file);
void shell_loop(bool input_from_file);

int main(int argc, char *argv[]) {
	printf("Hello World\n");
//    setup_environment();

	char line[512];
	char** command;
	int cmdType, foreground, lookup;

	while (1) {
		if (fgets(line, 512, stdin)) {
			line[strcspn(line, "\n")] = 0;
		}

		command = parse_command(line, &cmdType, &foreground, &lookup);

		pid_t child_pid;
		int child_status;

		child_pid = fork();
		if (child_pid == 0) {
			/* This is done by the child process. */

			execvp(command[0], command);

			/* If execv returns, it must have failed. */

			printf("Unknown command\n");
			exit(0);
		} else {
			/* This is run by the parent.  Wait for the child
			 to terminate. */
			pid_t tpid;
			do {
				tpid = wait(&child_status);
//				if(tpid != child_pid) process_terminated(tpid);
			} while (tpid != child_pid);

			printf("command has executed\n");
			//return child_status;
		}
	}

//    if( argc > 1 ){
//        start(true);
//    }
//    else{
//        start(false);
//    }

	return 0;
}

void start(bool read_from_file) {
	cd(""); // let shell starts from home

	if (read_from_file) {
		// file processing functions should be called from here

		shell_loop(true);
	} else {
		shell_loop(false);
	}
}

void shell_loop(bool input_from_file, char line[512], char** command,
		int cmdType, foreground, lookup) {

	bool from_file = input_from_file;

	while (true) {
		if (from_file) {
			//read next instruction from file

			// if end of file {from_file = false; continue;}
		} else {
			//read next instruction from console
			if (fgets(line, 512, stdin)) {
				line[strcspn(line, "\n")] = 0;
			}
		}

		// parsing the command
		command = parse_command(line, &cmdType, &foreground, &lookup);

		if(cmdType == TYPE_EXIT){
			// exit
			exit(0);
		}else if (cmdType == TYPE_COMMENT){
			// do nothing
			return;
		}else if (cmdType == TYPE_HISTORY){
			// print history
		}else if (cmdType == TYPE_EXPRESSION){
			// save variable in table
		}else {
			// do lookup

			if (cmdType == TYPE_CD){
				// do it in parent process
			}else if (cmdType == TYPE_ECHO){
				// we want to print the whole string as it is
				// in parent process too
			}else if (cmdType == TYPE_CMD_PATH){
				// execv(command[0],command);
			}else if (cmdType == TYPE_CMD){
				// execv(path + command[0],command);
				// we try each directory in the path
			}
		}


		pid_t child_pid;
		int child_status;


		child_pid = fork();
		if (child_pid == 0) {
			// This is done by the child process

			execvp(command[0], command);

			// If execv returns, it must have failed.

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
