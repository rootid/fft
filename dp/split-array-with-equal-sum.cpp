//Split array with equal Sum
//Given an array with n integers, you need to find if there are triplets (i, j, k) which satisfies following conditions:
//0 < i, i + 1 < j, j + 1 < k < n - 1
//Sum of subarrays (0, i - 1), (i + 1, j - 1), (j + 1, k - 1) and (k + 1, n - 1) should be equal.
//where we define that subarray (L, R) represents a slice of the original array starting from the element indexed L to the element indexed R.
//Example:
//Input: [1,2,1,2,1,2,1]
//Output: True
//Explanation:
//i = 1, j = 3, k = 5. 
//sum(0, i - 1) = sum(0, 0) = 1
//sum(i + 1, j - 1) = sum(2, 2) = 1
//sum(j + 1, k - 1) = sum(4, 4) = 1
//sum(k + 1, n - 1) = sum(6, 6) = 1
//Note:
//1 <= n <= 2000.
//Elements in the given array will be in range [-1,000,000, 1,000,000].

//Basicly we know:
//1. Need to find three point: x, y, z
//2. Total = 4*subArray + nums[x] + nums[y] + nums[z]
//then... I think the code will show you the idea...

//################################################### O(N^2) ################################################### 
class Solution {
public:
    bool splitArray(vector<int>& nums) {
        int i=0, j=nums.size()-2;
        int s=0; vector<int> sum;
        for(auto x: nums) {
            s+=x;
            sum.push_back(s);
        }
        int total = sum.back();
        for(j=nums.size()-2; j>i; j--) {
            for(i=0; i<j-1; i++) {
                if(sum[i]==total-sum[j]) { //found i+1 = x, j = z 
                    int y = total - 4*sum[i] - nums[i+1] - nums[j]; 
                    for(int k = i+1+1; k < j-1; k++)
                        if(nums[k] == y) return true;
                }
            }
            i=0;
        }
        return false;
    }
};

//################################################### O(N^2) ################################################### 
class Solution {
public:
    bool splitArray(vector<int>& nums) {
        int i=0, j=nums.size()-2;
        int s=0; vector<int> sum;
        unordered_map<int, vector<int>> map;
        for(int x=0; x<nums.size(); x++)
        {
            s+=nums[x];
            map[nums[x]].push_back(x);
            sum.push_back(s);
        }
        int total = sum.back();
        for(j=nums.size()-2; j>i; j--)
        {
            for(i=0; i<j-1; i++)
            {
                if(sum[i]==total-sum[j]) 
                {
                    int y = total - 4*sum[i] - nums[i+1] - nums[j]; 
                    if(map.find(y)!=map.end())
                    {
                        for(int x=0; x<map[y].size(); x++)
                        {
                            vector<int> bs = map[y];
                            int step = lower_bound(bs.begin(), bs.end(), i+2) - bs.begin();
                            if(step < j-1) return true;
                        }
                    }
                }
            }
            i=0;
        }
        return false;
    }
};

//################################################### O(N^2) ################################################### 
//Here j is used for middle cut, i for left cut and k for right cut.
//Iterate middle cuts and then find left cuts which divides the first half into two equal quarters, 
//store that quarter sums in the hashset. 
//Then find right cuts which divides the second half into two equal quarters and check if quarter sum is present in the hashset. If yes return true.
bool splitArray(int[] nums) { 
  if (nums.size() < 7)
      return false;
  vector<int>sum(nums.size(),0);
  for (int i = 1; i < nums.size(); i++) {
      sum[i] = sum[i - 1] + nums[i];
  }
  for (int j = 3; j < nums.size()- 3; j++) {
      unordered_set<int> set;
      for (int i = 1; i < j - 1; i++) {
          if (sum[i - 1] == sum[j - 1] - sum[i])
              set.add(sum[i - 1]);
      }
      for (int k = j + 2; k < nums.length - 1; k++) {
          if (sum[nums.size() - 1] - sum[k] == sum[k - 1] - sum[j] && set.find(sum[k - 1] - sum[j]))
              return true;
      }
  }
  return false;
}

//################################################### O(N^2) ################################################### 
public boolean splitArray(int[] nums) {
    if (nums.length < 7) return false;
    int [] sums = new int [nums.length];
    sums [0] = nums [0];
    for (int idx = 1; idx < nums.length; idx ++) sums [idx] += sums [idx - 1] + nums [idx];
        
    for (int idx1 = 1; idx1 < nums.length - 5; idx1 ++) {
        if (idx1 == 1 || sums [idx1 - 2] != sums [idx1 - 1]) {
            int s1 = sums [idx1 - 1];
            for (int idx2 = idx1 + 2; idx2 < nums.length - 3; idx2 ++) {
                int s2 = sums [idx2 - 1] - sums [idx1];    
                if (s1 == s2) {
                    for (int idx3 = idx2 + 2; idx3 < nums.length - 1; idx3 ++) {
                        int s3 = sums [idx3 - 1] - sums [idx2];        
                        int s4 = sums [sums.length - 1] - sums [idx3];    
                        if (s2 == s3 && s3 == s4) return true;
                    }
                }
            }
        }
    }
    return false;
}


//################################################### O(N^2) ################################################### 
bool splitArray(vector<int>& nums) {
    vector<int> sms;
    sms.push_back(0); //store prefix sum
    int N = nums.size();
    for(auto i : nums) {
        sms.push_back(sms[sms.size()-1] + i);
    }
    unordered_map<int, vector<int>> hsh; //inverted index
    for(int i = 0; i < sms.size(); i++) {
        hsh[sms[i]].push_back(i);
    }
    for(int i = 1; i < N - 1; i++ ) {
        for(int j = i + 1; j < N -1 ; j++) {
            for(auto f: hsh[sms[sms.size()-1] - sms[j+1]]) {
                if(f >= i) break;
                if(sms[f] == sms[i] - sms[f+1] && sms[f] == sms[j] - sms[i+1]) {
                    return true;
                }
            }
        }
    }
    return false;
}

//######################################### O(N^2) ######################################### 
//Just think this problem as a DFS. What we need is to search for 3 positions (i, j, k) and see if they divide the array to 4 parts with same summary. Some tricks:
//1. Calculate left on the fly. Thus at last we don't need to calc summary of the 4th part.
//2. Skip 0 during calculate target because adding zero won't change i
//
//[0,0,1,0,1,0,1,0]  : validate Tcase
bool splitArray(vector<int>& nums) {
    int sum = 0, target = 0;
    for (int num : nums) sum += num;
    for (int i = 1; i + 5 < nums.size(); i++) {
        if (i != 1 && nums[i - 1] == 0  && nums[i] == 0) continue;
        target += nums[i - 1]; //sum upto i-1 needs to be equal for all intervals
        if (dfs(nums, i + 1, target, sum - target - nums[i], 1)) return true;
    }
    return false;
}
    
bool dfs(vector<int>& nums, int start, int target, int left, int depth) {
    if (depth == 3) {
        if (left == target) return true;
        return false;
    }
    int sub = 0;
    for (int j = start + 1; j + 5 - depth * 2 < nums.size(); j++) {
        sub += nums[j - 1];
        if (sub == target) {
            if (dfs(nums, j + 1, target, left - sub - nums[j], depth + 1)) {
                return true;
            }
        }
    }
    return false;
}

//######################################### pytnoic ######################################### 
def splitArray(self, A):
    P = [0]
    for x in A: P.append(P[-1] + x)
    N = len(A)
    Pinv = collections.defaultdict(list)
    for i, u in enumerate(P):
        Pinv[u].append(i)
    for j in xrange(1, N-1):
        for k in xrange(j+1, N-1):
            for i in Pinv[P[-1] - P[k+1]]:
                if i >= j: break
                if P[i] == P[j] - P[i+1] == P[k] - P[j+1]:
                    return True
    return False


//The key idea is kind like divide and conquer (only twice though).
//First, for every middle point j, we split nums into two subarray nums[:j] and nums[j+1:]. In the helper function split, try to remove one element from the subarray, if the the sums of two remaining left and right sub-subarray are equal, we keep the sum of sub-subarray in the set we return. Once we have any intersection between the two sets, we know we can make it.
//Keep in mind len(nums) > 6 is a must since we need to split original array into four parts.

//NOTE : You don't need the explicit len(nums) > 6 test. If it's false, then the any(...) is false as well.
class Solution(object):
    def splitArray(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        def split(A):
            total = sum(A)
            for i in range(1, len(A)): A[i] += A[i-1]
            return {A[i-1] for i in range(1, len(A)-1) if A[i-1] == total - A[i]}
            
        return len(nums) > 6 and any(split(nums[:j]) & split(nums[j+1:]) \
                             for j in range(3, len(nums)-3))

//avoid repeat computation of A
def splitArray(self, nums):
        n = len(nums)
        s = [0] * (n + 1)
        for i in range(n): s[i + 1] = s[i] + nums[i]
        def check(l, r):
            return set(s[m] - s[l] for m in range(l + 1, r + 1) if s[m] - s[l] == s[r + 1] - s[m + 1])
        return any(check(0, j - 1) & check(j + 1, n - 1) for j in range(n))


// vim: set sw=2 sts=2 tw=120 et nospell : 
