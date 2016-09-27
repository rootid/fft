// Convert a Number to Hexadecimal
//Given an integer, write an algorithm to convert it to hexadecimal. For negative integer, two’s complement method is used.
//Note:
//All letters in hexadecimal (a-f) must be in lowercase.
//The hexadecimal string must not contain extra leading 0s. If the number is zero, it is represented by a single zero character '0'; otherwise, the first character in the hexadecimal string will not be the zero character.
//The given number is guaranteed to fit within the range of a 32-bit signed integer.
//You must not use any method provided by the library which converts/formats the number to hex directly.
//Example 1:
//Input:
//26
//Output:
//"1a"
//Example 2:
//Input:
//-1
//Output:
//"ffffffff"
//
#include<iostream>
using namespace std;
string toHex(int num) {
  string res;
  for (int i = 0; num && i < 8; i++) {
      int bit = num & 0xF;
      if (bit < 10) {
          res = char(bit + '0') + res;
      }
      else {
          res = char(bit - 10 + 'a') + res;
      }
      num >>= 4;
  }
  if(res.empty()) {
    return "0";
  }
  return res;
}
string toHex(int num) {
    string result = "";
    
    //for loop checks only bits 
    for(int i=0;i<8;i++) {
        int bit = num & 15;
        if(bit < 10) {
            result.push_back( bit + '0');
        } else {
            result.push_back (bit - 10 + 'a');
        }
        num = num >> 4;    
    }
     reverse(result.begin(),result.end());
     return result;
}
string toHex(int num) {
      string result = "";
      string res;
      //for loop checks for number of bits and number
      for(int i=0;i<8 && num;i++) {
          int bit = num & 15;
          if(bit < 10) {
              result += char( bit + '0');
          } else {
              result += char(bit - 10 + 'a');
          }
          num = num >> 4;
      }
     reverse(result.begin(),result.end());
     if(result.empty()) {
         return "0";
     }
     return result;
}
int main() {
}
