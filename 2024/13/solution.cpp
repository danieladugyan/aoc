#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> vec2;

template <typename T, typename Y>
auto operator<<(ostream& stream, pair<T, Y> const& p) -> ostream& {
    stream << "(" << p.first << ',' << p.second << ")";
    return stream;
}

int main() {
    vec2 a, b, prize;
    int total_tokens = 0;
    while (scanf("Button A: X+%d, Y+%d\n", &a.first, &a.second) != EOF) {
        scanf("Button B: X+%d, Y+%d\n", &b.first, &b.second);
        scanf("Prize: X=%d, Y=%d\n", &prize.first, &prize.second);

        // cout << a << endl;
        // cout << b << endl;
        // cout << prize << endl;

        vec2 pos;
        bool flag = false;
        int tokens = 0;
        for (int db = 0; db < 100; db++) {
            for (int da = 0; da < 100; da++) {
                pos = {a.first * da + b.first * db,
                       a.second * da + b.second * db};
                if (pos == prize) {
                    tokens = da * 3 + db;
                    // cout << "X: " << da << " Y: " << db << endl;
                    // cout << "tokens: " << tokens << endl;
                    flag = true;
                    break;
                }
            }

            if (flag) break;
        }
        total_tokens += tokens;

        // cout << endl;
    }
    cout << total_tokens << endl;
}