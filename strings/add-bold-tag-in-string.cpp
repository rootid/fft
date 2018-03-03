//Add Bold Tag in String
//Given a string s and a list of strings dict, you need to add a closed pair of bold tag <b> and </b> to wrap the
//substrings in s that exist in dict. If two such substrings overlap, you need to wrap them together by only one pair of
//closed bold tag. Also, if two substrings wrapped by bold tags are consecutive, you need to combine them.
//Example 1:
//Input:
//s = "abcxyz123"
//dict = ["abc","123"]
//Output:
//"<b>abc</b>xyz<b>123</b>"
//Example 2:
//Input:
//s = "aaabbcc"
//dict = ["aaa","aab","bc"]
//Output:
//"<b>aaabbc</b>c"
//Note:
//The given dict won't contain duplicates, and its length won't exceed 100.
//All the strings in input have length in range [1, 100]
//

//######################################## Trie ########################################

class trie{
public:
    bool isWord;
    unordered_map<char, trie*> next;
    trie(){
        isWord=false;
    }
};
class Solution {
public:
    string addBoldTag(string s, vector<string>& dict) {

        // Create trie
        trie* root = new trie();
        for(auto& word : dict){
            trie* node = root;
            for(char& c : word){
                if(node->next.find(c)==node->next.end()){
                    node->next[c]=new trie();
                }
                node = node->next[c];
            }
            node->isWord=true;
        }

        // "last" is the index of last character that currently belong to word
        string res="";
        int last = -1;
        for(int i=0; i<s.size(); i++) {
            trie* node = root;
            for(int j=i; j<s.size(); j++) {
                if(node->next.find(s[j]) == node->next.end())
                    break; //char is not part of Trie
                node = node->next[s[j]];
                if(node->isWord){
                    if(i>last)
                        res+="<b>";
                    last=max(last,j);
                }
            }
            res+=s[i];
            if(i==last)
                res+="</b>";
        }

        //Delete adjacent </b> and <b>
        for(int i =0; i<res.size()-6; i++){
            if(res.substr(i,7)=="</b><b>")
                res=res.substr(0,i)+res.substr(i+7);
        }
        return res;
    }
};


//#################################### Merge interval + find ####################################
class Solution {
public:
    string addBoldTag(string s, vector<string>& dict) {
        vector<pair<int, int>> ranges = findpairs(s, dict);
        ranges = merge(ranges);
        for (auto it = ranges.rbegin(); it != ranges.rend(); it++) {
            s.insert(it->second, "</b>");
            s.insert(it->first, "<b>");
        }
        return s;
    }

private:
    vector<pair<int, int>> findpairs(string s, vector<string>& dict) {
        vector<pair<int, int>> res;
        for (string w : dict) {
            int n = w.size();
            for (int i = 0; (i = s.find(w, i)) != string::npos; i++) {
                res.push_back(pair<int, int>(i, i + n));
            }
        }
        return res;
    }

    vector<pair<int, int>> merge(vector<pair<int, int>>& a) {
        vector<pair<int, int>> r;
        sort(a.begin(), a.end(), compare);
        for (int i = 0, j = -1; i < a.size(); i++) {
            if (j < 0 || a[i].first > r[j].second) {
                r.push_back(a[i]);
                j++;
            }
            else {
                r[j].second = max(r[j].second, a[i].second);
            }
        }

        return r;
    }

    static bool compare(pair<int, int>& a, pair<int, int>& b) {
        return a.first < b.first || a.first == b.first && a.second < b.second;
    }
};



//#################################### With HashMap ####################################
class Solution {
private:
  int searchMaxLen(string& s, int start, vector<string> words) {
      int len = 0;
      for(string w : words) {
          int wl = w.length();
          if(start+wl<=s.length() && s.substr(start, wl)==w)
              len = max(len, wl);
      }
      return len;
  }
public :
  string addBoldTag(string s, vector<string>& dict) {
      unordered_map<char, vector<string>> wdict;
      for(string word : dict) {
          wdict[word[0]].push_back(word);
      }

      for(int i=0; i<s.length(); ++i) {
          if(wdict.count(s[i]) == 0) continue;
          int len = searchMaxLen(s, i, wdict[s[i]]);
          if(len == 0) continue;
          for(int j=i+1; j<=i+len; ++j) {
              int curLen = searchMaxLen(s, j, wdict[s[j]]);
              len = max(len, j-i + curLen);
          }
          s.insert(i+len, "</b>");
          s.insert(i, "<b>");
          i += len+7;
      }
      return s;
  }

};

//#################################### Find matching char with start and end index ####################################
class Solution {
public:
    string addBoldTag(string s, vector<string>& dict) {
        int n = s.size();
        vector<int> open(n + 1), closed(n + 1);
        for ( string & w : dict ) {
            int i = -1;
            while ( (i = s.find(w, i + 1)) != string::npos ) {
                ++open[i];
                ++closed[i + w.size()];
            }
        }
        string tagged;
        int pre = 0;
        for ( int i = 0, t = 0; i <= n; ++i ) {
            if ( open[i] && 0 == t && ! closed[i] ) {
                tagged += s.substr(pre, i - pre) + "<b>";
                pre = i;
            }
            t += open[i];
            t -= closed[i];
            if ( closed[i] && 0 == t && ! open[i] ) {
                tagged += s.substr(pre, i - pre) + "</b>";
                pre = i;
            }
        }
        return tagged + s.substr(pre);
    }
};



//############################################ Pytonic ############################################
//######################################## Trie ########################################
//We put all the words in our given wordlist into a trie. Then, let's paint any letter in our string that should be
//bolded. For every starting position i in our string, let's find the longest word that S[i:] starts with, and paint
//S[i:i+len(word)].
//Afterwards, we have a boolean array where paint[i] = True iff S[i] is bolded. Let's write our letters from left to
//right. If we are on a bolded letter and there is an unbolded letter to the left (or if we are at the leftmost letter),
//we should start a <b> tag. Similarly for </b> tags: they start when our bolded letter has an unbolded right neighbor
//(or we are at the right-most letter.)
//
//def addBoldTag(self, S, A):
//    END = False
//    _trie = lambda: collections.defaultdict(_trie)
//    trie = _trie()
//
//    for word in A:
//        cur = trie
//        for letter in word:
//            cur = cur[letter]
//        cur[END] = END
//
//    paint = [False] * len(S)
//    for i in xrange(len(S)):
//        cur = trie
//        end = i
//        for j in xrange(i, len(S)):
//            if S[j] not in cur: break
//            cur = cur[S[j]]
//            if END in cur:
//                end = j + 1
//        paint[i:end] = [True] * (end - i)
//
//    ans = []
//    for i, u in enumerate(S):
//        if paint[i] and (i == 0 or not paint[i-1]):
//            ans.append('<b>')
//        ans.append(u)
//        if paint[i] and (i == len(S) - 1 or not paint[i+1]):
//            ans.append('</b>')
//
//    return "".join(ans)
//
//################################# Non-trie #################################
//def addBoldTag(self, S, A):
//    paint = [False] * len(S)
//    for i in xrange(len(S)):
//        block = S[i:]
//        for word in A:
//            if block.startswith(word):
//                paint[i:i+len(word)] = [True] * len(word)
//
//    ans = []
//    for i, u in enumerate(S):
//        if paint[i] and (i == 0 or not paint[i-1]):
//            ans.append('<b>')
//        ans.append(u)
//        if paint[i] and (i == len(S) - 1 or not paint[i+1]):
//            ans.append('</b>')
//
//    return "".join(ans)

// vim: set sw=2 sts=2 tw=120 et nospell :
