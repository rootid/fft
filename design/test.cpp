#include "../headers/global.hpp"

int main() {
  unordered_map<int, vector<int> > m;
  m[0] = vector<int>{9,8,7,12};
  cout << m[0][2] << endl;
  cout << m[0]<< endl;

}
