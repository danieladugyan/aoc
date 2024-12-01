#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> l, r;

    int a, b;
    while (cin >> a) {
        cin >> b;
        l.push_back(a);
        r.push_back(b);
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    int score = 0;
    for (auto& x : l) {
        int freq = count(r.begin(), r.end(), x);
        score += x * freq;
        // cout << x << " " << freq << endl;
    }
    cout << score << endl;
}