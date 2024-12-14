#include <bits/stdc++.h>

using namespace std;

// The regions are located in a matrix.
// In principle, each plant has an area of 1
// and is surrounded by 4 fences,
// with exceptions for each neighbouring plant of the same type.

// For each plant, walk out to it's neighbouring plants and add up the
// area/perimeterr. Skip already visited plants.

// typedef struct cost;
// struct cost {
//     int area;
//     int sides;
// };
typedef pair<int, int> vec2;

char get(vec2 p, vector<string> *m) {
    unsigned row = p.first;
    unsigned col = p.second;
    if (!(0 <= row && row < (*m).size())) return EOF;
    if (!(0 <= col && col < (*m)[row].size())) return EOF;

    return (*m)[row][col];
}

void print_pair(vec2 *p) {
    cout << "(" << (*p).first << "," << (*p).second << ")";
}

int region(vec2 p, vector<string> *m, set<vec2> *visited) {
    char plant = (*m)[p.first][p.second];
    set<vec2> q;
    q.insert(p);

    int area = 0;

    vector<vec2> dirs = {{0, 1}, {-1, 0}, {1, 0}, {0, -1}};
    vec2 curr, next;

    // position of perim, vertical/horizontal
    vector<vec2> perims;

    while (!q.empty()) {
        // pop from queue
        curr = *q.begin();
        q.erase(q.begin());
        area += 1;

        // cout << "curr: ";
        // print_pair(&curr);
        // cout << endl;

        // add to visited
        (*visited).insert(curr);

        // cout << "visited: " << endl;
        // for (auto &&i : *visited) {
        //     cout << "(" << i.first << "," << i.second << "), ";
        // }
        // cout << endl;

        // for each direction
        for (auto &&dir : dirs) {
            next = make_pair(curr.first + dir.first, curr.second + dir.second);
            bool is_plant = get(next, m) == plant;
            bool is_visited = (*visited).count(next);

            if (!is_plant) {
                perims.push_back(next);
            }

            // cout << "\tnext: ";
            // print_pair(&next);
            // cout << endl;

            // cout << " is_plant " << is_plant << " is_visited " << is_visited
            // << endl;

            if (is_plant && !is_visited) {
                q.insert(next);
            }
        }
    }

    for (auto &&i : perims) {
        cout << "perim: ";
        cout << "(" << i.first << "," << i.second << ")";
        cout << endl;
    }
    cout << endl;

    vec2 first = *perims.begin();
    vec2 curr_dir{0, 0};
    vector<vec2> diag_dirs = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
    set<vec2> vis;

    int sides = 0;
    bool flag;

    curr = first;
    do {
        vis.insert(curr);
        cout << "curr: ";
        print_pair(&curr);
        cout << " sides: " << sides;
        cout << endl;

        flag = false;
        for (auto &&dir : dirs) {
            next = make_pair(curr.first + dir.first, curr.second + dir.second);

            cout << "\tnext: ";
            print_pair(&next);
            cout << endl;

            if (find(perims.begin(), perims.end(), next) != perims.end() &&
                !vis.count(next)) {
                flag = true;
                curr = next;
                if (curr_dir != dir) {
                    sides += 1;
                    curr_dir = dir;
                }
                break;
            }
        }

        // if directly adjacent perim, continue to next perim
        if (flag) continue;

        // if diagonally adjacent, it's a new side
        for (auto &&dir : diag_dirs) {
            next = make_pair(curr.first + dir.first, curr.second + dir.second);

            cout << "\tnext: ";
            print_pair(&next);
            cout << endl;

            if (find(perims.begin(), perims.end(), next) != perims.end() &&
                !vis.count(next)) {
                flag = true;
                if (get({next.first, curr.second}, m) == plant) {
                    curr = {curr.first, next.second};
                    if (curr_dir != make_pair(0, dir.second)) {
                        sides += 1;
                        curr_dir = make_pair(0, dir.second);
                    }
                } else {
                    curr = {next.first, curr.second};
                    if (curr_dir != make_pair(dir.first, 0)) {
                        sides += 1;
                        curr_dir = make_pair(dir.first, 0);
                    }
                }
                break;
            }
        }

        if (flag) continue;

        vec2 diff = {first.first - curr.first, first.second - curr.second};
        if (abs(diff.first) <= 1 && abs(diff.second) <= 1) {
            curr = first;
        }

    } while (curr != first);

    cout << "area = " << area << " sides = " << sides << endl;
    return area * sides;
}

int main() {
    vector<string> m;
    string s;
    while (getline(cin, s)) {
        m.push_back(s);
    }

    set<vec2> visited;
    int sum = 0;
    for (unsigned row = 0; row < m.size(); row++) {
        for (unsigned col = 0; col < m[col].size(); col++) {
            char c = m[row][col];
            if (!isalpha(c)) continue;

            auto p = make_pair(row, col);
            if (visited.count(p)) continue;

            cout << "------" << endl;
            cout << c << ":" << endl;
            int r = region(p, &m, &visited);
            sum += r;
            cout << "region score = " << r << endl;
        }
    }
    cout << sum << endl;
}