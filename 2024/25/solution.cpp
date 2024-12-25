#include <bits/stdc++.h>

using namespace std;

#define WIDTH 5
#define HEIGHT 5

int main() {
    vector<vector<int>> keys;
    vector<vector<int>> locks;
    string s;

    bool is_lock = false;

    while (getline(cin, s)) {
        if (s == ".....") {
            is_lock = false;
            // cout << "key!" << endl;
        } else {
            is_lock = true;
            // cout << "lock!" << endl;
        }

        if (is_lock) {
            vector<int> lock(WIDTH, 0);
            for (int row = 0; row < HEIGHT; row++) {
                getline(cin, s);
                // cout << s << endl;
                for (unsigned col = 0; col < s.size(); col++) {
                    if (s[col] == '#') lock[col]++;
                }
            }
            locks.push_back(lock);
        } else {
            vector<int> key(WIDTH, 0);
            for (int row = 0; row < HEIGHT; row++) {
                getline(cin, s);
                // cout << s << endl;
                for (unsigned col = 0; col < s.size(); col++) {
                    if (s[col] == '#') key[col]++;
                }
            }
            keys.push_back(key);
        }
        getline(cin, s);
        getline(cin, s);
        // cout << endl;
    }

    // for (auto &&lock : locks) {
    //     for (auto &&i : lock) {
    //         cout << i << ",";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // for (auto &&key : keys) {
    //     for (auto &&i : key) {
    //         cout << i << ",";
    //     }
    //     cout << endl;
    // }
    int answer = 0;
    for (auto &&key : keys) {
        for (auto &&lock : locks) {
            bool fail = false;
            for (int col = 0; col < WIDTH; col++) {
                if (key[col] + lock[col] > HEIGHT) {
                    fail = true;
                    break;
                }
            }

            if (!fail) answer++;
        }
    }
    cout << answer << endl;
}