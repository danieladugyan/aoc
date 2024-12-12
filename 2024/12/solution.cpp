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
//     int perimeter;
// };

char get(pair<int, int> p, vector<string> *m) {
    unsigned row = p.first;
    unsigned col = p.second;
    if (!(0 <= row && row < (*m).size())) return EOF;
    if (!(0 <= col && col < (*m)[row].size())) return EOF;

    return (*m)[row][col];
}

void print_pair(pair<int, int> *p) {
    cout << "(" << (*p).first << "," << (*p).second << "), ";
}

int region(pair<int, int> p, vector<string> *m, set<pair<int, int>> *visited) {
    char plant = (*m)[p.first][p.second];
    set<pair<int, int>> q;
    q.insert(p);

    int area = 0;
    int perimeter = 0;

    vector<pair<int, int>> dirs = {{0, 1}, {-1, 0}, {1, 0}, {0, -1}};
    pair<int, int> curr, next;
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
                perimeter += 1;
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

    // cout << "area = " << area << " perim = " << perimeter << endl;
    return area * perimeter;
}

int main() {
    vector<string> m;
    string s;
    while (getline(cin, s)) {
        m.push_back(s);
    }

    set<pair<int, int>> visited;
    int sum = 0;
    for (unsigned row = 0; row < m.size(); row++) {
        for (unsigned col = 0; col < m[col].size(); col++) {
            char c = m[row][col];
            if (!isalpha(c)) continue;

            auto p = make_pair(row, col);
            if (visited.count(p)) continue;

            int r = region(p, &m, &visited);
            sum += r;

            // cout << "------" << endl;
            // cout << c << ":" << endl;
            // cout << "region score = " << r << endl;
        }
    }
    cout << sum << endl;
}