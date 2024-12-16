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

bool is_box(char c) { return c == '[' || c == ']'; }

bool push(vector<vec2> obstacles, vec2 dir, vector<string> *map) {
    vec2 obstacle1, obstacle2, next_pos1, next_pos2;
    char next_char1, next_char2;

    // If any collide into a wall, return without action.
    for (auto &&obstacle : obstacles) {
        obstacle1 = obstacle;
        next_pos1 = obstacle1 + dir;

        obstacle2 = obstacle + vec2{0, 1};
        next_pos2 = obstacle2 + dir;

        next_char1 = (*map)[next_pos1.real()][next_pos1.imag()];
        next_char2 = (*map)[next_pos2.real()][next_pos2.imag()];

        if (next_char1 == '#' || next_char2 == '#') {
            return false;
        }
    }

    // If any collide into an obstacle, push the obstacle in dir.
    vector<vec2> next_obstacles;
    for (auto &&obstacle : obstacles) {
        obstacle1 = obstacle;
        next_pos1 = obstacle1 + dir;

        obstacle2 = obstacle + vec2{0, 1};
        next_pos2 = obstacle2 + dir;

        next_char1 = (*map)[next_pos1.real()][next_pos1.imag()];
        next_char2 = (*map)[next_pos2.real()][next_pos2.imag()];

        if (is_box(next_char1) && next_pos1 != obstacle2) {
            if (next_char1 == '[') {
                next_obstacles.push_back(next_pos1);
            } else {
                next_obstacles.push_back(next_pos1 + vec2{0, -1});
            }
        }

        if (is_box(next_char2) && next_pos2 != obstacle1) {
            if (next_char2 == '[') {
                next_obstacles.push_back(next_pos2);
            } else {
                next_obstacles.push_back(next_pos2 + vec2{0, -1});
            }
        }
    }

    if (!next_obstacles.empty()) {
        // cout << "next: ";
        // for (auto &&i : next_obstacles) {
        //     cout << i << ", ";
        // }
        // cout << endl;

        bool pushed = push(next_obstacles, dir, map);
        if (!pushed) return false;
    }

    // If they would move into empty space, move!
    for (auto &&obstacle : obstacles) {
        obstacle1 = obstacle;
        next_pos1 = obstacle1 + dir;

        obstacle2 = obstacle + vec2{0, 1};
        next_pos2 = obstacle2 + dir;

        (*map)[obstacle1.real()][obstacle1.imag()] = '.';
        (*map)[obstacle2.real()][obstacle2.imag()] = '.';
        (*map)[next_pos1.real()][next_pos1.imag()] = '[';
        (*map)[next_pos2.real()][next_pos2.imag()] = ']';
    }

    return true;
}

// bool push(vec2 *obstacle, vec2 *dir, vector<string> *map) {
//     char c = (*map)[(*obstacle).real()][(*obstacle).imag()];
//     vec2 next_pos1, next_pos2, obstacle1, obstacle2;

//     if (c == '[') {
//         obstacle1 = *obstacle;
//         next_pos1 = obstacle1 + *dir;

//         obstacle2 = *obstacle + vec2{0, 1};
//         next_pos2 = obstacle2 + *dir;
//     } else {
//         obstacle1 = *obstacle + vec2{0, -1};
//         next_pos1 = obstacle1 + *dir;

//         obstacle2 = *obstacle;
//         next_pos2 = obstacle2 + *dir;
//     }
//     // cout << obstacle1 << endl;
//     // cout << obstacle2 << endl;

//     char next_char1 = (*map)[next_pos1.real()][next_pos1.imag()];
//     char next_char2 = (*map)[next_pos2.real()][next_pos2.imag()];

//     // If it collides into a wall, return without action.
//     if (next_char1 == '#' || next_char2 == '#') {
//         return false;
//     }

//     // If it collides into an obstacle, push the obstacle in dir.
//     if (is_box(next_char1) && next_pos1 != obstacle2) {
//         bool pushed = push(&next_pos1, dir, map);
//         if (!pushed) {
//             return false;
//         }
//     }

//     if (is_box(next_char2) && next_pos2 != obstacle1) {
//         bool pushed = push(&next_pos2, dir, map);
//         if (!pushed) {
//             return false;
//         }
//     }

//     // If it would move into empty space, move!
//     (*map)[(obstacle1).real()][(obstacle1).imag()] = '.';
//     (*map)[(obstacle2).real()][(obstacle2).imag()] = '.';
//     (*map)[(next_pos1).real()][(next_pos1).imag()] = '[';
//     (*map)[(next_pos2).real()][(next_pos2).imag()] = ']';
//     return true;
// }

void walk(vec2 *robot, vec2 *dir, vector<string> *map) {
    vec2 next_pos = *robot + *dir;
    char next_char = (*map)[next_pos.real()][next_pos.imag()];

    if (next_char == '#') {
        return;
    }

    vector<vec2> obstacles;
    bool pushed;
    if (next_char == '[') {
        obstacles.push_back(next_pos);
    } else if (next_char == ']') {
        obstacles.push_back(next_pos + vec2{0, -1});
    }

    pushed = push(obstacles, *dir, map);
    if (!pushed) {
        return;
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

    // scale map
    vec2 robot;
    for (unsigned row = 0; row < map.size(); row++) {
        for (unsigned col = 0; col < map[row].size(); col += 2) {
            c = map[row][col];
            switch (c) {
                case '@':
                    robot = {static_cast<int>(row), static_cast<int>(col)};
                    map[row].insert(map[row].begin() + col + 1, '.');
                    break;
                case '.':
                case '#':
                    map[row].insert(map[row].begin() + col + 1, c);
                    break;
                case 'O':
                    map[row][col] = '[';
                    map[row].insert(map[row].begin() + col + 1, ']');
                    break;
                default:
                    break;
            }
        }
    }

    // p_map();
    // cout << endl;

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
            if (map[row][col] == '[') {
                sum += row * 100 + col;
            }
        }
    }
    cout << sum << endl;
}