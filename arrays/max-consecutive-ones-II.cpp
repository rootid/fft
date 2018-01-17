//Max Consecutive Ones II
//Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most one 0.
//Example 1:
//Input: [1,0,1,1,0]
//Output: 4
//Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
//    After flipping, the maximum number of consecutive 1s is 4.
//Note:
//The input array will only contain 0 and 1.
//The length of input array is a positive integer and will not exceed 10,000
//

//######################################## 2-pointer Avg Case T: O(n) s: O(1) ######################################## 
public int findMaxConsecutiveOnes(int[] nums) {
    int max = 0, q = -1;
    for (int l = 0, h = 0; h < nums.length; h++) {
        if (nums[h] == 0) {
            l = q + 1;
            q = h;
        }
        max = Math.max(max, h - l + 1);
    }                                                               
    return max;             
}


//######################################## 2-pointer Avg Case T: O(n) s: O(1) ######################################## 
public int findMaxConsecutiveOnes(int[] nums) {
     int maxConsecutive = 0, zeroLeft = 0, zeroRight = 0;
     for (int i=0;i<nums.length;i++) {
         zeroRight++;
         if (nums[i] == 0) {
             zeroLeft = zeroRight;
             zeroRight = 0;
         }
         maxConsecutive = Math.max(maxConsecutive, zeroLeft+zeroRight); 
     }
     return maxConsecutive;
}

//######################################## 2-pointer + case when streaming input Avg Case T: O(n) s: O(1) ######################################## 
class ConOnes {
private:
  int right, left, maxL;
public:
  ConOnes() :right(0), left(0), maxL(0) {}
  int readNext(int digit) { 
	  return maxL = max(maxL, digit? ++right : left = (++right -= left)); 
  }
};


//######################################## 2-pointer generalized solution for K Avg Case T: O(n) s: O(1) ######################################## 
//Worst case : O(n^2)
//keep a window [l, right] that contains at most k zero
public int findMaxConsecutiveOnes(int[] nums) { 
	int max = 0, zero = 0, k = 1; // flip at most k zero
    for (int l = 0, right = 0; right < nums.length; right++) {
        if (nums[right] == 0) {
            zero++;
		}
        while (zero > k) {
			if (nums[l++] == 0) {
				zero--; 
			}
		}
        max = Math.max(max, right - l + 1);
    }                                                               
    return max;             
}
//######################################## 2-pointer generalized solution for K Avg Case T: O(n) s: O(K) ######################################## 
//Store up to k indexes of zero within the window [l, h] so that we know where to move l next when the window contains more than k zero. 
//If the input stream is infinite, then the output could be extremely large because there could be super long consecutive ones. 
//In that case we can use BigInteger for all indexes. For simplicity, here we will use int
//Time: O(n) Space: O(k)
 public int findMaxConsecutiveOnes(int[] nums) {                 
     int max = 0, k = 1; // flip at most k zero
     Queue<Integer> zeroIndex = new LinkedList<>(); 
     for (int l = 0, h = 0; h < nums.length; h++) {
         if (nums[h] == 0)
             zeroIndex.offer(h);
         if (zeroIndex.size() > k)                                   
             l = zeroIndex.poll() + 1;
         max = Math.max(max, h - l + 1);
     }
     return max;                     
}


//########################################  python  ######################################## 
//########################################  Avg Case T: O(n) s: O(K) ######################################## 
class Solution(object):
    def findMaxConsecutiveOnes(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        maximum, seqLen, lastZero = 0, 0, -1
        for i, n in enumerate(nums):
            if n == 1:
                seqLen += 1
            else:
                seqLen = i - lastZero
                lastZero = i
            maximum = max(maximum, seqLen)
        return maximum
