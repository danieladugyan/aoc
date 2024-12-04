#include <bits/stdc++.h>

using namespace std;

bool check_xmas(int i, int j, vector<string> lines) {
    int n = lines.size();
    int m = lines[0].size();
    
    if (!(i - 1 >= 0 && j - 1 >= 0 && i + 1 < n && j + 1 < m)) {
        return false;
    }

    return (
        // down-right
        lines[i - 1][j - 1] == 'M' &&
        lines[i + 1][j + 1] == 'S' &&
        // up-right
        lines[i + 1][j - 1] == 'M' &&
        lines[i - 1][j + 1] == 'S'
    ) || (
        // down-right
        lines[i - 1][j - 1] == 'S' &&
        lines[i + 1][j + 1] == 'M' &&
        // up-right
        lines[i + 1][j - 1] == 'M' &&
        lines[i - 1][j + 1] == 'S'
    ) || (
        // down-right
        lines[i - 1][j - 1] == 'M' &&
        lines[i + 1][j + 1] == 'S' &&
        // up-right
        lines[i + 1][j - 1] == 'S' &&
        lines[i - 1][j + 1] == 'M'
    ) || (
        // down-right
        lines[i - 1][j - 1] == 'S' &&
        lines[i + 1][j + 1] == 'M' &&
        // up-right
        lines[i + 1][j - 1] == 'S' &&
        lines[i - 1][j + 1] == 'M'
    );
}

int main() {
    vector<string> lines;
    string s;
    int occurs = 0;
    while (getline(cin, s)) {
        lines.push_back(s);
    }

    for (unsigned i = 0; i < lines.size(); i++) {
        for (unsigned j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] != 'A') continue;
            
            if (check_xmas(i, j, lines)) {
                occurs += 1;
            }
        }
    }
    cout << occurs << endl;
}