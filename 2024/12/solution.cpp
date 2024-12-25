#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> vec2;

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

template <typename T, typename Y>
auto operator<<(ostream &stream, pair<T, Y> const &p) -> ostream & {
    stream << "(" << p.first << ',' << p.second << ")";
    return stream;
}

int region(pair<int, int> p, vector<string> *m, set<pair<int, int>> *visited) {
    char plant = (*m)[p.first][p.second];
    set<pair<int, int>> q;
    q.insert(p);
    set<pair<vec2, vec2>> perims;

    int area = 0;
    int sides = 0;
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
                // "normalize" sides by always storing positive dir
                if (dir.first < 0 || dir.second < 0) {
                    perims.insert({next, {abs(dir.first), abs(dir.second)}});
                } else {
                    perims.insert({curr, dir});
                }
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

    // cout << "plant = " << plant << " | " << "pos = " << p
    //      << " | perimeter = " << perimeter << " | " << "set = " << perims.size()
    //      << endl;
    // for (auto &&i : perims) {
    //     cout << i.first << "->" << i.second << endl;
    // }

    pair<vec2, vec2> curr_perim, next_perim;
    while (!perims.empty()) {
        // take a perimeter segment from the "queue"
        curr_perim = *perims.begin();
        bool is_plant = get(curr_perim.first, m) == plant;

        // delete it and all of its adjacent perimeters
        perims.erase(perims.begin());
        while (true) {
            curr_perim = {{curr_perim.first.first + curr_perim.second.second,
                           curr_perim.first.second + curr_perim.second.first},
                          curr_perim.second};
            if (perims.count(curr_perim) &&
                (get(curr_perim.first, m) == plant) == is_plant) {
                perims.erase(curr_perim);
            } else {
                break;
            }
        }

        while (true) {
            curr_perim = {{curr_perim.first.first - curr_perim.second.second,
                           curr_perim.first.second - curr_perim.second.first},
                          curr_perim.second};
            if (perims.count(curr_perim) &&
                (get(curr_perim.first, m) == plant) == is_plant) {
                perims.erase(curr_perim);
            } else {
                break;
            }
        }

        sides++;
    }

    // cout << "area = " << area << " sides = " << sides << endl << endl;
    return area * sides;
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