//Given a non-empty list of words, return the k most frequent elements.
//Your answer should be sorted by frequency from highest to lowest. If two words have the same frequency, then the word
//with the lower alphabetical order comes first.
//Example 1:
//Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
//Output: ["i", "love"]
//Explanation: "i" and "love" are the two most frequent words.
//    Note that "i" comes before "love" due to a lower alphabetical order.
//Example 2:
//Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
//Output: ["the", "is", "sunny", "day"]
//Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
//    with the number of occurrence being 4, 3, 2 and 1 respectively.
//Note:
//    You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
//    Input words contain only lowercase letters.
//Follow up:
//    Try to solve it in O(n log k) time and O(n) extra space.
//

//######################################### Srting O(n log n) #########################################
//cnstrnt
//1. streaming/static list of words?
//2. how to brk tie when freq =?

//Ida
//1, Scan -> frq,word -> sort -> return top k , TC : O(n) + O(n log n)
//2. Scan -> freq , prq. (fre, string) , return top k ele : TC: O(N) + O(N * log N)
//3. Bucket sort

class Pair {
    Integer freq;
    String wrd;
}
public List<String> topKFrequent(String[] words, int k) {
    Map<String, Integer> map = new HashMap<>();
    List<String> result = new LinkedList();
    for(String wrd: words) map.put(wrd, map.getOrDefault(wrd, 1) + 1);
    List<Pair> lst = new ArrayList<Pair>();
    for(String key: map.keySet()) {
        Pair tmp = new Pair();
        tmp.freq = map.get(key);
        tmp.wrd = key;
        lst.add(tmp);
    }
    lst.sort((p1, p2) -> {
            if (p1.freq == p2.freq)
                return p1.wrd.compareTo(p2.wrd);
            return p2.freq.compareTo(p1.freq);
    });

    for(int i=0;i<k;i++) result.add(lst.get(i).wrd);
    return result;
}

//######################################### Pq O(n log k) #########################################
//Heap Size of length k
public List<String> topKFrequent(String[] words, int k) {
     List<String> result = new LinkedList<>();
     Map<String, Integer> map = new HashMap<>();
     for(int i=0; i<words.length; i++)
         map.put(words[i], map.getOrDefault(words[i], 1) + 1);

     PriorityQueue<Map.Entry<String, Integer>> pq = new PriorityQueue<>(
              (a,b) -> a.getValue()==b.getValue() ? b.getKey().compareTo(a.getKey()) : a.getValue()-b.getValue());

     for(Map.Entry<String, Integer> entry: map.entrySet()) {
         pq.offer(entry);
         if(pq.size()>k)
             pq.poll();
     }
     while(!pq.isEmpty())
         result.add(0, pq.poll().getKey());
     return result;
}

//######################################### Bucket sort  #########################################
public List<String> topKFrequent(String[] words, int k) {
      HashMap<String, Integer> map = new HashMap<>();
      int max = 0;
      for (String w: words) {
          map.put(w, map.getOrDefault(w, 0) + 1);
          max = Math.max(max, map.get(w));
      }
      List<String>[] bucket = new ArrayList[max + 1];
      for (Map.Entry<String, Integer> entry: map.entrySet()) {
          int fre = entry.getValue();
          if (bucket[fre] == null) {
              bucket[fre] = new ArrayList<>();
          }
          bucket[fre].add(entry.getKey());
      }
      List<String> res = new ArrayList<>();
      for (int i = max; i >= 0 && res.size() < k; i--) {
          if (bucket[i] != null) {
              Collections.sort(bucket[i]);
              res.addAll(bucket[i]);
          }
      }
      return res.subList(0, k);
}

// vim: set sw=2 sts=2 tw=120 et nospell :
