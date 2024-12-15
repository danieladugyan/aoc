#include <bits/stdc++.h>

#define p_map()            \
    for (auto &&i : map) { \
        cout << i << endl; \
    }
#define p_moves()            \
    for (auto &&i : moves) { \
        cout << i;           \
    }                        \
    cout << endl;

using namespace std;

typedef complex<int> vec2;

bool push(vec2 *obstacle, vec2 *dir, vector<string> *map) {
    // Try to push the obstacle in dir.
    vec2 next_pos = *obstacle + *dir;
    char next_char = (*map)[next_pos.real()][next_pos.imag()];

    // If it collides into a wall, return without action.
    if (next_char == '#') {
        return false;
    }

    // If it collides into an obstacle, push the obstacle in dir.
    if (next_char == 'O') {
        bool pushed = push(&next_pos, dir, map);
        if (!pushed) {
            return false;
        }
    }

    // If it would move into empty space, move!
    (*map)[(*obstacle).real()][(*obstacle).imag()] = '.';
    (*map)[(next_pos).real()][(next_pos).imag()] = 'O';
    return true;
}

void walk(vec2 *robot, vec2 *dir, vector<string> *map) {
    vec2 next_pos = *robot + *dir;
    char next_char = (*map)[next_pos.real()][next_pos.imag()];

    if (next_char == '#') {
        return;
    }

    if (next_char == 'O') {
        bool pushed = push(&next_pos, dir, map);
        if (!pushed) {
            return;
        }
    }

    (*map)[(*robot).real()][(*robot).imag()] = '.';
    *robot = next_pos;
    (*map)[(*robot).real()][(*robot).imag()] = '@';
}

int main() {
    vector<string> map;
    vector<char> moves;

    string s;
    char c;
    while (getline(cin, s)) {
        if (s.empty()) {
            break;
        }
        map.push_back(s);
    }

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            continue;
        }
        moves.push_back(c);
    }

    // find robot
    vec2 robot;
    for (unsigned row = 0; row < map.size(); row++) {
        for (unsigned col = 0; col < map[row].size(); col++) {
            if (map[row][col] == '@') {
                robot = {static_cast<int>(row), static_cast<int>(col)};
                break;
            }
        }
    }

    vec2 dir;
    for (auto &&move : moves) {
        switch (move) {
            case '<':
                dir = {0, -1};
                break;
            case '^':
                dir = {-1, 0};
                break;
            case '>':
                dir = {0, 1};
                break;
            case 'v':
                dir = {1, 0};
                break;
            default:
                cout << "error!" << endl;
                break;
        }

        walk(&robot, &dir, &map);

        // cout << "Move " << move << ":" << endl;
        // p_map();
        // cout << endl;
    }

    // p_map();
    // cout << "robot: " << robot << endl;

    long sum = 0;
    for (unsigned row = 0; row < map.size(); row++) {
        for (unsigned col = 0; col < map[row].size(); col++) {
            if (map[row][col] == 'O') {
                sum += row * 100 + col;
            }
        }
    }
    cout << sum << endl;
}