/* Author(s): treewolf - Section 04
 *
 * This is a lab6.c the csc60mshell
 * This program serves as a skeleton for starting for lab 6.
 * Student is required to use this program to build a mini shell
 * using the specification as documented in direction.
 * Date: Fall 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLINE 80
#define MAXARGS 20
#define MAX_PATH_LENGTH 50
#define TRUE 1

/* function prototypes */
void process_input(int argc, char **argv); 
int parseline(char *cmdline, char **argv);
void handle_redir(int count, char *argv[]);

/* ----------------------------------------------------------------- */
/*                  The main program starts here                     */
/* ----------------------------------------------------------------- */
int main(void)
{
    char cmdline[MAXLINE];
    char *argv[MAXARGS];
    int argc;
    int status;
    pid_t pid;

    /* Loop forever to wait and process commands */
    while (TRUE) {
	/* Print your shell name: csc60mshell (m for mini shell) */
	printf("csc60msh$> ");

	/* Read the command line */
	fgets(cmdline, MAXLINE, stdin);

	/* Call parseline to build argc/argv: their limits declared above */

	argc = parseline(cmdline, argv);

	/* If user hits enter key without a command, continue to loop again at the beginning */
	/*  Hint: if argc is zero, no command declared */
	/*  Hint: look up for the keyword "continue" in C */

	/* Handle build-in command: exit, pwd, or cd  */

	/*
 	// BEGIN DEBUGGING 
	printf("ARGC = %d\n",argc);
	int dbg;
	for(dbg=0; dbg<argc; ++dbg)
		printf("ARGV %d : %s\n", dbg,argv[dbg]);
	// END DEBUGGING	
	*/

	if(argc==0){
		continue;
	}
	if(strcmp(argv[0],"exit")==0){
		if(argc>1){
			printf("exit: Expression syntax\n");
			continue;
		}
		exit(EXIT_SUCCESS);
	}
	else if(strcmp(argv[0],"cd")==0){
		if(argv[1]==NULL){
			chdir(getenv("HOME"));
		}
		else{
			if(argc>2)
				printf("cd: too many arguments.\n");
			else{
				if(chdir(argv[1])==-1)
					printf("Error changing directory\n");
			}
		}		
	}
	else if(strcmp(argv[0],"pwd")==0){
		if(argc>1){
			printf("pwd: ignoring non-option arguments\n");
		}
		char buff[MAX_PATH_LENGTH];
		printf("%s\n",getcwd(buff,MAX_PATH_LENGTH));
	}
	else if(strcmp(argv[0],"help")==0){
		printf("\n\t-------------------------------\n");
		printf("\tCommands to use: cd, pwd, exit\n");
		printf("\tWritten by the all omniscent treewolf\n");
		printf("\t-------------------------------\n\n");
	}
	else{
		
		/* Else, fork off a process */
		pid = fork();
      		switch(pid){
	    		case -1:
				perror("Shell Program fork error");
	        		exit(EXIT_FAILURE);
	    		case 0:
				/* I am child process. I will execute the command, call: execvp */
				process_input(argc, argv);
				break;
	    		default:
				/* I am parent process */
				if (wait(&status) == -1)
					perror("Shell Program error");
				else
		    			printf("Child returned status: %d\n",status);
				break;
		} /* end of the switch */
	}	
	continue;
    } /* end of the while */
} /* end of main */

/* ----------------------------------------------------------------- */
/*                  parseline                                        */
/* ----------------------------------------------------------------- */
/* parse input line into argc/argv format */

int parseline(char *cmdline, char **argv)
{
    int count = 0;
    char *separator = " \n\t";
 
    argv[count] = strtok(cmdline, separator);
    while ((argv[count] != NULL) && (count+1 < MAXARGS)) {
	argv[++count] = strtok((char *) 0, separator);
    }		
    return count;
}
/* ----------------------------------------------------------------- */
/*                  process_input                                    */
/* ----------------------------------------------------------------- */
void process_input(int argc, char **argv) {
    /* Step 1: Call handle_redir to deal with operators:            */
    /* < , or  >, or both                                           */

    /* Step 2: perform system call execvp to execute command        */
    /* Hint: Please be sure to review execvp.c sample program       */
    /* if (........ == -1) {                                        */
    /*  perror("Shell Program");                                    */
    /*  _exit(-1);                                                  */
    /* }                                                            */
	handle_redir(argc, argv); 
	_exit(EXIT_SUCCESS);
}
/* ----------------------------------------------------------------- */
/* Handles errors and command for redir */
void handle_redir(int count, char *argv[]){
	int i;
	
	/* i know it is spelled wrong, but i like this spelling better */
	int flag_inCarrot =0;
	int flag_outCarrot = 0;
	int index_file = 0;

	for(i=0; i<count; ++i){
		int flag_isCarrot = 0;		

		/* Count number of in and out carrots */
		if(strcmp(argv[i],"<")==0){
			flag_outCarrot = 1;
			flag_isCarrot = 1;
		}
		else if(strcmp(argv[i],">")==0){
			flag_inCarrot = 1;
			flag_isCarrot = 1;
			index_file = i+1;
		}
		else
			flag_isCarrot = 0;

		/* Determine placement of carrots */
		if(flag_isCarrot == 1 && (i == 0 || i == count-1)){
			fprintf(stderr,"ERROR: incorrect syntax for redirection\n");
			return; 
		}
		else{}	
	}
	// check for multiple counts
	int c = 0;
	for(i = 0; i < count; ++i){
		if(c > 1){
			perror("ERROR: too many symbols\n");
			return;	
		}
		if(strcmp(argv[i],"<")==0 || strcmp(argv[i],">")==0)
			++c;	
	}
	if(flag_inCarrot + flag_outCarrot == 0){
		execvp(argv[0],argv);
		return;
	}
	else{
		int fid;
		
		/* Now handle redir > */
		if(flag_inCarrot == 1){
			fid = open(argv[index_file], O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if(fid < 0){
				perror("ERROR: file out creation failure\n");
				return;
			}
			dup2(fid, STDOUT_FILENO); //copy fileid to stdout
			close(fid);
			execlp(argv[0],argv[index_file],NULL);
		}
		else if(flag_outCarrot == 1){
			fid = open(argv[2],  O_RDONLY);
			if(fid < 0){
				perror("ERROR: file in creation failure\n");
				return;
			}
			dup2(fid,STDIN_FILENO); //copy fileid to stdin
			close(fid);
			execlp(argv[0],argv[0],NULL);
			return;
		}
		else{
			perror("REACHED ELSE");
		}
		return;
	}
}

/* Put your code here.  See pseudo-code in assignment directions     */

/* ----------------------------------------------------------------- */
/* ----------------------------------------------------------------- */
