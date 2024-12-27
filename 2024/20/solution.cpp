#include "lib.hpp"

int main() {
    vec2 start, goal;
    vector<string> m;
    string s;
    while (getline(cin, s)) {
        m.push_back(s);
    }

    priority_queue<pair<int, vec2>> q;
    set<vec2> processed;
    map<vec2, int> distance;
    int shortest_path = 0;
    for (unsigned row = 0; row < m.size(); row++) {
        for (unsigned col = 0; col < m[row].size(); col++) {
            distance[{row, col}] = INT_MAX;
            if (m[row][col] != '#') {
                shortest_path += 1;
            }
            if (m[row][col] == 'S') {
                start = {row, col};
                q.push({0, start});
                distance[start] = 0;
                shortest_path -= 1;
            }
            if (m[row][col] == 'E') {
                goal = {row, col};
            }
        }
    }

    map<vec2, vec2> prev;
    while (!q.empty()) {
        vec2 curr = q.top().second;
        q.pop();

        if (processed.count(curr)) continue;
        processed.insert(curr);

        for (auto&& dir : DIRS) {
            vec2 next = curr + dir;
            char c = m[next.first][next.second];
            if (c != '#') {
                int new_distance = distance[curr] + 1;
                if (new_distance < distance[next]) {
                    distance[next] = new_distance;
                    prev[next] = curr;
                    q.push({-new_distance, next});
                }
            }
        }
    }

    vector<vec2> path;
    vec2 curr = goal;
    while (prev.count(curr)) {
        path.insert(path.begin(), curr);
        curr = prev[curr];
    }
    path.insert(path.begin(), start);

    int cheats = 0;
    for (unsigned i = 0; i < path.size(); i++) {
        for (unsigned j = i; j < path.size(); j++) {
            auto&& p1 = path[i];
            auto&& p2 = path[j];
            vec2 v = p2 - p1;
            int length = abs(v.first) + abs(v.second);
            if (length > 20) continue;

            int cheat_distance = 0;
            for (unsigned pi = 0; pi < path.size(); pi++) {
                auto&& p = path[pi];
                if (p == p1) {
                    cheat_distance += length;
                    pi = j;
                } else {
                    cheat_distance += 1;
                }
            }

            int diff = shortest_path - cheat_distance;
            // cout << "diff = " << diff << endl;
            if (diff >= 100) {
                cheats += 1;
            }
        }
    }

    cout << cheats << endl;
}