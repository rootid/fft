//Jump Game
//Given an array of non-negative integers, you are initially positioned at the first index of the array.
//Each element in the array represents your maximum jump length at that position.
//Determine if you are able to reach the last index.
//For example:
//A = [2,3,1,1,4], return true.
//A = [3,2,1,0,4], return false.

//################################### O(n) : linear traversal ################################### 
public boolean canJump(int[] nums) {
   int m = 0; // m : tells the maximum index we can reach so far.
   for(int i=0;i<nums.length;i++) {
       if(i > m) return false;   
       m = Math.max(m, i + nums[i]);    
   }
   return true;
}
//################################### BFS with indexes ################################### 
public boolean canJump(int[] nums) {
     int dIdx = nums.length -1;
     if(dIdx == 0) return true;
     Queue<Integer> q = new ArrayDeque<>();
     q.offer(0);
     while(!q.isEmpty()) {
       int cIdx = q.poll();
       int cVal = nums[cIdx];
       if(cIdx + cVal == dIdx) return true;
       while(cVal >= 1) {
           if(cIdx + cVal >= dIdx) break;
           q.offer(cIdx + cVal);
           cVal--;
       }
       if(cVal >= 1) return true;
     }
     return false;
}

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

//Going forwards. m tells the maximum index we can reach so far.
def canJump(self, nums):
    m = 0
    for i, n in enumerate(nums):
        if i > m:
            return False
        m = max(m, i+n)
    return True
