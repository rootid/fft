//Given many words, words[i] has weight i.
//Design a class WordFilter that supports one function, WordFilter.f(String prefix, String suffix). It will return the word with given prefix and suffix with maximum weight. If no word exists, return -1.
//Examples:
//Input:
//WordFilter(["apple"])
//WordFilter.f("a", "e") // returns 0
//WordFilter.f("b", "") // returns -1
//Note:
//    words has length in range [1, 15000].
//    For each test case, up to words.length queries WordFilter.f may be made.
//    words[i] has length in range [1, 10].
//    prefix, suffix have lengths in range [0, 10].
//    words[i] and prefix, suffix queries consist of lowercase letters only.
//

//######################################### W/O Trie #########################################
//Before solving this problem, we need to know which operation is called the most.
//If f is more frequently than WordFilter, use method 1.
//If space complexity is concerned, use method 2.
//If the input string array might change frequently, use method 3.

//######################################### Method 1 #########################################
//WordFilter: Time = O(NL^2)
//f: Time = O(1)
//Space = O(NL^2)
//Note: N is the size of input array and L is the max length of input strings.
class WordFilter {
    HashMap<String, Integer> map = new HashMap<>();

    public WordFilter(String[] words) {
        for(int w = 0; w < words.length; w++){
            for(int i = 0; i <= 10 && i <= words[w].length(); i++){
                for(int j = 0; j <= 10 && j <= words[w].length(); j++){
                    map.put(words[w].substring(0, i) + "#" + words[w].substring(words[w].length()-j), w);
                }
            }
        }
    }

    public int f(String prefix, String suffix) {
        return (map.containsKey(prefix + "#" + suffix))? map.get(prefix + "#" + suffix) : -1;
    }
}


//######################################### Method 2 #########################################
//WordFilter: Time = O(NL)
//f: Time = O(N)
//Space = O(NL)

class WordFilter {
    HashMap<String, List<Integer>> mapPrefix = new HashMap<>();
    HashMap<String, List<Integer>> mapSuffix = new HashMap<>();

    public WordFilter(String[] words) {

        for(int w = 0; w < words.length; w++){
            for(int i = 0; i <= 10 && i <= words[w].length(); i++){
                String s = words[w].substring(0, i);
                if(!mapPrefix.containsKey(s)) mapPrefix.put(s, new ArrayList<>());
                mapPrefix.get(s).add(w);
            }
            for(int i = 0; i <= 10 && i <= words[w].length(); i++){
                String s = words[w].substring(words[w].length() - i);
                if(!mapSuffix.containsKey(s)) mapSuffix.put(s, new ArrayList<>());
                mapSuffix.get(s).add(w);
            }
        }
    }

    public int f(String prefix, String suffix) {

        if(!mapPrefix.containsKey(prefix) || !mapSuffix.containsKey(suffix)) return -1;
        List<Integer> p = mapPrefix.get(prefix);
        List<Integer> s = mapSuffix.get(suffix);
        int i = p.size()-1, j = s.size()-1;
        while(i >= 0 && j >= 0){
            if(p.get(i) < s.get(j)) j--;
            else if(p.get(i) > s.get(j)) i--;
            else return p.get(i);
        }
        return -1;
    }
}

//######################################### Method 3 #########################################
//WordFilter: Time = O(1)
//f: Time = O(NL)
//Space = O(1)

class WordFilter {
    String[] input;
    public WordFilter(String[] words) {
        input = words;
    }
    public int f(String prefix, String suffix) {
        for(int i = input.length-1; i >= 0; i--){
            if(input[i].startsWith(prefix) && input[i].endsWith(suffix)) return i;
        }
        return -1;
    }
}


//######################################### W/ Trie #########################################

//######################################### Paired Trie #########################################
//Say we are inserting the word apple. We could insert ('a', 'e'), ('p', 'l'), ('p', 'p'), ('l', 'p'), ('e', 'a') into our trie. Then, if we had equal length queries like prefix = "ap", suffix = "le", we could find the node trie['a', 'e']['p', 'l'] in our trie. This seems promising.
//What about queries that aren't equal? We should just insert them like normal. For example, to capture a case like prefix = "app", suffix = "e", we could create nodes trie['a', 'e']['p', None]['p', None].
//After inserting these pairs into our trie, our searches are straightforward.
//TC : O(NK^2+QK) where N is the number of words, K is the maximum length of a word, and Q is the number of queries.
//SC : O(NK^2), the size of the trie.
class WordFilter {
    TrieNode trie;
    public WordFilter(String[] words) {
        trie = new TrieNode();
        int wt = 0;
        for (String word: words) {
            TrieNode cur = trie;
            cur.weight = wt;
            int L = word.length();
            char[] chars = word.toCharArray();
            for (int i = 0; i < L; ++i) {

                TrieNode tmp = cur;
                for (int j = i; j < L; ++j) {
                    int code = (chars[j] - '`') * 27;
                    if (tmp.children.get(code) == null)
                        tmp.children.put(code, new TrieNode());
                    tmp = tmp.children.get(code);
                    tmp.weight = wt;
                }

                tmp = cur;
                for (int k = L - 1 - i; k >= 0; --k) {
                    int code = (chars[k] - '`');
                    if (tmp.children.get(code) == null)
                        tmp.children.put(code, new TrieNode());
                    tmp = tmp.children.get(code);
                    tmp.weight = wt;
                }

                int code = (chars[i] - '`') * 27 + (chars[L - 1 - i] - '`');
                if (cur.children.get(code) == null)
                    cur.children.put(code, new TrieNode());
                cur = cur.children.get(code);
                cur.weight = wt;

            }
            wt++;
        }
    }

    public int f(String prefix, String suffix) {
        TrieNode cur = trie;
        int i = 0, j = suffix.length() - 1;
        while (i < prefix.length() || j >= 0) {
            char c1 = i < prefix.length() ? prefix.charAt(i) : '`';
            char c2 = j >= 0 ? suffix.charAt(j) : '`';
            int code = (c1 - '`') * 27 + (c2 - '`');
            cur = cur.children.get(code);
            if (cur == null) return -1;
            i++; j--;
        }
        return cur.weight;
    }
}

class TrieNode {
    Map<Integer, TrieNode> children;
    int weight;
    public TrieNode() {
        children = new HashMap();
        weight = 0;
    }
}

//######################################### Trie of Suffix Wrapped Words #########################################
//Consider the word 'apple'. For each suffix of the word, we could insert that suffix, followed by '#', followed by the word, all into the trie.
//For example, we will insert '#apple', 'e#apple', 'le#apple', 'ple#apple', 'pple#apple', 'apple#apple' into the trie. Then for a query like prefix = "ap", suffix = "le", we can find it by querying our trie for le#ap.
//TC: O(NK^2+QK) where N is the number of words, K is the maximum length of a word, and Q is the number of queries.
//SC: O(NK^2), the size of the trie.

class WordFilter {
    TrieNode trie;
    public WordFilter(String[] words) {
        trie = new TrieNode();
        for (int weight = 0; weight < words.length; ++weight) {
            String word = words[weight] + "{";
            for (int i = 0; i < word.length(); ++i) {
                TrieNode cur = trie;
                cur.weight = weight;
                for (int j = i; j < 2 * word.length() - 1; ++j) {
                    int k = word.charAt(j % word.length()) - 'a';
                    if (cur.children[k] == null)
                        cur.children[k] = new TrieNode();
                    cur = cur.children[k];
                    cur.weight = weight;
                }
            }
        }
    }
    public int f(String prefix, String suffix) {
        TrieNode cur = trie;
        for (char letter: (suffix + '{' + prefix).toCharArray()) {
            if (cur.children[letter - 'a'] == null) return -1;
            cur = cur.children[letter - 'a'];
        }
        return cur.weight;
    }
}

class TrieNode {
    TrieNode[] children;
    int weight;
    public TrieNode() {
        children = new TrieNode[27];
        weight = 0;
    }
}


// vim: set sw=2 sts=2 tw=120 et nospell :
