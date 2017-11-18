// Find Minimum in Rotated Sorted Array
//Suppose a sorted array is rotated at some pivot unknown to you beforehand.
//(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
//Find the minimum element.
//You may assume no duplicate exists in the array.

//######################################### O(log n) ######################################### 
public int findMin(int[] nums) {
     int start = 0;
     int end = nums.length - 1;
     while(start < end) {
         int mid = start + (end -  start) / 2;
         if(nums[mid] > nums[end]) start = mid+1; //4,5,6,7,0,1,2  1. 4,5,6 2.7,0,1,2
         else end = mid;
     }
     return nums[start];    
}

//######################################### O(log n) ######################################### 
int getMin(vector<int>& nums,int start,int end) {
    while(start < end) {
        int mid = start + (end-start)/2;
        if(nums[mid] < nums[end]) { //4....7....2
            end = mid;
        } else if(nums[mid] > nums[end]) {  //0...1...2
            start = mid+1;
        } else {
            end = mid - 1;
        }
    }
    return nums[start];
}

int findMin(vector<int>& nums) {
    
    if (nums.size() == 1) {
        return nums[0];
    }
    int start = 0;
    int end = nums.size() - 1;
    return getMin(nums,start,end);
}
