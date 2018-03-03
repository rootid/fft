//Product of Array Exclude Itself
//Given an integers array A.
//Define B[i] = A[0] * ... * A[i-1] * A[i+1] * ... * A[n-1], calculate B
//WITHOUT divide operation.
//Have you met this question in a real interview?
//Example
//For A = [1, 2, 3], return [6, 3, 2].


//######################################### O(n) #########################################
//LT -> RT , RT -> LT
//MRG ans
public List<Long> productExcludeItself(List<Integer> nums) {
    List<Long> rst = new ArrayList<>();
    int len = nums.size();
    long[] lt = new long[len];
    long[] rt = new long[len];
    for (int i=0;i<len;i++) {
        rst.add(1L);
    }
    lt[0] = 1;
    rt[len-1] = 1;
    for(int i=1;i<len;i++) lt[i] = lt[i-1] * nums.get(i-1);
    for(int i=len-2;i>=0;i--) rt[i] = rt[i+1] * nums.get(i+1);
    for(int i=0;i<len;i++) rst.set(i , lt[i] * rt[i]);
    return rst;
}

//######################################### O(n^2) #########################################
public List<Long> productExcludeItself(List<Integer> nums) {
   //1,2,3 => [6, 3, 2]
   List<Long> rst = new ArrayList<>();
   for(int k=0;k<nums.size();k++)
     rst.add(getPrdctXcptK(nums, k));
   return rst;
}
private Long getPrdctXcptK(List<Integer> nums, int k) {
   Long rst = 1L;
   for(int i=0;i<nums.size();i++) {
      if(i != k) rst *= nums.get(i);
   }
   return rst;
}


