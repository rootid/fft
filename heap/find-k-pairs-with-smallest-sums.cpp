//Find K Pairs with Smallest Sums
//You are given two integer arrays nums1 and nums2 sorted in ascending order
//and an integer k.
//Define a pair (u,v) which consists of one element from the first array and
//one element from the second array.
//Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.
//Example 1:
//Given nums1 = [1,7,11], nums2 = [2,4,6],  k = 3
//Return: [1,2],[1,4],[1,6]
//The first 3 pairs are returned from the sequence:
//[1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
//Example 2:
//Given nums1 = [1,1,2], nums2 = [1,2,3],  k = 2
//Return: [1,1],[1,1]
//The first 2 pairs are returned from the sequence:
//[1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
//Example 3:
//Given nums1 = [1,2], nums2 = [3],  k = 3
//Return: [1,3],[2,3]
//All possible pairs are returned from the sequence:
//[1,3],[2,3]

//############################################ select top k ############################################
// O(kLogk)
//pq => {nums1,nums2, nums2.count}
public List<int[]> kSmallestPairs(int[] nums1, int[] nums2, int k) {
    PriorityQueue<int[]> que = new PriorityQueue<>((a,b)->a[0]+a[1]-b[0]-b[1]);
    List<int[]> res = new ArrayList<>();
    if(nums1.length==0 || nums2.length==0 || k==0) return res;
    for(int i=0; i<nums1.length && i<k; i++) que.offer(new int[]{nums1[i], nums2[0], 0}); //O(K)
    while(k-- > 0 && !que.isEmpty()){
        int[] cur = que.poll();
        res.add(new int[]{cur[0], cur[1]});
        if(cur[2] == nums2.length-1) continue;
        que.offer(new int[]{cur[0],nums2[cur[2]+1], cur[2]+1});
    }
    return res;
}


//############################################ select top k ############################################
// TC : O(n^2), O(n^2 log n^2)
public List<int[]> kSmallestPairs(int[] nums1, int[] nums2, int k) {
    List<int[]> result = new ArrayList<>();
    PriorityQueue<int[]> pq = new PriorityQueue<>((a,b) -> (a[0]+a[1])  - (b[0]+b[1]));
    for(int i:nums1)
        for(int j: nums2) pq.offer(new int[]{i,j});
    while(k-- > 0 && !pq.isEmpty()) {
        result.add(pq.poll());
    }
    return result;
}
//############################################ select top k ############################################
vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
     vector<pair<int, int>> v;
     if(nums1.empty() || nums2.empty()) return v;
     auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
         return a.first+a.second > b.first+b.second; };
     priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);
     for(auto n: nums1)
         for(auto m: nums2)
             minHeap.emplace(n, m);
     while(minHeap.size() && k--) {
         v.emplace_back(minHeap.top());
         minHeap.pop();
     }
     return v;
}


//############################################ same as above ############################################
vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int,int>> result;
        if (nums1.empty() || nums2.empty() || k <= 0)
            return result;
        auto comp = [&nums1, &nums2](pair<int, int> a, pair<int, int> b) {
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];};

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> min_heap(comp);

        min_heap.emplace(0, 0);
        while(k-- > 0 && min_heap.size()) {
            auto idx_pair = min_heap.top(); min_heap.pop();
            result.emplace_back(nums1[idx_pair.first], nums2[idx_pair.second]);
            if (idx_pair.first + 1 < nums1.size())
                min_heap.emplace(idx_pair.first + 1, idx_pair.second);
            if (idx_pair.first == 0 && idx_pair.second + 1 < nums2.size())
                min_heap.emplace(idx_pair.first, idx_pair.second + 1);
        }
        return result;
}



//################################  Create sum and then sort O(k^2) ################################
vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
  int m = nums1.size();
  int n = nums2.size();
  k = min(k, m*n);
  vector<pair<int, int> >result;
  for(int i1=0;i1<min(m,k);++i1) {
           for(int i2=0;i2<min(n,k);++i2) {
               result.push_back({nums1[i1],nums2[i2]});
           }
  }
  sort(result.begin(),result.end(),[](pair<int, int>&a,pair<int, int>&b){ return a.first+a.second < b.first+b.second;});
  if(result.size() > k) {
    result.erase(result.begin()+k,result.end());
  }
  return result;
}
