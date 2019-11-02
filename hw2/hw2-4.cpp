#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

int main() {
    int n, rr;
    cin >> n;  //First line is the total number of process
    int arrival[n], burst[n], ans_wait[n], ans_turn[n], sum_total = 0, sum_wait = 0, pri[n];
    vector<pair<int, int> > arr;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
    bool q_used[n], used[n];
    memset(q_used, false, sizeof(q_used));
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
    cin >> rr;
    queue<int> q;
    q.push(arr[0].second);
    int now = 0, already_run = 0;
    while(already_run < n) {
        if(!q.empty()) {
            int idx = q.front();
            q.pop();
            ans_wait[idx] += now - arrival[idx];
            bool flag = false;
            for(int i = 0, cnt = 0; i < burst[idx]; ++i) {
                q_used[idx] = true;
                now += 1;
                cnt += 1;
                for(int j = 0; j < (int)arr.size(); ++j) {
                    if(!q_used[arr[j].second]) {
                        if(now == arrival[arr[j].second]) {
                            q.push(arr[j].second);
                        }
                    }
                }
                if(cnt == rr && burst[idx] != cnt) {
                    flag = true; //表示還沒執行完成
                    arrival[idx] = now;
                    burst[idx] -= rr;
                    pq.push({pri[idx], idx});
                    break;
                }
            }
            if(!flag) {
                already_run += 1;
                ans_turn[idx] = now - ans_turn[idx];
                used[idx] = true;
            }
        }
        if(q.empty()) {
            int pq_idx = pq.top().second;
            pq.pop();
            used[pq_idx] = true;
            ans_wait[pq_idx] += now - arrival[pq_idx];
            now += burst[pq_idx];
            ans_turn[pq_idx] = now - ans_turn[pq_idx];
            already_run += 1;
        }
    }
    //cout result
    for(int i = 0; i < n; ++i) {
        cout << ans_wait[i] << " " << ans_turn[i] << '\n';
        sum_wait += ans_wait[i];
        sum_total += ans_turn[i];
    }
    cout << sum_wait << '\n' << sum_total << '\n';
}