//Shortest Palindrome
//Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.
//For example:
//Given "aacecaaa", return "aaacecaaa".
//Given "abcd", return "dcbabcd".

#include "../headers/global.hpp"
using namespace std;

//KMP : compute prefix function
string shortestPalindrome(string s) {
      string rev_s = s;
      reverse(rev_s.begin(), rev_s.end());
      string l = s + "#" + rev_s;
     
     //abaca : p1 = a,p2 = ab ,p3 = aba 
      vector<int> p(l.size(), 0);
      for (int i = 1; i < l.size(); i++) {
          int j = p[i - 1]; //Take the previous prefix val
          while (j > 0 && l[i] != l[j]) {
              j = p[j - 1];
          }
          //cout << "j = " << j << endl;
          if(l[i] == l[j]) {
            j++;
          }
          p[i] = j;
      }
      return rev_s.substr(0, s.size() - p[l.size() - 1]) + s;
}

//######################### Time limit exceeded ######################### 
bool is_part_of(string s,string rs) {
    int idx = 0;
    while(idx < rs.size()) {
      //cout << "s = " << s  << "#" << " rs = " << s << endl;
      if(s[idx] == rs[idx]) {
        idx++;
        continue;
      } 
      return false;
    }
    return true;
}

string shortestPalindrome(string s) {
    string rs = s;
    string sst = "";
    reverse(rs.begin(),rs.end()); //abcd => dcba
    int idx = 0;
    for(int i=0;i<rs.size();i++) {
      //cout << "rs.substr( " << idx << ") = " << rs.substr(idx) << endl;
      if(is_part_of(s,rs.substr(idx))) {
        break;
      } else {
        idx++;
      }
    }
    //cout << "s = " << s  << " | rs = " << rs << endl;
    cout << rs.substr(0,idx)  << "#" << s << endl;
    return rs.substr(0,idx) + s;
}

int main() {
  shortestPalindrome("abcd");
  shortestPalindrome("aacecaaa"); //aaacecaaa
  //aacecaaa+#+aacecaaa
}
