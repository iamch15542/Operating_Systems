#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include <semaphore.h>

using namespace std;

sem_t mut;
int list[1000001], length = 0;

struct PARAMS {
    int a;
};

// define thread variable    
pthread_t t[7];
// merge sort algorithm
void merge(int start, int mid, int end) {

    int len1 = mid - start, len2 = end - mid, idx1 = 0, idx2 = 0, tmp_idx = 0;
    int tmp_arr[len1 + len2];
    // merge
    // sem_wait(&mut);
    // for (int i = start ; i <= end ; i++)
    //     cout << list[i] << ' ';
    // cout << '\n';
    // sem_post(&mut);
    while (idx1 < len1 && idx2 < len2) {
        if (list[start + idx1] <= list[mid + idx2]) {
            tmp_arr[tmp_idx++] = list[start + idx1];
            idx1++;
        } else {
            tmp_arr[tmp_idx++] = list[mid + idx2];
            idx2++;
        }
    } 
    // sem_wait(&mut);
    // cout << "idx1:" << idx1 << ' ' << "idx2:" << idx2 << '\n';
    // sem_post(&mut);
    while(idx1 < len1) { 
        tmp_arr[tmp_idx++] = list[start + idx1];
        idx1++;
    } 
    while(idx2 < len2) { 
        tmp_arr[tmp_idx++] = list[mid + idx2];
        idx2++;
    } 
    // sem_wait(&mut);
    // cout << "sort ok\n";
    // cout << "tmp_idx: " << tmp_idx << '\n';
    // for (int i = 0 ; i < tmp_idx ; i++)
    //     cout << tmp_arr[i] << ' ';
    // cout << '\n';
    // sem_post(&mut);
    for(int i = 0; i < tmp_idx; ++i) {
        list[start + i] = tmp_arr[i];
    }
} 

// bubble sort algorithm
void sort(int low, int high) {
    for (int i = low ; i < high ; i++)
        for (int j = low ; j < high - 1 - i + low ; j++)
            if (list[j] > list[j + 1])
                swap(list[j], list[j + 1]);
    /*
    for (int i = high; i > low; --i) {
        for (int j = low; j < i; ++j) {
            if (list[j] > list[j + 1]) {
                int tmp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tmp;
            }
        }
    }
    */
}

// simple sort threading function
void* sort_thread(void* data) {
    PARAMS *para;
    para = (PARAMS *) data;
    int num = para->a;
    int start = 0, end  = 0;
    if(num == 0) {
        start = 0;
        end = length / 4;
    } else if(num == 1) {
        start = (length / 4);
        end = length / 2;
    } else if(num == 2) {
        start = (length / 2);
        end = (length * 3) / 4;
    } else if(num == 3) {
        start = (length * 3) / 4;
        end = length;
    }
    sort(start, end);
    pthread_exit(NULL); // exit child thread 
}

// merge sort threading function
void* merge_sort_thread(void* data){
    PARAMS *para;
    para = (PARAMS *) data;
    // sem_wait(&mut);
    // cout << para->a << " start\n";
    // sem_post(&mut);
    int num = para->a;
    int start = 0, end  = 0;
    if(num == 4) {
        pthread_join(t[0], NULL);
        pthread_join(t[1], NULL);
        start = 0;
        end = length / 2;
        //cout << start << " " << end << " " << num << '\n';
    } else if(num == 5) {
        pthread_join(t[2], NULL);
        pthread_join(t[3], NULL);
        //start = (length / 2) + 1;
        start = length / 2;
        end = length;
        //cout << start << " " << end << " " << num << '\n';
    } else if(num == 6) {
        pthread_join(t[4], NULL);
        pthread_join(t[5], NULL);
        start = 0;
        end = length;
        //cout << start << " " << end << " " << num << '\n';
    }
    //int mid = start + - start) / 2; 
    int mid = (start + end) / 2;
    // sort(start, end); 
    merge(start, mid, end);
    
    pthread_exit(NULL); // exit child thread 
}

// main fuction
int main(void) {
    while(cin >> list[length]) {
        length++;
    }
    struct PARAMS params[7];
    // creating 4 sort threads 
    for (int i = 0; i < 4; i++) {
        params[i].a = i;
        pthread_create(&t[i], NULL, sort_thread, (void*)&params[i]);
    }
    // create 3 merge sort threads
    for (int i = 4; i < 7; i++) {
        params[i].a = i;
        pthread_create(&t[i], NULL, merge_sort_thread, (void*)&params[i]);
    }
    pthread_join(t[6], NULL);
    for(int i = 0; i < length; ++i) {
        printf("%d ", list[i]);
    }
    printf("\n");
    return 0;
}

