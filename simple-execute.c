/*  Operating systems: Assignment 1
 *  ----------------------------------
 *  Name: Jake Epstein
 *  Institution: CUHK
 *  Purpose: The following program, when paired with simple-shell.c, can execute all
 *  basic bash commands with up to 2 pipes
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define MAX 10
struct scommand
{
	char **command;

}; 

int shell_execute(char ** args, int argc)
{
	int child_pid, wait_return, status;
	int numcommands = 1;
	int *csize = malloc(3*sizeof(int));
	int size = 0;
	//count the number of simple commands
	for(int i = 0; i < argc-1; i++) {
		if(strcmp(args[i], "|") == 0) {
			csize[numcommands-1] = size+1;
			numcommands++;
			size = 0;
		}
		size++;
	}
	csize[numcommands-1] = size+1;

	//malloc a structure for the number of commands
	struct scommand *commands = malloc(numcommands*sizeof(struct scommand));
	
	//malloc each string in the list of structures
	for(int i = 0; i < numcommands; i++) {
		commands[i].command = malloc(csize[i]*sizeof(char *));
		for(int y = 0; y < csize[i]; y++) {
			commands[i].command[y] = malloc(10*sizeof(char));
		}
	}

	//parse each simple command into the structure
	int z, b = 0;
	for(int y = 0; y < argc-1; y++) {
		if(strcmp(args[y], "|") == 0){
			commands[z].command[b] = NULL;
		//	printf("commands[%d].commands[%d]: %s\n", z, b , commands[z].command[b]);
			z++;
			b = 0;
		} else {
			commands[z].command[b] = args[y];
		//	printf("commands[%d].commands[%d]: %s\n", z, b, commands[z].command[b]);
			b++;
		}
	}

	commands[z].command[b] = NULL;
//	printf("commands[%d].commands[%d]. %s\n", z, b, commands[z].command[b]);
	
	int tmpin =  dup(0);
	int tmpout = dup(1);
	
	int fdin = dup(tmpin);
	int fdout;

	//loop through all commands
	for(int y=0; y<numcommands; y++) {
		dup2(fdin, 0);
		close(fdin);
		//if last command, create output
		if (y == numcommands-1) {
		//	printf("last command\n");
			fdout = dup(tmpout);
		} else { //otherwise, create pipe
			
		//	printf("pipe created\n");
			
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}

		//direct output
		dup2(fdout, 1);
		close(fdout);

		//if find the word EXIT within a command, quit
		if ( strcmp(commands[y].command[0], "EXIT") == 0 ) return -1;

		//create children
		if( (child_pid = fork()) < 0 ) {
			fprintf(stderr, "fork() error \n");
		//if child
		} else if (child_pid == 0 ) {
			//execute
			if ( execvp(commands[y].command[0], commands[y].command) < 0)
			{ 
				fprintf(stderr, "execvp error \n"); 
				exit(-1);
			}

		} else {
			if ( (wait_return = wait(&status) ) < 0) printf("wait error \n");
		}

	}
	
	//clean up i/o
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout); 
	
	return 0;
}
