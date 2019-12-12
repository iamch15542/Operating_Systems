#include <iostream>
#include <random>
using namespace std;


int main() {

    int thr_num = 0, param = 0, arr[10];
    std::random_device rd;
    std::default_random_engine gen = std::default_random_engine(rd());
    std::uniform_int_distribution<int> dis(0, 9);

    for(int i = 0; i < 10; ++i) {
        arr[i] = 0;
    }

    cin >> thr_num >> param;
    // cout << "random numbers between 1 and 10: \n";
    cout << thr_num << '\n' << param << '\n';
    for (int i = 0; i < param; ++i) {
        int tmp = dis(gen);
        arr[tmp]++;
        cout << tmp;
    }
    cout << '\n';

    for(int i = 0; i < 10; ++i) {
        cerr << "The total number of " << i << " : " << arr[i] << '\n';
    }
}