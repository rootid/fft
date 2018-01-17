//Search in Rotated Sorted Array II
//Follow up for "Search in Rotated Sorted Array":
//What if duplicates are allowed?
//Would this affect the run-time complexity? How and why?
//Write a function to determine if a given target is in the array.
//

//######################################### Addition check than + To handle duplicates######################################### 
//Worst case : O(n)
public boolean search(int[] nums, int target) {
    int m = nums.length;
    int start = 0;
    int end = m - 1;
    while(start < end) {
       int mid = start + (end - start)/2;
       if(nums[mid] == target) return true;
       if( (nums[start] == nums[mid]) && (nums[end] == nums[mid]) ) { start++; end--;}
       else if(nums[mid] > nums[end]) {  // eg. 3,4,5,6,1,2 //3,4,5  6,1,2
           if(target > nums[mid] || target <= nums[end]) start = mid+1;  // 1st half  eg. search(9) | search(2)
           else  end = mid; //2nd half
       } else { // eg. 5,6,1,2,3,4 //5,6,1 2,3,4
           if(target > nums[mid] && target <= nums[end]) start = mid+1; //normal binary search
            else  end = mid; //2nd half
       }
    }
    if(start > end || nums[start] != target) return false;
    return true;       
}



//
//######################################### Addition check than + Search in Rotated Sorted Array ######################################### 
//Worst case : O(n)
public boolean search(int[] nums, int target) {

    int m = nums.length;
    int start = 0;
    int end = m - 1;
    while(start < end) {
       int mid = start + (end - start)/2;
       if(nums[mid] == target) return true;
       if(nums[mid] > nums[end]) {  // eg. 3,4,5,6,1,2 //3,4,5  6,1,2
                                    //1,1,3,1 //1 //1,3,1
           if(target > nums[mid] || target <= nums[end]) start = mid+1;  // 1st half  eg. search(9) | search(2)
           else  end = mid; //2nd half
       } else if (nums[mid] < nums[end]){ // eg. 5,6,1,2,3,4 //5,6,1 2,3,4
           if(target > nums[mid] && target <= nums[end]) start = mid+1; //normal binary search
           else end = mid;
       } else 
           end -= 1; //When found same elements just keep start element //3,1,1 search(3)
        
    }
    if(start > end || nums[start] != target) return false;
    return true;       
}


bool search(vector<int>& a,int start,int end,int key) {
      while(start < end) {
          int mid = start + (end-start)/2;
          if(a[mid] == key) {
              return true;
          }
          if(a[mid] < a[end]) { // right half sorted  eg. 5,6,1,2,3,4 
              if(key>a[mid] && key<=a[end])
                  start = mid+1;
              else
                  end = mid;
          } else if(a[mid]>a[end]) {  // left half sorted eg. 3,4,5,6,1,2
              if(key >= a[start] && key<a[mid]) 
                  end = mid;
              else
                  start = mid+1;
          } else {
              end = end - 1;
          }
          
      }
     if (start == end && key != a[start]) { 
           return false;
   }
  return true;
}

bool search(vector<int>& nums, int target) {
  int start = 0;
  int end = nums.size() - 1;
  return search(nums,start,end,target);
}
