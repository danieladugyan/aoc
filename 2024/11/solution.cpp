#include <bits/stdc++.h>

using namespace std;
#define N 75

int main() {
    vector<long> stones;
    long stone;
    while (cin >> stone) {
        stones.push_back(stone);
    }

    string s, s1, s2;
    int digits;
    for (int n = 0; n < N; n++) {
        for (int i = 0; i < stones.size(); i++) {
            stone = stones[i];
            s = to_string(stone);
            digits = s.length();

            if (stone == 0) {
                stones[i] = 1;
            } else if (digits % 2 == 0) {
                s1 = s.substr(0, digits / 2);
                s2 = s.substr(digits / 2, digits);
                stones[i] = stol(s1);
                stones.insert(stones.begin() + i + 1, stoi(s2));
                i++;
            } else {
                stones[i] *= 2024;
            }
        }

        // for (auto &&i : stones) {
        //     cout << i << ", ";
        // }
        // cout << endl;
        // cout << "--------------------" << endl;
    }
    cout << stones.size() << endl;
}