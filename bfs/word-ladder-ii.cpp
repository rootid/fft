//Word Ladder II
//Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:
//Only one letter can be changed at a time
//Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
//For example,
//Given:
//beginWord = "hit"
//endWord = "cog"
//wordList = ["hot","dot","dog","lot","log","cog"]
//Return
//  [
//    ["hit","hot","dot","dog","cog"],
//    ["hit","hot","lot","log","cog"]
//  ]
//Note:
//Return an empty list if there is no such transformation sequence.
//All words have the same length.
//All words contain only lowercase alphabetic characters.
//You may assume no duplicates in the word list.
//You may assume beginWord and endWord are non-empty and are not the same.
//########################################## Double ended BFS ########################################## 
//O(k^d) to O(k^(d/2) + k^(d/2))  //d : # of search levelgs

//we can build the word tree by going forward in one direction and backwards in the other. We stop when we have found that a word in the next level of BFS is in the other level, but first we need to update the tree for the words in the current level.

void add_to_tree(map<string, vector<string>>& tree, string word, string neigh, bool forward) {
    if (forward) tree[word].push_back(neigh);
    else         tree[neigh].push_back(word);
}
vector<vector<string>> construct_paths(map<string, vector<string>>& tree, string start, string dest) {
    if (start == dest) {
        vector<string> res = {start};
        vector<vector<string>> arr = {res};
        return arr;
    }
    vector<vector<string>> result;
    for (auto succ: tree[start]) {
        for (auto path: construct_paths(tree, succ, dest)) {
            path.insert(path.begin(), start);
            result.push_back(path);
        }
    }
    return result;
}
bool bfs_levels(unordered_set<string>& now, unordered_set<string>& oth, bool& forward, map<string, vector<string>>& tree, unordered_set<string>& words_list, vector<char>& alphabet) {
    if (not now.size()) return false;
    if (now.size() > oth.size()){
        forward = not forward;
        return bfs_levels(oth, now, forward, tree, words_list, alphabet);
    }
    for (auto word: now) words_list.erase(word);
    for (auto word: oth) words_list.erase(word);
    
    bool done = false; unordered_set<string> next;
    for (string word: now) {
        for (int i = 0; i < word.size(); i++) {
            for (char c: alphabet) {
                auto neigh = word.substr(0, i) + c + word.substr(i+1);
                if (oth.count(neigh) > 0) {
                    done = true;
                    add_to_tree(tree, word, neigh, forward);
                }
                else {
                    if (not done and words_list.count(neigh) > 0) {
                        next.insert(neigh);
                        add_to_tree(tree, word, neigh, forward);
                    }
                }
            }
        }
    }
    forward = not forward;
    return done or bfs_levels(oth, next, forward, tree, words_list, alphabet);
}
vector<vector<string>> findLaddersHelper(string beginWord, string endWord, unordered_set<string> &wordList) {
    vector<char> alphabet(26);
    std::iota(alphabet.begin(), alphabet.end(), 'a');
    unordered_set<string> now = {beginWord}, oth = {endWord};
    map<string, vector<string> > tree; bool forward = true;
    auto is_found = bfs_levels(now, oth, forward, tree, wordList, alphabet);
    return construct_paths(tree, beginWord, endWord);    
}
vector<vector<string> > findLadders(string beginWord, string endWord, vector<string>& wordList) {
  unordered_map<string, vector<string>> m;
  unordered_set<string> dict(wordList.begin(),wordList.end());
  return findLaddersHelper(beginWord,endWord,dict);
}

//##################################################### DFS  ##################################################### 
class Solution {
private:
 vector<vector<string>> findLaddersHelper(string start, string end, unordered_set<string> &dict) {
        unordered_set<string> head={start}, tail={end};
        vector<vector<string>> ans;
        unordered_map<string, vector<string>> next;
        bool head_start = true;
        while (!head.empty() && !tail.empty()) {
            for (auto word:head) dict.erase(word);
            for (auto word:tail) dict.erase(word);
            if (head.size() > tail.size()) {
                swap(head, tail);
                head_start = !head_start;
            }
            unordered_set<string> temp_head;
            bool stop = false;
            for (auto word:head) {
                string original_word = word;
                for (int i=0; i<word.length(); i++) {
                    char temp = word[i];
                    for (char ch='a'; ch<='z'; ch++) {
                        if (ch == temp) continue;
                        word[i] = ch;
                        if (tail.find(word) != tail.end()) {
                            stop = true;
                            if (head_start) 
                                next[original_word].push_back(word);
                            else
                                next[word].push_back(original_word);
                        }
                        if (!stop && dict.find(word) != dict.end()) {
                            temp_head.insert(word);
                            if (head_start) 
                                next[original_word].push_back(word);
                            else
                                next[word].push_back(original_word);
                        }
                    }
                    word = original_word;
                }
            }
            if (stop) break;
            head = temp_head;
        }
        vector<string> v={start};
        dfs(ans, v, next, start, end);
        return ans;
    }
    
    void dfs(vector<vector<string>> &ans, vector<string> &v, unordered_map<string, vector<string>> &next, string s, string t) {
        if (s == t) {
            ans.push_back(v);
        }
        for (auto word:next[s]) {
            v.push_back(word);
            dfs(ans, v, next, word, t);
            v.pop_back();
        }
    }
public :
vector<vector<string> > findLadders(string beginWord, string endWord, vector<string>& wordList) {
  unordered_map<string, vector<string>> m;
  unordered_set<string> dict(wordList.begin(),wordList.end());
  return findLaddersHelper(beginWord,endWord,dict);
}
};
