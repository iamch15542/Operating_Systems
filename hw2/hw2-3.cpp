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
    int arrival[n], burst[n], ans_wait[n], ans_turn[n], sum_total = 0, sum_wait = 0, pri[n];
    vector<pair<int, int> > arr;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
    bool used[n];
    memset(used, false, sizeof(used));
    memset(ans_turn, 0, sizeof(ans_turn));
    memset(ans_wait, 0, sizeof(ans_wait));
    for(int i = 0; i < n; ++i) {
        cin >> arrival[i];
        arr.push_back({arrival[i], i});
        ans_turn[i] = arrival[i];
    }
    sort(arr.begin(), arr.end());
    for(int i = 0; i < n; ++i) {
        cin >> burst[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> pri[i];
    }
    pq.push({pri[arr[0].second], arr[0].second});
    int now = 0, already_run = 0;
    while(already_run < n) {
        int idx = pq.top().second;
        pq.pop();
        ans_wait[idx] += now - arrival[idx];
        bool preem = false;
        for(int i = 0, cnt = 0; i < burst[idx]; ++i) {
            now += 1;
            cnt += 1;
            for(int j = 0; j < (int)arr.size(); ++j) {
                if(arrival[arr[j].second] == now && !used[arr[j].second] && arr[j].second != idx) {
                    pq.push({pri[arr[j].second], arr[j].second});
                }
                if(arrival[arr[j].second] <= now) {
                    if(pri[arr[j].second] < pri[idx] && !used[arr[j].second]) {
                        //搶斷
                        if(burst[idx] == cnt) {
                            continue;
                        }
                        pq.push({pri[idx], idx});
                        arrival[idx] = now;
                        burst[idx] -= cnt;
                        preem = true;
                        break;
                    }
                }
            }
            if(preem) { break; }
        }
        if(!preem) {
            ans_turn[idx] = now - ans_turn[idx];
            used[idx] = true;
            already_run++;
            if(pq.empty()) {
                for(int i = 0; i < (int)arr.size(); ++i) {
                    if(!used[arr[i].second]) {
                        pq.push({pri[arr[i].second], arr[i].second});
                        break;
                    }
                }
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        cout << ans_wait[i] << " " << ans_turn[i] << '\n';
        sum_wait += ans_wait[i];
        sum_total += ans_turn[i];
    }
    cout << sum_wait << '\n' << sum_total << '\n';
}