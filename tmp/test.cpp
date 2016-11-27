#include "../headers/global.hpp"



bool is_check(int i,int j) {
  if(i == j) {
    return true;
  }
   return false;
}


int check_status() {
  is_check(11,1);
  return 10;
}


int main () {

 cout <<  check_status() << endl;
}
