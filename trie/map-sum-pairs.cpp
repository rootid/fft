//Map Sum Pairs
//Implement a MapSum class with insert, and sum methods.
//For the method insert, you'll be given a pair of (string, integer). The string represents the key and the integer represents the value. If the key already existed, then the original key-value pair will be overridden to the new one.
//For the method sum, you'll be given a string representing the prefix, and you need to return the sum of all the pairs' value whose key starts with the prefix.
//Example 1:
//Input: insert("apple", 3), Output: Null
//Input: sum("ap"), Output: 3
//Input: insert("app", 2), Output: Null
//Input: sum("ap"), Output: 5

class MapSum {
    /** Initialize your data structure here. */
    public MapSum() {
        
    }
    public void insert(String key, int val) {
        
    }
    public int sum(String prefix) {
        
    }
}

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum obj = new MapSum();
 * obj.insert(key,val);
 * int param_2 = obj.sum(prefix);
 */

//######################################### Trie ######################################### 
class MapSum {
    class TrieNode {
        Map<Character, TrieNode> children;
        boolean isWord; //NOTE : Not required
        int value; 
        public TrieNode() {
            children = new HashMap<Character, TrieNode>();
            isWord = false;
            value = 0;
        }
    }
    
    TrieNode root;
    
    /** Initialize your data structure here. */
    public MapSum() {
        root = new TrieNode();
    }
    
    public void insert(String key, int val) {
        TrieNode curr = root;
        for (char c : key.toCharArray()) {
            TrieNode next = curr.children.get(c);
            if (next == null) {
                next = new TrieNode();
                curr.children.put(c, next);
            }
            curr = next;
        }
        curr.isWord = true;
        curr.value = val;
    }
    
    public int sum(String prefix) {
        TrieNode curr = root;
    for (char c : prefix.toCharArray()) {
        TrieNode next = curr.children.get(c);
        if (next == null) {
            return 0;
        }
        curr = next;
        }
        
        return dfs(curr);
    }
    
    private int dfs(TrieNode root) {
        int sum = 0;
        for (char c : root.children.keySet()) {
            sum += dfs(root.children.get(c));
        }
        return sum + root.value;
    }
}

//######################################### Map + indexof (prefix check) ######################################### 
/** Initialize your data structure here. */
HashMap<String, Integer> map;
public MapSum() {
    map = new HashMap<>();
}

public void insert(String key, int val) {
    map.put(key, val);
}

public int sum(String prefix) {
    int sum = 0;
    for (Map.Entry<String, Integer> entry : map.entrySet()){
        String s = entry.getKey();
        int index = entry.getValue();
        if(s.indexOf(prefix) == 0){
            sum += index;
        }
    }
    return sum;
}

//######################################### Only unordered_map ######################################### 
public:
    /** Initialize your data structure here. */
    MapSum() {
        sum_res = 0;
    }
    
    void insert(string key, int val) {
        mp[key] = val;
    }
    
    int sum(string prefix) {
        sum_res = 0;
        int prefix_size = prefix.size();
        for(auto it : mp) {
            if(it.first.substr(0, prefix_size) == prefix) {
                sum_res += it.second;
            }
        }
        return sum_res;
    }
private:
    unordered_map<string, int> mp;
    int sum_res;

//######################################### Trie ######################################### 
class MapSum {
	private TrieNode root;

	/** Initialize your data structure here. */
	public MapSum() {
		root = new TrieNode(0);
	}

	public void insert(String key, int val) {
		TrieNode node = root;
		int ci;
		for (int i = 0; i < key.length(); i++) {
			ci = key.charAt(i) - 'a';
			if (node.children[ci] == null)
				node.children[ci] = new TrieNode(val);
			else // update node.sum along the path
				node.children[ci].sum += val;
			node = node.children[ci];
		}
		if (node.isAWord) { // key existed
			node.isAWord = false;
			insert(key, -node.val);
			// for updating all pre nodes'sum along the path
		}
		node.val = val;
		node.isAWord = true;
	}

	public int sum(String prefix) {
		TrieNode node = root;
		for (int i = 0; i < prefix.length(); i++) {
			node = node.children[prefix.charAt(i) - 'a'];
			if (node == null)
				return 0;
		}
		return node.sum;
	}
}

class TrieNode {
	public int val;
	public int sum;
	public boolean isAWord;
	public TrieNode[] children;

	public TrieNode(int val) {
		sum = this.val = val;
		isAWord = false;
		children = new TrieNode[26];
	}
}


