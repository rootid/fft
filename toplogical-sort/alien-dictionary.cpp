//Alien Dictionary
//There is a new alien language which uses the latin alphabet. However, the
//order among letters are unknown to you. You receive a list of non-empty words
//from the dictionary, where words are sorted lexicographically by the rules of
//this new language. Derive the order of letters in this language.
//Example 1:
//Given the following words in dictionary,
//[
//  "wrt",
//  "wrf",
//  "er",
//  "ett",
//  "rftt"
//]
//The correct order is: "wertf".
//Example 2:
//Given the following words in dictionary,
//[
//  "z",
//  "x"
//]
//The correct order is: "zx".
//Example 3:
//Given the following words in dictionary,
//[
//  "z",
//  "x",
//  "z"
//]
//The order is invalid, so return "".
//Note:
//    You may assume all letters are in lowercase.
//    You may assume that if a is a prefix of b, then a must appear before b in the given dictionary.
//    If the order is invalid, return an empty string.
//    There may be multiple valid order of letters, return any one of them is fine.

ublic class Solution {
    public String alienOrder(String[] words) {
        Map<Character, AlienChar> graph = new HashMap<Character, AlienChar>();
        // 如果建图失败，比如有a->b和b->a这样的边，就返回false
        boolean isBuildSucceed = buildGraph(words, graph);
        if(!isBuildSucceed){
            return "";
        }
        // 在建好的图中根据拓扑排序遍历
        String order = findOrder(graph);
        return order.length() == graph.size() ? order : "";
    }

    private boolean buildGraph(String[] words, Map<Character, AlienChar> graph){
        HashSet<String> visited = new HashSet<String>();
        // 初始化图，每个字母都初始化入度为0
        initializeGraph(words, graph);
        for(int wordIdx = 0; wordIdx < words.length - 1; wordIdx++){
            String before = words[wordIdx];
            String after = words[wordIdx + 1];
            Character prev = null, next = null;
            // 找到相邻两个单词第一个不一样的字母
            for(int letterIdx = 0; letterIdx < before.length() && letterIdx < after.length(); letterIdx++){
                if(before.charAt(letterIdx) != after.charAt(letterIdx)){
                    prev = before.charAt(letterIdx);
                    next = after.charAt(letterIdx);
                    break;
                }
            }
            // 如果有环，则建图失败
            if(prev != null && visited.contains(next + "" + prev)){
                return false;
            }
            // 如果这条边没有添加过，则在图中加入这条边
            if(prev != null && !visited.contains(prev + "" + next)){
                addEdge(prev, next, graph);
                visited.add(prev + "" + next);
            }
        }
        return true;
    }

    private void initializeGraph(String[] words, Map<Character, AlienChar> graph){
        for(String word : words){
            for(int idx = 0; idx < word.length(); idx++){
                if(!graph.containsKey(word.charAt(idx))){
                    graph.put(word.charAt(idx), new AlienChar(word.charAt(idx)));
                }
            }
        }
    }

    private void addEdge(char prev, char next, Map<Character, AlienChar> graph){
        AlienChar prevAlienChar = graph.get(prev);
        AlienChar nextAlienChar = graph.get(next);
        nextAlienChar.indegree += 1;
        prevAlienChar.later.add(nextAlienChar);
        graph.put(prev, prevAlienChar);
        graph.put(next, nextAlienChar);
    }

    private String findOrder(Map<Character, AlienChar> graph){
        StringBuilder order = new StringBuilder();
        Queue<AlienChar> queue = new LinkedList<AlienChar>();
        for(Character c : graph.keySet()){
            if(graph.get(c).indegree == 0){
                queue.offer(graph.get(c));
            }
        }
        while(!queue.isEmpty()){
            AlienChar curr = queue.poll();
            order.append(curr.val);
            for(AlienChar next : curr.later){
                if(--next.indegree == 0){
                    queue.offer(next);
                }
            }
        }
        return order.toString();
    }
}

class AlienChar {
    char val;
    ArrayList<AlienChar> later;
    int indegree;
    public AlienChar(char c){
        this.val = c;
        this.later = new ArrayList<AlienChar>();
        this.indegree = 0;
    }
}


