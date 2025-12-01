#include <bits/stdc++.h>
#include <cassert>
#include <cstdlib>

using namespace std;

int mod(int x, int div) {
  int res = x % div;
  if (res < 0) {
    res += div;
  }
  return res;
}

int main() {
  int ans = 0;

  int x = 50;
  int diff = 0;

  char c;
  int a;
  string s;

  while (getline(cin, s)) {
    stringstream ss(s);
    ss >> c >> a;

    if (c == 'L') {
      diff = -a;
    } else {
      diff = a;
    }

    cout << x << " rotated by " << diff << " | " << ans << endl;
    
    if (0 < (x + diff) && (x + diff) < 100) {
      x += diff;
    } else {
      int non_zero = x != 0;
      int remaining_diff;
      if (x == 0 || diff < 0) {
        remaining_diff = diff + x;
      } else {
        remaining_diff = diff - (100 - x);
      }
      int remaining_turns = abs(remaining_diff) / 100;
      int last_rotate = mod(remaining_diff, 100);
      
      // Unless we started at zero, we'll at least go past once.
      if (non_zero) ans += 1;

      // And then me may do some more full turns.
      ans += remaining_turns;

      // Then the dial reaches its final point.
      assert(last_rotate == mod(x + diff, 100));
      x = last_rotate;

      cout
        << "\t diff = " << diff << endl
        << "\t started at non-zero? " << non_zero << endl
        << "\t remaining diff = " << remaining_diff << endl
        << "\t full turns left = " << remaining_turns << endl
        << "\t last rotate = " << last_rotate << endl;
    }
  }

  cout << "answer = " << ans << endl;
}