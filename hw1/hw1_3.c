#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    //print main pid
    printf("Main Process ID : %d\n\n", getpid());
    pid_t pid, child2, child3, child4, child5;
    pid = fork();

    if(pid == 0) { //child 1

        printf("Fork 1. I'm the child %d, my parent is %d\n", getpid(), getppid());

        child2 = fork();
        
        if(child2 == 0) { // child 2

            printf("Fork 2. I'm the child %d, my parent is %d\n", getpid(), getppid());
            
            child4 = fork();
            
            if(child4 == 0) { // child 4
                
                printf("Fork 3. I'm the child %d, my parent is %d\n", getpid(), getppid());
            
            } else { //child4
                waitpid(child4, NULL, 0);
            }
        } else { // child1

            child3 = fork();
            
            if(child3 == 0) { //child 3

                printf("Fork 2. I'm the child %d, my parent is %d\n", getpid(), getppid());
                
                child5 = fork();
                
                if (child5 == 0) { //child 5
                    
                    printf("Fork 3. I'm the child %d, my parent is %d\n", getpid(), getppid());

                } else { //child3
                    waitpid(child5, NULL, 0);
                }
            } else {
                waitpid(child3, NULL, 0);
            }
        }
    } else {
        waitpid(pid, NULL, 0);
    }
}
