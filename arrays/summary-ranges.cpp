//Summary Ranges
//Given a sorted integer array without duplicates, return the summary of its
//ranges.
//For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].

//######################################## Good #####################################################
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

//###################################### BAd #######################################################
vector<string> summaryRanges(vector<int>& nums) {
    vector<string> res;
    int len = nums.size();
    if(len == 0) {
        return res;
    }
    int min = nums[0];
    int max = nums[0];
    for(int i=1;i<len;i++) {
        if(nums[i] - max == 1) {
           max = nums[i];
        } else {
            if(min == max)
                res.push_back(to_string(min));
            else
                res.push_back(to_string(min) + "->" +to_string(max));
            min = nums[i];
            max = nums[i];
        }
    }
     if(min == max)
                res.push_back(to_string(min));
            else
                res.push_back(to_string(min) + "->" +to_string(max));
    return res;
}

int main() {

}
