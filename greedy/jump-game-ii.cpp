//Jump Game II
//Given an array of non-negative integers, you are initially positioned at the first index of the array.
//Each element in the array represents your maximum jump length at that position.
//Your goal is to reach the last index in the minimum number of jumps.
//For example:
//Given array A = [2,3,1,1,4]
//The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)

//####################################################### BFS ####################################################### 
public int jump(int[] nums) {
	if (nums.length <= 1) return 0;
	int cnt = 0;
	int lastIdx = 0;
	Queue<Integer>idxQueue = new ArrayDeque<>();
	idxQueue.offer(0);
	while(!idxQueue.isEmpty()) {
		int maxReachable = lastIdx;
		while(!idxQueue.isEmpty()){
			int currIdx = idxQueue.poll();
			if (currIdx >= nums.length - 1) return cnt;
			lastIdx = Math.max(lastIdx, currIdx);
			maxReachable = Math.max(maxReachable, currIdx + nums[currIdx]);
		}
		for (int i = lastIdx + 1; i <= maxReachable; i++) idxQueue.offer(i);
		cnt++;
	}
	return -1;
}

//
//2,31
//2||
//3 1||
//1 4 ||
//#### TODO : need to add verfication step where we cannot reach to end 
// A={3,0,0,0,4} or A={0,5}
//

//####################################################### BFS ####################################################### 
int jump_bfs(vector<int>& nums) {
  int n = nums.size(), step = 0, start = 0, end = 0; 
  int dest = n - 1;
  while (end < dest) { 
    step++; 
    //each iteration increase the step
	int maxend = end + 1; //start,end : range of current node
    // Each time after we make a move, update start to be end + 1 and end to be the farthest index that can be reached in 1 i.e. maxend+1 move from the current [start, end]
	for (int i = start; i <= end; i++) { 
      if (i + nums[i] >= dest) {
        return step;
      } 
      maxend = max(maxend, i + nums[i]); 
    } 
    start = end + 1;
    end = maxend; 
  } 
  return step;
}

//####################################################### O(N) ####################################################### 
int jump(vector<int>& nums) { 
  if(nums.size() < 3 ) {
    return ;
  }
   int n = nums.size(); 
   if(n<2) {
     return 0;
   }
	 int level=0,currentMax=0,i=0,nextMax=0;
	 while(currentMax-i+1>0) {		//nodes count of current level>0
		 level++;
		 for(;i<=currentMax;i++) {	//traverse current level , and update the max reach of next level 
       nextMax=max( nextMax, nums[i]+i); 
       if(nextMax >= n-1) {
         return level;   // if last element is in level+1,  then the min jump=level 
       }
		 }
		 currentMax=nextMax;
	 }
	 return 0;
}


//####################################################### O(N) ####################################################### 
int jump(int A[], int n) { //O(N)
    	 if(n<2) return 0;
    	 int level=0,currentMax=0,i=0,nextMax=0;
    	 
    	 while(currentMax-i+1>0){ //nodes count of current level>0
    		 level++;
    		 for(;i<=currentMax;i++){ //traverse current level , and update the max reach of next level
    			nextMax=max(nextMax,A[i]+i);
    			if(nextMax>=n-1) return level;// if last element is in level+1,  then the min jump=level
    		 }
    
    		 if(currentMax==nextMax) return INT_MAX; //***cannot move forward from this level
    
    		 currentMax=nextMax;
    	 }	
    }
