#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<string> lines;
    string s;
    int pos = 0;
    unsigned row = 0, col = 0;
    bool found = false;
    pair<int, int> dir;

    // load map
    while (getline(cin, s)) {
        if (!found) {
            row++;
            pos = s.find("^", 0);
            if (pos != string::npos) {
                col = pos;
                found = true;
                dir = make_pair(-1, 0);
            }
            pos = s.find(">", 0);
            if (pos != string::npos) {
                col = pos;
                found = true;
                dir = make_pair(0, 1);
            }
            pos = s.find("v", 0);
            if (pos != string::npos) {
                col = pos;
                found = true;
                dir = make_pair(1, 0);
            }
            pos = s.find("<", 0);
            if (pos != string::npos) {
                col = pos;
                found = true;
                dir = make_pair(0, -1);
            }
            if (found) row--;
        }

        lines.push_back(s);
    }

    // cout << row << "," << col << endl;

    lines[row][col] = 'X';
    pos = 1;

    while (true) {
        switch (lines[row][col]) {
            case '#':
                // travel in direction
                row -= get<0>(dir);
                col -= get<1>(dir);

                // cout << "changing direction" << endl;
                if (dir == make_pair(-1, 0)) {
                    dir = make_pair(0, 1);
                } else if (dir == make_pair(0, 1)) {
                    dir = make_pair(1, 0);
                } else if (dir == make_pair(1, 0)) {
                    dir = make_pair(0, -1);
                } else {
                    dir = make_pair(-1, 0);
                }
                break;
            case '.':
                pos += 1;
                lines[row][col] = 'X';
                break;
            default:
                break;
        }

        // travel in direction
        row += get<0>(dir);
        col += get<1>(dir);

        // for (auto &&line : lines) {
        //     cout << line << endl;
        // }
        // cout << "----------" << endl;
        // sleep(1);

        // out-of-bounds?
        if (!(0 <= row && row < lines.size() && 0 <= col &&
              col < lines[row].size())) {
            break;
        }
    }
    cout << pos << endl;
}