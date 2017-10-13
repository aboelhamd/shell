#ifndef FILE_PROCESSING_H_   /* Include guard */
#define FILE_PROCESSING_H_
#include "stdio.h"

/*
 history file basic functions' prototypes
 */
// gets the history file and opens it
FILE* get_history_file();
// write a line to the history file
void write_to_history(char* line);

/*
 log file basic functions' prototypes
 */
// gets the log file and opens it
FILE* get_log_file();
// write a line to the log file
void write_to_log(char* line);

/*
 CommandsBatch file basic functions' prototypes
 */
// gets the batch file and opens it to be read
FILE* get_commands_batch_file(char* batch_path);

#endif // FILE_PROCESSING_H_
