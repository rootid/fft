#include<iostream>
#include<vector>
#include<string>
#include<limits.h>
#include<stdlib.h>

using namespace std;


//This class will be given a list of words (such as might be tokenized
//from a paragraph of text), and will provide a method that takes two
//words and returns the shortest distance (in words) between those two
//words in the provided text. 
//Example:
//  WordDistanceFinder finder = new WordDistanceFinder(Arrays.asList("the", "quick", "brown", "fox", "quick"));
//  assert(finder.distance("fox","the") == 3);
//  assert(finder.distance("quick", "fox") == 1);


//d(a,d)
//"a b d"
//
//time complexity : O(n)
//space complexity : O(k)

int getMinDistance(vector<string> tokens,string s,string s1) {

    int sDist = INT_MIN;
    int s1Dist = INT_MIN;
    int minDist = INT_MAX;
    for(int i=0;i<tokens.size();i++) {
      if (tokens[i] == s) {
        sDist = i;
      } else if (tokens[i] == s1) {
        s1Dist = i;
      }
      if (sDist != INT_MIN && s1Dist != INT_MIN ) {
          //minDist = min( (max(sDist,s1Dist) - min(sDist,s1Dist)), minDist);
          minDist = min( abs(sDist - s1Dist), minDist);
      }
    }
 
    return minDist;
}

int main() { 
  
    string strArr[] = {"quick","the","over","quick","brown","the","fox","over"};
    vector<string> sVec(strArr,strArr+sizeof(strArr)/sizeof(strArr[0]) );
  
    //string s = "the";
    //string s1 = "brown"; 

    string s = "quick";
    string s1 = "fox"; 
    int minDist = getMinDistance(sVec,s,s1);
    cout << "Min distance between the 2 strings = " << minDist << endl;
}
