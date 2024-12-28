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

    vector<vector<int>> prices;
    vector<vector<int>> priceDeltas;
    int idx = 0;
    while (cin >> secret) {
        int prev = 0, curr = 0;
        prices.push_back(vector<int>{});
        priceDeltas.push_back(vector<int>{});

        for (int i = 0; i < N; i++) {
            curr = secret % 10;
            if (i == 0) {
                // cout << secret << ": " << curr << endl;
            } else {
                prices[idx].push_back(curr);
                priceDeltas[idx].push_back(curr - prev);
                // cout << secret << ": " << curr << " (" << curr - prev << ")"
                //  << endl;
            }

            tmp = secret << 6;
            mix(&secret, tmp);
            prune(&secret);

            tmp = secret >> 5;
            mix(&secret, tmp);
            prune(&secret);

            tmp = secret << 11;
            mix(&secret, tmp);
            prune(&secret);

            prev = curr;
        }
        idx++;
        // cout << endl << endl;
    }

    // cout << prices << endl;
    // cout << priceDeltas << endl;

    int best_price = 0;
    for (int a = -9; a <= 9; a++) {
        cout << a << endl;
        for (int b = -9; b <= 9; b++) {
            cout << "\t" << b << endl;
            for (int c = -9; c <= 9; c++) {
                for (int d = -9; d <= 9; d++) {
                    vector<int> changes{a, b, c, d};

                    int total = 0;
                    for (unsigned i = 0; i < priceDeltas.size(); i++) {
                        auto xs = priceDeltas[i];
                        auto it = search(xs.begin(), xs.end(), changes.begin(),
                                         changes.end());
                        if (it != xs.end()) {
                            int idx = distance(xs.begin(), it);
                            total += prices[i][idx + 3];
                        }
                    }
                    if (total > best_price) {
                        // cout << total << ": " << changes << endl;
                        best_price = total;
                    }
                }
            }
        }
    }
    // cout << secret << endl;
    cout << best_price << endl;
}