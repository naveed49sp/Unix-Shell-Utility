/*

*  myshellv3.c: 
*  It handles i/o redirection
*  use of pipes
*  semicolon separated multiple commands on single line.
*/

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
#define HISTLEN 10
#define PROMPT "MSCSF19M521shell:- "

// version4 global variables
char** history;


int main(){
   char *cmdline;
   char** arglist;
   char* prompt = PROMPT; 
   char* command;
   //allocate memory to history
   history =(char**) malloc(sizeof(char*) * HISTLEN + 1);
   for (int i=0; i < HISTLEN; i++) {
      history[i] = malloc(sizeof(char) * MAX_LEN);
   }
   while((cmdline = read_cmd(prompt,stdin)) != NULL){
   	  command = strtok(cmdline, ";");
   	  while(command != NULL){
   	  	trim(command);
      	if((arglist = tokenize(command)) != NULL){
            execute(arglist);
       //  need to free arglist
         for(int j=0; j < MAXARGS+1; j++)
	         free(arglist[j]);
         free(arglist);
     }
     command = strtok(NULL, ";");
      }
      free(cmdline);
  }//end of while loop
   printf("\n");
   return 0;
}







