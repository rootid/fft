#include "../headers/global.hpp"

int C(int n,int k) {
  if(k == 0 || k == n) {
    return 1;
  }
  return C(n-1,k) + C(n-1,k-1);
}

int main () {

  cout << C(4,2) << endl;
  cout << C(4,3) << endl;
  cout << C(4,3) << endl;
}
