//Next Greater Element II
//Given a circular array (the next element of the last element is the first element of the array), print the Next Greater Number for every element. The Next Greater Number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, output -1 for this number.
//Example 1:
//Input: [1,2,1]
//Output: [2,-1,2]
//Explanation: The first 1's next greater number is 2; 
//The number 2 can't find next greater number; 
//The second 1's next greater number needs to search circularly, which is also 2.
//Note: The length of given array won't exceed 10000.



//For example [9, 8, 7, 3, 2, 1, 6]
//The stack will first contain indexes for [9, 8, 7, 3, 2, 1] and then 
//we see 6 which is greater than 1 so we pop 1 2 3 whose next greater element should be 6
//######################### Traverse from right to left ######################### 
//Traverse from right to left and maintain a decreasing stack
vector<int> nextGreaterElements(vector<int>& nums) {
       if (nums.empty()) {
         return {};
       }
       int n = nums.size();
       vector<int> res(n, -1);
       stack<int> st;
       for (int i = 2*n-1; i >= 0; --i) {
           int num = nums[i%n];
           while (!st.empty() && nums[st.top()] <= num) {
             st.pop();
           }
           //res[i%n] = st.empty() ? - 1 : nums[st.top()];
           if(!st.empty()) { 
             res[i%n] = nums[st.top()];  //To avoid updates to res continuosuly
           }
           st.push(i%n);
       }
       return res;
}

//######################### Traverse from left to right ######################### 
vector<int> nextGreaterElements(vector<int>& nums) { 
  int n = nums.size();
  vector<int> next(n, -1);
  stack<int> idxstack; // index stack
  for (int i = 0; i < n * 2; i++) { //array is circular
      int num = nums[i % n]; 
      //if idxstack not empty and current ele(num) > stack idx top
      while (!idxstack.empty() && num > nums[idxstack.top()]) { 
          next[idxstack.top()] = num;
          idxstack.pop();
      }
      //store elements upto n only
      if (i < n) { 
        idxstack.push(i);
      }
  }   
  return next;
}
