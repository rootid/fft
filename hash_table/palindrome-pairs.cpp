//Palindrome Pairs
//Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.
//Example 1:
//Given words = ["bat", "tab", "cat"]
//Return [[0, 1], [1, 0]]
//The palindromes are ["battab", "tabbat"]
//Example 2:
//Given words = ["abcd", "dcba", "lls", "s", "sssll"]
//Return [[0, 1], [1, 0], [3, 2], [2, 4]]
//The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]

//###########################################  hashtable #########################################
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int> > result;
        unordered_map<string, int> dict;
        int i, j, size = words.size();
        string left, right, tmp;
        for(i = 0; i < size; i++) {
            tmp = words[i];
            reverse(tmp.begin(), tmp.end());
            dict[tmp] = i; //store reverse string in map
        }
        
        for(i = 0; i < size; i++) {
            for(j = 0; j < words[i].size(); j++) {
                left = words[i].substr(0, j); //left(first half of string) + right 
                right = words[i].substr(j);  //abcd,dcba
                if(dict.find(left) != dict.end() && dict[left] != i && isPalindrome(right)) {
                    result.push_back({i, dict[left]});  
                    if(left.empty()) { //a,"" -> need to o/p [0,1],[1,0]
                        result.push_back({dict[left], i}); //reverse pair
                    }
                }
                if(dict.find(right) != dict.end() && dict[right] != i && isPalindrome(left))
                    result.push_back({dict[right], i});
            }
        }
        return result;
    }
    
private:
    bool isPalindrome(string s) {
        int start, end, size = s.size();
        for(start = 0, end = size - 1; start < end; start++, end--) {
            if(s[start] != s[end])
                return false;
        }
        return true;
    }

//########################################## get suffix and prefix #####################################################
 vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> result;
        unordered_map<string, int> dict;
        for(int i = 0; i < words.size(); i++) {
            dict[words[i]] = i;
        }
        for(int i = 0; i < words.size(); i++) {
            for(int j = 0; j <= words[i].length(); j++) {
                //check the suffix word
                if(is_palindrome(words[i], j, words[i].size() - 1)) {
                    /** the suffix word can be null to all the word **/
                    string suffix = words[i].substr(0, j);
                    reverse(suffix.begin(), suffix.end());
                    if(dict.find(suffix) != dict.end() && i != dict[suffix]) {
                        result.push_back({i, dict[suffix]});
                    }
                }
                //check the prefix word 
                if(j > 0 && is_palindrome(words[i], 0, j - 1)) {
                    string prefix = words[i].substr(j);
                    reverse(prefix.begin(), prefix.end());
                    if(dict.find(prefix) != dict.end() && dict[prefix] != i) {
                        result.push_back({dict[prefix], i});
                    }
                }
            }
        }
        return result;
    }
    
    bool is_palindrome(string& s, int start, int end) {
        while(start < end) {
            if(s[start++] != s[end--]) {
                return false;
            }
        }
        return true;
        
    }

//###########################################  pal-list  naive #########################################
vector<vector<int>> palindromePairs(vector<string>& words) {
    unordered_map<string, int> index;
    unordered_map<string, int> revIndex;
    vector<string> revWords(words.size(),"");
    for (int i = 0; i < words.size(); ++i) {
        string s = words[i];
        string r = s;
        reverse(r.begin(),r.end());
        index.put(s, i);
        revIndex.put(r, i);
        revWords[i] = r;
    }
    vector<vector<int> > result;
    result.addAll(findPairs(words, revWords, revIndex, false));
    result.addAll(findPairs(revWords, words, index, true));
    return result;
}
vector<vector<int> > findPairs(vector<string words, string[] revWords, unordered_map<string, int> revIndex, boolean reverse) {
    vector<vector<int>> result ;
    for (int i = 0; i < words.size(); ++i) {
        string s = words[i];
        for (int k = reverse ? 1 : 0; k <= s.size()(); ++k) { // check suffixes, <= because we allow empty words
            int j = revIndex.get(s.substr(k));
            if (j != null && j != i) { // reversed suffix is present in the words list
                // check whether the prefix is a palindrome
                if (s.regionMatches(0, revWords[i], s.size()() - k, k)) {
                    result.add(reverse ? Arrays.asvector(i, j) : Arrays.asvector(j, i));
                }
            }
        }
    }
    return result;
}
