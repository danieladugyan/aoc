#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> vec2;

vector<vec2> DIRS = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

template <typename T, typename Y>
auto operator<<(ostream &stream, pair<T, Y> const &p) -> ostream & {
    stream << "(" << p.first << ',' << p.second << ")";
    return stream;
}

vec2 operator+(vec2 const &p1, vec2 const &p2) {
    return {p1.first + p2.first, p1.second + p2.second};
}

vec2 operator-(vec2 const &p1, vec2 const &p2) {
    return {p1.first - p2.first, p1.second - p2.second};
}

template <typename T>
auto operator<<(ostream &stream, set<T> const &p) -> ostream & {
    if (p.size() == 0) {
        stream << "{}";
        return stream;
    }

    stream << "{";
    for (auto &&i : p) {
        cout << i << ", ";
    }
    cout << "\b\b" << "}";

    return stream;
}

template <typename T>
auto operator<<(ostream &stream, vector<T> const &p) -> ostream & {
    if (p.size() == 0) {
        stream << "[]";
        return stream;
    }

    stream << "[";
    for (auto &&i : p) {
        cout << i << ", ";
    }
    cout << "\b\b" << "]";

    return stream;
}