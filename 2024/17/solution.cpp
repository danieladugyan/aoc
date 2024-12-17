#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> instr;

int ra, rb, rc;  // registers A,B,C

#define ADV 0
#define BXL 1
#define BST 2
#define JNZ 3
#define BXC 4
#define OUT 5
#define BDV 6
#define CDV 7

int get_combo(int op) {
    if (op <= 3) return op;
    if (op == 4) return ra;
    if (op == 5) return rb;
    if (op == 6) return rc;

    cout << "error!" << endl;
    return -1;
}

template <typename T, typename Y>
auto operator<<(ostream& stream, pair<T, Y> const& p) -> ostream& {
    stream << "(" << p.first << ',' << p.second << ")";
    return stream;
}

int main() {
    vector<int> output;
    int opcode, operand;
    int pc = 0;  // instruction pointer

    scanf("Register A: %d\n", &ra);
    scanf("Register B: %d\n", &rb);
    scanf("Register C: %d\n", &rc);
    cin.ignore(100, ':');  // skip Program:

    vector<instr> program;
    while (cin >> opcode) {
        cin.ignore(1, ',');
        cin >> operand;
        cin.ignore(1, ',');
        program.push_back({opcode, operand});
    }

    cout << "ra = " << ra << endl;
    cout << "rb = " << rb << endl;
    cout << "rc = " << rc << endl;
    for (auto&& i : program) {
        cout << i << endl;
    }

loop:
    while (pc < program.size()) {
        auto [opcode, operand] = program[pc];
        // cout << "opcode = " << opcode << " operand = " << operand << endl;

        switch (opcode) {
            case ADV:
                ra = ra / pow(2, get_combo(operand));
                break;
            case BXL:
                rb = rb ^ operand;
                break;
            case BST:
                rb = get_combo(operand) % 8;
                break;
            case JNZ:
                if (ra != 0) {
                    // I store instructions in a list of pairs -> div by 2
                    pc = operand / 2;
                    goto loop;
                }
                break;
            case BXC:
                rb = rb ^ rc;
                break;
            case OUT:
                output.push_back(get_combo(operand) % 8);
                break;
            case BDV:
                rb = ra / pow(2, get_combo(operand));
                break;
            case CDV:
                rc = ra / pow(2, get_combo(operand));
                break;
            default:
                cout << "invalid opcode" << endl;
                break;
        }
        
        pc++;
    }

    for (auto&& i : output) {
        cout << i << ",";
    }
    cout << '\b' << endl;
}