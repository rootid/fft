//You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].
//Example:
//Given nums = [5, 2, 6, 1]
//To the right of 5 there are 2 smaller elements (2 and 1).
//To the right of 2 there is only 1 smaller element (1).
//To the right of 6 there is 1 smaller element (1).
//To the right of 1 there is 0 smaller element.
//Return the array [2, 1, 1, 0].
//
//o(n^2)
vector<int> countSmaller(vector<int>& nums) {
    
    vector<int> res(nums.size(),0);
    int len = nums.size();
    for(int i= len-2; i>=0;i--) {
        int n_idx = i+1;
        while( n_idx < len) {
            if(nums[i] > nums[n_idx++]) {
                res[i]++;
            }
        }
    }
    return res;
}
int main() {
}
