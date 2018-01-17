//Single Element in a Sorted Array
//Given a sorted array consisting of only integers where every element appears twice except for one element which appears once. Find this single element that appears only once.
//Example 1:
//Input: [1,1,2,3,3,4,4,8,8]
//Output: 2
//Example 2:
//Input: [3,3,7,7,10,11,11]
//Output: 10
//Note: Your solution should run in O(log n) time and O(1) space.


//same numbers will occur in pair. 
//I also mentioned explicitly that only two such numbers occur in all cases (except for the element which we want to find

//######################################## O(log n) : with XOR the indices ######################################## 
//every 2 numbers are partner. (even,odd), (even,odd).
//If mid is even, it's partner is next odd, if mid is odd, it's partner is previous even.
//
//
//if mid is even, add 1 to make it odd, or if it is odd, decrease it by one.
//[1,1,2,2,3].. then our mid = 2 (index 2 not value). Then we need to check for index 3 which is (10 ^ 1)b.
//if our mid was index 3, then doing 3 = (11) ^ 1 = 10b = 2;

//find the first index whose "partner index" (the index xor 1) holds a different value.
int singleNonDuplicate(vector<int>& nums) {
    int lo = 0, hi = nums.size()- 1;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (nums[mid] == nums[mid ^ 1]) //each iteration compare 2 elements
            lo = mid + 1;
        else
            hi = mid;
    }
    return nums[lo];
}

//######################################## O(log n) : with 2 variables ######################################## 
//leftFirst: One of the two conditions to go left is : if it is the second occurrence of that digit(3 here) than mid should be even (even number of elements before it, because everything repeats twice)
//
//1     1    2    3    3    4    4    5    5
//                    mid
//leftSecond: Another condition to go left is : if it is the first occurrence of that digit(4 here) than mid should be odd (odd number of elements before it, because everything repeats twice) :
//Considering a different example:
//
//1   2   2   3   3   4   4   5   5   6   6
//                   mid
//IF any of the above conditions are true, we go left otherwise right.


//if(nums[mid]!=nums[mid-1]
//Consider this example: [1,3,3,5,5].
//Eventually you'll be looking at the subarray [1,3], with low = 0, high = 1 which implies mid = 0. I think your array access nums[mid-1] would throw index out of bounds here. you should check for valid index, or did i miss something?
//is a bug, needs check
//
//return nums[low];
//Why? Shouldn't return nums[mid] be the one finding the right number? Once you exited the loop, the search was unsuccessful, you could return fail or throw. are you simply returning "something" in this case or is this actually needed for the answer to be correct?
//when the first or last element is the answer, the search will terminate unsuccessfully, but at that point, since we know the array has 1 element that matches the condition, we just return it.
//e.g: [1,1,2] or [1,2,2]. // return nums[low] fixes this.

int singleNonDuplicate(vector<int>& nums) {
  int low =0;
  int high = nums.size()-1;
  int mid;
  bool left;
  bool leftFirst;
  bool leftSecond;
  while(low<high) {
      mid = low + (high-low)/2;
      if(nums[mid] != nums[mid-1] && nums[mid]!=nums[mid+1])
        return nums[mid];
      //conditions to be true if an element is in left side 
      leftFirst = (nums[mid] == nums[mid-1]) && (mid)%2 == 0; //if its the second occurence of that element 
      leftSecond = (nums[mid] == nums[mid+1]) && (mid)% 2== 1; //if its the first occurence of that element 
      left = leftFirst||leftSecond;  //if any of the above conditions are true, We will go left
      if(left)
          high = mid-1;
      else
          low = mid+1;
  }
  return nums[low];
}


//######################################## pytonic ######################################## 
//######################################## O(log n) : with XOR indices ######################################## 
def singleNonDuplicate(self, nums):
    lo, hi = 0, len(nums) - 1
    while lo < hi:
        mid = (lo + hi) / 2
        if nums[mid] == nums[mid ^ 1]:
            lo = mid + 1
        else:
            hi = mid
    return nums[lo]
// vim: set sw=2 sts=2 tw=120 et nospell : 
