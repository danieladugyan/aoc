#include <bits/stdc++.h>

using namespace std;

int walk(tuple<int, int> pos, vector<vector<int>> m, int n,
         set<tuple<int, int>> *visited) {
    unsigned row = get<0>(pos), col = get<1>(pos);

    // for (int i = 0; i < n; i++) {
    //     cout << '\t';
    // }
    // cout << "walk to " << row << " " << col << endl;

    if (m[row][col] == 9) {
        tuple<int, int> p = make_pair(row, col);
        if (visited->count(p)) {
            return 0;
        } else {
            visited->insert(p);
            return 1;
        }
    }

    int sum = 0;
    if (col + 1 < m[row].size() && m[row][col + 1] - m[row][col] == 1) {
        sum += walk(make_pair(row, col + 1), m, n + 1, visited);
    }
    if (col > 0 && m[row][col - 1] - m[row][col] == 1) {
        sum += walk(make_pair(row, col - 1), m, n + 1, visited);
    }
    if (row + 1 < m.size() && m[row + 1][col] - m[row][col] == 1) {
        sum += walk(make_pair(row + 1, col), m, n + 1, visited);
    }
    if (row > 0 && m[row - 1][col] - m[row][col] == 1) {
        sum += walk(make_pair(row - 1, col), m, n + 1, visited);
    }
    return sum;
}

int main() {
    vector<vector<int>> m;
    vector<tuple<int, int>> zeros;
    string s;
    int i = 0, j = 0;
    int x;

    while (getline(cin, s)) {
        vector<int> xs;
        m.push_back(xs);
        j = 0;
        for (auto &&c : s) {
            x = c - '0';
            m[i].push_back(x);
            if (x == 0) {
                zeros.push_back(make_pair(i, j));
            }
            j++;
        }

        i++;
    }

    // for (auto &&i : m) {
    //     for (auto &&j : i) {
    //         cout << j << ", ";
    //     }
    //     cout << endl;
    // }

    int sum = 0;
    set<tuple<int, int>> visited;
    for (auto &&pos : zeros) {
        // cout << "(" << get<0>(pos) << ", " << get<1>(pos) << ")" << endl;
        sum += walk(pos, m, 0, &visited);
        visited.clear();
    }
    cout << sum << endl;
}
