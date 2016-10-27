//Integer to Roman
//Given an integer, convert it to a roman numeral.
//Input is guaranteed to be within the range from 1 to 3999.
//
#include<iostream>
#include<string>
#include<vector>
using namespace std;

string intToRoman(int num) {
  string roman;
  vector<int> dec_num ({1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1});
  vector<string> roman_num({"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"});
  int startIdx = 0;
  while(num != 0) {
    if(num / dec_num[startIdx] != 0) {
      roman += roman_num[startIdx];
      num = num - dec_num[startIdx];
    }  else {
      startIdx += 1;
    }
  }
  return roman;
}

string intToRoman(int num) {
  string roman;
  vector<int> dec_num ({1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1});
  vector<string> roman_num({"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"});
  int startIdx = 0;
  while(num != 0) {
    for(int i=startIdx;i<dec_num.size();i++)
    if(num / dec_num[i] != 0) {
      int cr  = num/dec_num[i];
      for(int j=0;j<cr;j++) {
        roman += roman_num[i];
      }
      num = num % dec_num[i];
    }  else {
      startIdx += 1;
    }
   }
  return roman;
}
string intToRoman(int num) {
  string roman;
  vector<int> dec_num ({1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1});
  vector<string> roman_num({"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"});
   
   while(num != 0) {
    for(int i=0;i<dec_num.size();i++)
    if(num / dec_num[i] != 0) {
      int cr  = num/dec_num[i];
      for(int j=0;j<cr;j++) {
        roman += roman_num[i];
      }
      num = num % dec_num[i];
    } 
   }
  return roman;
}
//Recursion
//
 string intToRoman(int num) {                
    for (int i = 0; i < int_dict.size(); i++) {
        if (int_dict[i] <= num)
            return roman_dict[i] + intToRoman(num - int_dict[i]);
    }
    return "";
}
int main() {
  cout <<  " 6 = " << intToRoman(6)  << endl;
  cout <<  " 1 = " << intToRoman(1)  << endl;
  cout <<  " 4 = " << intToRoman(4)  << endl;
}
