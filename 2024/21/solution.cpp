#include <bits/stdc++.h>

using namespace std;

#define NUMPAD_ROWS 4
#define NUMPAD_COLS 3
#define KEYPAD_ROWS 2
#define KEYPAD_COLS 3

typedef complex<int> vec2;

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

string walk(vec2* origin, vec2 goal) {
    string moves;
    vec2 pos = *origin;
    for (vec2 delta = goal - pos; delta != 0; delta = goal - pos) {
        // positive i = down
        if (delta.imag() > 0) {
            pos += complex<int>({0, 1});
            pos.imag(pos.imag() + 1);
            moves.push_back('v');
        }

        if (delta.imag() < 0) {
            pos.imag(pos.imag() - 1);
            moves.push_back('^');
        }

        if (delta.real() > 0) {
            pos.real(pos.real() + 1);
            moves.push_back('>');
        }

        if (delta.real() < 0) {
            pos.real(pos.real() - 1);
            moves.push_back('<');
        }
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

    vec2 robot1 = num_coords['A'];
    vec2 robot2 = key_coords['A'];
    vec2 robot3 = key_coords['A'];

    string pin;
    while (getline(cin, pin)) {
        // cout << pin << ":";

        for (auto&& c : pin) {
            auto moves = walk(&robot1, num_coords[c]);
        }
    }
}