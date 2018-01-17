//Total Hamming Distance
//The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
//Now your job is to find the total Hamming distance between all pairs of the given numbers.
//Example:
//Input: 4, 14, 2
//Output: 6
//Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
//showing the four bits relevant in this case). So the answer will be:
//HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
//Note:
//Elements of the given array are in the range of 0 to 10^9
//Length of the array will not exceed 10^4.


//Use the bitwise operation to reduce the time complexity. 
//All the numbers can be viewed as 32 bits with 0s and 1s. 
//So for each bit, we just need to count the total number of 1s, then the total number of 0s will be (total numbers - the numbers of 1s). 
//And the contribution to the Hamming distance will be count of 1s times the count of 0s. Similar argument can be applied to all the rest bits.

int totalHammingDistance(vector<int>& nums) {
   int res = 0;
   for(int i=0; i<32; ++i){
       int one = 0;
       for(int j=0; j<nums.size(); ++j){
           if( (1<<i) & nums[j]) {
             ++one;//one is the numbers of 1s;
           }
       }
       res += one* (nums.size() - one);// nums of 1's X nums of 0's 
   }
   return res;
   //1 1 1 0
   //1 1 1 1 
   //1 1 1 0  LSB (2 0's + 1 1's) = contributes to 2 result
}
