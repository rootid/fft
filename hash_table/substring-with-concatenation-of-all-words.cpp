//Substring with Concatenation of All Words
//IMP
//You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.
//For example, given:
//s: "barfoothefoobarman"
//words: ["foo", "bar"]
//You should return the indices: [0,9].
//(order does not matter).

//############################################ Traversal left-right #########################################################
//TC : O(n * num * len),
vector<int> findSubstring(string s, vector<string>& words) { 
  unordered_map<string, int> counts;
  for (string word : words) {
      counts[word]++; //ab , ba , ab
  }
  int n = s.length(), num = words.size(), len = words[0].length();
  vector<int> indexes;
  for (int i = 0; i < n - num * len + 1; i++) { //iterate over string s // n - num*len + 1  //num*len : reduces the search
      unordered_map<string, int> seen; //no clean-up of map as locally declared
      int j = 0;
      for (; j < num; j++) { //iterave over all wrods
          string word = s.substr(i + j * len, len); //word : window of size len starts with (i+ j*len)
          if (counts.find(word) != counts.end()) {
              seen[word]++;
              if (seen[word] > counts[word])
                  break;
          } 
          else break;
      }
      if (j == num) { //visited all words
        indexes.push_back(i);
      }
  }
  return indexes; 
}
