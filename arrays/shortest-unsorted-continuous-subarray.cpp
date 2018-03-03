//Shortest Unsorted Continuous Subarray
//Given an integer array, you need to find one continuous subarray that if you
//only sort this subarray in ascending order, then the whole array will be
//sorted in ascending order, too.
//You need to find the shortest such subarray and output its length.
//Example 1:
//Input: [2, 6, 4, 8, 10, 9, 15]
//Output: 5
//Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the
//whole array sorted in ascending order.
//Note:
//Then length of the input array is in range [1, 10,000].
//The input array may contain duplicates, so ascending order here means <=.
//######################### Good O(log n) #########################
int findUnsortedSubarray(vector<int>& nums) {
  vector<int> sorted(nums);
  sort(sorted.begin(), sorted.end());
  int n = nums.size(), left = 0, right = n - 1;
  while (left < n && nums[left] == sorted[left]) {
      left++;
  }
  while (right > left && nums[right] == sorted[right]) {
      right--;
  }
  return right + 1 - left;
}

//######################### Ugly O(log n) #########################
int findUnsortedSubarray(vector<int>& nums) {
  vector<int> nums2(nums.begin(),nums.end());
  sort(nums2.begin(),nums2.end());
  int startIdx = 0;
  int endIdx = 0;
  int idx = 0;
  int len = nums2.size();
  while(idx < len) {
    if(nums[idx] != nums2[idx]) {
      startIdx = idx;
      break;
    }
    idx++;
  }
  idx = len-1;
  while(idx >= 0) {
    if(nums[idx] != nums2[idx]) {
      endIdx = idx;
      break;
    }
    idx--;
  }
  return startIdx+endIdx-1;
}

//######################### T O(n) + S O(2n) #########################
int findUnsortedSubarray(vector<int>& nums) {
  int n = nums.size();
  vector<int> maxlhs(n);   // max number from left to cur
  vector<int> minrhs(n);   // min number from right to cur
  for (int i = n - 1, minr = INT_MAX; i >= 0; i--) {
    minrhs[i] = minr = min(minr, nums[i]);
  }
  for (int i = 0, maxl = INT_MIN; i < n;  i++) {
    maxlhs[i] = maxl = max(maxl, nums[i]);
  }
  int i = 0, j = n - 1;
  while (i < n && nums[i] <= minrhs[i]) {
    i++;
  }
  while (j > i && nums[j] >= maxlhs[j]) {
    j--;
  }
  return j + 1 - i;
}

//######################### O(n) #########################
//Space O(1)
int findUnsortedSubarray(vector<int>& nums) {
       int shortest = 0;
       int left = 0, right = nums.size() - 1;
       //find start left
       while (left < nums.size() - 1 && nums[left] <= nums[left + 1]) {
         left++;
       }
       //find start right
       while (right > 0 && nums[right] >= nums[right - 1]) {
         right--;
       };
       if (right > left) {
         //find max and min value (vmax,vmin)
         int vmin = INT_MAX, vmax = INT_MIN;
         for (int i = left; i <= right; ++i) {
             if (nums[i] > vmax) {
               vmax = nums[i];
             }
             if (nums[i] < vmin) {
               vmin = nums[i];
             }
         }
         while (left >= 0 && nums[left] > vmin) {
           left--;
         };
         while (right < nums.size() && nums[right] < vmax) {
           right++;
         };

           shortest = right - left - 1;
       }
       return shortest;
}

//######################### O(n) + S O(1)#########################
int findUnsortedSubarray(vector<int>& nums) {
  int n = nums.size();
  if (n <= 1) return 0;
  int left = 0, right = n - 1;
  while (left < n - 1 && nums[left] <= nums[left + 1]) ++left;
  if (left == n - 1) return 0; // return 0 if already sorted.
  // Or we know the array is unsorted
  // So, it's no need to judge right > 0
  while (/*right > 0 && */nums[right] >= nums[right - 1]) --right;
  int rmin = INT_MAX, lmax = INT_MIN;
  for (int i = left; i <= right; ++i) {
      if (nums[i] > lmax) lmax = nums[i];
      if (nums[i] < rmin) rmin = nums[i];
  }
  while (left >= 0 && nums[left] > rmin) --left;
  while (right < n && nums[right] < lmax) ++right;
  return right - left - 1;
}

//############################ pytonic  ############################
//def findUnsortedSubarray(self, A):
//    B = sorted(A)
//    if A == B: return 0
//    for i in xrange(len(A)):
//        if A[i] != B[i]: break
//    for j in xrange(len(A)-1, -1, -1):
//        if A[j] != B[j]: break
//    return j - i + 1
