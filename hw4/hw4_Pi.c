#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

// define global variable
long long ans = 0;

// define mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// define thread variable    
pthread_t t[4];

struct PARAMS {
    int a; // which thread
    int b; // per thread need to run
    long long c; // record point num
};

// count
void* cnt_thread(void* data) {
    PARAMS *para;
    para = (PARAMS *) data;
    int num = para->a, per_p = para->b;
    long long cnt = 0;
    double x, y;
    unsigned int seed = rand();

    for(int i = (num*per_p); i < (per_p + (num*per_p)); ++i) {
        x = (double)rand_r(&seed)/RAND_MAX;
        y = (double)rand_r(&seed)/RAND_MAX;
        if ((x*x + y*y) <= 1.0) {
            cnt++;
        }
    }

    // write cnt into sum
    pthread_mutex_lock(&mutex);
    ans += cnt;
    para->c = cnt;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}


int main() {

    // initial
    int thread_num = 0, point_number = 0;
    struct PARAMS params[7];

    // print student ID
    printf("0616091\n");

    // input param
    scanf("%d", &thread_num);
    scanf("%d", &point_number);

    // per thread need to run
    int per_point = point_number / thread_num;

    srand((unsigned)time(NULL));

    // creating thread_num threads 
    for(int i = 0; i < thread_num; ++i) {
        params[i].a = i;
        params[i].b = per_point;
        pthread_create(&t[i], NULL, cnt_thread, (void*)&params[i]);
    }
    for(int i = 0; i < thread_num; ++i) {
        pthread_join(t[i], NULL);
    }

    // print thread
    for(int i = 0; i < thread_num; ++i) {
        printf("Thread %d, There are %lld points in the circle\n", i, params[i].c);
    }

    pthread_mutex_destroy(&mutex);

    // print answer
    printf("Pi : %lf\n", 4.0 * (double)ans / (double)point_number);
}