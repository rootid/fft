//Matchsticks to Square
//Remember the story of Little Match Girl? By now, you know exactly what matchsticks the little match girl has, please find out a way you can make one square by using up all those matchsticks. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.
//Your input will be several matchsticks the girl has, represented with their stick length. Your output will either be true or false, to represent whether you could make one square using all the matchsticks the little match girl has.
//Example 1:
//Input: [1,1,2,2,2]
//Output: true
//Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
//Example 2:
//Input: [3,3,3,3,4]
//Output: false
//Explanation: You cannot find a way to form a square with all the matchsticks.
//Note:
//The length sum of the given matchsticks is in the range of 0 to 10^9.
//The length of the given matchstick array will not exceed 15.

//Eg . {1,1,2,2,2} and if BM = {01100} = {1,2}
//0 : do not select matchstick
//1 : select the matchstick

//################################## backtracking + Bit mask ################################## 
bool makesquare(vector<int>& nums) {
    int n = nums.size();
    long sum = accumulate(nums.begin(), nums.end(), 0l);
    if (sum % 4)
        return false;
    long sideLen = sum / 4;
    // need to solve the problem of partitioning nums into four equal subsets each having
    // sum equal to sideLen
    vector<int> usedMasks;
    // validHalfSubsets[i] == true iff the subset represented by bitmask i
    // has sum == 2*sideLen, AND the subset represented by i can be further partitioned into
    // two equal subsets. See below for how it is used.
    vector<bool> validHalfSubsets(1<<n, false);

    // E.g., if n = 5, (1 << 5 - 1) = 11111 represents the whole set
    int all = (1 << n) - 1;
    // go through all possible subsets each represented by a bitmask
    for (int mask = 0; mask <= all; mask++) {
        long subsetSum = 0;
        // calculate the sum of this subset
        for (int i = 0; i < 32; i++) {
	    if ((mask >> i) & 1)
		subsetSum += nums[i];
        }
	// if this subset has what we want
	if (subsetSum == sideLen) {
	    for (int usedMask : usedMasks) {
	    // if this mask and usedMask are mutually exclusive
	        if ((usedMask & mask) == 0) {
		    // then they form a valid half subset whose sum is 2 * sideLen,
                    // that can be further partitioned into two equal subsets (usedMask and mask)
		    int validHalf = usedMask | mask;
		    validHalfSubsets[validHalf] = true;
		    // if in the past we concluded that the other half is also a valid
		    // half subset, DONE!
		    if (validHalfSubsets[all ^ validHalf])
		        return true;
	        }
            }
	    usedMasks.push_back(mask);
        }
    }
    return false;
}


//################################## Optimized backtracking ################################## 
//1. Each stick is used once if (sidesLength[i] + matches[k] > target) continue;
//2. Sort (descending order) // sort(nums.begin(), nums.end(), [](const int &l, const int &r){return l > r;});
//3. Check the length only once
    bool dfs(vector<int> &sidesLength,const vector<int> &matches, int index, const int target) {
        if (index == matches.size())
            return sidesLength[0] == sidesLength[1] && sidesLength[1] == sidesLength[2] && sidesLength[2] == sidesLength[3];
        for (int i = 0; i < 4; ++i) {
            if (sidesLength[i] + matches[index] > target) // first
                continue;
            int j = i;
            while (--j >= 0) // third
                if (sidesLength[i] == sidesLength[j]) 
                    break;
            if (j != -1) continue;
            sidesLength[i] += matches[index];
            if (dfs(sidesLength, matches, index + 1, target))
                return true;
            sidesLength[i] -= matches[index];
        }
        return false;
    }
public:
    bool makesquare(vector<int>& nums) {
        if (nums.size() < 4) return false;
        int sum = 0;
        for (const int val: nums) {
            sum += val;
        }
        if (sum % 4 != 0) return false; //not a square
        sort(nums.begin(), nums.end(), [](const int &l, const int &r){return l > r;}); // second
        vector<int> sidesLength(4, 0);
        return dfs(sidesLength, nums, 0, sum / 4);
    }

//######################### backtraking ######################### 
//square has a 4 sides T : O(4^n)
//NPC problem
class Solution {
    bool dfs(vector<int> &sidesLength,const vector<int> &matches, int k) {
        if (k == matches.size()) { //verify the sides after picking all the sticks
            return sidesLength[0] == sidesLength[1] && sidesLength[1] == sidesLength[2] && sidesLength[2] == sidesLength[3];
        }
        for (int i = 0; i < 4; ++i) { // n choose 4 : nC4
            sidesLength[i] += matches[k];
            if (dfs(sidesLength, matches, k + 1))
                return true;
            sidesLength[i] -= matches[k];
        }
        return false;
    }
public:
    bool makesquare(vector<int>& nums) {
        if (nums.empty()) return false;
        vector<int> sidesLength(4, 0);
        return dfs(sidesLength, nums, 0);
    }
};

//######################### DFS with min sum ######################### 

public:    
    bool makesquare(vector<int>& nums) {
      int sum;
      if (nums.size() < 4 || (sum = accumulate(nums.begin(), nums.end(), 0))%4) return false;
      return sortSmall(nums), dfs(nums.begin(), vector<int>(4,sum/4));
    }
private: // helpers   
    // sort nums descendingly and calculate 4 smallest subsums
    void sortSmall(vector<int>& nums) {
      sort(nums.rbegin(), nums.rend());
      small = { *((e=nums.end())-1), *(e-2), min(*(e-1)+*(e-2),*(e-3)), 
                min(max(*(e-1)+*(e-2),*(e-3)),*(e-4)) };
    }

    // check if can partition into subsums {s[j]} starting at nums[i]
    bool dfs(vector<int>::iterator i, const vector<int>& s) {
      if (i == e) return true;
      // check min condition
      for (int j = 0; j < s.size(); ++j) if (small[j] > s[j]) return false; 
      for (int j = 0; j < s.size(); ++j) {        
        if (s[j] < *i || j && s[j] == s[j-1]) continue;
        // build unique valid subsums
        vector<int> ss(s); if (!(ss[j] -= *i)) ss.erase(ss.begin()+j);
        if (sort(ss.begin(),ss.end()), dfs(i+1, ss)) return true;
      }
      return false;
    }
    
    vector<int>::iterator e; // end of nums sorted descendingly
    vector<int> small = vector<int>(4); // 4 smallest subsums

//############### NAive DFS  ###################### 
public boolean makesquare(int[] nums) {
    if (nums.length < 4) return false;
        
    int perimeter = 0;
    for (int ele : nums) perimeter += ele;
    if (perimeter % 4 != 0) return false;
    
    int side = perimeter / 4;

    return makesquareSub(nums, nums.length - 1, new int[] {side, side, side, side});
}

private boolean makesquareSub(int[] nums, int i, int[] s) {
    if (i < 0) return s[0] == 0 && s[1] == 0 && s[2] == 0 && s[3] == 0;
        
    for (int j = 0; j < s.length; j++) {
        if (nums[i] > s[j]) continue;
        s[j] -= nums[i];
        if (makesquareSub(nums, i - 1, s)) return true;
        s[j] += nums[i];
    }
        
    return false;
}
//###################### DFS + sort ###################### 

public boolean makesquare(int[] nums) {
    if (nums.length < 4) return false;
        
    int perimeter = 0;
    for (int ele : nums) perimeter += ele;
    if (perimeter % 4 != 0) return false;
        
    Arrays.sort(nums);
    int side = perimeter / 4;

    return makesquareSub(nums, nums.length - 1, new int[] {side, side, side, side});
}
    
private boolean makesquareSub(int[] nums, int i, int[] s) {
    if (i < 0) return s[0] == 0 && s[1] == 0 && s[2] == 0 && s[3] == 0;
        
    for (int j = 0; j < s.length; j++) {
        if (nums[i] > s[j]) continue;
        s[j] -= nums[i];
        if (makesquareSub(nums, i - 1, s)) return true;
        s[j] += nums[i];
    }
        
    return false;
}
