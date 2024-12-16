#include <bits/stdc++.h>

using namespace std;

typedef complex<int> vec2;

struct player_t {
    vec2 dir;
    vec2 pos;
};

vector<vec2> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
vec2 goal;
vec2 pos;
int lowest_score = INT_MAX;

void turn_ccw(player_t* player) {
    auto it = find(dirs.begin(), dirs.end(), player->dir);
    if (prev(it) < dirs.begin()) {
        player->dir = dirs.back();
    } else {
        player->dir = *prev(it);
    }
}
void turn_cw(player_t* player) {
    auto it = find(dirs.begin(), dirs.end(), player->dir);

    if (next(it) == dirs.end()) {
        player->dir = dirs.front();
    } else {
        player->dir = *next(it);
    }
}
char get_at(vec2 pos, vector<string>* map) {
    return (*map)[pos.real()][pos.imag()];
}

pair<int, int> pos_pair(vec2 pos) {
    return pair<int, int>{pos.real(), pos.imag()};
}

void print_map(player_t* player, vector<string>* map) {
    for (unsigned row = 0; row < (*map).size(); row++) {
        for (unsigned col = 0; col < (*map)[row].size(); col++) {
            if (player->pos == vec2{row, col}) {
                cout << "S";
            } else {
                cout << get_at(vec2{row, col}, map);
            }
        }
        cout << endl;
    }
}

void walk(player_t* player, vector<string>* map, int score,
          set<pair<int, int>> visited) {
    // cout << "score: " << score << endl;
    // cout << "player: " << player->pos << " " << player->dir << endl;
    // print_map(player, map);
    // for (auto&& v : visited) {
    //     cout << vec2{get<0>(v), get<1>(v)} << ", ";
    // }
    // cout << endl;
    // cout << endl;

    if (get_at(player->pos, map) == 'E') {
        lowest_score = min(lowest_score, score);
        cout << "found path: " << score << endl;
        return;
    }

    // prune search
    if (score > lowest_score) {
        return;
    }

    visited.insert(pos_pair(player->pos));
    // try to walk forward
    player->pos += player->dir;
    if (get_at(player->pos, map) != '#' &&
        !visited.count(pos_pair(player->pos))) {
        walk(player, map, score + 1, visited);
    }
    player->pos -= player->dir;

    // try to rotate CW
    turn_cw(player);
    pos = player->pos + player->dir;
    if (get_at(pos, map) != '#' && !visited.count(pos_pair(pos))) {
        walk(player, map, score + 1000, visited);
    }
    turn_ccw(player);

    // try to rotate CCW
    turn_ccw(player);
    pos = player->pos + player->dir;
    if (get_at(pos, map) != '#' && !visited.count(pos_pair(pos))) {
        walk(player, map, score + 1000, visited);
    }
    turn_cw(player);
}

int main() {
    string s;
    vector<string> map;
    player_t player;

    while (getline(cin, s)) {
        map.push_back(s);
    }

    for (unsigned row = 0; row < map.size(); row++) {
        for (unsigned col = 0; col < map[row].size(); col++) {
            if (map[row][col] == 'S') {
                player.pos = {static_cast<int>(row), static_cast<int>(col)};
                player.dir = {0, 1};  // eastwards
            }
            if (map[row][col] == 'E') {
                goal = {static_cast<int>(row), static_cast<int>(col)};
            }
        }
    }

    for (auto&& i : map) {
        cout << i << endl;
    }

    cout << "player: " << player.pos << " " << player.dir << endl;
    cout << "goal: " << goal << endl;

    set<pair<int, int>> seen = {pos_pair(player.pos)};
    walk(&player, &map, 0, seen);
    cout << "lowest score: " << lowest_score << endl;
}