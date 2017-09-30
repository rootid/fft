//Split Array into Consecutive Subsequences
//You are given an integer array sorted in ascending order (may contain duplicates), you need to split them into several subsequences, where each subsequences consist of at least 3 consecutive integers. Return whether you can make such a split.
//Example 1:
//Input: [1,2,3,3,4,5]
//Output: True
//Explanation:
//You can split them into two consecutive subsequences : 
//1, 2, 3
//3, 4, 5
//Example 2:
//Input: [1,2,3,3,4,4,5,5]
//Output: True
//Explanation:
//You can split them into two consecutive subsequences : 
//1, 2, 3, 4, 5
//3, 4, 5
//Example 3:
//Input: [1,2,3,4,4,5]
//Output: False
//Note:
//The length of the input is in range of [1, 10000]
//1. We iterate through the array once to get the frequency of all the elements in the array
//2. We iterate through the array once more and for each element we either see if it can be appended to a previously constructed consecutive sequence or if it can be the start of a new consecutive sequence. If neither are true, then we return false.
//#########################################  O(n) #########################################  
public boolean isPossible(int[] nums) {
    Map<Integer, Integer> freq = new HashMap<>(), appendfreq = new HashMap<>();
    for (int i : nums) freq.put(i, freq.getOrDefault(i,0) + 1);
    for (int i : nums) {
        if (freq.get(i) == 0) continue;
        else if (appendfreq.getOrDefault(i,0) > 0) {
            appendfreq.put(i, appendfreq.get(i) - 1);
            appendfreq.put(i+1, appendfreq.getOrDefault(i+1,0) + 1);
        }   
        else if (freq.getOrDefault(i+1,0) > 0 && freq.getOrDefault(i+2,0) > 0) {
            freq.put(i+1, freq.get(i+1) - 1);
            freq.put(i+2, freq.get(i+2) - 1);
            appendfreq.put(i+3, appendfreq.getOrDefault(i+3,0) + 1);
        }
        else return false;
        freq.put(i, freq.get(i) - 1);
    }
    return true;
}
//#########################################  O(n) #########################################  
bool isPossible(vector<int>& nums) {
    unordered_map<int, int> f, a;
    for (int i : nums) f[i]++;
    for (int i : nums)
        if (f[i] && f[i]-- && !(a[i] && a[i]-- && ++a[i+1]) && !(f[i+1]-- && f[i+2]-- && ++a[i+3]))
            return false;
    return true;
}
//The basic idea is that, for each distinct element ele in the input array, we only need to maintain three pieces of information: the number of consecutive subsequences ending at ele with length of 1, length of 2 and length >= 3.
//The input array will be scanned linearly from left to right. Let cur be the element currently being examined and cnt as its number of appearance. pre is the element processed immediately before cur. The number of consecutive subsequences ending at pre with length of 1, length of 2 and length >= 3 are denoted as p1, p2 and p3, respectively. There are two cases in general:
//cur != pre + 1: for this case, cur cannot be added to any consecutive subsequences ending at pre, therefore, we must have p1 == 0 && p2 == 0; otherwise the input array cannot be split into consecutive subsequences of length >= 3. Now let c1, c2, c3 be the number of consecutive subsequences ending at cur with length of 1, length of 2 and length >= 3, respectively, we will have c1 = cnt, c2 = 0, c3 = 0, which means we only have consecutive subsequence ending at cur with length of 1 and its number given by cnt.
//cur == pre + 1: for this case, cur can be added to consecutive subsequences ending at pre and thus extend those subsequences. But priorities should be given to those with length of 1 first, then length of 2 and lastly length >= 3. Also we must have cnt >= p1 + p2; otherwise the input array cannot be split into consecutive subsequences of length >= 3. Again let c1, c2, c3 be the number of consecutive subsequences ending at cur with length of 1, length of 2 and length >= 3, respectively, we will have: c2 = p1, c3 = p2 + min(p3, cnt - (p1 + p2)), c1 = max(cnt - (p1 + p2 + p3), 0). The meaning is as follows: first adding cur to the end of subsequences of length 1 will make them subsequences of length 2, and we have p1 such subsequences, therefore c2 = p1. Then adding cur to the end of subsequences of length 2 will make them subsequences of length 3, and we have p2 such subsequences, therefore c3 is at least p2. If cnt > p1 + p2, we can add the remaining cur to the end of subsequences of length >= 3 to make them even longer subsequences. The number of such subsequences is the smaller one of p3 and cnt - (p1 + p2). In total, c3 = p2 + min(p3, cnt - (p1 + p2)). If cnt > p1 + p2 + p3, then we still have remaining cur that cannot be added to any subsequences. These residue cur will form subsequences of length 1, hence c1 = max(cnt - (p1 + p2 + p3), 0).
//For either case, we need to update: pre = cur, p1 = c1, p2 = c2, p3 = c3 after processing the current element. When all the elements are done, we check the values of p1 and p2. The input array can be split into consecutive subsequences of length >= 3 if and only if p1 == 0 && p2 == 0.
//Here is the O(n) time and O(1) space Java solution:
//#########################################  O(n) #########################################  
public boolean isPossible(int[] nums) {
    int pre = Integer.MIN_VALUE, p1 = 0, p2 = 0, p3 = 0;
    int cur = 0, cnt = 0, c1 = 0, c2 = 0, c3 = 0;
    for (int i = 0; i < nums.length; pre = cur, p1 = c1, p2 = c2, p3 = c3) {
        for (cur = nums[i], cnt = 0; i < nums.length && cur == nums[i]; cnt++, i++);
        if (cur != pre + 1) {
            if (p1 != 0 || p2 != 0) return false;
            c1 = cnt; c2 = 0; c3 = 0;
        } else {
            if (cnt < p1 + p2) return false;
            c1 = Math.max(0, cnt - (p1 + p2 + p3));
            c2 = p1;
            c3 = p2 + Math.min(p3, cnt - (p1 + p2));
        }
    }
    return p1 == 0 && p2 == 0;
}
//######################################### Greedy  #########################################  
def isPossible(self, nums):
    """
    :type nums: List[int]
    :rtype: bool
    """
    chains = {}
    for x in nums:
        #count of chains end with x and having length 0,1,2,3+
        pre = chains.setdefault(x-1, [0,0,0,0])
        cur = chains.setdefault(x, [0,0,0,0])
        #add x to the shortest chain
        if pre[1] > 0:
            pre[1] -= 1
            cur[2] += 1
        elif pre[2] > 0:
            pre[2] -= 1
            cur[3] += 1
        elif pre[3] > 0:
            pre[3] -= 1
            cur[3] += 1
        else:
            cur[1] += 1
    for x in chains:
        if chains[x][1] or chains[x][2]:
            return False
    return True

//######################################### Greedy ######################################### 
//Maintain a set of consecutive sequences, call this set s. s begins as an empty set of consecutive sequences.
//Now, iterate through each num in nums. For each iteration, if there exists a consecutive sequence in s that ends with element num-1, then append num to the end of the shortest such sequence; otherwise, create a new sequence that begins with num.
//The problem has a solution (i.e. the array can be split into consecutive subsequences such that each subsequence consists of at least 3 consecutive integers) if and only if each sequence in s has size greater than or equal to 3.
//Proof of Algorithm
//Why does this algorithm work? It was intuitive to me, but I could not indisputably prove that it was correct. Hopefully, someone else can prove it.
//Implementation
//We don't need to actually store each sequence. Instead, we just need to know (1) the number of sequences that end at a particular element, and (2) the size of each of those sequences. To implement this, we can have an unordered map backs to represent the sequences: backs[key] returns a priority queue (smallest value at top) of the sizes of all sequences that end with element key. Now that we have (1) and (2), we can implement the algorithm above without knowing each particular sequence.
//For each num in nums, if there exists any sequence that ends with num-1 (i.e. if backs[num-1] is a non-empty priority queue), then find such a sequence with the smallest possible size (get the smallest value from the priority queue at backs[num-1]). Now, the sequence will be extended by 1 since we will add num to it. So pop the smallest value count from the priority queue at backs[num-1], and add a new value count+1 to the priority queue at backs[num].
//If no sequence was found that ends in num-1 (i.e. backs[num-1] is empty), then create a new sequence. In other words, add 1 to the priority queue at backs[num].

bool isPossible(vector<int>& nums) {
		unordered_map<int, priority_queue<int, vector<int>, std::greater<int>>> backs;
		// Keep track of the number of sequences with size < 3
		int need_more = 0;
		for (int num : nums) {
			if (! backs[num - 1].empty()) {	// There exists a sequence that ends in num-1
				// Append 'num' to this sequence
				// Remove the existing sequence
				// Add a new sequence ending in 'num' with size incremented by 1 
				int count = backs[num - 1].top();
				backs[num - 1].pop();
				backs[num].push(++count);
				if (count == 3)
					need_more--;
			}
			else
			{	// There is no sequence that ends in num-1
				// Create a new sequence with size 1 that ends with 'num'
				backs[num].push(1);
				need_more++;
			}
		}
		return need_more == 0;
	}

//############################################### NO DP ###################################
public class Solution {
    public boolean isPossible(int[] nums) {
        int base = nums[0];
        for (int i = 0; i < nums.length; i++){
            nums[i] = nums[i] - base;
        }
        int[] fre = new int[nums[nums.length - 1] + 3];
        for (int n : nums) fre[n]++;
        for (int i = 2; i <= nums[nums.length - 1] + 2; i++){
            int one = Math.max(fre[i - 1] - fre[i - 2], 0);
            int two = Math.max(0, fre[i - 2] - (i >= 3 ? fre[i - 3] : 0));
            if (fre[i] < one + two || fre[i - 1] < two){
                return false;
            }
        }
        return true;
    }
}

//######################################### DP  ######################################### 
//I feel this problem hard. The idea here is DP.
//If numbers are not continuous, I check each segment. For example, 1,2,3,3,4,5, 9,10,11;
//Count frequency of each continuous number. Note the value of numbers doesn't matter.
//DP part. I use parameter "ones" for subsequences with length 1 ending with index i, "twos" for subsequences with length 2 ending with index i, and "tot" for all subsequences ending with index i.
//When processing next number, if the frequency of new number mp[i+1] < ones+twos, there is no way to split, return false.
//In a greedy way, we need append the new number to short sequences first. So
//twos[i+1] = ones[i];
//ones[i+1] = mp[i+1]-tot, i.e. the extra new number
//If it is possible to split, ones and twos would be 0 by the end of the loop.
//The run time is clearly O(n).
class Solution {
public:
    bool isPossible(vector<int>& nums) {
        int n = nums.size(), k = 0;
        //if nums are not continuous, check each section
        //for example, 1,2,3, 6,7,8;
        for (int i = 1; i < n; i++) {
            if (nums[i]-nums[i-1] > 1) {
                if (!check(nums, k, i-1)) 
                    return false;
                k = i;
            }
        }
        return check(nums, k, n-1);
    }
private:
    bool check(vector<int>& nums, int s, int e) {
        int n = nums[e]-nums[s]+1;
        // count frequency of each number
        vector<int> mp(n, 0);
        for (int i = s, tmp = nums[s]; i <= e; i++)
            mp[nums[i]-tmp]++;
        // ones is subsequences with length 1 ending with index i-1
        // twos is subsequences with length 2 ending with index i-1
        // tot  is all subsequences ending with index i-1
        // initially ones[0] ending with index -1, i.e. nonexistent 
        vector<int> ones(n+1, 0), twos(n+1, 0), tot(n+1, 0);
        for (int i = 0; i < n; i++) {
            // we need at least ones+twos new number to make consecutive sequence
            // for examle, two 2, five 1,2, we need at least seven 3
            if (mp[i] < ones[i] + twos[i]) return false;
            // Greedy, appending to short sequences first
            // so twos = ones, and new ones is the extra new number
            twos[i+1] = ones[i];
            ones[i+1] = max(0, mp[i]-tot[i]);
            tot[i+1] = mp[i];
        }
        // if no subsequence length <= 2, return true
        return ones[n] == 0 && twos[n] == 0;
    }
};
