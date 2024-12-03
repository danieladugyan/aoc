#include <bits/stdc++.h>

using namespace std;

int main() {
    char c;
    int a, b;
    int sum = 0;
    bool enabled = true;
    
    // Sometimes in life, one must ask of themselves
    // not whether they can, but whether they should...

    while (cin >> noskipws >> c) {
        if (c == 'd') {
            cin >> noskipws >> c;
            if (c == 'o') {
                cin >> noskipws >> c;
                if (c == '(') {
                    cin >> noskipws >> c;
                    if (c == ')') {
                        cin >> noskipws >> c;
                        enabled = true;
                    }
                } else if (c == 'n') {
                    cin >> noskipws >> c;
                    if (c == '\'') {
                        cin >> noskipws >> c;
                        if (c == 't') {
                            cin >> noskipws >> c;
                            if (c == '(') {
                                cin >> noskipws >> c;
                                if (c == ')') {
                                    enabled = false;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (!enabled) {
            continue;
        }

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