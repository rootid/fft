//Split Array with Equal Sum
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

//################################################### Brute Force ###################################################
//TC : O(N^4)
//SC : O(1)
//Algorithm
//Before we start looking at any of the approaches for solving this problem, firstly we need to look at the limits imposed on iii, jjj and kkk by the given set of constraints. The figure below shows the maximum and minimum values that iii, jjj and kkk can assume.
//Split_Array
//Thus, the limits based on the length of the array nnn can now be rewritten as:
//1≤i≤n−6
//i+2≤j≤n−4
//j+2≤k≤n−2
//Having discussed the limits imposed on the cuts iii, jjj, kkk that we will apply on the given array numsnumsnums, let's look at the first solution that comes to our mind.
//We simply traverse over all the elements of the array. We consider all the possible subarrays taking care of the constraints imposed on the cuts, and check if any such cuts exist which satisfy the given equal sum quadruples criteria.
public class Solution {

    public int sum(int[] nums, int l, int r) {
        int summ = 0;
        for (int i = l; i < r; i++)
            summ += nums[i];
        return summ;
    }

    public boolean splitArray(int[] nums) {
        if (nums.length < 7)
            return false;
        for (int i = 1; i < nums.length - 5; i++) {
            int sum1 = sum(nums, 0, i);
            for (int j = i + 2; j < nums.length - 3; j++) {
                int sum2 = sum(nums, i + 1, j);
                for (int k = j + 2; k < nums.length - 1; k++) {
                    int sum3 = sum(nums, j + 1, k);
                    int sum4 = sum(nums, k + 1, nums.length);
                    if (sum1 == sum2 && sum3 == sum4 && sum2 == sum4)
                        return true;
                }
            }
        }
        return false;
    }
}

//################################################### O(N^2) ###################################################
//L ------------- sum(0, i - 1) = sum(0, 0) = 1
//L------------- sum(i + 1, j - 1) = sum(2, 2) = 1
//
//R------------- sum(j + 1, k - 1) = sum(4, 4) = 1
//R------------- sum(k + 1, n - 1) = sum(6, 6) = 1
// j is used for middle cut, i for left cut and k for right cut.
// 0 ->>>>>>> j  <<<<<<<<<<- n-1
//	  i--j-1--j--j+2-----n-1
//
//Here j is used for middle cut, i for left cut and k for right cut.
//Iterate middle cuts and then find left cuts which divides the first half into two equal quarters,
//store that quarter sums in the hashset.
//Then find right cuts which divides the second half into two equal quarters and check if quarter sum is present in the hashset. If yes return true.
public boolean splitArray(int[] nums) {
	if (nums.length < 7)
		return false;
    int[] sum = new int[nums.length];
    sum[0] = nums[0];
    for (int i = 1; i < nums.length; i++) {
        sum[i] = sum[i - 1] + nums[i]; //store sum from i = o to n
    }
    for (int j = 3; j < nums.length - 3; j++) {
        HashSet < Integer > set = new HashSet < > ();
        for (int i = 1; i < j - 1; i++) {
            if (sum[i - 1] == sum[j - 1] - sum[i]) //(0,i-1) == (i+1,j-1) -- I
                set.add(sum[i - 1]);
        }
        for (int k = j + 2; k < nums.length - 1; k++) { //why not k = j+1
            if (sum[nums.length - 1] - sum[k] == sum[k - 1] - sum[j] && set.contains(sum[k - 1] - sum[j])) //(k+1,n-1) = (j+1,k-1) && ( (j+1,k-1) == I )
                return true;
        }
    }
    return false;
  }
}



//################################################### Backtracking ###################################################
//O(n^3)
//Just think this problem as a DFS. What we need is to search for 3 positions (i, j, k)
//and see if they divide the array to 4 parts with same summary. Some tricks:
//Calculate left on the fly. Thus at last we don't need to calc summary of the 4th part.
//Skip 0 during calculate target because adding zero won't change it.
public class Solution {
    public boolean splitArray(int[] nums) {
        int sum = 0, target = 0;
        for (int num : nums) sum += num;
        for (int i = 1; i + 5 < nums.length; i++) {
            if (i != 1 && nums[i - 1] == 0  && nums[i] == 0) continue;
            target += nums[i - 1];
            if (dfs(nums, i + 1, target, sum - target - nums[i], 1)) return true;
        }
        return false;
    }

    private boolean dfs(int[] nums, int start, int target, int left, int depth) {
        if (depth == 3) {
            if (left == target) return true;
            return false;
        }

        int sub = 0;
        for (int j = start + 1; j + 5 - depth * 2 < nums.length; j++) {
            sub += nums[j - 1];
            if (sub == target) {
                if (dfs(nums, j + 1, target, left - sub - nums[j], depth + 1)) {
                    return true;
                }
            }
        }

        return false;
    }
}

//################################################### python ###################################################
//Let A be the array. As in most problems involving querying the sum of contiguous elements of an array,
//let P[x] = sum(A[:x]) be the prefix sums of A, which can be found in linear time.
//Then the sums in question are P[i] = P[j] - P[i+1] = P[k] - P[j+1] = P[-1] - P[k+1].
//For every j < k, P[i] = P[-1] - P[k+1] is a necessary requirement to choose i,
//so let's iterate over those indices first. This gives us the advantage that since we are iterating over a sorted list of candidate indices i, we can break when i >= j.
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


//#########################################  Divide and Conquer #########################################
//First, for every middle point j, we split nums into two subarray nums[:j] and nums[j+1:].
//In the helper function split, try to remove one element from the subarray,
//if the the sums of two remaining left and right sub-subarray are equal, we keep the sum of sub-subarray in the set we return.
//Once we have any intersection between the two sets, we know we can make it.
//Keep in mind len(nums) > 6 is a must since we need to split original array into four parts.
//like divide and conquer (only twice though).
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

//#########################################  Divide and Conquer + Optimized #########################################
def splitArray(self, nums):
        n = len(nums)
        s = [0] * (n + 1)
        for i in range(n): s[i + 1] = s[i] + nums[i]
        def check(l, r):
            return set(s[m] - s[l] for m in range(l + 1, r + 1) if s[m] - s[l] == s[r + 1] - s[m + 1])
        return any(check(0, j - 1) & check(j + 1, n - 1) for j in range(n))


//################################################### CPP version  ###################################################
class Solution {
public:
    bool splitArray(vector<int>& nums) {
        vector<int> sms;
        sms.push_back(0);
        int N = nums.size();

        for(auto i : nums) {
            sms.push_back(sms[sms.size()-1] + i);

        }

        unordered_map<int, vector<int>> hsh;

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
};

//################################################### O(n^3) ###################################################
class Solution {
public:
    bool splitArray(vector<int>& nums) {
        vector<int> sum;
        int prev = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0 && i > 0 && nums[i - 1] == 0)  continue; // skip extra 0s to accelerate
            prev += nums[i];
            sum.push_back(prev);
        }

        int n = sum.size();
        for (int i = 1; i < n; i++) {
            int sum1 = sum[i - 1];
            for (int j = i + 2; j < n - 3; j++) {
                int sum2 = sum[j - 1] - sum[i];
                if (sum2 != sum1) continue;
                for (int k = j + 2; k < n - 1; k++) {
                    int sum3 = sum[k - 1] - sum[j];
                    int sum4 = sum[n - 1] - sum[k];
                    if (sum2 == sum3 && sum3 == sum4) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};
