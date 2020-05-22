#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <myshell.h>

#define MAX_LEN 512
#define MAXARGS 10
#define ARGLEN 30
#define HISTLEN 10


char** history;
int size = 0;

void set_hist(char* cmdline)
{
	if(size !=0){// make room for new command
		for(int i = size; i>=1; i--){
			strcpy(history[i], history[i-1]);
		}
	}
	
	strncpy(history[0], cmdline, MAX_LEN); //copy new command in the start index
	size++;
}

char* get_hist(int ind)
{
   if (ind == -1) { //user want to execute last command
      ind = 0;
   }
   if(ind > size){
   	     return NULL;
   }
   
   	char* cmdline = (char*)malloc(sizeof(char*) * MAX_LEN);
    strncpy(cmdline, history[ind], MAX_LEN);
    return cmdline;
}

