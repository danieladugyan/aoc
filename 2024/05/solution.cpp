#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<tuple<int, int>> rules;
    int sum = 0;
    int a, b;
    char c;
    string s;

    while (getline(cin, s) && !s.empty()) {
        stringstream ss(s);
        ss >> a >> c >> b;
        rules.push_back(make_pair(a, b));
    }

    while (getline(cin, s)) {
        vector<int> pages;
        stringstream ss(s);
        while (ss >> a) {
            pages.push_back(a);
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }

        bool fail = false;
        for (auto &&i : rules) {
            a = get<0>(i);
            b = get<1>(i);
            auto a_it = find(pages.begin(), pages.end(), a);
            auto b_it = find(pages.begin(), pages.end(), b);
            if (a_it == pages.end() || b_it == pages.end()) continue;
            if (b_it < a_it) {
                fail = true;
                // cout << "fail: " << a << "|" << b << endl;
                break;
            }
        }

        if (fail) {
            for (unsigned i = 0; i < pages.size(); i++) {
                for (unsigned j = 0; j < pages.size(); j++) {
                    auto it = find_if(rules.begin(), rules.end(),
                                      [i, j, pages](tuple<int, int> &e) {
                                          return get<0>(e) == pages[i] &&
                                                 get<1>(e) == pages[j];
                                      });
                    if (it != rules.end() && j > i) {
                        iter_swap(pages.begin() + i, pages.begin() + j);
                    }
                }
            }

            // cout << "fail: ";
            // for (auto &&i : pages) {
            //     cout << i << ", ";
            // }
            int add = *(pages.begin() + pages.size() / 2);
            // cout << add;
            // cout << endl;

            sum += add;
        }
    }

    cout << sum << endl;
}