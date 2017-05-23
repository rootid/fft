//Longest Harmonious Subsequence
//We define a harmonious array is an array where the difference between its maximum value and its minimum value is exactly 1.
//Now, given an integer array, you need to find the length of its longest harmonious subsequence among all its possible subsequences.
//Example 1:
//Input: [1,3,2,2,5,2,3,7]
//Output: 5
//Explanation: The longest harmonious subsequence is [3,2,2,2,3].
//Note: The length of the input array will not exceed 20,000.
//

//#############################  with ordered_map ########################## 
int findLHS(vector<int>& nums) {
    map<int, int> freqs;
    for (int n : nums) {
        freqs[n]++;
    }
    int longest = 0;
    int lastNum = 0;
    int lastFreq = 0;
    for (auto& p : freqs) {
        int freq2 = 0;
        if (lastFreq && p.first == lastNum + 1) {
            freq2 = p.second + lastFreq;
        }
        longest = max(longest, freq2);
        lastNum = p.first;
        lastFreq = p.second;
    }
    return longest;
}

//#############################  with unordered_map ########################## 
int findLHS(vector<int>& nums) {
    unordered_map<int,int> mp;
    //map<int,int> mp;
    for(const auto& x: nums) {
      ++mp[x];
    }
    int len = 0;
    for (const auto& x: mp) {
        int y = x.first;
        //max and min diff must be exactly 1
        if (mp.count(y+1)) {
          len = max(len, x.second + mp[y+1]);
        }
        if (mp.count(y-1)) {
          len = max(len, x.second + mp[y-1]);
        }
    }
    return len;
}


//############################# pytonic ########################## 
//Let count[x] be the number of x's in our array.
//
//Suppose our longest subsequence B has min(B) = x and max(B) = x+1.
//Evidently, it should use all occurrences of x and x+1 to maximize it's length, so len(B) = count[x] + count[x+1].
//Additionally, it must use x and x+1 atleast once, so count[x] and count[x+1] should both be positive.
//def findLHS(self, A):
//    count = collections.Counter(A)
//    ans = 0
//    for x in count:
//        if x+1 in count:
//            ans = max(ans, count[x] + count[x+1])
//    return ans
////Alternative to collections.Counter(A)
//count = {}
//for x in A:
//    count[x] = count.get(x, 0) + 1
//
//count is a dictionary mapping values in our array to the number of times they occur. For example, if our array is A = [1, 1, 1, 2, 5, 5, 5], then our dictionary will be count = {1: 3, 2: 1, 5: 3}. When we iterate over count, we iterate over it's keys. So for x in count will loop through it's inner block three times, with the variable x = 1, x = 2, and x = 5.
//
//def findLHS(self, nums):
//        c = collections.Counter(nums)
//        return max(c[x] + c[x + 1] if c[x + 1] else 0 for x in c) if nums else 0
