//Longest Consecutive Sequence
//Given an unsorted array of integers, find the length of the longest
//consecutive elements sequence.
//For example,
//Given [100, 4, 200, 1, 3, 2],
//The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length:
//4.
//Your algorithm should run in O(n) complexity.
int longestConsecutive(vector<int>& nums) {

  unordered_set<int> vals;
  int count = 0;
  for(auto& i:nums) {
    vals.insert(i);
  }
  for(auto& j:vals) {
      if(vals.find(j - 1) == vals.end()) {
        int m = j + 1;
        while(vals.find(m) != vals.end()) {
            m++;
        }
        count = max(count, m - j);
    }
  }
  return count;
}
