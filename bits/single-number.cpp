//Single Number
//Given an array of integers, every element appears twice except for one. Find that single one.
//Note:
//Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

int singleNumber(vector<int>& nums) {
    int reqNo =0;
    for(int x:nums) {
        reqNo ^= x;
    }
    return reqNo;
}
