#include <bits/stdc++.h>

using namespace std;

int main() {
    char c;
    int a, b;
    int sum = 0;
    while (cin >> noskipws >> c) {
        if (c == 'm') {
            cin >> noskipws >> c;
            if (c == 'u') {
                cin >> noskipws >> c;
                if (c == 'l') {
                    cin >> noskipws >> c;
                    if (c == '(') {
                        cin >> noskipws >> a;
                        if (!cin.fail()) {
                            cin >> noskipws >> c;
                            if (c == ',') {
                                cin >> noskipws >> b;
                                if (!cin.fail()) {
                                    cin >> noskipws >> c;
                                    if (c == ')') {
                                        sum += a * b;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << sum << endl;
}