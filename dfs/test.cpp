#include "../headers/global.hpp"

void boolValid() {
  bool t = false;
  cout << t << endl;
  t |= true;
  cout << t << endl;
}

int main() {
  string st = "hi)heloo";
  cout << st << endl;
  cout << "0,2"<< st.substr(0,2) << " 3, " << st.substr(3) << endl;
}
