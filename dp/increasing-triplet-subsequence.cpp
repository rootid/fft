//Increasing Triplet Subsequence
//Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.
//Formally the function should:
//Return true if there exists i, j, k 
//such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.
//Your algorithm should run in O(n) time complexity and O(1) space complexity.
//Examples:
//Given [1, 2, 3, 4, 5],
//return true.
//Given [5, 4, 3, 2, 1],
//return false.
//################## Linear with only 2 variables ################## 
bool increasingTriplet(vector<int>& nums) {
   if(nums.size() <3) {
        return false;
   }
    int one = INT_MAX;
    int two = INT_MAX;
    for(auto num:nums){
        if(num>one){
            if(num>two){
                return true;
            }else{
                two = num;
            }
         } else{
            one = num;
         }
    }
    return false;
}
//#################### Same as increasing subsequence Only issue : Can't return
//the sequence 
bool increasingTriplet(vector<int>& nums) {
    if(nums.size() < 3) {
        return false;
    }
    vector<int> store;
    for(auto num:nums) {
        if( store.empty() || num > store.back()) {
            store.push_back(num);
        } else {
            *lower_bound(store.begin(),store.end(),num) = num;
        }
    }
    
    if(store.size() >= 3) {
        return true;
    }
    return false;
}
