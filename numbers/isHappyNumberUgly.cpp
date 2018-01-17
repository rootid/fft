//Happy Number
#include<iostream>
#include<math.h>
using namespace std;


void reduceNumber(int& n) {
  int temp = n;
  int result = 0;
  while(temp > 0 ) {
    int next = temp/10;
    int rem = temp%10;
    result += pow(rem,2);
    temp = next;
  }
  //cout << "R = " << result << endl;
  n = result;
}

bool isHappy(int n) {
 
  if(n < 0) {
    n = n * -1;
  }
  if (n <= 9) {
    if(n == 1) {
      return true;
    }
    return false;
  }
  reduceNumber(n);
  isHappy(n);
}


int main() {

  isHappy(19);
  isHappy(-19);
}
