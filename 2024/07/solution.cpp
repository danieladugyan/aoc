#include <bits/stdc++.h>

using namespace std;

int main() {
    long answer = 0;
    string s;
    while (getline(cin, s)) {
        stringstream ss(s);
        // parse line
        long test, num;
        vector<long> nums;

        ss >> test;
        ss.ignore(1);  // skip colon

        while (ss >> num) {
            nums.push_back(num);
        }

        // cout << test << ": ";
        // for (auto &&i : nums) {
        //     cout << i << ",";
        // }
        // cout << endl;

        long n = nums.size();
        bool flag = false;
        // (n-1) gaps to place operands, i.e ++ +* *+ **
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    string ops;
                    if (i + j + k != n - 1) {
                        continue;
                    }
                    int muls = i, adds = j, cons = k;
                    for (int x = 0; x < muls; x++) {
                        ops.push_back('*');
                    }
                    for (int x = 0; x < adds; x++) {
                        ops.push_back('+');
                    }
                    for (int x = 0; x < cons; x++) {
                        ops.push_back('|');
                    }

                    do {
                        auto copynums = nums;
                        for (unsigned j = 0; j < ops.size(); j++) {
                            // cout << "\t" << copynums[j] << ops[j]
                            //      << copynums[j + 1] << endl;

                            if (ops[j] == '*') {
                                copynums[j + 1] *= copynums[j];
                            }
                            if (ops[j] == '+') {
                                copynums[j + 1] += copynums[j];
                            }
                            if (ops[j] == '|') {
                                copynums[j + 1] =
                                    stol(to_string(copynums[j]) +
                                         to_string(copynums[j + 1]));
                            }
                        }
                        long res = copynums.back();

                        // cout << "\t" << ops << ": ";
                        // cout << res << '\n' << endl;

                        if (res == test) {
                            answer += res;
                            goto end;
                        }

                    } while (next_permutation(ops.begin(), ops.end()));
                }
            }
        }
    end:
        flag = false;
    }

    cout << answer << endl;
}