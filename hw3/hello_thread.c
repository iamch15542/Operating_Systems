#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// child threading function
void* child(void* data) {
    char *str = (char*) data; // get data "Child"
    for(int i = 0; i < 3; ++i){
        printf("%s\n", str);// output every second
        sleep(1);
    }
    pthread_exit(NULL); // exit child thread 
}

// main fuction
int main(void) {
    // define thread variable
    pthread_t t;
    // create child thread
    pthread_create(&t, NULL, child, "Child");
    // main thread
    for(int i = 0; i < 3; ++i){
        printf("Master\n"); // output "Master" every second
        sleep(1);
    }
    pthread_join(t, NULL);// wait for all child threading finished
    return 0;
}
