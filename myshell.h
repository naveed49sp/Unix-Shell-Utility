#include <stdbool.h>
// version1 functions
int execute(char* arglist[]);
char** tokenize(char* cmdline);
char* read_cmd(char*, FILE*);

// version2 functions
int redirect_input(char *arglist[]);
void redirect_output(char *arglist[], int tI);
bool pipes(char *arglist[]);
void execute_piped_cmd(char *arglist[]);

// version3 functions
void trim(char * str);

// version4 functions
void set_history(char* cmdline);
char* get_history(int index);
