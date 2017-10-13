#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_processing.h"
#include "environment.h"

/*
 history file section
 */

FILE* get_history_file() {
	// open the file for reading and writing
	// creates it if it foesn't exist
	return fopen(get_history_path(), "a+");

}

void write_to_history(char* line) {
	FILE* file = get_history_file();
	fputs(line, file);
	fputs("\n", file);
	fclose(file);
}

/*
 log file section
 */

FILE* get_log_file() {
	// open the file for reading and writing
	// creates it if it foesn't exist
	return fopen(get_log_path(), "a+");
}

void write_to_log(char* line) {
	FILE* file = get_log_file();
	fputs(line, file);
	fputs("\n", file);
	fclose(file);
}

/*
 CommandsBatch file section
 */

FILE* get_commands_batch_file(char* batch_path) {
	// open the file for reading and writing
	// creates it if it foesn't exist
	return fopen(batch_path, "r");
}
