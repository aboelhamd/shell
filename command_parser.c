//#include "main.h"
#include "command_parser.h"
#include "constants.h"
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>


char** split( char str[] )
{
	char ** res = malloc((size_t)100);
	memset(res,0,(size_t)100);
	char *  p    = strtok (str, " ");


	int i = 0;
	// split string and append tokens to 'res'
	while (p){
		printf("%s\n",p);

		res[i] = p;
		i++;

		p = strtok (NULL, " ");
	}

	return res;
}

int matches(char* regex_str, char* command){
	int error;
	regex_t regex;

	error = regcomp(&regex,regex_str,REG_EXTENDED);


	if(!error){
		error = regexec(&regex, command , (size_t)0 , NULL , 0);
	}

	regfree(&regex);

	return !error;
}

int need_lookup( char command[] ){
	char* regex_str = "\\$[a-zA-Z_][a-zA-Z0-9_]*";

	return matches(regex_str,command);
}

int is_exp( char command[] ){
	char* regex_str = "^[a-zA-Z_][a-zA-Z0-9_]*=[a-zA-Z0-9_]+(\\s+&)?$";

	return matches(regex_str,command);
}

int is_foreground( char command[] ){
	char* regex_str = "&\\s*$";

	return !matches(regex_str,command);
}

int is_comment( char command[] ){
	char* regex_str = "^\\s*#";

	return matches(regex_str,command);
}

int is_cd( char command[] ){
	char* regex_str = "^\\s*cd";

	return matches(regex_str,command);
}

int is_echo( char command[] ){
	char* regex_str = "^\\s*echo";

	return matches(regex_str,command);
}

int is_history( char command[] ){
	return !strcmp(command,"history");
}

int is_command_path( char command[] ){
	char* regex_str = "^\\s*/";

	return matches(regex_str,command);
}

char** clean_command( char command[] , int cmdType , int foreground ){

	char** res = split(command);

	// if & found , remove it
	if(!foreground){
		// make the last string null
		res[sizeof res*4/sizeof res[0]-2] = '\0';
//		printf("here  %d\n",sizeof res*4/sizeof res[0]-2);
	}

	if((cmdType==TYPE_CD)|(cmdType==TYPE_ECHO)){
		res++;
	}

	return res;
}

char** parse_command( char command[] , int* cmdType , int* foreground , int* lookup){
	// These 3 types do not need lookup for variables
	if(is_comment(command)){
		*cmdType = TYPE_COMMENT;
	}else if(is_exp(command)){
		*cmdType = TYPE_EXPRESSION;
	}else if(is_history(command)){
		*cmdType = TYPE_HISTORY;
	}
	// These 3 types may be need look up for variables
	else if(is_command_path(command)){
		*cmdType = TYPE_CMD_PATH;
	}else if(is_cd(command)){
		*cmdType = TYPE_CD;
	}
	else if(is_echo(command)){
		*cmdType = TYPE_ECHO;
	}
	else {
		*cmdType = TYPE_CMD;
	}

	// need lookup
	*lookup = need_lookup(command);

	// foreground or background
	*foreground = is_foreground(command);

	return clean_command(command,*cmdType,*foreground);
//	return split(command);
}



/*int main (void)
{
	char str[] = "    cd /home     &  ";

//	printf("%s\n",trim(str));
//
//	printf("%d\n",need_exp_eval(str));
//	printf("%d\n",is_exp(str));
//	printf("%d\n",is_foreground(str));
//	printf("%d\n",is_comment(str));
//	printf("%d\n",is_command_path(str));
	int cmdType=-1, ground=-1, lookup=-1;




	// print the result

	//printf("%d   %d\n",cmdType, ground);

	char** res =  parse_command(str,&cmdType,&ground,&lookup);
	printf("%d  %d  %d\n",cmdType,ground,lookup);
	if(res){
        int i = 0;
        while (res[i]){
            printf ("res[%d] = %s\n", i, res[i]);
            i++;
        }
    }
//	printf("Hello\n");

	//execv(res[0],res);
//    printf("%d\n",execv("/bin/echo",res));
//	printf("%s\n",getenv("PATH"));

  return 0;
}*/
