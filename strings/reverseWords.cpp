//Reverse Words in a String
//For example,
//Given s = "the sky is blue",
//return "blue is sky the". => "eulb si yks eht"
#include<iostream>
#include<string>
using namespace std;

void reverseSentenceHelper(string &s,int startIdx,int endIdx) {
  while(startIdx < endIdx) {
    //cout << s << " >>>> S = " << startIdx << " E = " << endIdx << endl;
    char tmp = s[endIdx];
    s[endIdx] = s[startIdx];
    s[startIdx] = tmp;
    startIdx++;
    endIdx--;
  }
}

void reverseWordHelper(string &s) {
  int len = s.length() - 1;
  int startIdx = 0;
  int endIdx = 0;
  for(int i=0;i<len;i++) {
      if(s[i] == ' ') {
        endIdx = i - 1;
        //cout << s << "|S = " << startIdx << " E = " << endIdx  << endl;
        reverseSentenceHelper(s,startIdx,endIdx);
        startIdx = endIdx + 2;
      }
  }
  //cout << s << " <<<< S = " << startIdx << " E = " << len << endl;
  reverseSentenceHelper(s,startIdx,len);
}

void reverseWords(string &s) {
  int len = s.length() - 1;
  int endIdx = max(len,0);
  int startIdx = 0;
  //Revese sentence
  reverseSentenceHelper(s,startIdx,endIdx);
  cout << s << endl;
  reverseWordHelper(s);
  cout << s << endl;
}

  
int main () {


  string s = "the sky is blue"; 
  reverseWords(s);

}
