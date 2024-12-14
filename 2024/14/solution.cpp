#include <bits/stdc++.h>

using namespace std;
// #define WIDTH 11
// #define HEIGHT 7
#define WIDTH 101
#define HEIGHT 103
#define TIME 100

typedef complex<int> vec2;

inline int mod(int a, int n) { return (a % n + n) % n; }

class Robot {
   public:
    vec2 p;
    vec2 v;

    void move() {
        p += v;
        p.real(mod(p.real(), WIDTH));
        p.imag(mod(p.imag(), HEIGHT));
    }

    friend bool operator<(const Robot &c1, const Robot &c2);
};

bool operator<(const Robot &c1, const Robot &c2) {
    return c1.p.real() < c2.p.real() && c1.p.imag() < c2.p.imag();
}

ostream &operator<<(ostream &os, const Robot &r) {
    return os << "Robot(p=" << r.p << ", v=" << r.v << ")";
}

bool is_likely_tree(int area[WIDTH][HEIGHT]) {
    // check if there are lots of robots in a line
    int max_row = 0;
    for (int y = 0; y < HEIGHT; y++) {
        int row = 0;
        for (int x = 0; x < WIDTH; x++) {
            if (area[x][y]) {
                row++;
            }
        }
        max_row = max(max_row, row);
    }
    return max_row > 20;
}

int main() {
    vector<Robot> robots;
    int px, py, vx, vy;
    while (scanf("p=%d,%d v=%d,%d\n", &px, &py, &vx, &vy) != EOF) {
        Robot r;
        r.p = {px, py};
        r.v = {vx, vy};
        robots.push_back(r);
    }

    int time = 0;
    while (true) {
        int area[WIDTH][HEIGHT] = {};

        for (auto &&r : robots) {
            r.move();
            px = r.p.real();
            py = r.p.imag();
            area[px][py] += 1;
        }
        time++;

        if (is_likely_tree(area)) {
            cout << "t = " << time << endl;
            for (int x = 0; x < WIDTH; x++) {
                for (int y = 0; y < HEIGHT; y++) {
                    cout << area[x][y];
                }
                cout << endl;
            }
            cout << "------------------" << endl;
        }
    }
}
