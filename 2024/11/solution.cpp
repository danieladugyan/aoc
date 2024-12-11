#include <bits/stdc++.h>

using namespace std;
#define N 75

map<pair<long, long>, long> cache;

long get_stones(long stone, long n) {
    if (n == 0) return 1;

    pair<long, long> p = make_pair(stone, n);
    if (cache.count(p)) {
        // cout << "cache hit: " << p.first << ", " << p.second << ": " << cache[p] << endl;
        return cache[p];
    }

    long digits = 0;
    string s = to_string(stone);
    digits = s.length();

    long res = 0;
    if (stone == 0) {
        res = get_stones(1, n - 1);
    } else if (digits % 2 == 0) {
        string s1 = s.substr(0, digits / 2);
        string s2 = s.substr(digits / 2, digits);
        res += get_stones(stol(s1), n - 1);
        res += get_stones(stol(s2), n - 1);
    } else {
        res = get_stones(stone * 2024, n - 1);
    }
    cache[p] = res;

    return res;
}

int main() {
    vector<long> stones;
    long stone;
    while (cin >> stone) {
        stones.push_back(stone);
    }

    long length = 0;
    for (auto &&stone : stones) {
        long res = get_stones(stone, N);
        // cout << stone << ": " << res << endl;
        length += res;
    }

    cout << length << endl;
}