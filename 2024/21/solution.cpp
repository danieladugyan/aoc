#include "lib.hpp"

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

string walk(vec2 robot_pos, vec2 goal, vec2 danger) {
    string row_moves;
    string col_moves;
    vec2 diff = goal - robot_pos;
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

    // avoid disallowed corner of pads
    if (vec2{goal.first, robot_pos.second} == danger) {
        return col_moves + row_moves + 'A';
    };
    if (vec2{robot_pos.first, goal.second} == danger) {
        return row_moves + col_moves + 'A';
    };

    // Why is it optimal to go left first (if needed), otherwise up/down?
    if (d_col < 0) {
        return col_moves + row_moves + 'A';
    }
    return row_moves + col_moves + 'A';
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

    int answer = 0;
    string pin;
    while (getline(cin, pin)) {
        int pin_numeric = stoi(pin.substr(0, 3));

        vec2 robot1 = num_coords['A'];
        string moves1;
        for (auto&& c : pin) {
            vec2 next = num_coords[c];
            moves1 += walk(robot1, next, num_coords[EOF]);
            robot1 = next;
        }

        vec2 robot2 = key_coords['A'];
        string moves2;
        for (auto&& c : moves1) {
            vec2 next = key_coords[c];
            moves2 += walk(robot2, next, key_coords[EOF]);
            robot2 = next;
        }

        vec2 robot3 = key_coords['A'];
        string moves3;
        for (auto&& c : moves2) {
            vec2 next = key_coords[c];
            moves3 += walk(robot3, next, key_coords[EOF]);
            robot3 = next;
        }

        // cout << pin << ": " << moves3 << endl;
        // cout << moves3.size() << " * " << pin_numeric << endl;
        answer += moves3.size() * pin_numeric;
        // cout << moves3 << endl;
        // cout << moves2 << endl;
        // cout << moves1 << endl;
        // cout << pin << endl;
    }
    cout << answer << endl;
}