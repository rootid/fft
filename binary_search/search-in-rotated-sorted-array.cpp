//Search in Rotated Sorted Array
//Suppose a sorted array is rotated at some pivot unknown to you beforehand.
//(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
//You are given a target value to search. If found in the array return its
//index, otherwise return -1.
//You may assume no duplicate exists in the array.
//

//######################################### Binary search  #########################################
//1. 2 Arrays ( 1. Detect Sorted array (binary search) & Partially sorted array
//(binary search) )

public int search(int[] nums, int target) {
    int m = nums.length;
    int start = 0;
    int end = m - 1;
    while(start < end) {
       int mid = start + (end - start)/2;
       if(nums[mid] == target) return mid;
       if(nums[mid] > nums[end]) {  // eg. 3,4,5,6,1,2 //3,4,5  6,1,2
           if(target > nums[mid] || target <= nums[end]) start = mid+1;  // 1st half  eg. search(9) | search(2)
           else end = mid; //2nd half
       } else { // eg. 5,6,1,2,3,4 //5,6,1 2,3,4
           if(target > nums[mid] && target <= nums[end]) start = mid+1; //normal binary search
           else end = mid;
       }
    }
    if(start > end || nums[start] != target) return -1;
    return start;
}

//######################################### FindMinIndex / Transition index  #########################################
public int search(int[] nums, int target) {
    int minIdx = findMinIdx(nums);
    if (target == nums[minIdx]) return minIdx;
    int m = nums.length;
    int start = (target <= nums[m - 1]) ? minIdx : 0; //lower limit
    int end = (target > nums[m - 1]) ? minIdx : m - 1; //upper limit

    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (nums[mid] == target) return mid;
        else if (target > nums[mid]) start = mid + 1;
        else end = mid - 1;
    }
    return -1;
}

public int findMinIdx(int[] nums) {
    int start = 0, end = nums.length - 1;
    while (start < end) {
        int mid = start + (end -  start) / 2;
        if (nums[mid] > nums[end]) start = mid + 1; //4,5,6,7,0,1,2 //7,2 (0)
        else end = mid;
    }
	return start;
}


//######################################### Clever idea #########################################
//[12, 13, 14, 15, 16, 17, 18, 19, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
//1. If target is let's say 14, then we adjust nums to this, where "inf" means
//infinity:
//[12, 13, 14, 15, 16, 17, 18, 19, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf]

//2. If target is let's say 7, then we adjust nums to this:
//[-inf, -inf, -inf, -inf, -inf, -inf, -inf, -inf, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]

//If nums[mid] and target are "on the same side" of nums[0],
//we just take nums[mid]. Otherwise we use -infinity or +infinity as needed.

int search(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size();
    while (lo < hi) {
        int mid = (lo + hi) / 2;

        double num = (nums[mid] < nums[0]) == (target < nums[0])
                   ? nums[mid]
                   : target < nums[0] ? -INFINITY : INFINITY;

        if (num < target)
            lo = mid + 1;
        else if (num > target)
            hi = mid;
        else
            return mid;
    }
    return -1;
}

//######################################### Clever idea #########################################
public int search(int[] nums, int target) {
    int lo = 0, hi = nums.length - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        int num = nums[mid];
        // If nums[mid] and target are "on the same side" of nums[0], we just take nums[mid].
        if ((nums[mid] < nums[0]) == (target < nums[0])) {
            num = nums[mid];
        } else {
            num = target < nums[0] ? Integer.MIN_VALUE : Integer.MAX_VALUE;
        }

        if (num < target)
            lo = mid + 1;
        else if (num > target)
            hi = mid - 1;
        else
            return mid;
    }
    return -1;
}

int search(vector<int>& a,int start,int end,int key) {
     while(start < end) {
         int mid = start + (end-start)/2;
         if(a[mid] == key) {
             return mid;
         }
         if(a[mid] < a[end]) { // right half sorted  eg. 5,6,1,2,3,4
             if(key>a[mid] && key<=a[end])
                 start = mid+1;
             else
                 end = mid;
         } else {  // left half sorted eg. 3,4,5,6,1,2
          //else if(a[mid]>a[end]) {  // left half sorted
             if(key >= a[start] && key<a[mid])
                 end = mid;
             else
                 start = mid+1;
         }
         //else {  //In case duplicates allowed
         //    end = end - 1;
         //}

     }
    if (start == end && key != a[start]) {
          return -1;
  }
 return start;
}


int search(vector<int>& nums, int target) {
  int start = 0;
  int end = nums.size() - 1;
  return search(nums,start,end,target);
}
