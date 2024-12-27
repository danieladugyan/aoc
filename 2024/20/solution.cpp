#include "lib.hpp"

int main() {
    vec2 start, goal;
    vector<string> m;
    string s;
    while (getline(cin, s)) {
        m.push_back(s);
    }

    set<vec2> path;
    priority_queue<pair<int, vec2>> q;
    set<vec2> processed;
    map<vec2, int> distance;
    int shortest_path = 0;
    for (unsigned row = 0; row < m.size(); row++) {
        for (unsigned col = 0; col < m[row].size(); col++) {
            distance[{row, col}] = INT_MAX;
            if (m[row][col] != '#') {
                shortest_path += 1;
                path.insert({row, col});
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

    set<pair<vec2, vec2>> cheats;
    for (auto &&p : path) {
        for (auto &&d1 : DIRS) {
            vec2 cheat1 = p + d1;
            char c1 = m[cheat1.first][cheat1.second];
            bool in_wall = cheat1.first == 0 || cheat1.first == m.size() - 1 ||
                           cheat1.second == 0 ||
                           cheat1.second == m[cheat1.first].size() - 1;
            if (c1 != '#' || in_wall) {
                continue;  // TODO: does c1 really need to be an obstacle?
            }
            m[cheat1.first][cheat1.second] = '1';
            for (auto &&d2 : DIRS) {
                vec2 cheat2 = cheat1 + d2;
                char c2 = m[cheat2.first][cheat2.second];
                bool in_wall = cheat2.first == 0 ||
                               cheat2.first == m.size() - 1 ||
                               cheat2.second == 0 ||
                               cheat2.second == m[cheat2.first].size() - 1;
                if (c2 == '#' || in_wall || d1 + d2 == vec2{0, 0}) continue;
                m[cheat2.first][cheat2.second] = '2';

                // Dijkstra with "cheat" instance
                priority_queue<pair<int, vec2>> q_copy = q;
                set<vec2> processed_copy = processed;
                map<vec2, int> distance_copy = distance;
                bool been_at_1 = false;
                while (!q_copy.empty()) {
                    vec2 curr = q_copy.top().second;
                    q_copy.pop();

                    if (processed_copy.count(curr)) continue;
                    processed_copy.insert(curr);
                    if (m[curr.first][curr.second] == '1') been_at_1 = true;

                    for (auto &&dir : DIRS) {
                        vec2 next = curr + dir;
                        char c = m[next.first][next.second];
                        if (c != '#') {
                            if (c == '2' && !been_at_1) continue;
                            int new_distance = distance_copy[curr] + 1;
                            if (new_distance < distance_copy[next]) {
                                distance_copy[next] = new_distance;
                                q_copy.push({-new_distance, next});
                            }
                        }
                    }
                }

                int diff = shortest_path - distance_copy[goal];
                if (diff >= 100) {
                    // for (auto &&line : m) {
                    //     cout << line << endl;
                    // }
                    // cout << "diff = " << diff << endl;
                    // cout << p << "," << cheat2 << endl;
                    // cout << "----------" << endl;
                    cheats.insert({p, cheat2});
                }

                m[cheat2.first][cheat2.second] = c2;
            }
            m[cheat1.first][cheat1.second] = c1;
        }
    }
    cout << cheats.size() << endl;

}