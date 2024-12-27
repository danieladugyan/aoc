#include "lib.hpp"

#define ROBOTS 25
#define NUMPAD_ROWS 4
#define NUMPAD_COLS 3
#define KEYPAD_ROWS 2
#define KEYPAD_COLS 3

char numpad[NUMPAD_ROWS][NUMPAD_COLS] = {
    {'7', '8', '9'},
    {'4', '5', '6'},
    {'1', '2', '3'},
    {EOF, '0', 'A'},
};

char keypad[KEYPAD_ROWS][KEYPAD_COLS] = {
    {EOF, '^', 'A'},
    {'<', 'v', '>'},
};

map<char, vec2> num_coords;
map<char, vec2> key_coords;
map<vec2, char> dir_move = {
    {{0, 1}, '>'},
    {{0, -1}, '<'},
    {{1, 0}, 'v'},
    {{-1, 0}, '^'},
};

map<pair<int, string>, long> cache;

/*
 *  Returns the numbers of steps the last robot needs to take
 *  for the robots[i] to move to its goal.
 */
long walk(int i, vector<vec2>* robots, vec2 goal) {
    string row_moves;
    string col_moves;
    vec2 robot_pos = (*robots)[i];
    vec2 diff = goal - robot_pos;
    vec2 danger;
    if (i == 0) {
        danger = num_coords[EOF];
    } else {
        danger = key_coords[EOF];
    }

    int d_row = diff.first;
    if (d_row > 0) {
        row_moves.append(string(d_row, 'v'));
    } else if (d_row < 0) {
        row_moves.append(string(-d_row, '^'));
    }

    int d_col = diff.second;
    if (d_col > 0) {
        col_moves.append(string(d_col, '>'));
    } else if (d_col < 0) {
        col_moves.append(string(-d_col, '<'));
    }

    (*robots)[i] = goal;
    string moves;
    if (vec2{goal.first, robot_pos.second} == danger) {
        moves = col_moves + row_moves;
    } else if (vec2{robot_pos.first, goal.second} == danger) {
        moves = row_moves + col_moves;
    } else if (d_col < 0) {
        // Why is it optimal to go left first (if needed), otherwise up/down?
        moves = col_moves + row_moves;
    } else {
        moves = row_moves + col_moves;
    }
    moves += 'A';

    if (i == ROBOTS) {
        return moves.size();
    } else {
        long answer = 0;

        pair<int, string> cache_key{i, moves};
        if (cache.count(cache_key)) {
            answer = cache[cache_key];
        } else {
            i++;
            for (auto&& c : moves) {
                answer += walk(i, robots, key_coords[c]);
            }
        }

        // if (i < 8) {
        //     cout << string(i * 2, ' ') << i << ": " << robot_pos << " " <<
        //     goal << " " << answer << endl;
        // }
        cache[cache_key] = answer;

        return answer;
    }
}

int main() {
    for (int row = 0; row < NUMPAD_ROWS; row++) {
        for (int col = 0; col < NUMPAD_COLS; col++) {
            char c = numpad[row][col];
            num_coords[c] = {row, col};
        }
    }

    for (int row = 0; row < KEYPAD_ROWS; row++) {
        for (int col = 0; col < KEYPAD_COLS; col++) {
            char c = keypad[row][col];
            key_coords[c] = {row, col};
        }
    }

    long answer = 0;
    string pin;
    while (getline(cin, pin)) {
        int pin_numeric = stoi(pin.substr(0, 3));

        vector<vec2> robots;
        robots.push_back(num_coords['A']);
        for (int i = 0; i < ROBOTS; i++) {
            robots.push_back(key_coords['A']);
        }

        for (auto&& pc : pin) {
            cout << pc << endl;
            answer += walk(0, &robots, num_coords[pc]) * pin_numeric;
            cache.clear();
        }

        // cout << moves3.size() << " * " << pin_numeric << endl;
        // cout << moves3 << endl;
        // cout << moves2 << endl;
        // cout << moves1 << endl;
        // cout << pin << endl;
    }
    cout << answer << endl;
}