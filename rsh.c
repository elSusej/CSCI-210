#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define N 12

extern char **environ;

char *allowed[N] = {"cp","touch","mkdir","ls","pwd","cat","grep","chmod","diff","cd","exit","help"};

int isAllowed(const char* cmd) {
    // TODO
    // return 1 if cmd is one of the allowed commands
    // return 0 otherwise
    for (int i = 0; i < 12; i++) {
        if ( strcmp(cmd,allowed[i]) == 0 ) {
            return 1;
        }
    }
    
    return 0;
}

int main() {

    // TODO
    // Add variables as needed

    char line[256];
    char linecpy[256];
    char* argv[20];
    char* token;

    while (1) {

    fprintf(stdout,"rsh> ");

    if (fgets(line,256,stdin)==NULL) continue;

    if (strcmp(line,"\n")==0) continue;

    line[strlen(line)-1]='\0';

    strcpy(linecpy, line);
    token = strtok(linecpy, " ");
    int i = 0;

    while (token != NULL) {
        argv[i] = token;
        token = strtok(NULL, " ");
        i++;
    }

    argv[i] = NULL;

    if (isAllowed(argv[0]) == 0) {
        printf("NOT ALLOWED!\n");
    }
    // TODO
    // Add code to spawn processes for the first 9 commands
    // And add code to execute cd, exit, help command
    
    /*if (strcmp(argv[0],"cp") == 0) {
        
    }
    if (strcmp(argv[0],"cp") == 0) {
        
    }
    if (strcmp(argv[0],"cp") == 0) {
        
    }
    if (strcmp(argv[0],"cp") == 0) {
        
    }
    if (strcmp(argv[0],"cp") == 0) {
        
    }
    if (strcmp(argv[0],"cp") == 0) {
        
    }
    if (strcmp(argv[0],"cp") == 0) {
        
    }
    if (strcmp(argv[0],"cp") == 0) {
        
    }
    */
    if (strcmp(argv[0],"cd") == 0) {
        if ((argv[1] != NULL) && (argv[2] != NULL)) {
            printf("-rsh: cd: too many arguments");
        }
        else {
            chdir(argv[1]);
        }
    }
    if (strcmp(argv[0],"exit") == 0) {
        break;
    }
    if (strcmp(argv[0],"help") == 0) {
        printf("The allowed commands are:\n");
        for (int i = 0; i < 12; i++) {
            printf("%s\n", allowed[i]);
        }
    }
    // Use the example provided in myspawn.c

    }
    return 0;
}