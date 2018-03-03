//Sequence Reconstruction
//Check whether the original sequence org can be uniquely reconstructed from
//the sequences in seqs. The org sequence is a permutation of the integers from
//1 to n, with 1 ≤ n ≤ 104. Reconstruction means building a shortest common
//supersequence of the sequences in seqs (i.e., a shortest sequence so that all
//sequences in seqs are subsequences of it). Determine whether there is only
//one sequence that can be reconstructed from seqs and it is the org sequence.
//Example 1:
//Input:
//org: [1,2,3], seqs: [[1,2],[1,3]]
//Output:
//false
//Explanation:
//[1,2,3] is not the only one sequence that can be reconstructed, because [1,3,2] is also a valid sequence that can be reconstructed.
//Example 2:
//Input:
//org: [1,2,3], seqs: [[1,2]]
//Output:
//false
//Explanation:
//The reconstructed sequence can only be [1,2].
//Example 3:
//Input:
//org: [1,2,3], seqs: [[1,2],[1,3],[2,3]]
//Output:
//true
//Explanation:
//The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct the original
//sequence [1,2,3].
//Example 4:
//Input:
//org: [4,1,5,2,6,3], seqs: [[5,2,6,3],[4,1,5,2]]
//Output:
//true
//

//######################################### Topological sort #########################################
  public boolean sequenceReconstruction(int[] org, List<List<Integer>> seqs) {
        Map<Integer, Set<Integer>> map = new HashMap<>();
        int[] degree = new int[org.length];

        // for(int i = 1; i<=org.length; i++) map.put(i, new HashSet<>());
       //cannot init map with org, has to do with seqs, to avoid case like [1], [], expected: false

        for(List<Integer> list: seqs){
            if(list.size()==1) map.computeIfAbsent(list.get(0), k->new HashSet<Integer>()); //dont forget
            for(int i = 1; i<list.size(); i++){
                int pre = list.get(i-1);
                int cur = list.get(i);
                map.computeIfAbsent(pre, k->new HashSet<Integer>());
                map.computeIfAbsent(cur, k->new HashSet<Integer>());
                if(pre>org.length || cur>org.length || pre<1 || cur<1) return false;
                //dont forget. or degree array can "ArrayIndexOutOfBoundsException"

                if(!map.get(pre).contains(cur)){
                    degree[cur-1]++;
                    map.get(pre).add(cur);
                }
            }
        }

        Queue<Integer> q = new LinkedList<>();
        for(int i = 0; i<degree.length; i++){
            if(degree[i]==0) q.add(i+1);
        }
        int index = 0;
        while(!q.isEmpty()){
            if(q.size()>1) return false; //check with org
            int cur = q.poll();
            if(org[index++] != cur) return false; //check with org
            if(!map.containsKey(cur)) continue; //don't forget
            for(int ii: map.get(cur)){
                degree[ii-1]--;
                if(degree[ii-1]==0) q.add(ii);
            }
        }
        return index == org.length && index==map.size();//has to check with map size
    }

//######################################### Topological sort #########################################
public boolean sequenceReconstruction(int[] org, int[][] seqs) {
    Map<Integer, Set<Integer>> map = new HashMap<>();
    Map<Integer, Integer> indegree = new HashMap<>();
    for (int[] seq : seqs) {
        for (int i : seq) {
            map.putIfAbsent(i, new HashSet<>());
            indegree.putIfAbsent(i, 0);
        }
    }

    for (int[] seq : seqs) {
        if (seq.length == 1) continue;
        for (int i = 1; i < seq.length; i++)
            if (map.get(seq[i - 1]).add(seq[i]))
                indegree.put(seq[i], indegree.get(seq[i]) + 1);
    }

    if (org.length != indegree.size()) return false;

    Queue<Integer> q = new ArrayDeque<>();
    for (int key : indegree.keySet())
        if (indegree.get(key) == 0) q.add(key);

    int cnt = 0;
    while (q.size() == 1) {
        for (int next : map.get(q.poll())) {
            indegree.put(next, indegree.get(next) - 1);
            if (indegree.get(next) == 0) q.add(next);
        }
        cnt++;
    }

    return cnt == indegree.size();
}
