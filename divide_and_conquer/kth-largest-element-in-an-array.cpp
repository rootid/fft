//Kth Largest Element in an Array
//Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.
//For example,
//Given [3,2,1,5,6,4] and k = 2, return 5.
//Note: 
//You may assume k is always valid, 1 ≤ k ≤ array's length.

//########################### min heap ########################### 
int findKthLargest(vector<int>& nums, int k) {
     priority_queue<int> pq(nums.begin(), nums.end()); //store in ascending order pq
     for (int i = 0; i < k - 1; i++) {
         pq.pop(); 
     }
     return pq.top();
}


//########################### max heap ########################### 
int findKthLargest(vector<int>& nums, int k) {
     priority_queue<int, vector<int>, greater<int> > pq;
     for(int i = 0; i < nums.size(); i++) {
         if(pq.size() == k) {
             int x = pq.top();
             if(nums[i] > x) { //store only upto k max elements
                 pq.pop();
                 pq.push(nums[i]);
             }
         } else {
             pq.push(nums[i]);
         }
     }
     return pq.top();
}

//########################################## Good  partition ########################################## 
int partition(vector<int>& nums, int left, int right) {
      int pivot = nums[left];
      int l = left + 1, r = right;
      while (l <= r) {
          if (nums[l] < pivot && nums[r] > pivot) {
              swap(nums[l++], nums[r--]);
          }
          if (nums[l] >= pivot) {
            l++; 
          }
          if (nums[r] <= pivot) {
            r--;
          }
      }
      swap(nums[left], nums[r]);
      return r;
}
  
int findKthLargest(vector<int>& nums, int k) {
      int left = 0, right = nums.size() - 1;
      while (true) {
          int pos = partition(nums, left, right);
          if (pos == k - 1) {
            return nums[pos];
          }
          if (pos > k - 1) { 
            right = pos - 1;
          }
          else { 
            left = pos + 1; 
          }
      }
}


//########################################## Ugly partition ########################################## 
int partition (vector<int> &vec,int start,int end) {
   int lt_pivot_idx = -1;
   int pivot_element = vec[end];
   for (int idx = 0; idx < (end -1) ;idx++) {
       if (vec[idx] < pivot_element) {
            lt_pivot_idx += 1;
            swap(vec[idx],vec[lt_pivot_idx]);
       } 
   }
  swap(vec[lt_pivot_idx + 1],vec[end]);
  return lt_pivot_idx + 1;
}

int findKthLargestHelper(vector<int> &vec,int k,int start,int end) {
    int p = 0; 
    if (k > end) {
      return -1;
    } 
    p = partition(vec,start,end);
    if (p < k) {
        findKthLargestHelper(vec,k,p,end);
    } else if (p > k) {
        findKthLargestHelper(vec,k,start,p-1);
    } 
    return vec[k];
}

int findKthLargest(vector<int> &vec,int k) {
  return findKthLargestHelper(vec,k,0,vec.size());
}
