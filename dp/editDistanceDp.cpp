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
  if(m == 0 || n == 0) {
    return m + n;
  }
  int opt[m+1][n+1];
  
  //initialization languge agnostic
  for(int i=0;i<=m;i++) {
    for(int j=0;j<=n;j++) {
      opt[i][j] = 0;
    }
  }

  for(int j=0;j<=n;j++) {
    opt[0][j] = j;
  }

  //Traverse in ROW-MAJOR order
  for(int i=1;i<=m;i++) {
    opt[i][0] = i;  //for each row traverse colmn
    for (int j=1;j<=n;j++) {
      int min_ = min(opt[i-1][j]+1,opt[i][j-1]+1); 
      if(word1[i] == word2[j]) {
        opt[i][j] = min(min_ ,opt[i-1][j-1]);
      } else {
        opt[i][j] = min(min_ , (opt[i-1][j-1] + 1) );
      }
    }
  }

  return opt[m][n];
}



int main() {

    string s = "algorithm";
    string t = "altruistic";

    int n = minDistance(s,t);
    cout << " min DIST ( " << s << "," << t << " ) = " << n << endl;


}
