//Given an array of integers and an integer k, you need to find the number of
//unique k-diff pairs in the array. Here a k-diff pair is defined as an integer
//pair (i, j), where i and j are both numbers in the array and their absolute
//difference is k.
//
//Example 1:
//Input: [3, 1, 4, 1, 5], k = 2
//Output: 2
//Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
//Although we have two 1s in the input, we should only return the number of
//unique pairs.
//Example 2:
//Input:[1, 2, 3, 4, 5], k = 1
//Output: 4
//Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4)
//and (4, 5).
//Example 3:
//Input: [1, 3, 1, 5, 4], k = 0
//Output: 1
//Explanation: There is one 0-diff pair in the array, (1, 1).
//Note:
//The pairs (i, j) and (j, i) count as the same pair.
//The length of the array won't exceed 10,000.
//All the integers in the given input belong to the range: [-1e7, 1e7].

//######################### O(n) #########################
int findPairs(vector<int>& nums, int k) {
  int n = nums.size();
  if (n <= 1 || k < 1) {
	return 0;
  }
  unordered_set<int> st;
  unordered_set<int> val;
  for (int i = 0; i < n; i++) {
    //[1, 3, 1, 5, 4], k = 0
    int diff_positive = nums[i] + k;
    int diff_negative = nums[i] - k;
    if (val.count(diff_negative)) {
      st.insert(diff_negative);
    }
    if (val.count(diff_positive)) {
      st.insert(nums[i]);  //CAse : [3,1,4,1,5] k= 2 o/p :2
    }
	  val.insert(nums[i]);
  }

  return st.size();
}

//######################### NEEDS TO FIX #########################
int findPairs(vector<int>& nums, int k) {
  unordered_set<int> t;
  int cnt = 0;
  for(auto i:nums) {
      t.insert(i);
  }
  for(auto i:nums) {
      int diff_positive = i + k;
      int diff_negative = i -k;
      if(t.find(diff_positive) != t.end()) {
          cnt += 1;
          t.erase(diff_positive);
      } else if(t.find(diff_negative) != t.end()) {
          cnt += 1;
          t.erase(diff_negative);
      }
  }
  return cnt;
}


//################################# With HashMap #################################
int findPairs(vector<int>& nums, int k) {
  int ans = 0;
  if(nums.size() == 0 || k < 0)
      return ans;
  unordered_map<int,int> dict;
  for(int i = 0; i < nums.size(); ++ i)
      ++ dict[nums[i]];
  unordered_map<int,int>::iterator it = dict.begin();
  for(; it != dict.end(); ++ it){
      if(dict.find(it->first - k) != dict.end()){
          if(k != 0)
              ++ ans;
          else if(it->second > 1)
              ++ ans;
      }
  }
  return ans;
}
