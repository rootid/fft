#include "../headers/global.hpp"

//Sort Characters By Frequency
//Given a string, sort it in decreasing order based on the frequency of characters.
//Example 1:
//Input:
//"tree"
//Output:
//"eert"
//Explanation:
//'e' appears twice while 'r' and 't' both appear once.
//So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
//Example 2:
//Input:
//"cccaaa"
//Output:
//"cccaaa"
//Explanation:
//Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
//Note that "cacaca" is incorrect, as the same characters must be together.
//Example 3:
//Input:
//"Aabb"
//Output:
//"bbAa"
//Explanation:
//"bbaA" is also a valid answer, but "Aabb" is incorrect.
//Note that 'A' and 'a' are treated as two different characters.

//######################################### Iteration ######################################### 
string frequencySort(string s) {
     unordered_map<char,int> freq_map;
     for(char c:s) {
         freq_map[c]++;
     }
     vector<string> inv_freq_map(s.size() + 1,"");
     for(auto&i:freq_map) {
         char c = i.first;
         int cnt = i.second;
         ///cout << " char " << c << " cnt " << cnt << endl;
         inv_freq_map[cnt].append(cnt,c); //append cnt chars of c 
     }
     //for(auto& i:inv_freq_map) {
     //  cout << i << endl;
     //}
     string res;
     for(int i=s.size();i>=0;i--) {
         if(!inv_freq_map[i].empty()) {
             res += inv_freq_map[i];
         }
     }
     //cout << res << endl;
     return res;
}

//Iteration 2
string frequencySort(string s) {
      string res;
      if (s.size()==0) return res;
      vector<pair<int,int>> map(256,make_pair(0,0));//<freq, char-char(0)>
      for (int i = 0; i<256; i++) {
          map[i].second = i;
      }
      for(int i = 0; i < s.size(); i++)
          map[s[i]].first++;
      sort(map.begin(), map.end(), greater<pair<int,int>>());// sort pairs by freq
      int i = 0;
      while(map[i].first != 0) {
          for (int j = 0; j < map[i].first;j++)
              res.push_back(char(0)+map[i].second);
          i++;
      }
      return res;
}

int main() {
  frequencySort("tree");
}
