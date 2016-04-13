//Edit Distance
//Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)
//You have the following 3 operations permitted on a word:
//a) Insert a character
//b) Delete a character
//c) Replace a character

#include<iostream>
#include<string>
#define MAX 3
using namespace std;

//Recursive implementation
int minDistance(string word1, string word2) {

  //base case
  int m = word1.length();
  int n = word2.length();
  int opt[MAX];
  if(m == 0 || n == 0) {
    return m + n;
  }
  opt[0] = minDistance(word1.substr(0,m-1),word2) + 1;
  opt[1] = minDistance(word1,word2.substr(0,n-1)) + 1;
  if(word1[m-1] == word2[n-1]) {
    opt[2] = minDistance(word1.substr(0,m-1),word2.substr(0,n-1));
  } else {
    opt[2] = minDistance(word1.substr(0,m-1),word2.substr(0,n-1)) + 1;
  }

  int min = opt[0];
  for(int i=1;i<MAX;i++) {
    if(min > opt[i]) {
      min = opt[i];
    }
  }
  return min;
}



int main() {

    string s = "algorithm";
    string t = "altruistic";

    int n = minDistance(s,t);
    cout << " min DIST ( " << s << "," << t << " ) = " << n << endl;

    n = edit_distance_rec(s,t);
    cout << " min DIST ( " << s << "," << t << " ) = " << n << endl;

}
