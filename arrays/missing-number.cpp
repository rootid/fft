// Missing Number
//Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.
//For example,
//Given nums = [0, 1, 3] return 2.
//Note:
//Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?
//[1,0] return 2
//

//############################### 1.swapping number solution ############################### 
public int MissingNumber(int[] nums) {
    for(int i = 0; i < nums.Length; i++) {
        while(i < nums.Length && nums[i] == i) i++;
        while(i < nums.Length && nums[i] != i) { //when idx != nums[idx]
            if(nums[i] >= nums.Length || nums[i] < 0) break;
            nums[i] = nums[i] ^ nums[nums[i]] ^ (nums[nums[i]] = nums[i]); //nums, i , nums[i]
        }
    }
    for(int i = 0; i < nums.Length; i++)
        if(nums[i] != i) return i;
    return nums.Length;
}

//###############################1.2 Another swapping solution by avoiding the 2nd loop. Idea from novostary.###############################
public int MissingNumber(int[] nums) {
    int lastIndex = nums.Length;
    for(int i = 0; i < nums.Length; )
        if(nums[i] == i) i++;
        else if(nums[i] < nums.Length)
            nums[i] = nums[i] ^ nums[nums[i]] ^ (nums[nums[i]] = nums[i]);
        else lastIndex = i++;
    return lastIndex;
}
//###############################2.Bitwise operation solutio###############################n
public int MissingNumber(int[] nums) {
    int xorResult = 0;
    for(int i = 0; i < nums.Length; i++)
        xorResult ^= nums[i] ^ i;
    xorResult ^= nums.Length;
    return xorResult;
}

int missingNumber(vector<int>& nums) {
    int res  = nums.size();
    for(int i=0;i<nums.size();i++) {
        res ^= i+1; //(0,1)
        res ^= nums[i]; //(1,0)
    }
    return res;
}
