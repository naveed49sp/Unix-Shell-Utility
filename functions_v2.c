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

int redirect_input(char *arglist[]){
	int i=0;

	while(1){
  		if(arglist[i]==NULL){
    		break;
    	}

    	if(strcmp(arglist[i],"<")==0){
    		int fd0= open(arglist[i+1], O_RDONLY);
    		if(fd0 < 0){
    			perror("Can't open input redirection file ");
    			exit(0);
      		}
      		dup2(fd0,0);
      		//close(fd0);
      		return i;
 		}
      	i++;
    }
    return -1;
}

void redirect_output(char* arglist[], int tI){


	int i=0;
	while(1){
     	if(arglist[i]==NULL){
   			break;
  		}

		if(strcmp(arglist[i],">")==0){
			int fd1= open(arglist[i+1], O_WRONLY|O_CREAT|O_TRUNC);
			if(fd1 < 0){
				perror("Can't open output redirection file");
				exit(0);
			}
			dup2(fd1,1); //descriptor#1 will be used for fd1
			//close(fd1);
			arglist[i]=NULL;
			arglist[i+1]=NULL;      				
   			break;
      	}
      	i++;
    }
    if(tI!=-1){
  		arglist[tI]=NULL;
   		arglist[tI+1]=NULL;
	}

}

bool pipes(char *arglist[]){
	int i=0;
	while(1){
		if(arglist[i]==NULL)
			break;
		if(strcmp(arglist[i],"|")==0)
			return true;
		i++;
	}
	return false;
}

void execute_piped_cmd(char *arglist[]){
      			
    //creating argument list for each pipe
    char** tempArglist = (char**)malloc(sizeof(char*) * (MAXARGS+1));
	for(int j=0; j < MAXARGS+1; j++){
		tempArglist[j] = (char*)malloc(sizeof(char)* ARGLEN);
		tempArglist[j]=NULL;
	}
	int check=-1;
	int i=0,j=0; // i index for parameter arglist and j is index for tempArglist
	while(1){
	   	if(arglist[i]==NULL || strcmp(arglist[i],"|")==0){ // there is nothing or pipe in the arglist entry
			if(check==-1){ // This is the first pipe
				tempArglist[j]=">";  // redirecting output of previous command to tempout.txt
				tempArglist[j+1]="tempout.txt";
				j++;
				check=1;
			}
			else { // there is more than one pipes in arglist and this is not the first one

				FILE *source; 
				source = fopen("tempout.txt", "r"); //read from the file which is written by previous command
							
				FILE *target;
				target = fopen("tempin.txt", "w");

				char ch;
				while ((ch = fgetc(source)) != EOF) 
					fputc(ch, target);
    			fclose(source);
   				fclose(target);

				tempArglist[j]="<"; // redirecting to take input from tempin.txt
				tempArglist[j+1]="tempin.txt";
							
				if(arglist[i]!=NULL){
					tempArglist[j+2]=">";
					tempArglist[j+3]="tempout.txt";
				}

				j=j+3;
			}			    		
			execute(tempArglist);
			for(int k=0;k<=j;k++){ // after executing the command we are removing redirection symbols from the command
		   			tempArglist[k]=NULL;
			}
			j=0;
			i++;			    		
		}
		// if entry of arglist is not null or pipe then copy the commmand into tempArglist		
		tempArglist[j]=arglist[i];
		j++;
		if(arglist[i]==NULL) {
			break;
		}
		i++;
			    	
	}
}
