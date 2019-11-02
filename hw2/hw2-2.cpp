#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

int main() {
    int n;
    cin >> n;  //First line is the total number of process
    int arrival[n], burst[n], ans_wait[n], ans_turn[n], total = 0, sum_total = 0, sum_wait = 0, pri[n], run[n];
    vector<pair<int, int> > arr;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
    bool used[n];
    memset(used, false, sizeof(used));
    for(int i = 0; i < n; ++i) {
        cin >> arrival[i];
        arr.push_back({arrival[i], i});
    }
    sort(arr.begin(), arr.end());
    for(int i = 0; i < n; ++i) {
        cin >> burst[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> pri[i];
    }
    pq.push({pri[arr[0].second], arr[0].second});
    int cnt = 0, now = 0;
    while(cnt < n) {
        int idx = pq.top().second;
        used[idx] = true;
        pq.pop();
        now += burst[idx];
        for(int i = 1; i < (int)arr.size(); ++i) {
            if(!used[arr[i].second] && arrival[arr[i].second] <= now) {
                pq.push({pri[arr[i].second], arr[i].second});
                used[arr[i].second] = true;
            }
        }
        run[cnt] = idx;
        cnt++;
    }
    for(int i = 0; i < n; ++i){
        ans_wait[run[i]] = total - arrival[run[i]];
        total += burst[run[i]];
        ans_turn[run[i]] = total - arrival[run[i]];
    }
    for(int i = 0; i < n; ++i) {
        cout << ans_wait[i] << " " << ans_turn[i] << '\n';
        sum_wait += ans_wait[i];
        sum_total += ans_turn[i];
    }
    cout << sum_wait << '\n' << sum_total << '\n';
}