//Search in Rotated Sorted Array
//Suppose a sorted array is rotated at some pivot unknown to you beforehand.
//(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
//You are given a target value to search. If found in the array return its index, otherwise return -1.
//You may assume no duplicate exists in the array.
//
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
