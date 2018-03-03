//Find Anagram Mappings 77.9% Easy
//Given two lists Aand B, and B is an anagram of A. B is an anagram of A means B is made by randomizing the order of the
//elements in A.
// We want to find an index mapping P, from A to B. A mapping P[i] = j means the ith element in A appears in B at index j.
// These lists A and B may contain duplicates. If there are multiple answers, output any of them.
// For example, given
// A = [12, 28, 46, 32, 50]
// B = [50, 12, 32, 46, 28]
// We should return
// [1, 4, 3, 2, 0]
// as P[0] = 1 because the 0th element of A appears at B[1], and P[1] = 4 because the 1st element of A appears at B[4], and so on.
// Note:
//     1. A, B have equal lengths in range [1, 100].
//     2. A[i], B[i] are integers in range [0, 10^5].

//#############################################################################
// Consider A an B as whole not in parts
//If choose to use only most recently found element index
public int[] anagramMappings(int[] A, int[] B) {
      int len = A.length;
      int result[] = new int[len];
      Map<Integer, Integer> strMap = new HashMap<>();
      for(int i=0;i<len;i++) {
          strMap.put(B[i], i);
      }
      for(int i=0;i<len;i++)
          result[i] = strMap.get(A[i]);
      return result;
}


//#############################################################################
//If choose to use pick from matching index
  public int[] anagramMappings(int[] A, int[] B) {
        int len = A.length;
        int result[] = new int[len];
        Map<Integer, List<Integer>> strMap = new HashMap<>();
        for(int i=0;i<len;i++) {
             if(!strMap.containsKey(B[i])) {
                 List<Integer> lst = new ArrayList<>();
                 strMap.put(B[i],lst);
             }
             strMap.get(B[i]).add(i);
        }
        for(int i=0;i<len;i++)
           result[i] = strMap.get(A[i]).remove(map.get(A[i]).size() - 1);
        return result;

    }


//#############################################################################
 vector<int> anagramMappings(vector<int>& a, vector<int>& b) {
        if(a.size()!=b.size()) return vector<int>();    //not required as per the question

        unordered_map<int, int> m;    //<values of b, index in b>
        for(int i=0; i<b.size(); i++)
            m[b[i]]=i;

        vector<int> ans(a.size());
        for(int i=0; i<a.size(); i++) {
            auto loc = m.find(a[i]);
            ans[i]=loc->second;
        }

        return ans;
    }



//#############################################################################
//O(N) solution using hashmap:
def anagramMappings(self, A, B):
        d = {}
        for i, b in enumerate(B):
            if b not in d:
                d[b] = []
            d[b].append(i)
        return [d[a].pop() for a in A]

//#############################################################################
def anagramMappings(self, A, B):
        d = {b:i for i,b in enumerate(B)}
        return [d[a] for a in A]


//#############################################################################
//O(N^2) solution in 1 line:
def anagramMappings(self, A, B):
        return [B.index(a) for a in A]


/* vim: set ts=2 sw=2 sts=2 tw=120 et: */
