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

    int diff = 0;
    auto y = r.begin();

    for (auto& x : l) {
        diff += abs(x - *y);
        ++y;
        // cout << x << " " << *y << endl;
        // cout << "diff: " << diff << endl;
    }
    cout << diff << endl;
}