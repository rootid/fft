//Implement a method to perform basic string compression using the counts of repeated characters. For example, the string aabcccccaaa would become a2blc5a3. If the "compressed" string would not become smaller than the original string, your method should return
//the original string. You can assume the string has only uppercase and lowercase letters (a - z).
#include<iostream>
#include<sstream>
#include<string>
using namespace std;


string get_compressed_string(string& s) {
  int len = s.size();
  stringstream ss;
  int count = 1;
  string compressed_string = "";
  for(int i=1;i<len;i++) {
    if(s[i] == s[i-1]) {
      count += 1;
    } else {
      ss << count;
      compressed_string += s[i-1];
      compressed_string+=ss.str();
      ss.str("");
      count = 1;
    }
  }
  ss << count;
  compressed_string += s[len - 1];
  compressed_string += ss.str();
  cout << compressed_string << endl;
  if(compressed_string.size() > s.size()) {
      return s;
  }
  return compressed_string;
    
}

int main() {

  string s = "aabcccccaaa";
  string c = get_compressed_string(s);
  cout << "c = " << c << endl;
}
