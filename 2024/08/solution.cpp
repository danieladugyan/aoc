#include <bits/stdc++.h>

using namespace std;

void print_map(map<char, vector<complex<int>>> *m) {
    for (auto &&a : *m) {
        cout << a.first << ": ";
        for (auto &&b : a.second) {
            cout << b << ", ";
        }
        cout << endl;
    }
}

bool bounds(complex<int> z, int w, int h) {
    return 0 <= real(z) && real(z) < w && 0 <= imag(z) && imag(z) < h;
}

int main() {
    // antenna type -> positions
    map<char, vector<complex<int>>> m;
    int i = 0, j = 0;
    int w = 0, h = 0;
    for (char c = getchar(); c != EOF; c = getchar()) {
        if (isdigit(c) || isalpha(c)) {
            vector<complex<int>> empty;
            m.try_emplace(c, empty);
            auto z = complex(i, j);
            m[c].push_back(z);
        }

        if (c == '\n') {
            i = 0;
            j++;
        } else {
            i++;
        }
        w = max(w, i);
        h = max(h, i);
    }

    // print_map(&m);
    // cout << "w: " << w << ", h: " << h << endl;

    // For each point p, determine if it's an antinode!
    // 1. p must be in line with two antennas of the same type
    // 2. one of the antennas must be twice as far away from p as the other

    // For any pair of antennas with the same frequency, there are two
    // antinodes.
    // -> any two points form a line, and the antinodes occur on either side,
    // placed at p1 - d and p2 + d where d is the distance between p1 and p2.

    // For each antenna type
    set<pair<int, int>> locs;
    for (auto &&a : m) {
        // For each antenna pair
        for (auto &&p1 : a.second) {
            for (auto &&p2 : a.second) {
                if (p1 == p2) continue;
                complex<int> diff = p2 - p1;
                int d = gcd(real(diff), imag(diff));
                diff = {real(diff) / d, imag(diff) / d};
                for (complex<int> pos = p1; bounds(pos, w, h); pos += diff) {
                    pair<int, int> z{real(pos), imag(pos)};
                    locs.insert(z);
                }
                for (complex<int> pos = p1; bounds(pos, w, h); pos -= diff) {
                    pair<int, int> z{real(pos), imag(pos)};
                    locs.insert(z);
                }
            }
        }
    }
    cout << locs.size() << endl;
}