//Summary Ranges
//Given a sorted integer array without duplicates, return the summary of its ranges.
//For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].
//
vector<string> summaryRanges(vector<int>& nums) {
    const int len = nums.size();
    vector<string> res;
    if ( 0 == len) return res;
    for (int i = 0; i < len;) {
        int start = i, end = i;
        while (end + 1 < len && nums[end+1] == nums[end] + 1) {
          end++;
        }
        if (end > start) { 
          res.push_back(to_string(nums[start]) + "->" + to_string(nums[end]));
        }
        else {
          res.push_back(to_string(nums[start]));
        }
        i = end+1;
    }
    return res;
}
