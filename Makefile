#compiler variable
CC=gcc
#flag compile variable
CFLAGS=-c

all : shell

shell : main.o command_parser.o commands.o constants.o environment.o variables.o file_processing.o
	$(CC) main.o command_parser.o commands.o constants.o environment.o variables.o file_processing.o -o shell

main.o : main.c command_parser.h constants.h environment.h variables.h commands.h file_processing.h
	$(CC) $(CFLAGS) main.c

command_parser.o : command_parser.c command_parser.h constants.h
	$(CC) $(CFLAGS) command_parser.c

commands.o : commands.c command_parser.h commands.h file_processing.h
	$(CC) $(CFLAGS) commands.c

constants.o : constants.c constants.h
	$(CC) $(CFLAGS) constants.c

environment.o : environment.c environment.h
	$(CC) $(CFLAGS) environment.c

variables.o : variables.c command_parser.h variables.h
	$(CC) $(CFLAGS) variables.c

file_processing.o : file_processing.c environment.h file_processing.h
	$(CC) $(CFLAGS) file_processing.c

clean : 
	rm -rf *o shell