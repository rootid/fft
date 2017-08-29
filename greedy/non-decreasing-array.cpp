//Non-decreasing Array
//Given an array with n integers, your task is to check if it could become non-decreasing by modifying at most 1 element.
//We define an array is non-decreasing if array[i] <= array[i + 1] holds for every i (1 <= i < n).
//Example 1:
//Input: [4,2,3]
//Output: True
//Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
//Example 2:
//Input: [4,2,1]
//Output: False
//Explanation: You can't get a non-decreasing array by modify at most one element.
//Note: The n belongs to [1, 10,000].

//################################################### Greedy O(n) ################################################### 
//Always update the last element in the array based on the compare result.
//
//When you find nums[i-1] > nums[i] for some i,
//you will prefer to change nums[i-1]'s value, since a larger nums[i] will give you more risks that you get inversion errors after position i.
//But, if you also find nums[i-2] > nums[i],
//then you have to change nums[i]'s value instead,
//or else you need to change both of nums[i-2]'s and nums[i-1]'s values.
public boolean checkPossibility(int[] nums) {
	int cnt = 0;                                                                    //the number of changes
    for(int i = 1; i < nums.length && cnt<=1 ; i++){
        if(nums[i-1] > nums[i]) { //decreasing order
            cnt++;
			//(check for the last compare result (nums[i-2],nums[i])
            if(i-2< 0 || nums[i-2] <= nums[i]) {
				nums[i-1] = nums[i];                    //modify nums[i-1] of a priority 
			}
            else { 
				nums[i] = nums[i-1];                                                //have to modify nums[i]
			}
        }
    }
    return cnt<=1; 
}
