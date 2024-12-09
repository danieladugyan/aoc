#include <bits/stdc++.h>

using namespace std;

bool is_block(int c) { return c != -1; }

int main() {
    vector<int> disk;
    int i = 0;
    int id = 0;
    char c;
    while ((c = getchar()) != '\n') {
        bool isFile = i % 2 == 0;
        int size = c - '0';
        // cout << "c: " << c << "id: " << id << " i: " << i
        //      << " isFile: " << isFile << " size: " << size << endl;
        for (int j = 0; j < size; j++) {
            if (isFile) {
                disk.push_back(id);
            } else {
                disk.push_back(-1);
            }
        }
        if (isFile) {
            id++;
        }
        i++;
    }

    // for (auto &&i : disk) {
    //     cout << i << " ";
    // }

    i = 0;
    while (true) {
        if (disk[i] == -1) {
            int block;
            for (block = disk.size() - 1; block >= 0; block--) {
                if (is_block(disk[block])) {
                    break;
                }
            }

            auto space = find(disk.begin(), disk.end(), -1);

            if (distance(disk.begin(), space) > block) {
                // cout << "no more free blocks" << endl;
                break;
            }

            iter_swap(disk.begin() + block, space);
        }
        i++;
    }
    
    for (auto &&i : disk) {
        cout << i;
    }
    cout << endl;
    cout << "---------" << endl;

    i = 0;
    long sum = 0;
    for (auto &&c : disk) {
        if (c == -1) {
            break;
        }
        // cout << i << " * " << c << endl;
        sum += i * (c);
        i++;
    }
    cout << sum << endl;
}