//3Sum Smaller
//Given an array of n integers nums and a target, find the number of index
//triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] +
//nums[j] + nums[k] < target.
//For example, given nums = [-2, 0, 1, 3], and target = 2.
//Return 2. Because there are two triplets which sums are less than 2:
//[-2, 0, 1]
//[-2, 0, 3]
//

#include<iostream>
#include<vector>
using namespace std;

//######################################### Binary search #########################################
//TC : O(n^2 log n)
//SC : O(1)
public int threeSumSmaller(int[] nums, int target) {
    Arrays.sort(nums);
    int sum = 0;
    for (int i = 0; i < nums.length - 2; i++) {
        sum += twoSumSmaller(nums, i + 1, target - nums[i]);
    }
    return sum;
}

private int twoSumSmaller(int[] nums, int startIndex, int target) {
    int sum = 0;
    for (int i = startIndex; i < nums.length - 1; i++) {
        int j = binarySearch(nums, i, target - nums[i]);
        sum += j - i;
    }
    return sum;
}

private int binarySearch(int[] nums, int startIndex, int target) {
    int left = startIndex;
    int right = nums.length - 1;
    while (left < right) {
        int mid = (left + right + 1) / 2;
        if (nums[mid] < target) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

//######################################### 2 pointer #########################################
//TC : O(n^2)
//SC : O(1)
public int threeSumSmaller(int[] nums, int target) {
    Arrays.sort(nums);
    int sum = 0;
    for (int i = 0; i < nums.length - 2; i++) {
        sum += twoSumSmaller(nums, i + 1, target - nums[i]);
    }
    return sum;
}

private int twoSumSmaller(int[] nums, int startIndex, int target) {
    int sum = 0;
    int left = startIndex;
    int right = nums.length - 1;
    while (left < right) {
        if (nums[left] + nums[right] < target) {
            sum += right - left;
            left++;
        } else {
            right--;
        }
    }
    return sum;
}

//######################################### iteration  #########################################
//T : O(n^2)
public class Solution {
    int count;
    public int threeSumSmaller(int[] nums, int target) {
        count = 0;
        Arrays.sort(nums);
        int len = nums.length;
        for(int i=0; i<len-2; i++) {
            int left = i+1, right = len-1;
            while(left < right) {
                if(nums[i] + nums[left] + nums[right] < target) {
                    count += right-left;
                    left++;
                } else {
                    right--;
                }
            }
        }

        return count;
    }
}

//######################################### iteration  #########################################
//T : O(n^2)
public class Solution {
    public int threeSumSmaller(int[] nums, int target) {
        int n = nums.length, cnt = 0;
        Arrays.sort(nums);
        for (int i = 0; i < n - 2 && nums[i] * 3 < target; i++)
            for (int l = i + 1, r = n - 1; l < r;)
                if (nums[i] + nums[l] + nums[r] < target)
                    cnt += r - l++; //all r in (l, r] will also satisfy the condition
                else
                    r--;
        return cnt;
    }
}


//######################################### iteration  #########################################
int threeSumSmaller(vector<int>& nums, int target) {

  int len = nums.size();
  if(len < 3) {
    return 0;
  }
  int cnt = 0;
  for(int i=0;i<len-2;i++) {
    int left = i + 1;
    int right = len -1;
    while(left < right) {
      int sum_ = nums[i] + nums[left] + nums[right];
      if(sum_ < target) {
        cnt += (right-left); //count all the digits where sum < target
        left += 1;
      } else {
        right -= 1;
      }
    }
  }
 return cnt;
}

int main() {

}

