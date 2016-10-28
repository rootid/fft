//Third Maximum Number
//Given a non-empty array of integers, return the third maximum number in this array. If it does not exist, return the maximum number. The time complexity must be in O(n).
//Example 1:
//Input: [3, 2, 1]
//Output: 1
//Explanation: The third maximum is 1.
//Example 2:
//Input: [1, 2]
//Output: 2
//Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
//Example 3:
//Input: [2, 2, 3, 1]
//Output: 1
//Explanation: Note that the third maximum here means the third maximum distinct number.
//Both numbers with value 2 are both considered as second maximum.
//
int thirdMax(vector<int>& nums) {
    int ln = nums.size();
   vector<long long> max_vec(3, LLONG_MIN);
    int cnt = 0;
    for(int i=0;i<ln;i++) {
        if(nums[i] > max_vec[0]) {
            max_vec[2] = max_vec[1];
            max_vec[1] = max_vec[0];
            max_vec[0] = nums[i];
        } else if(nums[i] > max_vec[1] && nums[i] != max_vec[0]) {
            max_vec[2] = max_vec[1];
            max_vec[1] = nums[i];
        } else if(nums[i] > max_vec[2] && nums[i] != max_vec[0] && nums[i] != max_vec[1]) {
           max_vec[2] = nums[i]; 
        }
    }
    if(max_vec[2] != LLONG_MIN) {
      return (int)max_vec[2];
    }
    return (int)max_vec[0];
}

//
// [1,2,-2147483648]
int thirdMax(vector<int>& nums) {
    int ln = nums.size();
    vector<int> max_vec(3,INT_MIN);
    int cnt = 0;
    for(int i=0;i<ln;i++) {
        if(nums[i] > max_vec[0]) {
            max_vec[2] = max_vec[1];
            max_vec[1] = max_vec[0];
            max_vec[0] = nums[i];
            cnt++;
        } else if(nums[i] > max_vec[1] && nums[i] != max_vec[0]) {
            max_vec[2] = max_vec[1];
            max_vec[1] = nums[i]; 
             cnt++;
        } else if(nums[i] > max_vec[2] && nums[i] != max_vec[0] && nums[i] != max_vec[1]) {
           max_vec[2] = nums[i]; 
            cnt++;
        }
    }
    
    if(ln < 3 ||  cnt < 3) {
        return max_vec[0];
    }
    return max_vec[2];
}
