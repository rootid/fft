//Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.
//For example, Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
//Given word1 = "coding", word2 = "practice", return 3. Given word1 = "makes", word2 = "coding", return 1.
//Note
//You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.

#include<iostream>
#include<vector>
#include<string>
#include<limits.h>
#include<cmath>
using namespace std;

int shortestDistance(vector<string>& words, string word1, string word2) {
  int l = -1;
  int r = -1; 
  int minDist = INT_MAX;
  for(int i=0;i<words.size();i++) {
      if(words[i] == word1) {
        l = i;
      } 
      else if(words[i] == word2) {
        r = i;
      }
      if(l != -1 && r != -1) {
        if(minDist > abs(l-r) ) {
          minDist = abs(l-r);
        }
      }
  }
  cout << " r = " << minDist << endl;
  return minDist;
}

int main () {
  
  vector<string> words({"practice", "makes", "perfect", "coding", "makes"});
  shortestDistance(words,"makes","coding");
}
