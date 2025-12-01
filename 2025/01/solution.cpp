#include <bits/stdc++.h>

using namespace std;

int main() {
  int ans = 0;
  int x = 50;
  
  char c;
  int a;
  string s;
  while (getline(cin, s)) {
    stringstream ss(s);
    ss >> c >> a;
    
    if (c == 'L') {
      x -= a;
    } else {
      x += a;
    }
    x %= 100;

    if (x == 0) ans++;
  }

  // for (int &i : xs) {
  //   cout << i << endl;
  // }

  // x = 0;
  // for (unsigned i = 0; i < xs.size(); i++) {
    
  // }

  cout << "answer = " << ans << endl;
}