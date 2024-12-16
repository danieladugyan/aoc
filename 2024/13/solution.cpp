#include <bits/stdc++.h>

using namespace std;
typedef pair<long, long> vec2;

template <typename T, typename Y>
auto operator<<(ostream& stream, pair<T, Y> const& p) -> ostream& {
    stream << "(" << p.first << ',' << p.second << ")";
    return stream;
}

int main() {
    vec2 a, b, prize;
    int i = 0;
    while (scanf("Button A: X+%li, Y+%li\n", &a.first, &a.second) != EOF) {
        scanf("Button B: X+%li, Y+%li\n", &b.first, &b.second);
        scanf("Prize: X=%li, Y=%li\n", &prize.first, &prize.second);

        stringstream ss;
        ss << "data" << i << ".dzn";
        ofstream file(ss.str());

        prize.first += 10000000000000;
        prize.second += 10000000000000;

        file << "ax = " << a.first << ";" << endl;
        file << "ay = " << a.second << ";" << endl;
        file << "bx = " << b.first << ";" << endl;
        file << "by = " << b.second << ";" << endl;
        file << "x = " << prize.first << ";" << endl;
        file << "y = " << prize.second << ";" << endl;
        file.close();
        i++;
    }
}