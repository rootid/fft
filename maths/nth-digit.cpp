//Nth Digit
//Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...
//Note:
//n is positive and will fit within the range of a 32-bit signed integer (n < 231).
//Example 1:
//Input:
//3
//Output:
//3
//Example 2:
//Input:
//11
//Output:
//0
//Explanation:
//The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.
#include<iostream>
#include<sstream>
#include<algorithm>
using namespace std;
//
//
 int findNthDigit(int n) {
    //int base = 9;
    int digits = 1;
    int actual_number = 0;
    int mult = 1;
    n -= 1;
    // while(digit * base < n) {
    while(n/9/mult/digits >= 1 ) {  // TO avoid overflow use divide operation
        n -= 9 * mult * digits;
        digits++;
        mult *= 10;
    }
    actual_number = mult + n/digits;
    int idx = n % digits;
    stringstream ss;
    ss << actual_number;
    string tmp = ss.str();
    return  (int)  (tmp[idx] - '0');
}
//UGLY 
int findNthDigit(int n) {
    
    long base = 9;
    int digit = 1;
    //9 * 1
    //90 * 2 
    //900 * 3
    int actual_number = 0;
    int mult = 1;
    while(digit * base < n) {
        n = n - digit*base;  // 250 -9 = 241 , 241 - 180 = 61 // 11=> 2
        digit++;
        base *= 10;
        mult *= 10;
    }
    actual_number +=  n/digit;
    if(mult > 1) {
      actual_number += mult;
    }
    cout << " n " << n  << " D = " << digit << endl;
    cout << " # " << actual_number << endl;
    int idx = n % digit;  //61 % 3 = 1
    //cout << " idx = " << idx << endl;
    stringstream ss;
    ss << actual_number;
    string tmp = ss.str();
    reverse(tmp.begin(),tmp.end());
    //cout << " tmp = " << tmp[idx] << endl;
    return  (int)  (tmp[idx] - '0');
}
int main() {
  int n_ = findNthDigit(9);
  n_ = findNthDigit(11);
  cout << "Nth digit " << n_ << endl;
  //int n_ = findNthDigit(20);
  n_ = findNthDigit(250);
  cout << "Nth digit " << n_ << endl;
}
