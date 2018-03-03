//Find the Duplicate Number
//Given an array nums containing n + 1 integers where each integer is between 1
//and n (inclusive), prove that at least one duplicate number must exist.
//Assume that there is only one duplicate number, find the duplicate one.
//Note:
//You must not modify the array (assume the array is read only).
//You must use only constant, O(1) extra space.
//Your runtime complexity should be less than O(n2).
//There is only one duplicate number in the array, but it could be repeated
//more than once

//Step 1:
//The array's indices are in [0, n]. The array's values are in [1, n]. This
//means nums[0] will lead us to an index that is in [1, n] (because nums[0] is
//a value). But nobody will lead us back to index 0 (because everyone's value
//is in [1, n] not including 0).
//Step 2:
//Starting from index 0, we can definitely reach a cycle. Why? By
//contradiction. If we cannot reach a cycle, that is to say, we always meet a
//new index, and then meet a new index, but there are only finite number of
//indices. So we will reach a cycle.
//Step 3:
//Then this cycle's entrace's index must be one duplicated number (because two
//guys lead us to it).
//Step 4:
//Since there is only one duplicated number, then that's it.

int findDuplicate3(vector<int>& nums) {
	if (nums.size() > 1) {
		int slow = nums[0];
		int fast = nums[nums[0]];
		while (slow != fast) {
			slow = nums[slow];
			fast = nums[nums[fast]];
		}
		fast = 0;
		while (fast != slow) {
			fast = nums[fast];
			slow = nums[slow];
		}
		return slow;
	}
	return -1;
}
