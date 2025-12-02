#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

typedef long long num;

bool is_invalid(num x) {
  string s = to_string(x);
  if (s.length() % 2 != 0) return false;
  int m = s.length() / 2;
  string h1 = s.substr(0, m);
  string h2 = s.substr(m, m);
  return h1.compare(h2) == 0;
}

int main() {
  num ans = 0;

  num start, end;
  while (cin >> start) {
    cin.ignore(1);
    cin >> end;
    cin.ignore(1);
    
    // cout << start << " - " << end << endl;
    for (; start <= end; start++) {
      // cout << "\t" << start << " | " <<  is_invalid(start) << endl;
      if (is_invalid(start)) {
        ans += start;
      }
    }
  }

  cout << "answer = " << ans << endl;
}