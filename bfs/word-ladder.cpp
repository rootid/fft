//Word Ladder
//Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:
//Only one letter can be changed at a time
//Each intermediate word must exist in the word list
//For example,
//Given:
//beginWord = "hit"
//endWord = "cog"
//wordList = ["hot","dot","dog","lot","log"]
//As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
//return its length 5.
//Note:
//Return 0 if there is no such transformation sequence.
//All words have the same length.
//All words contain only lowercase alphabetic characters.
//
int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
    //simple idea : at each level 
    queue<string> bq;
    bq.push(beginWord);
    bq.push("");
    int level = 1;
    string str = beginWord;
    while(!bq.empty()) {
        string str = bq.front();
        bq.pop();
        if(str != "") {
            for(int i=0;i<str.size();i++) {
                char tmp = str[i];
                for(char j='a';j<='z';j++) {
                    if(tmp == j) {
                        continue;
                    }
                    str[i] = j;
                    if(str == endWord) {
                        level += 1;
                        return level;
                    }
                    if(wordList.find(str) != wordList.end()) {
                        bq.push(str);    // Collect all one edit distance words
                        wordList.erase(str);  //to avoid revisits
                    }
                }
                str[i] = tmp;
            }
        } else if(!bq.empty()) {   // 2 word eg. "hot" ---> "dog" ["hot","dog"]
            bq.push("");   
            level++;
        }
    }
    
    return 0; //no transformation
}
