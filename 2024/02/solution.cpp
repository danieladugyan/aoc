#include <bits/stdc++.h>

using namespace std;

bool check(int curr, int next) { return next - curr >= 1 && next - curr <= 3; }

int main() {
    string s;
    vector<int> levels;
    int a;
    int reports = 0;
    int failed = 0;

    // read every line (report)
    while (getline(cin, s)) {
        stringstream ss(s);
        // push every number into a vector
        while (ss >> a) {
            levels.push_back(a);
        }

        // is the array increasing or decreasing?
        if (levels.front() > levels.back()) {
            reverse(levels.begin(), levels.end());
        }

        cout << "diff: " << levels.back() - levels.front() << endl;
        cout << "level: ";
        for (auto &&i : levels) {
            cout << i << ", ";
        }
        cout << endl;

        unsigned int i = 0;
        while (i < levels.size() - 1) {
            int curr = levels[i], next = levels[i + 1],
                nextnext = levels[i + 2];
            cout << curr << " " << next << " ";

            if (check(curr, next)) {
                cout << "pass" << endl;
            } else {
                if (failed == 0) {
                    if (i + 2 >= levels.size()) {
                        cout << "first fail at end of report -> pass!";
                        break;
                    }

                    failed++;
                    if (i > 0) { // <-- forgot the edge case where i = 0
                        if (check(levels[i - 1], next)) {
                            cout << "saved, delete " << curr << endl;
                            levels.erase(levels.begin() + i);
                            // i--;
                            continue;
                        }
                    } else {
                        if (check(next, nextnext)) {
                            cout << "saved, delete " << curr << endl;
                            levels.erase(levels.begin() + i);
                            // i--;
                            continue;
                        }
                    }

                    if (check(curr, nextnext)) {
                        cout << "saved, delete " << next << endl;
                        levels.erase(levels.begin() + i + 1);
                        i++;
                        continue;
                    }

                    cout << "lookahead failed" << endl;
                    failed++;
                    break;
                } else {
                    cout << "fail, again." << endl;
                    failed++;
                    break;
                }
            }

            i++;
        }

        if (failed < 2) {
            reports++;
        }
        failed = 0;
        levels.clear();

        cout << reports << endl;
    }
    cout << reports << endl;
}