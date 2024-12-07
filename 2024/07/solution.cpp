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
            // cout << i << ",";
        // }
        // cout << endl;

        long n = nums.size();
        bool flag = false;
        // (n-1) gaps to place operands, i.e ++ +* *+ **
        for (int i = 0; i < n; i++) {
            string ops;
            int adds = i, muls = n - 1 - i;
            for (int j = 0; j < muls; j++) {
                ops.push_back('*');
            }
            for (int j = 0; j < adds; j++) {
                ops.push_back('+');
            }

            do {
                auto copynums = nums;
                for (unsigned j = 0; j < ops.size(); j++) {
                    // cout << "\t" << copynums[j] << ops[j] << copynums[j + 1] << endl;

                    if (ops[j] == '*') {
                        copynums[j + 1] *= copynums[j];
                    }
                    if (ops[j] == '+') {
                        copynums[j + 1] += copynums[j];
                    }
                }
                long res = copynums.back();

                // cout << "\t" << ops << ": ";
                // cout << res << endl;

                if (res == test) {
                    flag = true;
                    answer += res;
                    break;
                }

            } while (next_permutation(ops.begin(), ops.end()));
            if (flag) {
                break;
            }
        }
    }

    cout << answer << endl;
}