//Next Greater Element I
//You are given two arrays (without duplicates) nums1 and nums2 where nums1’s
//elements are subset of nums2. Find all the next greater numbers for nums1's
//elements in the corresponding places of nums2.
//The Next Greater Number of a number x in nums1 is the first greater number to
//its right in nums2. If it does not exist, output -1 for this number.
//Example 1:
//Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
//Output: [-1,3,-1]
//Explanation:
//    For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
//    For number 1 in the first array, the next greater number for it in the second array is 3.
//    For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
//Example 2:
//Input: nums1 = [2,4], nums2 = [1,2,3,4].
//Output: [3,-1]
//Explanation:
//    For number 2 in the first array, the next greater number for it in the second array is 3.
//    For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
//Note:
//All elements in nums1 and nums2 are unique.
//The length of both nums1 and nums2 would not exceed 1000.



//################## With stack + map + Traverse right to left ####################################
vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
     if (findNums.empty()) return {};
     int n = nums.size();
     unordered_map<int, int> ng;
     stack<int> st;
     for (int i = n-1; i >= 0; --i) {
         while (!st.empty() && st.top() < nums[i]) st.pop();
         ng[nums[i]] = st.empty() ? -1 : st.top();
         st.push(nums[i]);
     }

     int m = findNums.size();
     vector<int> res(m);
     for (int i = 0; i < m; ++i) res[i] = ng[findNums[i]];
     return res;
 }
//findNums  = [4,1,2]
//nums  = [1,3,4,2]
//################## With stack + map + Traverse left to right  ####################################
vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
    stack<int> s;
    //map store k,v => 1,
    unordered_map<int, int> m;
    for (int n : nums) {
        while (s.size() && s.top() < n) {
            m[s.top()] = n; //Stores next greater element
            s.pop();
        }
        s.push(n);
    }
    vector<int> ans;
    for (int n : findNums) {
      if(m.count(n) != 0) {
        ans.push_back(m[n]);
      } else {
        ans.push_back(-1);
      }
      //ans.push_back(m.count(n) ? m[n] : -1);
    }
    return ans;
}

//################## With Heap ##################
//
  vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        unordered_map<int,int> num2idx;
        //map num to its index in findNums
        for(int i=0; i<findNums.size(); i++)
            num2idx[findNums[i]] = i;

        priority_queue<int,vector<int>,std::greater<int>> min_heap;
        vector<int> ans(findNums.size(),0);
        for(int i : nums){

            //In nums, we find an element from findNums. Push it into the heap.
            //The elements in the heap are numbers whose first greater number still not found.
            if(num2idx.count(i))
                min_heap.push(i);

            //See if the current number i is the first greater number for elements in heap.
            //If so, we found the first greater number i.
            //Since it's a min_heap, once we find an element not smaller than i, we can stop the loop.
            while(!min_heap.empty() && min_heap.top()<i){
                int idx = num2idx[min_heap.top()];
                ans[idx] = i;
                min_heap.pop();
            }
        }

        //Elements still in the heap are numbers without first greater number
        while(!min_heap.empty()){
            int idx = num2idx[min_heap.top()];
            ans[idx] = -1;
            min_heap.pop();
        }

        return ans;
    }
