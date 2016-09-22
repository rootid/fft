int singleNumber(vector<int>& nums) {
    int reqNo =0;
    for(int x:nums) {
        reqNo ^= x;
    }
    return reqNo;
}
