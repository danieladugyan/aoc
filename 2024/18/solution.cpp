#include <bits/stdc++.h>
#define RANGE 70    // 70
#define BYTES 1024  // 1024
using namespace std;

typedef pair<int, int> vec2;

template <typename T, typename Y>
auto operator<<(ostream &stream, pair<T, Y> const &p) -> ostream & {
    stream << "(" << p.first << ',' << p.second << ")";
    return stream;
}

int main() {
    set<vec2> falling;
    queue<vec2> more_falling;
    int row, col;
    while (scanf("%d,%d\n", &col, &row) != EOF) {
        if (falling.size() >= BYTES) {
            more_falling.push({row, col});
        } else {
            falling.insert({row, col});
        }
    }

    while (more_falling.size() > 0) {
        vec2 next_falling_byte = more_falling.front();
        falling.insert(next_falling_byte);
        more_falling.pop();

        priority_queue<pair<int, vec2>> q;
        set<vec2> processed;
        map<vec2, int> distance;
        for (row = 0; row <= RANGE; row++) {
            for (col = 0; col <= RANGE; col++) {
                distance[{row, col}] = INT_MAX;
            }
        }
        distance[{0, 0}] = 0;
        q.push({0, {0, 0}});

        while (!q.empty()) {
            vec2 a = q.top().second;
            q.pop();
            if (processed.count(a)) continue;
            processed.insert(a);

            for (auto dir : vector<vec2>{{0, 1}, {1, 0}, {-1, 0}, {0, -1}}) {
                vec2 b = {a.first + dir.first, a.second + dir.second};
                bool in_bounds = 0 <= b.first && b.first <= RANGE &&
                                 0 <= b.second && b.second <= RANGE;
                bool is_wall = falling.count(b);
                if (!in_bounds || is_wall) continue;

                int new_distance = distance[a] + 1;
                if (new_distance < distance[b]) {
                    distance[b] = new_distance;
                    q.push({-new_distance, b});
                }
            }
        }

        int d = distance[{RANGE, RANGE}];
        if (d == INT_MAX) {
            cout << next_falling_byte << endl;
            break;
        }
        // cout << next_falling_byte << " " << d << endl;
    }
}