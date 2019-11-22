#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/* function definitions */
void sort(int list[], int len);

int main(int argc, const char * argv[]) {
    int list[1000001], length = 0;
    while(cin >> list[length]) {
        length++;
    }
    sort(list, length);    
    for(int i = 0; i < length; ++i) {
        cout << list[i] << " ";
    }
    cout << '\n';
    return 0;
}

void sort(int list[], int len) {
    for (int i = len - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (list[j] > list[j + 1]) {
                int tmp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tmp;
            }
        }
    }
}

