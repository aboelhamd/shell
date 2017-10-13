#include "environment.h"
#include <unistd.h>
#include <string.h>

char * project_path;
char history_path[512];
char log_path[512];

void setup_environment(void) {
	// project path is the current working path when program starts
	project_path = getcwd(project_path, (size_t) 200);

	/* setup the history file path  */
	memset(history_path, 0, 512);
	// append file's relative directory (project directory) to the path
	strcat(history_path, get_project_path());
	// append file name to the path
	strcat(history_path, "/history.txt");

	/* setup the log file path  */
	memset(log_path, 0, 512);
	// append file's relative directory (project directory) to the path
	strcat(log_path, get_project_path());
	// append file name to the path
	strcat(log_path, "/log.txt");
}

char * get_project_path() {
	return project_path;
}
char * get_history_path() {
	return history_path;
}
char * get_log_path() {
	return log_path;
}
