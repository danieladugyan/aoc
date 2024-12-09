#include <bits/stdc++.h>

using namespace std;

bool is_block(int c) { return c != -1; }
void print_disk(vector<int> *disk) {
    for (auto &&i : *disk) {
        if (i == -1) {
            cout << ".";
        } else {
            cout << i;
        }
    }
    cout << endl;
}

int main() {
    vector<int> disk;
    map<int, pair<int, int>> block_map;  // block -> (pos, size)
    map<int, int> space_map;             // pos -> size
    int i = 0;
    int id = -1;
    char c;
    while ((c = getchar()) != '\n') {
        bool is_file = i % 2 == 0;
        int size = c - '0';
        // cout << "c: " << c << "id: " << id << " i: " << i
        //      << " is_file: " << is_file << " size: " << size << endl;
        if (is_file) {
            id++;
            block_map[id] = make_pair(disk.size(), size);
        } else {
            space_map[disk.size()] = size;
        }

        for (int j = 0; j < size; j++) {
            if (is_file) {
                disk.push_back(id);
            } else {
                disk.push_back(-1);
            }
        }

        i++;
    }

    // for (auto &&i : disk) {
    //     if (i == -1) {
    //         cout << ".";
    //     } else {
    //         cout << i;
    //     }
    // }
    // cout << endl;

    for (auto it1 = block_map.rbegin(); it1 != block_map.rend(); ++it1) {
        int block_pos = it1->second.first;
        int block_size = it1->second.second;

        // cout << iter->first << ": (" << iter->second.first << ", "
        //      << iter->second.second << ")" << endl;

        // print_disk(&disk);

        for (auto it2 = space_map.begin(); it2 != space_map.end(); ++it2) {
            int space_pos = it2->first;
            int space_size = it2->second;

            if (space_size >= block_size && space_pos < block_pos) {
                // move block
                for (i = 0; i < block_size; i++) {
                    iter_swap(disk.begin() + block_pos + i,
                              disk.begin() + space_pos + i);
                }

                // update map of free space
                space_map.erase(space_pos);
                if (block_size < space_size) {
                    space_map[space_pos + i] = space_size - block_size;
                }

                break;
            }
            // cout << it2->first << ": " << it2->second << endl;
        }
    }

    i = 0;
    long sum = 0;
    for (auto &&c : disk) {
        if (c != -1) {
            // cout << i << " * " << c << endl;
            sum += i * (c);
        }

        i++;
    }
    cout << sum << endl;
}