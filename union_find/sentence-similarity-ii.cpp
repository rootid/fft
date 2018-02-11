//Sentence Similarity II
//Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.
//For example, words1 = ["great", "acting", "skills"] and words2 = ["fine", "drama", "talent"] are similar, if the similar word pairs are pairs = [["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]].
//Note that the similarity relation is transitive. For example, if "great" and "good" are similar, and "fine" and "good" are similar, then "great" and "fine" are similar.
//Similarity is also symmetric. For example, "great" and "fine" being similar is the same as "fine" and "great" being similar.
//Also, a word is always similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"], pairs = [] are similar, even though there are no specified similar word pairs.
//Finally, sentences can only be similar if they have the same number of words. So a sentence like words1 = ["great"] can never be similar to words2 = ["doubleplus","good"].
//Note:
//The length of words1 and words2 will not exceed 1000.
//The length of pairs will not exceed 2000.
//The length of each pairs[i] will be 2.
//The length of each words[i] and pairs[i][j] will be in the range [1, 20].


//######################################### UF #########################################
//
//This is a good use case for Union-Find, compare to Sentence Similarity I, here the similarity between words are transitive, so all the connected(similar) words should be group into an union represented by their ultimate parent(or family holder, you name it).
//The connections can be represented by an parent map Map<String, String> m, which record the direct parent-ship we learned in each pair, but not the ultimate-parent. To build it, go through the input pairs, for each pair<w1, w2>, use the recursive find() method to find the ultimate-parent for both word - parent1, parent2, if they are different, assign parent1 as parent of parent2(or the other way around), so that the to families are merged.
//The classic find(x) method will find the ultimate-parent of x. I modified it a little bit, make it do a little of extra initialization work - assign x itself as its parent when it is not initialize - so that we don't have to explicitly initialize the map at the beginning.
class Solution {
    public boolean areSentencesSimilarTwo(String[] a, String[] b, String[][] pairs) {
        if (a.length != b.length) return false;
        Map<String, String> m = new HashMap<>();
        for (String[] p : pairs) {
            String parent1 = find(m, p[0]), parent2 = find(m, p[1]);
            if (!parent1.equals(parent2)) m.put(parent1, parent2);
        }

        for (int i = 0; i < a.length; i++)
            if (!a[i].equals(b[i]) && !find(m, a[i]).equals(find(m, b[i]))) return false;

        return true;
    }

    private String find(Map<String, String> m, String s) {
        if (!m.containsKey(s)) m.put(s, s);
        return s.equals(m.get(s)) ? s : find(m, m.get(s));
    }
}


//######################################### Path compression #########################################
string find(unordered_map<string, string>& mp, string word) {
    if(!mp.count(word)) {
        mp[word] = word;
        return word;
    }
    while(mp[word] != word) {
        if(mp.count(mp[word])) mp[word] = mp[mp[word]];
        word = mp[word];
    }
    return word;
}

//######################################### DFS #########################################
//Time Complexity: O(NP), where NNN is the maximum length of words1 and words2, and PPP is the length of pairs. Each of NNN searches could search the entire graph.
//Space Complexity: O(P), the size of pairs.
class Solution {
    public boolean areSentencesSimilarTwo(
            String[] words1, String[] words2, String[][] pairs) {
        if (words1.length != words2.length) return false;
        Map<String, List<String>> graph = new HashMap();
        for (String[] pair: pairs) {
            for (String p: pair) if (!graph.containsKey(p)) {
                graph.put(p, new ArrayList());
            }
            graph.get(pair[0]).add(pair[1]);
            graph.get(pair[1]).add(pair[0]);
        }

        for (int i = 0; i < words1.length; ++i) {
            String w1 = words1[i], w2 = words2[i];
            Stack<String> stack = new Stack();
            Set<String> seen = new HashSet();
            stack.push(w1);
            seen.add(w1);
            search: {
                while (!stack.isEmpty()) {
                    String word = stack.pop();
                    if (word.equals(w2)) break search;
                    if (graph.containsKey(word)) {
                        for (String nei: graph.get(word)) {
                            if (!seen.contains(nei)) {
                                stack.push(nei);
                                seen.add(nei);
                            }
                        }
                    }
                }
                return false;
            }
        }
        return true;
    }
}

//######################################### Union Find #########################################
//Time Complexity: O(NlogP+P), where NNN is the maximum length of words1 and words2, and PPP is the length of pairs. If we used union-by-rank, this complexity improves to O(N∗α(P)+P)≈O(N+P)O(N * \alpha(P) + P) \approx O(N + P)O(N∗α(P)+P)≈O(N+P), where α\alphaα is the Inverse-Ackermann function.
//
//Space Complexity: O(P), the size of pairs.
class Solution {
    public boolean areSentencesSimilarTwo(String[] words1, String[] words2, String[][] pairs) {
        if (words1.length != words2.length) return false;
        Map<String, Integer> index = new HashMap();
        int count = 0;
        DSU dsu = new DSU(2 * pairs.length);
        for (String[] pair: pairs) {
            for (String p: pair) if (!index.containsKey(p)) {
                index.put(p, count++);
            }
            dsu.union(index.get(pair[0]), index.get(pair[1]));
        }

        for (int i = 0; i < words1.length; ++i) {
            String w1 = words1[i], w2 = words2[i];
            if (w1.equals(w2)) continue;
            if (!index.containsKey(w1) || !index.containsKey(w2) ||
                    dsu.find(index.get(w1)) != dsu.find(index.get(w2)))
                return false;
        }
        return true;
    }
}

class DSU {
    int[] parent;
    public DSU(int N) {
        parent = new int[N];
        for (int i = 0; i < N; ++i)
            parent[i] = i;
    }
    public int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    public void union(int x, int y) {
        parent[find(x)] = find(y);
    }
}
