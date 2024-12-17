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
    int output = 0;
    int opcode, operand;
    int pc = 0;  // instruction pointer

    scanf("Register A: %d\n", &ra);
    scanf("Register B: %d\n", &rb);
    scanf("Register C: %d\n", &rc);
    cin.ignore(100, ':');  // skip Program:
    ra = 0;
    int rb_orig = rb, rc_orig = rc;
    int ra_idx = 0b10110010001110011011;

    vector<instr> program;
    vector<int> raw;
    while (cin >> opcode) {
        cin.ignore(1, ',');
        cin >> operand;
        cin.ignore(1, ',');
        raw.push_back(opcode);
        raw.push_back(operand);
        program.push_back({opcode, operand});
    }

    cout << "ra = " << ra << endl;
    cout << "rb = " << rb << endl;
    cout << "rc = " << rc << endl;
    for (auto&& i : program) {
        cout << i << endl;
    }

nxt:
    while (output < raw.size()) {
        // cout << ra_idx << endl;
        ra = ra_idx;
        rb = rb_orig;
        rc = rc_orig;
        pc = 0;
        output = 0;
    loop:
        while (pc < program.size()) {
            auto [opcode, operand] = program[pc];

            // cout << "opcode = " << opcode << " operand = " << operand <<
            // endl;

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
                    // if out doesn't match program, give up
                    if (raw[output] != get_combo(operand) % 8) {
                        ra_idx += 0b100000000000000000000;
                        goto nxt;
                    } else {
                        cout << "ra_idx = " << ra_idx << "("
                             << bitset<32>{ra_idx} << ")"
                             << " output = " << output << endl;
                        output++;
                    }
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
        ra_idx += 0b100000000000000000000;
    }

    cout << ra_idx - 1 << endl;
}