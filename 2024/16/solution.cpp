#include <bits/stdc++.h>
#define POS 0
#define DIR 1

using namespace std;

typedef pair<int, int> vec2;
typedef pair<vec2, vec2> node_t;  // pos, dir

vector<vec2> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

node_t get_node(vec2 pos, vec2 dir) {
    node_t n;
    n.first = pos;
    n.second = dir;
    return n;
}

void turn_ccw(node_t* node) {
    auto it = find(dirs.begin(), dirs.end(), node->second);
    if (prev(it) < dirs.begin()) {
        node->second = dirs.back();
    } else {
        node->second = *prev(it);
    }
}
void turn_cw(node_t* node) {
    auto it = find(dirs.begin(), dirs.end(), node->second);

    if (next(it) == dirs.end()) {
        node->second = dirs.front();
    } else {
        node->second = *next(it);
    }
}

char get_at(vec2 pos, vector<string>* map) {
    return (*map)[pos.first][pos.second];
}

int main() {
    string s;
    vec2 goal;
    vector<string> m;
    node_t player;
    node_t node;
    map<node_t, int> distance;

    while (getline(cin, s)) {
        m.push_back(s);
    }

    for (unsigned row = 0; row < m.size(); row++) {
        for (unsigned col = 0; col < m[row].size(); col++) {
            vec2 pos = {static_cast<int>(row), static_cast<int>(col)};
            for (auto&& dir : dirs) {
                node = get_node(pos, dir);
                distance[node] = INT_MAX;
            }

            if (m[row][col] == 'S') {
                get<POS>(player) = pos;
                get<DIR>(player) = {0, 1};  // eastwards
                distance[player] = 0;
            }

            if (m[row][col] == 'E') {
                goal = pos;
            }
        }
    }

    set<node_t> seen;
    map<node_t, set<node_t>> pred;

    // -distance, node_hash
    priority_queue<pair<int, node_t>> q;
    q.push({0, player});
    while (!q.empty()) {
        // we're at node a...
        node_t a = q.top().second;
        q.pop();

        if (seen.count(a)) continue;
        seen.insert(a);

        node_t b1 = a;
        get<POS>(b1).first += get<DIR>(b1).first;
        get<POS>(b1).second += get<DIR>(b1).second;

        node_t b2 = a;
        turn_cw(&b2);

        node_t b3 = a;
        turn_ccw(&b3);

        vector<pair<node_t, int>> adj = {{b1, 1}, {b2, 1000}, {b3, 1000}};

        for (auto u : adj) {
            if (get_at(get<POS>(u.first), &m) == '#') {
                continue;
            }

            // ...going to node b.
            node_t b = u.first;
            int w = u.second;
            if (distance[a] + w <= distance[b]) {
                distance[b] = distance[a] + w;
                q.push({-distance[b], b});
                pred.try_emplace(b, set<node_t>{});
                pred[b].insert(a);
            }
        }
    }

    // NOTE! this assumes there's only node with least cost
    // Conceivably, you could reach the goal with different direction,
    // but the same score. Not given our specific input though.
    node_t goal_node;
    int shortest = INT_MAX;
    for (auto&& dir : dirs) {
        node = get_node(goal, dir);
        if (shortest > distance[node]) {
            shortest = distance[node];
            goal_node = node;
        }
    }
    cout << "score: " << shortest << endl;

    node = goal_node;
    set<vec2> tiles;
    vector<node_t> xs{goal_node};
    while (!xs.empty()) {
        node = xs.back();
        xs.pop_back();

        tiles.insert(get<POS>(node));
        // if (node == player) break;

        // cout << "(" << get<POS>(node).first << ", " << get<POS>(node).second
        //      << ")" << " | ";
        // cout << "(" << get<DIR>(node).first << ", " << get<DIR>(node).second
        //      << ")" << endl;

        for (auto&& i : pred[node]) {
            if (find(xs.begin(), xs.end(), i) == xs.end()) {
                xs.push_back(i);
            }
        }
    }

    cout << "tiles: " << tiles.size() << endl;
}