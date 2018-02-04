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

//######################################### BFS - to find shortest length, DFS = xplore path #########################################
public List<List<String>> findLadders(String start, String end, List<String> wordList) {
   HashSet<String> dict = new HashSet<String>(wordList);
   List<List<String>> res = new ArrayList<List<String>>();
   HashMap<String, ArrayList<String>> nodeNeighbors = new HashMap<String, ArrayList<String>>();// Neighbors for every node
   HashMap<String, Integer> distance = new HashMap<String, Integer>();// Distance of every node from the start node
   ArrayList<String> solution = new ArrayList<String>();

   dict.add(start);
   bfs(start, end, dict, nodeNeighbors, distance);
   dfs(start, end, dict, nodeNeighbors, distance, solution, res);
   return res;
}

// BFS: Trace every node's distance from the start node (level by level).
private void bfs(String start, String end, Set<String> dict, HashMap<String, ArrayList<String>> nodeNeighbors, HashMap<String, Integer> distance) {
  for (String str : dict)
      nodeNeighbors.put(str, new ArrayList<String>());

  Queue<String> queue = new LinkedList<String>();
  queue.offer(start);
  distance.put(start, 0);

  while (!queue.isEmpty()) {
      int count = queue.size();
      boolean foundEnd = false;
      for (int i = 0; i < count; i++) {
          String cur = queue.poll();
          int curDistance = distance.get(cur);
          ArrayList<String> neighbors = getNeighbors(cur, dict);

          for (String neighbor : neighbors) {
              nodeNeighbors.get(cur).add(neighbor);
              if (!distance.containsKey(neighbor)) {// Check if visited
                  distance.put(neighbor, curDistance + 1);
                  if (end.equals(neighbor))// Found the shortest path
                      foundEnd = true;
                  else
                      queue.offer(neighbor);
                  }
              }
          }

          if (foundEnd)
              break;
      }
  }

// Find all next level nodes.
private ArrayList<String> getNeighbors(String node, Set<String> dict) {
  ArrayList<String> res = new ArrayList<String>();
  char chs[] = node.toCharArray();

  for (char ch ='a'; ch <= 'z'; ch++) {
      for (int i = 0; i < chs.length; i++) {
          if (chs[i] == ch) continue;
          char old_ch = chs[i];
          chs[i] = ch;
          if (dict.contains(String.valueOf(chs))) {
              res.add(String.valueOf(chs));
          }
          chs[i] = old_ch;
      }

  }
  return res;
}

// DFS: output all paths with the shortest distance.
private void dfs(String cur, String end, Set<String> dict, HashMap<String, ArrayList<String>> nodeNeighbors, HashMap<String, Integer> distance, ArrayList<String> solution, List<List<String>> res) {
    solution.add(cur);
    if (end.equals(cur)) {
       res.add(new ArrayList<String>(solution));
    } else {
       for (String next : nodeNeighbors.get(cur)) {
            if (distance.get(next) == distance.get(cur) + 1) {
                 dfs(next, end, dict, nodeNeighbors, distance, solution, res);
            }
        }
    }
   solution.remove(solution.size() - 1);
}

//##################################################### BFS #####################################################
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


//######################################### Double BFS  #########################################
// BT BFS traversal = O(2^l)  l = # of levels
//If we know source and destination, we can build the word tree by going forward in one direction and backwards in the other. We stop when we have found that a word in the next level of BFS is in the other level, but first we need to update the tree for the words in the current level.
//Then we build the result by doing a DFS on the tree constructed by the BFS.
//The difference between normal and double BFS is that the search changes from O(k^d) to O(k^(d/2) + k^(d/2)). Same complexity class
//
//Let's call k the max number of neighbors of a node, and d is the distance from start to end. In traditional BFS, we explore k nodes at each BFS level, each one generating in the worst case k neighbors till we find end. So the maximum number of nodes we explore till we reach end is k*k*k...*k, d times. So it's O(k^d).
//In double-ended BFS we finish when the forward and backward searches collide. Where do they collide? Approximately at d/2 distance. Let's call this point mid. So it's O(k^(d/2)) (start to mid) + O(k^(d/2)) (end to mid), yielding O(k^(d/2)). Yes, it's the same class of complexity of standard BFS, but for large graphs double-ended BFS may give you the right result waaaaaaay faster.
class Solution(object):

    # Solution using double BFS


    def findLadders(self, begin, end, words_list):

        def construct_paths(source, dest, tree):
            if source == dest:
                return [[source]]
            return [[source] + path for succ in tree[source]
                                    for path in construct_paths(succ, dest, tree)]

        def add_path(tree, word, neigh, is_forw):
            if is_forw: tree[word]  += neigh,
            else:       tree[neigh] += word,

        def bfs_level(this_lev, oth_lev, tree, is_forw, words_set):
            if not this_lev: return False
            if len(this_lev) > len(oth_lev):
                return bfs_level(oth_lev, this_lev, tree, not is_forw, words_set)
            for word in (this_lev | oth_lev):
                words_set.discard(word)
            next_lev, done = set(), False
            while this_lev:
                word = this_lev.pop()
                for c in string.ascii_lowercase:
                    for index in range(len(word)):
                        neigh = word[:index] + c + word[index+1:]
                        if neigh in oth_lev:
                            done = True
                            add_path(tree, word, neigh, is_forw)
                        if not done and neigh in words_set:
                            next_lev.add(neigh)
                            add_path(tree, word, neigh, is_forw)
            return done or bfs_level(next_lev, oth_lev, tree, is_forw, words_set)

        tree, path, paths = collections.defaultdict(list), [begin], []
        is_found = bfs_level(set([begin]), set([end]), tree, True, words_list)
        return construct_paths(begin, end, tree)

//######################################### Double BFS  #########################################
void add_to_tree(map<string, vector<string>>& tree,
              string word,
              string neigh,
              bool forward) {
    if (forward) tree[word].push_back(neigh);
    else         tree[neigh].push_back(word);

}

vector<vector<string>> construct_paths(map<string,
                                       vector<string>>& tree,
                                       string start,
                                       string dest) {
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

bool bfs_levels(unordered_set<string>& now,
                unordered_set<string>& oth,
                bool& forward,
                map<string, vector<string>>& tree,
                unordered_set<string>& words_list,
                vector<char>& alphabet) {

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


class Solution {
public:
    vector<vector<string>> findLadders(string beginWord,
                                       string endWord,
                                       unordered_set<string> &wordList) {

        vector<char> alphabet(26);
        std::iota(alphabet.begin(), alphabet.end(), 'a');
        unordered_set<string> now = {beginWord}, oth = {endWord};
        map<string, vector<string>> tree; bool forward = true;
        auto is_found = bfs_levels(now, oth, forward, tree, wordList, alphabet);
        return construct_paths(tree, beginWord, endWord);

    }
};


//######################################### BFS  #########################################
/**
 * we are essentially building a graph, from start, BF.
 * and at each level we find all reachable words from parent.
 * we stop if the current level contains end,
 * we return any path whose last node is end.
 *
 * to achieve BFT, use a deuqe;
 * a key improvement is to remove all the words we already reached
 * in PREVIOUS LEVEL; we don't need to try visit them again
 * in subsequent level, that is guaranteed to be non-optimal solution.
 * at each new level, we will removeAll() words reached in previous level from dict.
 */

class Solution {
    public List<List<String>> findLadders(String beginWord, String endWord, List<String> wordList) {
        List<List<String>> out = new ArrayList<List<String>>();
        if (beginWord == null || endWord == null || wordList == null || wordList.size() < 1) {
            return out;
        }
        Set<String> set = new HashSet<String>();
        for (String word : wordList) {
            set.add(word);
        }
        if (!set.contains(endWord)) {
            return out;
        }
        Queue<List<String>> q = new LinkedList<List<String>>();
        q.offer(Arrays.asList(beginWord));
        boolean find = false;
        while (!q.isEmpty() && !find) {
            int size = q.size();
            Set<String> toDelete = new HashSet<String>();
            while (size-- > 0) {
                List<String> path = new ArrayList<String>(q.poll());
                char[] curr = path.get(path.size()-1).toCharArray();
                for (int i = 0; i < curr.length; ++i) {
                    char backup = curr[i];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        curr[i] = c;
                        String next = new String(curr);
                        if (set.contains(next)) {
                            path.add(next);
                            q.offer(new ArrayList<String>(path));
                            if (next.equals(endWord)) {
                                out.add(new ArrayList<String>(path));
                                find = true;
                            }
                            path.remove(path.size()-1);
                            toDelete.add(next);
                        }
                    }
                    curr[i] = backup;
                }
            }
            for (String word : toDelete) {
                if (set.contains(word)) {
                    set.remove(word);
                }
            }
        }
        return out;
    }
}


//######################################### Dict to eliminate duplicates #########################################
class Solution:
# @param start, a string
# @param end, a string
# @param dict, a set of string
# @return a list of lists of string
def findLadders(self, start, end, dic):
    dic.add(end)
    level = {start}
    parents = collections.defaultdict(set)
    while level and end not in parents:
        next_level = collections.defaultdict(set)
        for node in level:
            for char in string.ascii_lowercase:
                for i in range(len(start)):
                    n = node[:i]+char+node[i+1:]
                    if n in dic and n not in parents:
                        next_level[n].add(node)
        level = next_level
        parents.update(next_level)
    res = [[end]]
    while res and res[0][0] != start:
        res = [[p]+r for r in res for p in parents[r[0]]]
    return res

//######################################### Double BFS #########################################
//1. Use Bidirectional BFS which always expand from direction with less nodes
//2. Use char[] to build string so it would be fast
//3. Instead of scanning dict each time, we build new string from existing string and check if it is in dict
public List<List<String>> findLadders(String beginWord, String endWord, Set<String> wordList) {
    //we use bi-directional BFS to find shortest path
    Set<String> fwd = new HashSet<String>();
    fwd.add(beginWord);
    Set<String> bwd = new HashSet<String>();
    bwd.add(endWord);
    Map<String, List<String>> hs = new HashMap<String, List<String>>();
    BFS(fwd, bwd, wordList, false, hs);
    List<List<String>> result = new ArrayList<List<String>>();
    //if two parts cannot be connected, then return empty list
    if(!isConnected) return result;
    //we need to add start node to temp list as there is no other node can get start node
    List<String> temp = new ArrayList<String>();
    temp.add(beginWord);
    DFS(result, temp, beginWord, endWord, hs);
    return result;
}

//flag of whether we have connected two parts
boolean isConnected = false;
public void BFS(Set<String> forward, Set<String> backward, Set<String> dict, boolean swap, Map<String, List<String>> hs){
    //boundary check
    if(forward.isEmpty() || backward.isEmpty()){
        return;
    }

    //we always do BFS on direction with less nodes
    //here we assume forward set has less nodes, if not, we swap them
    if(forward.size() > backward.size()){
        BFS(backward, forward, dict, !swap, hs);
        return;
    }

    //remove all forward/backward words from dict to avoid duplicate addition
    dict.removeAll(forward);
    dict.removeAll(backward);

    //new set contains all new nodes from forward set
    Set<String> set3 = new HashSet<String>();

    //do BFS on every node of forward direction
    for(String str : forward){
        //try to change each char of str
        for(int i = 0; i < str.length(); i++){
            //try to replace current char with every chars from a to z
            char[] ary = str.toCharArray();
            for(char j = 'a'; j <= 'z'; j++){
                ary[i] = j;
                String temp = new String(ary);

                //we skip this string if it is not in dict nor in backward
                if(!backward.contains(temp) && !dict.contains(temp)){
                    continue;
                }

                //we follow forward direction
                String key = !swap? str : temp;
                String val = !swap? temp : str;

                if(!hs.containsKey(key)) hs.put(key, new ArrayList<String>());

                //if temp string is in backward set, then it will connect two parts
                if(backward.contains(temp)){
                    hs.get(key).add(val);
                    isConnected = true;
                }

                //if temp is in dict, then we can add it to set3 as new nodes in next layer
                if(!isConnected && dict.contains(temp)){
                    hs.get(key).add(val);
                    set3.add(temp);
                }
            }

        }
    }
    //to force our path to be shortest, we will not do BFS if we have found shortest path(isConnected = true)
    if(!isConnected){
        BFS(set3, backward, dict, swap, hs);
    }
}

public void DFS(List<List<String>> result, List<String> temp, String start, String end, Map<String, List<String>> hs){
    //we will use DFS, more specifically backtracking to build paths
    //boundary case
    if(start.equals(end)){
        result.add(new ArrayList<String>(temp));
        return;
    }
    //not each node in hs is valid node in shortest path, if we found current node does not have children node,
    //then it means it is not in shortest path
    if(!hs.containsKey(start)){
        return;
    }
    for(String s : hs.get(start)){
        temp.add(s);
        DFS(result, temp, s, end, hs);
        temp.remove(temp.size()-1);

    }
}

//######################################### Double BFS #########################################
public List<List<String>> findLadders(String start, String end, Set<String> dict) {
    // hash set for both ends
    Set<String> set1 = new HashSet<String>();
    Set<String> set2 = new HashSet<String>();

    // initial words in both ends
    set1.add(start);
    set2.add(end);

    // we use a map to help construct the final result
    Map<String, List<String>> map = new HashMap<String, List<String>>();

    // build the map
    helper(dict, set1, set2, map, false);

    List<List<String>> res = new ArrayList<List<String>>();
    List<String> sol = new ArrayList<String>(Arrays.asList(start));

    // recursively build the final result
    generateList(start, end, map, sol, res);

    return res;
  }

  boolean helper(Set<String> dict, Set<String> set1, Set<String> set2, Map<String, List<String>> map, boolean flip) {
    if (set1.isEmpty()) {
      return false;
    }

    if (set1.size() > set2.size()) {
      return helper(dict, set2, set1, map, !flip);
    }

    // remove words on current both ends from the dict
    dict.removeAll(set1);
    dict.removeAll(set2);

    // as we only need the shortest paths
    // we use a boolean value help early termination
    boolean done = false;

    // set for the next level
    Set<String> set = new HashSet<String>();

    // for each string in end 1
    for (String str : set1) {
      for (int i = 0; i < str.length(); i++) {
        char[] chars = str.toCharArray();

        // change one character for every position
        for (char ch = 'a'; ch <= 'z'; ch++) {
          chars[i] = ch;

          String word = new String(chars);

          // make sure we construct the tree in the correct direction
          String key = flip ? word : str;
          String val = flip ? str : word;

          List<String> list = map.containsKey(key) ? map.get(key) : new ArrayList<String>();

          if (set2.contains(word)) {
            done = true;
            list.add(val);
            map.put(key, list);
          }

          if (!done && dict.contains(word)) {
            set.add(word);
            list.add(val);
            map.put(key, list);
          }
        }
      }
    }
    // early terminate if done is true
    return done || helper(dict, set2, set, map, !flip);
  }

  void generateList(String start, String end, Map<String, List<String>> map, List<String> sol, List<List<String>> res) {
    if (start.equals(end)) {
      res.add(new ArrayList<String>(sol));
      return;
    }
    // need this check in case the diff between start and end happens to be one
    // e.g "a", "c", {"a", "b", "c"}
    if (!map.containsKey(start)) {
      return;
    }
    for (String word : map.get(start)) {
      sol.add(word);
      generateList(word, end, map, sol, res);
      sol.remove(sol.size() - 1);
    }
  }
// vim: set sw=2 sts=2 tw=120 et nospell :
