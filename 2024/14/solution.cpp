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

int main() {
    vector<Robot> robots;
    int px, py, vx, vy;
    while (scanf("p=%d,%d v=%d,%d\n", &px, &py, &vx, &vy) != EOF) {
        Robot r;
        r.p = {px, py};
        r.v = {vx, vy};
        robots.push_back(r);
    }

    for (int i = 0; i < TIME; i++) {
        for (auto &&r : robots) {
            r.move();
        }
    }

    sort(robots.begin(), robots.end());
    for (auto &&r : robots) {
        cout << r << endl;
    }

    int quads[4] = {};
    for (auto &&r : robots) {
        px = r.p.real();
        py = r.p.imag();

        if (px < WIDTH / 2 && py < HEIGHT / 2) {
            ++quads[0];
        } else if (px > WIDTH / 2 && py < HEIGHT / 2) {
            ++quads[1];
        } else if (px < WIDTH / 2 && py > HEIGHT / 2) {
            ++quads[2];
        } else if (px > WIDTH / 2 && py > HEIGHT / 2) {
            ++quads[3];
        }
    }

    int answer = 1;
    for (int i = 0; i < 4; i++) {
        answer *= quads[i];
    }
    cout << answer << endl;
}
