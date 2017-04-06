//Minimum Moves to Equal Array Elements II
//Given a non-empty integer array, find the minimum number of moves required to make all array elements equal, where a move is incrementing a selected element by 1 or decrementing a selected element by 1.
//You may assume the array's length is at most 10,000.
//Example:
//Input:
//[1,2,3]
//Output:
//2
//Explanation:
//Only two moves are needed (remember each move increments or decrements one element):
//[1,2,3]  =>  [2,2,3]  =>  [2,2,2]
//
int minMoves2(vector<int>& nums) { 
  //sort(nums.begin(),nums.end()); 
  //int median = nums[nums.size()/2]; // Works for both odd and even number of elements
  nth_element(nums.begin(), nums.begin() + nums.size()/2, nums.end());
  int median = nums[ nums.size()/2];
  int res = 0;
  for(int i=0;i<nums.size();i++) {
      res += abs(nums[i]-median); // How far is each element from median 
  }
  return res;
}



//f(x) = (|x-xi| + |x-xN-i|) + (N%2)*|x-xN/2+1|
//|x-xi| + |x-xN+1-i| >= |xN+1-i - xi|
//TODO : verify for even # missing term (N%2)*|x-xN/2+1| in implementation
//my thought : f(x) = (|x-xi| + |x-xN-i|) + (~(N%2)) *|x-xN/2+1|
int minMoves2(vector<int>& nums) {
  sort(nums.begin(), nums.end()); int n = nums.size(), res = 0;
  for (int i = 0; i < n/2; ++i) {
    res += (nums[n-1-i]-nums[i]);
  }
  return res;
}
