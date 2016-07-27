


vector<vector<int>> threeSum(vector<int>& nums) {
  int len = nums.size(); 
  if(len <=2) return {};
  sort(nums.begin(),nums.end());
  vector<vector<int>> result;
  for(int i=0;i<len;i++) {
    int target = -nums[i];
    int ltIdx = i+1;
    int rtIdx = len-1-i;
    while(ltIdx < rtIdx) {
        if(nums[ltIdx] + nums[rtIdx] > target) {
            rtIdx -= 1;
        } else if (nums[ltIdx] + nums[rtIdx] < target) {
            ltIdx += 1;
        } else {
            result.push_back(vector<int>{nums[i], nums[ltIdx], nums[rtIdx]});
            while( ltIdx < rtIdx && nums[ltIdx] == nums[ltIdx+1]) {
              ltIdx += 1;
            }
            while(ltIdx < rtIdx && nums[rtIdx] == nums[rtIdx-1]) {
              
              rtIdx -= 1;
            }
        }
   }
   while(nums[i] == -target) {
     i++;
     if(i == len) {
       break;
     }
   }
  }
  return result;
}


vector<vector<int> > threeSum(vector<int> &num) {
    vector<vector<int> > res;
    std::sort(num.begin(), num.end());
    for (int i = 0; i < num.size(); i++) {
        int target = -num[i];
        int front = i + 1;
        int back = num.size() - 1;
        while (front < back) {
            int sum = num[front] + num[back];
            // Finding answer which start from number num[i]
            if (sum < target)
                front++;
            else if (sum > target)
                back--;
            else {
                vector<int> triplet(3, 0);
                triplet[0] = num[i];
                triplet[1] = num[front];
                triplet[2] = num[back];
                res.push_back(triplet);
                // Processing duplicates of Number 2
                // Rolling the front pointer to the next different number forwards
                while (front < back && num[front] == triplet[1]) front++;
                // Processing duplicates of Number 3
                // Rolling the back pointer to the next different number backwards
                while (front < back && num[back] == triplet[2]) rear--;
            }
        }
        // Processing duplicates of Number 1
        while (i + 1 < num.size() && num[i + 1] == num[i]) 
            i++;
    }
    return res;
}
