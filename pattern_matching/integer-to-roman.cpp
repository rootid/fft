//Integer to Roman
//Given an integer, convert it to a roman numeral.
//Input is guaranteed to be within the range from 1 to 3999.
//
#include<iostream>
#include<string>
#include<vector>
using namespace std;


//######################################### Iteration + Index solution  ######################################### 
public static String intToRoman(int num) {
	//Zero doesnot exist in roman
    String M[] = {"", "M", "MM", "MMM"}; //"", 1000-3000
    String C[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"}; // "" , 100-900 C: 100, CC: 200, CCC: 300, CD: 400
    String X[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"}; //"", 10-90
    String I[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"}; //"",1-9
    return M[num/1000] + C[(num%1000)/100] + X[(num%100)/10] + I[num%10];
}
//######################################### Recursion ######################################### 
string intToRoman(int num) {                
    for (int i = 0; i < int_dict.size(); i++) {
        if (int_dict[i] <= num)
            return roman_dict[i] + intToRoman(num - int_dict[i]);
    }
    return "";
}

//######################################### Iteration  ######################################### 
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
int main() {
  cout <<  " 6 = " << intToRoman(6)  << endl;
  cout <<  " 1 = " << intToRoman(1)  << endl;
  cout <<  " 4 = " << intToRoman(4)  << endl;
}
