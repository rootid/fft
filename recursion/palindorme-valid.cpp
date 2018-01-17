#include "../headers/global.hpp"

bool isPalindorme(string s) {
  if(s.size() <= 1) {
    return true;
  } 
  if(s[0] == s[s.size() - 1] && isPalindorme(s.substr(1,s.size() - 2))) {
    return true;
  } 
  return false;
}

bool palindorme_helper(string& s,int start,int end) {
  if(start >= end) {
    return true;
  }
  if(s[start] == s[end] && palindorme_helper(s,start+1,end-1) ) {
    return true;
  } 
  
  return false;
}

bool isPalindorme_rec(string s) {
  int len = s.size();
  return palindorme_helper(s,0,len-1);
}


int main() {

  bool t =  isPalindorme("a");
  cout << "isPalindorme" << t << endl;
  t = isPalindorme("aa");
  cout << "isPalindorme" << t << endl;
  t = isPalindorme("aab");
  cout << "isPalindorme" << t << endl;
  t = isPalindorme_rec("aabbba");
  cout << "isPalindorme" << t << endl;

  t = isPalindorme_rec("aabbaa");
  cout << "isPalindorme" << t << endl;
}
