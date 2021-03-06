//Number of Segments in a String
//Count the number of segments in a string, where a segment is defined to be a
//contiguous sequence of non-space characters.
//Please note that the string does not contain any non-printable characters.
//Example:
//Input: "Hello, my name is John"
//Output: 5
#include "../headers/global.hpp"

//##################################### With Split #####################################
public int countSegments(String s) {
    if(s == null || s.length() == 0) return 0;
    //" a ".split("\\s+").length() will return 2 so added extra prefex char :
    //" a ".split(" +").length() will return true
    return ("x "+ s).split("\\s+").length - 1;
}
//##################################### With Regex #####################################
int countSegments(string s) {
  cout << s << endl;
  return regex_replace(regex_replace(s, regex("\\S+"), "x"),regex("\\s+"), "").size();
}

//############################### W/O Regex ##############################
int countSegments(string s) {
      int res = 0;
      for (int i = 0; i < s.size(); i++) {
          res += s[i] != ' ' && (i + 1 == s.size() || s[i + 1] == ' '); //check 2 chracters at a time
      }
      return res;
}

int main() {
  countSegments("Hello, my name is John");
}
