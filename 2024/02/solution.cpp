#include <bits/stdc++.h>

using namespace std;

bool comp(int a, int b) { return a > b; }

int main() {
    string s;
    vector<int> level;
    int a;
    int sorted = 0;
    bool fail = false;
    while (getline(cin, s)) {
        stringstream ss(s);
        while (ss >> a) {
            level.push_back(a);
        }

        cout << "level: ";
        for (auto &&i : level) {
            cout << i << ", ";
        }
        cout << endl;

        if (level[0] > level[1]) {
            reverse(level.begin(), level.end());
        }
        for (int i = 0; i < level.size() - 1; i++) {
            cout << level[i] << " " << level[i + 1];
            if (!(level[i + 1] - level[i] >= 1 &&
                  level[i + 1] - level[i] <= 3)) {
                fail = true;
                cout << " fail" << endl;
                break;
            } else {
                cout << " pass" << endl;
            }
        }

        if (!fail) {
            sorted++;
        } else {
            fail = false;
        }

        cout << sorted << endl;

        level.clear();
    }
    cout << sorted << endl;
}