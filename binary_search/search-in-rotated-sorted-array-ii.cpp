//Search in Rotated Sorted Array II
//Follow up for "Search in Rotated Sorted Array":
//What if duplicates are allowed?
//Would this affect the run-time complexity? How and why?
//Write a function to determine if a given target is in the array.
//
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
