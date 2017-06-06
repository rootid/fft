//Array Nesting
//A zero-indexed array A consisting of N different integers is given. The array contains all integers in the range [0, N - 1].
//Sets S[K] for 0 <= K < N are defined as follows:
//S[K] = { A[K], A[A[K]], A[A[A[K]]], ... }.
//Sets S[K] are finite for each K and should NOT contain duplicates.
//Write a function that given an array A consisting of N integers, return the size of the largest set S[K] for this array.
//Example 1:
//Input: A = [5,4,0,3,1,6,2]
//Output: 4
//Explanation: 
//A[0] = 5, A[1] = 4, A[2] = 0, A[3] = 3, A[4] = 1, A[5] = 6, A[6] = 2.
//One of the longest S[K]:
//S[0] = {A[0], A[5], A[6], A[2]} = {5, 6, 2, 0}
//Note:
//N is an integer within the range [1, 20,000].
//The elements of A are all distinct.
//Each element of array A is an integer within the range [0, N-1].


//The idea is to, start from every number, find circles in those index-pointer-chains, 
//every time you find a set (a circle) mark every number as visited (-1) 
//so that next time you won't step on it again.
//################################### O(N) ######################
int arrayNesting(vector<int>& nums) {
    size_t maxsize = 0;
    for (int i = 0; i < nums.size(); i++) {
        size_t size = 0;
        for (int k = i; nums[k] >= 0; size++) {
            int last_visited = nums[k];
            nums[k] = -1; // mark nums[k] as visited;
            k = last_visited;
        }
        maxsize = max(maxsize, size);
    }
    return maxsize;
}

//##########################################  DFS  #########################################
//Pruning is must as for each S[k], it is a circle. There is no need to do extra DFS once one element has been visited.
//This is actually a DFS.  Use a visited map to keep track of visited node. If a 
//number is visited before, then the set that starts at this number must be smaller then
//previous max. So we can safely skip this number. In total it's O(n) complexity.
int arrayNesting(vector<int>& nums) {
    int largest = 0;
    vector<int> visited(nums.size(), 0);
    for(int i = 0; i < nums.size(); i++){
        largest = max(largest, largest_nesting(nums, visited, nums[i], 0));
    }
    return largest;
}

int largest_nesting(vector<int>& nums, vector<int>& visited, int idx, int size){
    if(visited[nums[idx]] == 0){
        visited[nums[idx]] = 1;
        return largest_nesting(nums, visited, nums[idx], size + 1);
    } else {
        return size;
    }
}

//######################################## pytonic ######################################################## 
//class Solution(object):
//    def arrayNesting(self, nums):
//        """
//        :type nums: List[int]
//        :rtype: int
//        """
//        # find the size of all the isolated circles
//        visited = [False] * len(nums)
//        max_count = 0
//        for i, num in enumerate(nums):
//            count = 0
//            while not visited[i]:
//                visited[i] = True
//                count += 1
//                i = nums[i]
//            max_count = max(count, max_count)
//        return max_count
//

//For every value 0 <= x < N, consider the set S_x = {x, A[x], A[A[x]], A[A[A[x]]],...}
//Every node x belongs to some representative set S_i. We'll repeatedly take an unvisited node and visit all members of it's representative set. We keep track of the size of this set bns = |S_i| and take a running max ans = max(ans, bns
//def arrayNesting(self, A):
//    N = len(A)
//    ans = 0
//    seen = [False] * N
//    for x in xrange(N):
//    	bns = 0
//    	while not seen[x]:
//            seen[x] = True
//            x = A[x]
//            bns += 1
//        ans = max(ans, bns)
//    return ans
//
//
//######################################## Bucket sort ######################################## 
//public class Solution {
//    public int ArrayNesting(int[] nums) {
//        if (nums.Length == 0) return 0;
//        
//        var global = 1;
//        for (int i = 0; i < nums.Length; i++) {
//            var local = 1;
//            while(nums[i] != i) {
//                var temp = nums[i];
//                nums[i] = nums[temp];
//                nums[temp] = temp;
//                local++;
//            }
//            global = Math.Max(local, global);
//        }
//        return global;
//    }
//}
