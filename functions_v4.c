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
int last_index = 0;

void set_hist(char* cmdline)
{
	int index;
	if(last_index>=HISTLEN)
		index = last_index % 10;
	else
		index = last_index;
   strncpy(history[index], cmdline, MAX_LEN);
   last_index++;
}

char* get_hist(int index)
{
   if (index== -1) { //user want to execute last command
      index = last_index;
   }
   if(index > last_index){
   	     return NULL;
   }
   
   	char* cmdline = (char*)malloc(sizeof(char*) * MAX_LEN);
    strncpy(cmdline, history[index], MAX_LEN);
    return cmdline;

}

