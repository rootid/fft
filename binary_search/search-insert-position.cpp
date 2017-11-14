//Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
//You may assume no duplicates in the array.
//Here are few examples.
//[1,3,5,6], 5 → 2
//[1,3,5,6], 2 → 1
//[1,3,5,6], 7 → 4
//[1,3,5,6], 0 → 0


//######################################### Binary Search (start,end-1) ######################################### 
public int searchInsert(int[] nums, int target) {
    int end = nums.length-1;
    int start = 0;
    int mid = 0;
    while(start <= end) {
        mid = start + (end - start)/2;
        if(nums[mid] == target) return mid;
        if(nums[mid] > target)
            end = mid - 1;
        else
            start = mid + 1;
    }
    return start;
}

//######################################### Binary Search (start,end] ######################################### 
public int searchInsert(int[] nums, int target) {
    int end = nums.length;
    int start = 0;
    int mid = 0;
    while(start < end) {
        mid = start + (end - start)/2;
        if(nums[mid] == target) return mid;
        if(nums[mid] > target)
            end = mid;
        else
            start = mid + 1;
    }
    return start;
}

//######################################### In built Java Arrays binary search ######################################### 
public int searchInsert(int[] nums, int target) {
   int idx =  Arrays.binarySearch(nums, target);
   return idx < 0 ? ~idx : idx; 
}

//######################################### Binary Search ######################################### 
int searchInsert(vector<int>& a, int target) {
    int end = a.size() -1;
    int start  = 0;
    while(start <= end) {
        // Invariant: the desired index is between (start, end)
        int mid = start + (end - start)/2;
        if(a[mid] == target) {
            return mid;
        } else if (a[mid] > target) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

 // (1) At this point, start > end. That is, start >= end+1
 // (2) From the invariant, we know that the index is between [start, end+1], so start <= end+1. Follwing from (1), now we know start == end+1.
 // (3) Folstarting from (2), the index is between [start, end+1] = [start, start], which means that start is the desired index
 // Therefore, we return start as the answer. You can also return end+1 as the result, since start == end+1
    return start;
}
