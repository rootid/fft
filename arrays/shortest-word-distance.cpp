//Shortest Word Distance
//Given a list of words and two words word1 and word2, return the shortest
//distance between these two words in the list.
//For example,
//Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
//Given word1 = “coding”, word2 = “practice”, return 3.
//Given word1 = "makes", word2 = "coding", return 1.
//Note:
//You may assume that word1 does not equal to word2, and word1 and word2 are
//both in the list.
//
//TC : O(n) , SC: O(1)
int shortestDistance(vector<string>& words, string word1, string word2) {
     int len = words.size();
     int idx1 = len;
     int idx2 = len;
     int min_dist = len;
     int idx = 0;
     for(auto& word:words) {
         idx += 1;
         if(word == word1) {
             idx1 = idx;
              min_dist = min(min_dist, abs(idx1-idx2));
         } else if(word == word2) {
             idx2 = idx;
              min_dist = min(min_dist, abs(idx1-idx2));
         }
     }
     return min_dist;
}

//TC : O(n^2) , SC: O(1)
int shortestDistance(vector<string>& words, string word1, string word2) {
      unordered_map<string,vector<int> > w_map;
      int idx = 0;
      for(auto word:words) {
          idx += 1;
          w_map[word].push_back(idx);
      }
      int min_dist = words.size();
      vector<int> len1 = w_map[word1];
      vector<int> len2 = w_map[word2];
      for(auto& i:len1) {
          for(auto& j : len2) {
              if( abs(i-j) < min_dist) {
                  min_dist = abs(i-j);
              }
          }
      }
      return min_dist;
 }
