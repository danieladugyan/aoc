#include "lib.hpp"

enum Gate { AND, OR, XOR };

map<string, Gate> stringToGate = {
    {"AND", Gate::AND}, {"OR", Gate::OR}, {"XOR", Gate::XOR}};

struct circuit {
    string left;
    Gate gate;
    string right;
    string out;
};

auto operator<<(ostream &stream, circuit const &p) -> ostream & {
    stream << "Circuit(" << p.left << ' ' << p.gate << ' ' << p.right << " -> "
           << p.out << ')';
    return stream;
}

int main() {
    map<string, bool> system;
    queue<circuit> circuits;

    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        string symbol = line.substr(0, line.find(":"));
        bool value = line.back() - '0';
        system[symbol] = value;
    }

    string left, right, out, gate;
    while (cin >> left) {
        cin >> gate;
        cin >> right;
        cin.ignore(4);
        cin >> out;
        circuits.push({left, stringToGate[gate], right, out});
    }

    // cout << system << endl;
    // cout << circuits.front() << endl;

    while (!circuits.empty()) {
        circuit c = circuits.front();
        circuits.pop();

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
            circuits.push(c);
        }
    }

    long long answer = 0;
    for (auto &&i : system) {
        auto [symbol, value] = i;
        if (symbol.starts_with('z')) {
            int idx = stoi(symbol.substr(1));
            answer |= ((long long)value << idx);
            // cout << idx << ": " << value << " | " << ((long long)value << idx)
            //      << endl;
        }
    }
    cout << answer << endl;
}