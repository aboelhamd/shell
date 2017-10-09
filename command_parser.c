//#include "main.h"
#include "command_parser.h"
#include "constants.h"
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

char** parse_command( char command[] , int* cmdType , int* ground , int* exp_eval)
{

	if(is_comment(command)){
		cmdType = TYPE_COMMENT;
	}else if(is_exp(command)){
		cmdType = TYPE_EXPRESSION;
	}else if(is_history(command)){
		cmdType = TYPE_EXPRESSION;
	}else {
		if(is_command_path(command)){
			cmdType = TYPE_CMD_PATH;
		}else if(is_cd(command)){
			cmdType = TYPE_CD;
		}
		else if(is_ech(command)){
			cmdType = TYPE_CD;
		}
		else if(is_cd(command)){
			cmdType = TYPE_CD;
		}
	}

    	/* if first char is # , then it's a comment
    	 we ignore the whole command

    	 if first char is / , then it's the command path
    	 we send it to expression function */


    	/* if p == cd
    	 we send it to expression function

    	 if p == history

    	 if p == printenv

    	 if p == exit

    	 if p == echo
    	 we send it to expression function*/

    	/* if p has = then it's an expression
    	 if p has $ then it's and expression evaluation */

    }

	return NULL;
}

char** split( char* str )
{
	char ** res  = NULL;
	char *  p    = strtok (str, " ");
	int n_spaces = 0;


	// split string and append tokens to 'res'
	while (p){
	  res = realloc (res, sizeof (char*) * ++n_spaces);

	  if (res == NULL)
	    break; /* memory allocation failed */

	  res[n_spaces-1] = p;

	  p = strtok (NULL, " ");
	}

	return res;
}

char *trim(char *str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while( isspace((unsigned char) *frontp) ) { ++frontp; }
    if( endp != frontp )
    {
        while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
    }

    if( str + len - 1 != endp )
            *(endp + 1) = '\0';
    else if( frontp != str &&  endp == frontp )
            *str = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
            while( *frontp ) { *endp++ = *frontp++; }
            *endp = '\0';
    }


    return str;
}

int need_exp_eval( char command[] ){
	int error;
	regex_t regex;
	char cmd_copy[strlen(command)];
	strcpy(cmd_copy,command);

	error = regcomp(&regex,"\\$[a-zA-Z_][a-zA-Z0-9_]*",REG_EXTENDED);


	if(!error){
		error = regexec(&regex, cmd_copy , (size_t)0 , NULL , 0);
	}

	regfree(&regex);

	return !error;
}

int is_exp( char command[] ){
	int error;
	regex_t regex;

	error = regcomp(&regex,"^[a-zA-Z_][a-zA-Z0-9_]*=[a-zA-Z0-9_]+(\\s+&)?$",REG_EXTENDED);

	if(!error){
		error = regexec(&regex, command , (size_t)0 , NULL , 0);
	}

	regfree(&regex);

	return !error;
}

int is_foreground( char command[] ){
	// if last str == & then it's background
	return command[strlen(command)-1]!='&';
}

int is_comment( char command[] ){
	return command[0] == '#';
}

int is_cd( char command[] ){
	return command[0] == '#';
}

int is_echo( char command[] ){
	return command[0] == '#';
}

int is_history( char command[] ){
	return !strcmp(command,"history");
}

int is_command_path( char command[] ){
	return command[0] == '/';
}


int main (void)
{
	char str[] = "    x12=4     &  ";

	printf("%s\n",trim(str));

	printf("%d\n",need_exp_eval(str));
	printf("%d\n",is_exp(str));
	printf("%d\n",is_foreground(str));
	printf("%d\n",is_comment(str));
	printf("%d\n",is_command_path(str));
	//int cmdType=-1, ground=-1;




	// print the result

	//printf("%d   %d\n",cmdType, ground);

	char** res =  split(str);
	if(res){
        int i = 0;
        while (res[i]){
            printf ("res[%d] = %s\n", i, res[i]);
            i++;
        }
    }

	/*//execv(res[0],res);
    printf("%d\n",execv("/bin/echo",res));
	printf("%s\n",getenv("PATH"));*/

  return 0;
}
