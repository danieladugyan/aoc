#include "lib.hpp"

enum Gate { AND, OR, XOR };

map<string, Gate> stringToGate = {
    {"AND", Gate::AND}, {"OR", Gate::OR}, {"XOR", Gate::XOR}};
map<Gate, string> gateToString = {
    {Gate::AND, "AND"}, {Gate::OR, "OR"}, {Gate::XOR, "XOR"}};

struct circuit {
    string left;
    Gate gate;
    string right;
    string out;
};

typedef long long num;

auto operator<<(ostream &stream, circuit const &p) -> ostream & {
    stream << "Circuit(" << p.left << ' ' << p.gate << ' ' << p.right << " -> "
           << p.out << ')';
    return stream;
}

map<string, bool> simulate(map<string, bool> system, vector<circuit> circuits) {
    while (!circuits.empty()) {
        circuit c = circuits.front();
        circuits.erase(circuits.begin());

        if (system.count(c.left) && system.count(c.right)) {
            switch (c.gate) {
                case Gate::AND:
                    system[c.out] = system[c.left] & system[c.right];
                    break;
                case Gate::OR:
                    system[c.out] = system[c.left] | system[c.right];
                    break;
                case Gate::XOR:
                    system[c.out] = system[c.left] ^ system[c.right];
                    break;
            }
        } else {
            circuits.push_back(c);
        }
    }
    return system;
}

int main() {
    map<string, bool> system;
    vector<circuit> circuits;

    int xi = 0, yi = 0, zi = 0;
    num x = 0, y = 0, z = 0;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        string symbol = line.substr(0, line.find(":"));
        bool value = line.back() - '0';
        system[symbol] = value;

        if (symbol[0] == 'x') {
            x |= ((num)value << xi);
            xi++;
        } else {
            y |= ((num)value << yi);
            yi++;
        }
    }

    string left, right, out, gate;
    while (cin >> left) {
        cin >> gate;
        cin >> right;
        cin.ignore(4);
        cin >> out;
        circuits.push_back({left, stringToGate[gate], right, out});
    }

    // z = x + y;
    // cout << "x = " << x << endl;
    // cout << "y = " << y << endl;
    // cout << "z = " << z << endl;

    // cout << system << endl;
    // cout << circuits.front() << endl;

    map<string, set<string>> graph;
    for (auto &&i : circuits) {
        graph[i.left].insert(i.out);
        graph[i.right].insert(i.out);
    }

    for (auto &&i : system) {
        auto [symbol, _] = i;
        if (symbol[0] != 'x') continue;

        cout << symbol << ": " << graph[symbol] << endl;
        for (auto &&j : graph[symbol]) {
            if (graph.count(j)) {
                cout << "\t" << graph[j] << endl;
                for (auto &&k : graph[j]) {
                    if (graph.count(k)) {
                        cout << "\t\t" << graph[k] << endl;
                    }
                }
            }
        }

        string ySymbol{symbol};
        ySymbol[0] = 'y';
        cout << ySymbol << ": " << graph[ySymbol] << endl;
        for (auto &&j : graph[ySymbol]) {
            if (graph.count(j)) {
                cout << "\t" << graph[j] << endl;
                for (auto &&k : graph[j]) {
                    if (graph.count(k)) {
                        cout << "\t\t" << graph[k] << endl;
                    }
                }
            }
        }
    }

    // num answer = 0;
    // for (auto &&i : simulate(system, circuits)) {
    //     auto [symbol, value] = i;
    //     if (symbol[0] == 'z') {
    //         answer |= ((num)value << zi);
    //         zi++;
    //         // cout << idx << ": " << value << " | " << ((num)value << idx)
    //         //      << endl;
    //     }
    // }

    // vector<int> incorrect;
    // bool z_bit, a_bit;
    // for (int i = 0; i < 50; i++) {
    //     z_bit = z & (1 << i);
    //     a_bit = answer & (1 << i);
    //     if (z_bit != a_bit) {
    //         incorrect.push_back(i);
    //     }
    // }

    // cout << incorrect << endl;
    // cout << answer << endl;
}