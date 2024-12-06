#include <bits/stdc++.h>
#define DEBUG 0

using namespace std;

int main() {
    vector<string> lines;
    string s;
    auto pos = string::npos;
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
    auto guard_pos = make_pair(row, col);
    auto guard_dir = dir;
    int loop = 0;

    for (unsigned i = 0; i < lines.size(); i++) {
        for (unsigned j = 0; j < lines[i].size(); j++) {
            auto temp = lines;
            // can't place obstacle on guard
            if (i == get<0>(guard_pos) && j == get<1>(guard_pos)) {
                continue;
            }
            // skip if already an obstacle
            if (temp[i][j] == 'X') {
                continue;
            }

            // For all valid obstacle placements

#if DEBUG
            cout << i << "," << j << endl;
#endif

            // place the new obstacle
            temp[i][j] = 'O';

            // reset to initial guard state
            row = get<0>(guard_pos);
            col = get<1>(guard_pos);
            dir = guard_dir;

            // log initial record
            set<tuple<int, int, tuple<int, int>>> record;
            record.insert(make_tuple(row, col, dir));

            while (true) {
#if DEBUG
                temp[row][col] = 'X';
                for (auto &&line : temp) {
                    cout << line << endl;
                }
                cout << "----------" << endl;
#endif
                auto next_row = row + get<0>(dir);
                auto next_col = col + get<1>(dir);

                // The guard eventually leaves the mapped area.
                if (!(0 <= next_row && next_row < temp.size() &&
                      0 <= next_col && next_col < temp[row].size())) {
                    break;
                }

                // If there is something directly in front, turn right 90 deg.
                if (temp[next_row][next_col] == '#' ||
                    temp[next_row][next_col] == 'O') {
                    if (dir == make_pair(-1, 0)) {
                        dir = make_pair(0, 1);
                    } else if (dir == make_pair(0, 1)) {
                        dir = make_pair(1, 0);
                    } else if (dir == make_pair(1, 0)) {
                        dir = make_pair(0, -1);
                    } else {
                        dir = make_pair(-1, 0);
                    }
                } else {
                    // Otherwise, take a step forward.
                    row += get<0>(dir);
                    col += get<1>(dir);
                }

                // If recurring pos+dir, the guard is stuck in a loop.
                if (record.count(make_tuple(row, col, dir))) {
#if DEBUG
                    cout << "loop: " << i << "," << j << endl;
#endif
                    loop += 1;
                    break;
                }
                record.insert(make_tuple(row, col, dir));
            }
        }
    }

    cout << loop << endl;
}