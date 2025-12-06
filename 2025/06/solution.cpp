#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define MULTIPLY '*'
#define ADD '+'

template <typename T>
auto operator<<(ostream &stream, vector<T> const &p) -> ostream & {
    stream << "[";
    for (auto &&i : p) {
        cout << i << ", ";
    }
    cout << "\b\b" << "]";

    return stream;
}

int main() {
  long long ans = 0;
  string s;
  vector<vector<int>> nums;

  while (getline(cin, s)) {
    stringstream ss(s);
    vector<int> xs;
    
    int a;
    while (ss >> a) {
      xs.push_back(a);
    }
    
    if (!xs.empty()) nums.push_back(xs);
  }

  // for (auto &xs : nums) {
  //   cout << xs << endl;
  // }
  
  char c;
  stringstream ss(s);
  unsigned i = 0;
  while (ss >> c) {
    long long res = 0;
    
    switch (c) {
      case MULTIPLY:
        res = 1;
        for (unsigned j = 0; j < nums.size(); j++) {
          res *= nums[j][i];
        }
        break;
      case ADD:
        for (unsigned j = 0; j < nums.size(); j++) {
          res += nums[j][i];
        }
        break;
      default:
        break;
    }

    i++;
    ans += res;
  }

  cout << ans << endl;
}