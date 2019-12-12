#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// define global variable
int arr[10];
long long length = 0;

// define semaphore
sem_t sem1;

// define thread variable    
pthread_t t[4];

struct PARAMS {
    int a;
    int b;
    char*c;
};

// search series
void search_s(int low, int high, char* s) {
    // for (int i = low; i < high; i++) {
    //     for (int j = low; j < high - 1 - i + low; j++) {
    //         if (list[j] > list[j + 1]) {
    //             int tmp = list[j];
    //             list[j] = list[j + 1];
    //             list[j + 1] = tmp;
    //         }
    //     }
    // }

    // write ans into array
    sem_wait(&sem1);
    for (int i = low; i < high ; ++i) {
        int tmp = (int)(*(s+i)) - 48;
        // printf("asdf%dasdf\n", tmp);
        // printf("%c", *(s+i));
        arr[tmp]++;
    }
    // printf("\n");
    // printf("mother fuck\n");
    sem_post(&sem1);
}


// count series
void* cnt_thread(void* data) {
    PARAMS *para;
    para = (PARAMS *) data;
    int num = para->a, thr_num = para->b;
    char *series = para->c;
    int start = 0, end  = 0;
    if(num == 0) {
        start = 0;
        end = length / thr_num;
    } else if(num == 1) {
        start = (length / thr_num);
        end = (length * 2) / thr_num;
    } else if(num == 2) {
        start = (length * 2) / thr_num;
        end = (length * 3) / thr_num;
    } else if(num == 3) {
        start = (length * 3) / thr_num;
        end = length;
    }
    // sem_wait(&sem1);
    search_s(start, end, series);
    // printf("%dasdfasdfsadf\n", num);
    // sem_post(&sem1);
    pthread_exit(NULL);
}


int main() {

    // initial
    int thread_num = 0;
    sem_init(&sem1, 0, 1);
    struct PARAMS params[7];
    for(int i = 0; i < 10; ++i) {
        arr[i] = 0;
    }

    // print student ID
    printf("0616091\n");

    // input param
    scanf("%d", &thread_num);
    scanf("%lld", &length);

    // get memory to store input
    char *input = (char*)malloc(sizeof(char) * (length + 10)); 

    // input series
    scanf("%s", input);

    // creating thread_num threads 
    for (int i = 0; i < thread_num; ++i) {
        params[i].a = i;
        params[i].b = thread_num;
        params[i].c = input;
        pthread_create(&t[i], NULL, cnt_thread, (void*)&params[i]);
    }
    for (int i = 0; i < thread_num; ++i) {
        pthread_join(t[i], NULL);
    }

    //printf("%s", input);

    // print answer
    for(int i = 0; i < 10; ++i) {
        printf("The total number of %d : %d\n", i, arr[i]);
    }

    // free memory
    free(input);
}