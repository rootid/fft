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
          int j = p[i - 1]; //p1 = 
          while (j > 0 && l[i] != l[j]) {
              j = p[j - 1];
          }
          cout << "j = " << j << endl;
          if(l[i] == l[j]) {
            j++;
          }
          p[i] = j;
      }
      return rev_s.substr(0, s.size() - p[l.size() - 1]) + s;
}

int main() {
  shortestPalindrome("abcd");
  shortestPalindrome("aacecaaa"); //aaacecaaa
  //aacecaaa+#+aacecaaa
}
