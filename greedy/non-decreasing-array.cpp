//Non-decreasing Array
//Given an array with n integers, your task is to check if it could become
//non-decreasing by modifying at most 1 element.
//We define an array is non-decreasing if array[i] <= array[i + 1] holds for
//every i (1 <= i < n).
//Example 1:
//Input: [4,2,3]
//Output: True
//Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
//Example 2:
//Input: [4,2,1]
//Output: False
//Explanation: You can't get a non-decreasing array by modify at most one
//element.
//Note: The n belongs to [1, 10,000].


//######################################### Count inversion #########################################
//first find any inversions, and if the number of inversions is > 1, then we
//need to modify more than 1 element and hence we return False.
//Once we find an inversion,
//We have to fix either the current value or the next value appropriately so
//that any future inversions can be detected correctly.
def checkPossibility(self, nums):
    count_dec = 0
    for i in range(len(nums) - 1):
        if nums[i] > nums[i + 1]:
            count_dec += 1
            if i == 0:
                nums[i] = nums[i + 1]
            elif nums[i - 1] <= nums[i + 1]:
                nums[i] = nums[i - 1]
            else:
                nums[i + 1] = nums[i]
        if count_dec > 1:
            return False
    return True



//######################################### Input modification n#########################################
//2 Examples:
// 0  ...  i ...
// 1 1 2 4[2]5 6  - in this case we can just raise a[i] to 4;
//         4
// 1 1 2[4]2 3 4  - in this case lower a[i-1] is better;
//       2
//
//lower a[i-1] to match a[i] if possible - (a[i-2] not exist or no smaller than
//a[i]);
//otherwise rise a[i] to match a[i-1].
class Solution {
    public boolean checkPossibility(int[] a) {
        int modified = 0;
        for (int i = 1; i < a.length; i++) {
            if (a[i] < a[i - 1]) {
                if (modified++ > 0) return false;
                if (i - 2 < 0 || a[i - 2] <= a[i]) a[i - 1] = a[i]; // lower a[i - 1]
                else a[i] = a[i - 1]; // rise a[i]
            }
        }
        return true;
    }
}

//######################################### No input modification n#########################################
class Solution {
    public boolean checkPossibility(int[] a) {
        int modified = 0;
        for (int i = 1, prev = a[0]; i < a.length; i++) {
            if (a[i] < prev) {
                if (modified++ > 0) return false;
                if (i - 2 >= 0 && a[i - 2] > a[i]) continue;
            }
            prev = a[i];
        }
        return true;
    }
}

//################################################### Greedy O(n) ###################################################
//Always update the last element in the array based on the compare result.
//
//When you find nums[i-1] > nums[i] for some i,
//you will prefer to change nums[i-1]'s value, since a larger nums[i] will give
//you more risks that you get inversion errors after position i.
//But, if you also find nums[i-2] > nums[i],
//then you have to change nums[i]'s value instead,
//or else you need to change both of nums[i-2]'s and nums[i-1]'s values.
public boolean checkPossibility(int[] nums) {
		int cnt = 0;                                                                    //the number of changes
        for(int i = 1; i < nums.length && cnt<=1 ; i++){
            if(nums[i-1] > nums[i]){
                cnt++;
                if(i-2<0 || nums[i-2] <= nums[i])nums[i-1] = nums[i];                    //modify nums[i-1] of a priority
                else nums[i] = nums[i-1];                                                //have to modify nums[i]
            }
        }
        return cnt<=1;
}

//################################################### Greedy O(n) ###################################################
public boolean checkPossibility(int[] nums) {
    int n = nums.length, count = 0;
    for (int i = 0; i + 1 < n; i++) {
        if (nums[i] > nums[i + 1]) {
            count++;
            if (i > 0 && nums[i + 1] < nums[i - 1]) nums[i + 1] = nums[i];
            else nums[i] = nums[i + 1];
        }
    }

    return count <= 1;
}

//######################################### Greedy #########################################
//First, find a pair where the order is wrong.
//Then there are two possibilities, either the first in the pair can be
//modified
//or the second can be modified to create a valid sequence.
//We simply modify both of them and check for validity of the modified arrays
//by comparing with the array after sorting.
class Solution(object):
    def checkPossibility(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        one, two = nums[:], nums[:]
        for i in range(len(nums) - 1):
            if nums[i] > nums[i + 1]:
                one[i] = nums[i + 1]
                two[i + 1] = nums[i]
                break
        return one == sorted(one) or two == sorted(two)

