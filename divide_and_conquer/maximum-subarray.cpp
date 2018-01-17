//Maximum Subarray
//Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
//For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
//the contiguous subarray [4,-1,2,1] has the largest sum = 6


//O(n log n)
int merge_max(vector<int>& nums,int l,int r,int mid) {
    int suml = 0;
    int maxl = INT_MIN;
    for (int i = mid; i >= l; i--) {
        suml += nums[i];
        if (suml > maxl) {
            maxl = suml;
        }
    }
    int sumr = 0;
    int maxr = INT_MIN;
    for (int i = mid +1; i <= r; i++) {
        sumr += nums[i];
        if(sumr > maxr) {
            maxr = sumr;
        }
    }
    return maxl+maxr;
}

int get_max(vector<int>& nums,int start,int end) {
    if(start == end) {
        return nums[start];
    }
    int mid = start + (end-start)/2;
    int start_max = 0;
    int end_max = 0;
    int cross_max = 0;
    int max = INT_MIN;
    start_max = get_max(nums,start,mid);
    end_max = get_max(nums,mid+1,end);
    cross_max = merge_max(nums,start,end,mid);

    if (start_max > end_max){
        max = start_max;
    } else {
        max = end_max;
    }
    if(cross_max > max){
        max = cross_max;
    }
    return max;
}

int maxSubArray(vector<int>& nums) {
  if(nums.size() == 0) {
    return -1;
  }
  return get_max(nums,0,nums.size() - 1);
}
