//Keyboard Row
//Given a List of words, return the words that can be typed using letters of alphabet on only one row's of American keyboard like the image below.
//Example 1:
//Input: ["Hello", "Alaska", "Dad", "Peace"]
//Output: ["Alaska", "Dad"]
//Note:
//You may use one character in the keyboard more than once.
//You may assume the input string will only contain letters of alphabet.

//###################################################### Map ########################################### 
vector<string> findWords(vector<string>& words) {
    unordered_set<char> row1 {'q', 'w', 'e', 'r', 't', 'y','u', 'i', 'o', 'p'};
    unordered_set<char> row2 {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'}; 
    unordered_set<char> row3 { 'z', 'x', 'c', 'v', 'b' ,'n', 'm'};
    vector<unordered_set<char>> rows {row1, row2, row3};
    
    
    vector<string> validWords;
    for(int i=0; i<words.size(); ++i){
        int row=0;
        //Identify the row
        for(int k=0; k<3; ++k){
            if(rows[k].count((char)tolower(words[i][0])) > 0) row = k;
        }
        validWords.push_back(words[i]);
        //check picked word is valid or not
        for(int j=1; j<words[i].size(); ++j){
            if(rows[row].count((char)tolower(words[i][j])) == 0){
                validWords.pop_back();
                break;
            }
        }
        
    }
    return validWords;
}

//###################################################### Bit manipulation  ########################################### 
vector<string> findWords(vector<string>& words) {
      vector<int> dict(26);
      vector<string> rows = {"QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"};
      for (int i = 0; i < rows.size(); i++) {
          for (auto c : rows[i]) dict[c-'A'] = 1 << i;
      }
      vector<string> res;
      for (auto w : words) {
          int r = 7;
          for (char c : w) {
              r &= dict[toupper(c)-'A'];
              if (r == 0) break;
          }
          if (r) res.push_back(w);
      }
      return res;
}
