//Longest Word in Dictionary
//Given a list of strings words representing an English Dictionary, find the
//longest word in words that can be built one character at a time by other
//words in words. If there is more than one possible answer, return the longest
//word with the smallest lexicographical order.
//If there is no answer, return the empty string.
//Example 1:
//Input:
//words = ["w","wo","wor","worl", "world"]
//Output: "world"
//Explanation:
//The word "world" can be built one character at a time by "w", "wo", "wor",
//and "worl".
//Example 2:
//Input:
//words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
//Output: "apple"
//Explanation:
//Both "apply" and "apple" can be built from other words in the dictionary.
//However, "apple" is lexicographically smaller than "apply".
//Note:
//All the strings in the input will only contain lowercase letters.
//The length of words will be in the range [1, 1000].
//The length of words[i] will be in the range [1, 30].
//

//######################################### Sort + HashSet  #########################################
//Sort the words alphabetically, therefore shorter words always comes before
//longer words;
//Along the sorted list, populate the words that can be built;
//Any prefix of a word must comes before that word.

public String longestWord(String[] words) {
    Arrays.sort(words);
    Set<String> store = new HashSet<>();
    String res = "";
    for(String w: words) {
        if( w.length() == 1 || store.contains(w.substring(0, w.length() -1))) {
            res = w.length() > res.length() ? w : res;
            store.add(w);
        }

    }
    return res;
}


//######################################### Sort + HashSet  #########################################

  string longestWord(vector<string>& words) {
        sort(words.begin(), words.end());
        unordered_set<string> built;
        string res;
        for (string w : words) {
            if (w.size() == 1 || built.count(w.substr(0, w.size() - 1))) {
                res = w.size() > res.size() ? w : res;
                built.insert(w);
            }
        }
        return res;
    }

//######################################### Trie + Sort #########################################
class Solution {
    class TrieNode{
        public char val;
        public TrieNode[] hash;
        public TrieNode(){
            this.val='\u0000';
            this.hash=new TrieNode[26];
        }
        public TrieNode(char c){
            this.val=c;
            this.hash=new TrieNode[26];
        }
    }
    public String longestWord(String[] words) {
        TrieNode root=new TrieNode();
        Arrays.sort(words);
        String res="";
        for(String word:words){
            TrieNode curr=root;
            for(int i=0;i<word.length();i++){
                if(curr.hash[word.charAt(i)-'a']==null && i<word.length()-1)
                    break;
                if(curr.hash[word.charAt(i)-'a']==null){
                    TrieNode temp=new TrieNode(word.charAt(i));
                    curr.hash[word.charAt(i)-'a']=temp;
                }
                curr=curr.hash[word.charAt(i)-'a'];
                if(i==word.length()-1)
                    res= res.length() < word.length()? word : res;
            }
        }
        return res;
    }
}


//######################################### Trie + DFS  #########################################

class Solution {
    public String longestWord(String[] words) {
        TrieNode root = new TrieNode ();
        root.word = "-";
        for (String word : words)
            root.insert (word);
        return dfs (root, "");
    }

    String dfs (TrieNode node, String accum) {
        if (node == null || node.word.length () == 0)
            return accum;
        String res = "";
        if (!node.word.equals ("-"))
            accum = node.word;
        for (TrieNode child : node.links) {
            String curRes = dfs (child, accum);
            if (curRes.length () > res.length () || (curRes.length () == res.length () && curRes.compareTo (res) < 0))
                res = curRes;
        }
        return res;
    }

    /* Hand write this class every time you need to so you can remember well */
    static class TrieNode {
        String word = "";
        TrieNode[] links = new TrieNode[26];

        void insert (String s) {
            char[] chs = s.toCharArray ();
            TrieNode curNode = this;
            for (int i = 0; i < chs.length; i++) {
                int index = chs[i] - 'a';
                if (curNode.links[index] == null)
                    curNode.links[index] = new TrieNode ();
                curNode = curNode.links[index];
            }
            curNode.word = s;
        }
    }
