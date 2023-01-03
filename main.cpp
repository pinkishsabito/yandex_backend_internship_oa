// #include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>

using namespace std;

void solution_a() {
    int n;
    cin >> n;
    vector<vector<string>> all(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        string now;
        for (auto j : s) {
            if (j == ',') {
                all[i].push_back(now);
                now = "";
            } else {
                now += j;
            }
        }
        all[i].push_back(now);
    }
    function<string(int)> turn = [&](int x) {
        string hexo;
        map<int, char> dec = {
                {0, '0'},
                {1, '1'},
                {2, '2'},
                {3, '3'},
                {4, '4'},
                {5, '5'},
                {6, '6'},
                {7, '7'},
                {8, '8'},
                {9, '9'},
                {10, 'A'},
                {11, 'B'},
                {12, 'C'},
                {13, 'D'},
                {14, 'E'},
                {15, 'F'}
        };
        while (x) {
            hexo.push_back(dec[x % 16]);
            x /= 16;
        }
        while (hexo.size() > 3) {
            hexo.pop_back();
        }
        while (hexo.size() < 3) {
            hexo.push_back('0');
        }
        reverse(hexo.begin(), hexo.end());
        return hexo;

    };
    function<int(string)> sum = [&](const string& x) {
        int sum = 0;
        for (char i : x) {
            sum += i - '0';
        }
        return sum;
    };
    for (int i = 0; i < n; ++i) {
        set<char> diff;
        for (int j = 0; j < 3; ++j) {
            for (auto k : all[i][j]) {
                diff.insert(k);
            }
        }
        int total = 0;
        total += (int)diff.size();
        total += sum(all[i][3] + all[i][4])* 64;
        total += (all[i][0][0] - 'A' + 1) * 256;
        cout << turn(total) << ' ';
    }
}

void solution_b() {
    int n;
    cin >> n;
    map<int, vector<vector<int>>> saved;
    for (int i = 0; i < n; ++i) {
        int d, h, m, j;
        cin >> d >> h >> m >> j;
        char s;
        cin >> s;
        saved[j].push_back({(d * 24 + h) * 60 + m, s});
    }
    for (auto& i: saved) {
        sort(i.second.begin(), i.second.end());
    }
    for (const auto& i: saved) {
        int answer = 0, last = 0;
        for (const auto& j: i.second) {
            if (j[1] == 66) {
                continue;
            }
            if (j[1] == 65) {
                last = j[0];
            } else {
                answer += j[0] - last;
            }
        }
        cout << answer << endl;
    }
}

void solution_d() {
    const int max_size = 5e5 + 500;
    vector<int> all;
    int n;
    cin >> n;
    vector<vector<int>> rs(max_size, {0, 0, 0});
    for (int i = 0; i < n; ++i) {
        cin >> rs[i][0] >> rs[i][1] >> rs[i][2];
        all.push_back(rs[i][0]);
        all.push_back(rs[i][1]);
    }
    int q;
    cin >> q;
    vector<vector<int>> qs(max_size, {0, 0, 0});
    for (int i = 0; i < q; ++i) {
        cin >> qs[i][0] >> qs[i][1] >> qs[i][2];
        all.push_back(qs[i][0]);
        all.push_back(qs[i][1]);
    }
    sort(all.begin(), all.end());
    all.resize(unique(all.begin(), all.end()) - all.begin());
    vector<vector<int>> value(3, vector<int>(max_size));
    for (int i = 0; i < n; ++i) {
        int l = rs[i][0], r = rs[i][1];
        rs[i][0] = (int)(upper_bound(all.begin(), all.end(), rs[i][0]) - all.begin());
        rs[i][1] = (int)(upper_bound(all.begin(), all.end(), rs[i][1]) - all.begin());
        value[1][rs[i][0]] += rs[i][2];
        value[2][rs[i][1]] += r - l;
    }
    vector<vector<int>> new_q[3];
    for (int i = 0; i < q; ++i) {
        qs[i][0] = (int)(upper_bound(all.begin(), all.end(), qs[i][0]) - all.begin());
        qs[i][1] = (int)(upper_bound(all.begin(), all.end(), qs[i][1]) - all.begin());
        new_q[qs[i][2]].push_back({qs[i][0], qs[i][1], i});
    }
    const int block = (int)sqrt(n + q) + 1;
    function<bool(vector<int>, vector<int>)> comparator = [&](const vector<int>& a, const vector<int>& b) {
        if (a[0] / block == b[0] / block) {
            return a[1] / block < b[1] / block;
        }
        return a[0] / block < b[0] / block;
    };
    sort(new_q[1].begin(), new_q[1].end(), comparator);
    sort(new_q[2].begin(), new_q[2].end(), comparator);
    vector<int> answer(q);
    for (int i = 1; i <= 2; ++i) {
        int L = 1, R = 0, result = 0;
        for (auto j : new_q[i]) {
            int l = j[0], r = j[1], index = j[2];
            while (L < l) {
                result -= value[i][L++];
            }
            while (L > l) {
                result += value[i][--L];
            }
            while (R < r) {
                result += value[i][++R];
            }
            while (R > r) {
                result -= value[i][R--];
            }
            assert(index < q);
            answer[index] = result;
        }
    }
    for (auto i : answer) {
        cout << i << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solution_d();
    return 0;
}
