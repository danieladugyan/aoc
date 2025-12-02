#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

typedef long long num;

bool is_invalid(num x) {
  string s = to_string(x);

  // Task: Determine if the string consists of repeating sub-strings.
  // Iterate through the string, begin at the first char.

  // If the next char is equal, then we're repeating so all good.
  // If it's not, then make a window out of the first 2 chars,
  // and proceed by checking if the next two chars are equal.
  // If they are, then all good, otherwise, make a buffer out of
  // the first 3 chars, and compare with the next 3, and so on...

  // Example: 999
  // Start at size = 1 and i = 1, i.e first char as repeating.
  // s = 1, i = 1 | 0->1 equal to 1 -> 2?
  // Yes, so add size to i, i.e i = 2
  // s = 1, i = 2 | 0->1 equal to 2 -> 3?
  // Yes, so add size to i, i.e i = 3
  
  // Example: 123
  // s = 1, i = 1 | 0->1 equal to 1 -> 2? 1 equal to 2?
  // No, so add 1 to size and set i to size.
  // s = 2, i = 2 | 0->2 equal to 2 -> 4? 12 equal to 3X?
  // ERR! Ran out of string! So return false.

  int size = 1;
  unsigned i = size;
  for (;;) {
    string s1 = s.substr(0, size);
    
    if (i + size > s.size()) return false;
    string s2 = s.substr(i, size);
    
    // cout << "size = " << size << ", i = " << i << ", s1 = " << s1 << ", s2 = " << s2 << endl;

    if (s1 == s2) {
      // If repeating, check next window
      i += size;
      if (i >= s.size()) break;
    } else {
      // Otherwise, restart with new window
      size++;
      i = size;
      if (i >= s.size()) return false;
    }
  }

  return true;
}

int main() {
  num ans = 0;

  // bool res = is_invalid(12);
  // cout << "12 = " << res << endl;
  // res = is_invalid(999);
  // cout << "999 = " << res << endl;
  // res = is_invalid(123);
  // cout << "123 = " << res << endl;
  // res = is_invalid(1185);
  // cout << "1185 = " << res << endl;

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