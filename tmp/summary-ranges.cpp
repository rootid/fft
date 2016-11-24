//Summary Ranges
//Given a sorted integer array without duplicates, return the summary of its ranges.
//For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].
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
