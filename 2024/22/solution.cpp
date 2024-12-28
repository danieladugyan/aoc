#include "lib.hpp"

typedef long num;

#define N 2000

// 16777216: 2^24
// 2048: 2^11
// 64: 2^6
// 32: 2^5

void mix(num* secret, num value) { *secret ^= value; }

void prune(num* secret) { *secret &= 0xffffff; }

int main() {
    num secret, tmp;

    // secret = 42;
    // mix(&secret, 15);
    // cout << "mix: got " << secret << ", expected 37" << endl;

    // secret = 100000000;
    // prune(&secret);
    // cout << "prune: got " << secret << ", expected 16113920" << endl;

    // cout << "*64: got " << (5 << 6) << ", expected 320" << endl;
    // cout << "/32: got " << (450 >> 5) << ", expected 14" << endl;
    // cout << "*2048: got " << (450 >> 5) << ", expected 14" << endl;

    num answer = 0;
    while (cin >> secret) {
        // cout << secret << ": ";
        for (int i = 0; i < N; i++) {
            tmp = secret << 6;
            mix(&secret, tmp);
            prune(&secret);

            tmp = secret >> 5;
            mix(&secret, tmp);
            prune(&secret);

            tmp = secret << 11;
            mix(&secret, tmp);
            prune(&secret);
        }
        answer += secret;
        // cout << secret << endl;
    }
    cout << answer << endl;
}