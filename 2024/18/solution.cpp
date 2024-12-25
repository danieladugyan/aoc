#include <bits/stdc++.h>
#define WIDTH 7   // 70
#define HEIGHT 7  // 70
#define BYTES 12  // 1024
using namespace std;

typedef pair<int, int> vec2;

template <typename T, typename Y>
auto operator<<(ostream& stream, pair<T, Y> const& p) -> ostream& {
    stream << "(" << p.first << ',' << p.second << ")";
    return stream;
}

int main() {
    vector<vec2> falling;
    int x, y;
    char mem[WIDTH][HEIGHT] = {};
    int i = 0;
    while (scanf("%d,%d\n", &x, &y) != EOF) {
        falling.push_back({x, y});
        mem[x][y] = '#';
        
        if (i >= BYTES) {
            break;
        }
    }

    for (x = 0; x < WIDTH; x++) {
        for (y = 0; y < WIDTH; y++) {
            if (mem[x][y] == 0) {
                cout << ".";
            } else {
                cout << mem[x][y];
            }
        }
        cout << endl;
    }
}