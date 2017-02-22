//Jump Game
//Given an array of non-negative integers, you are initially positioned at the first index of the array.
//Each element in the array represents your maximum jump length at that position.
//Determine if you are able to reach the last index.
//For example:
//A = [2,3,1,1,4], return true.
//A = [3,2,1,0,4], return false.

//iterate and update the maximal index that can reached
//###################################   ################################### 
bool canJump(vector<int>& nums) {
    int len = nums.size();
    int global_reach = 0;
    for (int reach = 0; global_reach < len && global_reach <= reach; global_reach++) {
        reach = max(global_reach + nums[global_reach], reach);
    }
    return global_reach == len;
}

//######################## Traversing right to left + O(n) space ######################## 
bool canJump(vector<int>& nums) {
    int len = nums.size();
    vector<bool> b(len,false);
    int dist = 1;
    b[len - 1] = true;
    for(int i=len-2;i>=0;i--) {
        if(b[i] == false) {
            if(nums[i] >= dist) {
                b[i] = true;
                dist = 1;
            } else {
                dist += 1;
            }
        }
    }
    return b[0];
}
