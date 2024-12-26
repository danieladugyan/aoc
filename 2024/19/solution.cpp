#include <bits/stdc++.h>

using namespace std;

struct compare {
    inline bool operator()(const std::string &first,
                           const std::string &second) const {
        return first.size() > second.size();
    }
};
compare c;

vector<string> patterns;

template <typename T>
auto operator<<(ostream &stream, set<T> const &p) -> ostream & {
    stream << "{";
    for (auto &&i : p) {
        cout << i << ", ";
    }
    cout << "\b\b" << "}";

    return stream;
}

template <typename T>
auto operator<<(ostream &stream, vector<T> const &p) -> ostream & {
    stream << "[";
    for (auto &&i : p) {
        cout << i << ", ";
    }
    cout << "\b\b" << "]";

    return stream;
}

map<string, bool> cache;

bool match(string original, string s) {
    vector<string> matching;
    // cout << original << ": s = " << s << endl;

    if (cache.count(s)) {
        return cache[s];
    }

    copy_if(patterns.begin(), patterns.end(), back_inserter(matching),
            [&s](string p) { return s.starts_with(p); });

    if (matching.size() == 1 && matching[0] == s) {
        cache[original] = true;
        return true;
    }

    for (auto &&m : matching) {
        if (match(original, s.substr(m.size()))) {
            cache[s] = true;
            return true;
        }
    }

    cache[s] = false;
    return false;
}

int main() {
    string s;
    while (cin.good()) {
        getline(cin, s, ',');
        cout << "s = " << s << endl;
        if (s == "\n") break;
        patterns.push_back(s);
    }
    sort(patterns.begin(), patterns.end(), c);

    vector<string> designs;
    while (getline(cin, s)) {
        designs.push_back(s);
    }

    cout << "patterns: " << patterns << endl;
    cout << "designs: " << designs << endl;

    int answer = 0;
    for (auto &&design : designs) {
        if (match(design, design)) {
            // cout << "design = " << design << endl;
            answer += 1;
        };
        // cout << endl;
    }

    cout << "answer = " << answer << endl;
}