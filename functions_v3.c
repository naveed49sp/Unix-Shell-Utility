#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


void trim(char * str)
{
    int index, i;   
    //Trim leading white spaces
    index = 0;
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
    {
        index++;
    }

    /* Shift all trailing characters to its left */
    i = 0;
    while(str[i + index] != '\0')
    {
        str[i] = str[i + index];
        i++;
    }
    str[i] = '\0'; // Terminate string with NULL


    
    //Trim trailing white spaces
    i = 0;
    index = -1;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index = i;
        }
        i++;
    }
    /* Mark the next character to last non white space character as NULL */
    str[index + 1] = '\0';
}
