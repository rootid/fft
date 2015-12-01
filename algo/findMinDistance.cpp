#include<iostream>
#include<vector>
#include<string>
#include<limits.h>
#include<stdlib.h>

using namespace std;

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
          minDist = min( (max(sDist,s1Dist) - min(sDist,s1Dist)), minDist);
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
    string s1 = "over"; 
    int minDist = getMinDistance(sVec,s,s1);
    cout << "Min distance between the 2 strings = " << minDist << endl;
}
