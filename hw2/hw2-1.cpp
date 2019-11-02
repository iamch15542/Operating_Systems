#include <iostream>
#include <map>
using namespace std;

int main() {
    int n;
    cin >> n;  //First line is the total number of process
    int arrival[n], burst[n], ans_wait[n], ans_turn[n], total = 0, sum_total = 0, sum_wait = 0;
    map<int, int> arr;
    for(int i = 0; i < n; ++i) {
        cin >> arrival[i];
        arr[arrival[i]] = i;
    }
    for(int i = 0; i < n; ++i) {
        cin >> burst[i];
    }
    for(auto&m : arr){
        ans_wait[m.second] = total - arrival[m.second];
        total += burst[m.second];
        ans_turn[m.second] = total - arrival[m.second];
    }
    for(int i = 0; i < n; ++i) {
        cout << ans_wait[i] << " " << ans_turn[i] << '\n';
        sum_wait += ans_wait[i];
        sum_total += ans_turn[i];
    }
    cout << sum_wait << '\n' << sum_total << '\n';
}