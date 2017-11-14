//Sliding Window Maximum
//Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
//For example,
//Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.
//Window position                Max
//---------------               -----
//[1  3  -1] -3  5  3  6  7       3
// 1 [3  -1  -3] 5  3  6  7       3
// 1  3 [-1  -3  5] 3  6  7       5
// 1  3  -1 [-3  5  3] 6  7       5
// 1  3  -1  -3 [5  3  6] 7       6
// 1  3  -1  -3  5 [3  6  7]      7
//Therefore, return the max sliding window as [3,3,5,5,6,7].
//Note: 
//You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.
//Follow up:
//Could you solve it in linear time?
//Hint:
//How about using a data structure such as deque (double-ended queue)?
//The queue size need not be the same as the window’s size.
//Remove redundant elements and the queue should store only elements that need to be considered.

//########################################### Use of deque and store indices ##############################################    
//1. Push always 
//2. Pop when monotonic increase/limit reached
public int[] maxSlidingWindow(int[] nums, int k) {
    Deque<Integer> deque = new ArrayDeque<>();
    int m = nums.length;
    if(m == 0) return nums;
    int[] result = new int[m-k+1];
    //push always , pop when monotonic increase/limit reached;
    int idx = 0;
    for(int i=0;i<nums.length;i++) {
        if(!deque.isEmpty() && deque.getFirst() == i-k) deque.pollFirst();
        while(!deque.isEmpty() && nums[i] > nums[deque.peekLast()]) {
            deque.pollLast();
        }
        deque.offer(i);
        if(i >= k-1) result[idx++] = nums[deque.peekFirst()];
    }
    return result;
}

//########################################### Use of deque and store deque  ##############################################    
vector<int> maxSlidingWindow(vector<int>& nums, int k) { 
  int len = nums.size();
  vector<int> result;
  deque<int> dqIdx;
  for(int i=0;i<len;i++) {
      //only keep at most k elements
      if(!dqIdx.empty() && dqIdx.front() == i-k) { //limit the size
          dqIdx.pop_front();
      } 
      while (!dqIdx.empty() && nums[i] > nums[dqIdx.back()]) { //10,8,4,12 monotonic-decrease->increase
          dqIdx.pop_back();   
      }
      dqIdx.push_back(i); //store monotonic-decrease
      if(i >= k-1) {
          result.push_back(nums[dqIdx.front()]);
      }
  }
  return result; 
}

//########################################### Use of deque and store values ##############################################    
vector<int> maxSlidingWindow(vector<int>& nums, int k) { 
  vector<int> ans;
  deque<int> dq;
  for(int i = 0; i < nums.size(); i++){
      while(!dq.empty() && dq.back() < nums[i]) dq.pop_back();
      dq.push_back(nums[i]);
      if(i >= k - 1){
          ans.push_back(dq.front());
          if(nums[i - k + 1] == dq.front()) dq.pop_front();
      }
  }
  return ans;
}
