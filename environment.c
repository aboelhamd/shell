#include "environment.h"
#include "unistd.h"

char * project_path;

void setup_environment( void ){
	project_path = getcwd(project_path,(size_t)200);
}

char * get_project_path(){
	return project_path;
}
