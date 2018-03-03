//Word Ladder
//Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation
//sequence from beginWord to endWord, such that:
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

//######################################## BFS  ########################################
 //cnstrnt
    //1. empty workds?
    //2. empty wordlist/ 1 word?
    //3. alphabets/ numbers?
    //Ida
    //1. word -> [a-z] -> list? -> q (BFS) -> len  TC = O(26* len * qlen), SC= O(len)
    //2. tlist -> one letter word ->q (visited) -> TC = O(n)*O(len) , SC= O(len) -> add q
class Solution {
  public int ladderLength(String beginWord, String endWord, List<String> wordList) {
    Set<String> dict = new HashSet<>(wordList);
    Queue<String> queue = new LinkedList<>();
    queue.add(beginWord);
    int level = 1;
    while (!queue.isEmpty()) {
        int size = queue.size();
        for (int q=0; q < size; q++) {
            char[] cur = queue.poll().toCharArray();
            for (int i=0; i < cur.length; i++) {
                char tmp = cur[i];
                for (char chr='a'; chr <= 'z'; chr++) {
                    cur[i] = chr;
                    String dest = new String(cur);
                    if (dict.contains(dest)) {
                        if (dest.equals(endWord)) return level+1;
                        queue.add(dest);
                        dict.remove(dest);
                    }
                }
                cur[i] = tmp;
            }
        }
        level++;
    }
    return 0;
   }
}

//######################################## BFS  ########################################
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

//######################################## Bi-directional BFS  ########################################
public int ladderLength2(String beginWord, String endWord, List<String> wordList) {
	if (!wordList.contains(endWord)) return 0;
	Set<String> beginSet = new HashSet<>(), endSet = new HashSet<>(), visited = new HashSet<>();
	beginSet.add(beginWord);
	endSet.add(endWord);
	int len = 1;
	while (!beginSet.isEmpty() && !endSet.isEmpty()) {
		if (beginSet.size() > endSet.size()) { // swap two set
			Set<String> set = beginSet;
			beginSet = endSet;
			endSet = set;
		}
		Set<String> temp = new HashSet<String>();
		for (String a : beginSet) {
			for (String s : wordList) {
				if (vaild(a, s)) {
					if (endSet.contains(s)) return len + 1;
					if (!visited.contains(s)){
						temp.add(s);
						visited.add(s);
					}
				}
			}
		}
		beginSet = temp;
		len++;
	}
	return 0;
}

private boolean vaild(String a, String b){
	int e = 0;
	for (int i = 0; i < a.length(); i++) {
		if (a.charAt(i) != b.charAt(i)) e++;
		if (e > 1) return false;
	}
	return true;
}


//######################################## Bi-directional BFS  ########################################
class Solution:
    # @param {string} beginWord
    # @param {string} endWord
    # @param {set<string>} wordDict
    # @return {integer}
    def ladderLength(self, beginWord, endWord, wordDict):
        length = 2
        front, back = set([beginWord]), set([endWord])
        wordDict.discard(beginWord)
        while front:
            # generate all valid transformations
            front = wordDict & (set(word[:index] + ch + word[index+1:] for word in front
                                for index in range(len(beginWord)) for ch in 'abcdefghijklmnopqrstuvwxyz'))
            if front & back:
                # there are common elements in front and back, done
                return length
            length += 1
            if len(front) > len(back):
                # swap front and back for better performance (fewer choices in generating nextSet)
                front, back = back, front
            # remove transformations from wordDict to avoid cycle
            wordDict -= front
        return 0


//######################################## BFS  ########################################
class Solution:
    # @param {string} beginWord
    # @param {string} endWord
    # @param {set<string>} wordDict
    # @return {integer}
    def ladderLength(self, beginWord, endWord, wordDict):
        front, back=set([beginWord]), set([endWord])
        length=2
        width=len(beginWord)
        charSet=list(string.lowercase)
        wordDict.discard(beginWord)
        wordDict.discard(endWord)
        while front:
            newFront=set()
            for phrase in front:
                for i in xrange(width):
                    for c in charSet:
                        nw=phrase[:i]+c+phrase[i+1:]
                        if nw in back:
                            return length
                        if nw in wordDict:
                            newFront.add(nw)
            front=newFront
            if len(front)>len(back):
                front,back=back,front
            wordDict-=front
            length+=1
        return 0
// vim: set sw=2 sts=2 tw=120 et nospell :
