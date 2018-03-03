//Contains Duplicate III
//Given an array of integers, find out whether there are two distinct indices i
//and j in the array such that the absolute difference between nums[i] and
//nums[j] is at most t and the absolute difference between i and j is at most
//k.

//Keep only at most k elements in the set and use binary search to find
//element <= t
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
      set<long long> window;
	    for (int i = 0; i < nums.size(); ++i) {
		    if (i > k && i - k - 1 < nums.size()) { //i-k-1  //first element in the set
		        window.erase(nums[i - k - 1]); //erase the first element
		    }
		    auto it = window.lower_bound((long long)nums[i] - t);
		    if (it != window.cend() && *it - nums[i] <= t) {
		        return true;
		    }
		    window.insert(nums[i]);
	    }

	    return false;
}
