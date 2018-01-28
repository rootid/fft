//Degree of an Array
//Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.
//Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.
//Example 1:
//Input: [1, 2, 2, 3, 1]
//Output: 2
//Explanation:
//The input array has a degree of 2 because both elements 1 and 2 appear twice.
//Of the subarrays that have the same degree:
//[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
//The shortest length is 2. So return 2.
//Example 2:
//Input: [1,2,2,3,1,4,2]
//Output: 6
//Note:
//nums.length will be between 1 and 50,000.
//nums[i] will be an integer between 0 and 49,999.
//

//######################################### T : O(N), S(N) #########################################
public int findShortestSubArray(int[] nums) {
    //Max freq, , list of nums
    //start,end -> capture
    Map<Integer, Integer[]> freqMap = new HashMap<>();
    int mxFrq = 0;
    for(int i=0;i<nums.length;i++) {
        if(!freqMap.containsKey(nums[i])) {
            int[] tmp = new int[3];
            tmp[0] = 1;
            tmp[1] = i;
            tmp[2] = i;
            freqMap.put(nums[i], tmp);
        }
        freqMap.get(nums[i])[2] = i;
        freqMap.get(nums[i])[0]++;
        mxFrq = Math.max( freqMap.get(nums[i])[0], mxFrq) ;
    }
    int minLen = Integer.MAX_VALUE;
    for(int k: freqMap.keySet()) {
        if(freqMap.get(k)[0] == mxFrq) minLen = Math.min(freqMap.get(k)[2] - freqMap.get(k)[1]  + 1, minLen);
    }
    return minLen;
}

//######################################### O(N) #########################################
def findShortestSubArray(self, nums):
        c = collections.Counter(nums)
        first, last = {}, {}
        for i, v in enumerate(nums):
            first.setdefault(v, i)
            last[v] = i
        degree = max(c.values())
        return min(last[v] - first[v] + 1 for v in c if c[v] == degree)


//######################################### O(N) #########################################
//Counter replacement with defaultdict
def findShortestSubArray(self, nums):
    map = defaultdict(list)
    for i in range(len(nums)):
        map[nums[i]].append(i)
    return min((-len(list), list[-1] - list[0] + 1) for list in map.values())[1]

//######################################### Brute force  #########################################
def findShortestSubArray(self, nums):
    return min((-nums.count(x), len(nums) - nums.index(x) - nums[::-1].index(x)) for x in set(nums))[1]
