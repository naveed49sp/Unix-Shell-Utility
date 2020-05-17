#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <myshell.h>
#include <stdbool.h> 

#define MAX_LEN 512
#define MAXARGS 10
#define ARGLEN 30

int execute(char* arglist[]){
   int status;
   int inputfd = dup(0); //creating copies of i/o file descriptors
   int outputfd = dup(1);
   int tI=-1; //index of input sympol "<" in arglist
   int cpid = fork();
   switch(cpid){
      case -1:
         perror("fork failed");
	      exit(1);
      case 0: // child process     
      	 if(pipes(arglist)){ 
      	 	execute_piped_cmd(arglist);
      	 	return 0;      	 	
		   }
		 tI=redirect_input(arglist);
      	 redirect_output(arglist,tI); 	
	     execvp(arglist[0], arglist);
 	     perror("Command not found...");
	     exit(1);
      default: // parent process
	     waitpid(cpid, &status, 0);
	     dup2(inputfd, 0); //restoring input and output file descriptors
	     dup2(outputfd, 1);
         //printf("child exited with status %d \n", status >> 8);
         return 0;
   }
}
char** tokenize(char* cmdline){
//allocate memory
   char** arglist = (char**)malloc(sizeof(char*)* (MAXARGS+1));
   for(int j=0; j < MAXARGS+1; j++){
	   arglist[j] = (char*)malloc(sizeof(char)* ARGLEN);
      bzero(arglist[j],ARGLEN); // copies n bytes each with a value of zero into the string
    }
   if(cmdline[0] == '\0')//if user has entered nothing and pressed enter key
      return NULL;
   int argnum = 0; //slots used
   char*cp = cmdline; // pos in string
   char*start;
   int len;
   while(*cp != '\0'){
      while(*cp == ' ' || *cp == '\t') //skip leading spaces
          cp++;
      start = cp; //start of the word
      len = 1; //initialize length of the word to 1
      //find the end of the word
      while(*++cp != '\0' && !(*cp ==' ' || *cp == '\t')) // not end of string and not space or tab
         len++;
      strncpy(arglist[argnum], start, len);
      arglist[argnum][len] = '\0'; // terminate the argument with null
      argnum++;
   }
   arglist[argnum] = NULL;
   return arglist;
}      

char* read_cmd(char* prompt, FILE* fp){
   printf("%s", prompt);
  int c; //input character
   int pos = 0; //position of character in cmdline
   char* cmdline = (char*) malloc(sizeof(char)*MAX_LEN);
   while((c = getc(fp)) != EOF){
       if(c == '\n')
	  break;
       cmdline[pos++] = c;
   }
//these two lines are added, in case user press ctrl+d to exit the shell
   if(c == EOF && pos == 0) 
      return NULL;
   cmdline[pos] = '\0';
   return cmdline;
}

