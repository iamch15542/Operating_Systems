#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 80

int main(void)
{
    char *arg[MAX_LINE / 2 + 1]; /*command line arguments*/
    int should_run = 1; /*flag to determine when to exit program*/
    char inputbuffer[MAX_LINE];
    pid_t pid;
    
    while(should_run){
        printf("osh>");
        fflush(stdout);
        
        //read line
        fgets(inputbuffer, sizeof(inputbuffer), stdin);
        int cnt = 0, background = 0;
        for(int i = 0; i < MAX_LINE; ++i) {
            if(inputbuffer[i] == '&') {
                background = 1;
                inputbuffer[i] = '\0';
            }
            if(inputbuffer[i] == '\n') {
                inputbuffer[i] = '\0';
                break;
            }
        }
        char *pch;
        pch = strtok(inputbuffer, " ");
        while (pch != NULL){
            arg[cnt++] = pch;
            pch = strtok(NULL, " ");
        }
        arg[cnt] = NULL;
        
        //exit
        if (strncmp(arg[0], "exit", 4) == 0) should_run = 0;
        
        //other
        if(should_run) {
            pid = fork();
            if(pid == 0) {
                //printf("child pid is %d\n", getpid());
                execvp(arg[0], arg);
            }
            if(pid > 0) {
                //printf("parent pid is %d\n", getpid());
                if (background == 0) { //parent wait for child
		            waitpid(pid, NULL, 0);
                }
            }
        }
        /**
         * your code!
         * After reading user input, the step are:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) if command included &, parent will not invoke wait()
         */
    }
    
    return 0;
}
