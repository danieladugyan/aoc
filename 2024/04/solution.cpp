#include <bits/stdc++.h>

using namespace std;

int check_horizontal(int i, int j, vector<string> lines) {
    int m = lines[0].size();
    return (
        j + 3 < m &&
        lines[i][j + 1] == 'M' &&
        lines[i][j + 2] == 'A' &&
        lines[i][j + 3] == 'S'
    ) + (
        j - 3 >= 0 &&
        lines[i][j - 1] == 'M' &&
        lines[i][j - 2] == 'A' &&
        lines[i][j - 3] == 'S'
    );
}
int check_vertical(int i, int j, vector<string> lines) {
    int n = lines.size();
    return 
        (i + 3 < n
        && lines[i + 1][j] == 'M'
        && lines[i + 2][j] == 'A'
        && lines[i + 3][j] == 'S') +
        (i - 3 >= 0
        && lines[i - 1][j] == 'M'
        && lines[i - 2][j] == 'A'
        && lines[i - 3][j] == 'S');
}
int check_diagonal(int i, int j, vector<string> lines) {
    int n = lines.size();
    int m = lines[0].size();
    return 
        (i + 3 < n && j + 3 < m
        && lines[i + 1][j + 1] == 'M'
        && lines[i + 2][j + 2] == 'A'
        && lines[i + 3][j + 3] == 'S') +
        (i - 3 >= 0 && j + 3 < m
        && lines[i - 1][j + 1] == 'M' 
        && lines[i - 2][j + 2] == 'A' 
        && lines[i - 3][j + 3] == 'S') +
        (i + 3 < n && j - 3 >= 0
        && lines[i + 1][j - 1] == 'M' 
        && lines[i + 2][j - 2] == 'A' 
        && lines[i + 3][j - 3] == 'S') +
        (i - 3 >= 0 && j - 3 >= 0
        && lines[i - 1][j - 1] == 'M'
        && lines[i - 2][j - 2] == 'A'
        && lines[i - 3][j - 3] == 'S');
}

int main() {
    vector<string> lines;
    string s;
    int occurs = 0;
    int sum = 0;
    while (getline(cin, s)) {
        lines.push_back(s);
    }

    for (unsigned i = 0; i < lines.size(); i++) {
        for (unsigned j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] != 'X') continue;
            
            if ((sum = check_horizontal(i, j, lines))) {
                // cout << sum << " horizontal:" << i << ", " << j << endl;
                occurs += sum;
            }
            
            if ((sum = check_vertical(i, j, lines))) {
                // cout << sum << " vertical:" << i << ", " << j << endl;
                occurs += sum;
            }
            
            if ((sum = check_diagonal(i, j, lines))) {
                // cout << sum << " diagonal:" << i << ", " << j << endl;
                occurs += sum;
            }
        }
    }
    cout << occurs << endl;
}