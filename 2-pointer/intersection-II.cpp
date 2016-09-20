vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
      sort(nums1.begin(),nums1.end());
      sort(nums2.begin(),nums2.end());
      vector<int> nums3;
      int idx = 0;
      int l1 = nums1.size() - 1;
      int l2 = nums2.size() -1 ;
      while(l1 >= 0 && l2 >= 0) {
          if(nums1[l1] > nums2[l2]) {
              l1 -= 1;
          } else if (nums1[l1] < nums2[l2]) {
              l2 -=1 ;
          } else {
             // To Keep the re-visited elements
              while( l1 >= 0 && l2 >= 0 && nums1[l1] == nums2[l2] ) {
                  nums3.push_back(nums1[l1]);
                  l1 -= 1;
                  l2 -= 1;
              }
          }
      }
      return nums3;
}


vector<int> intersectGood(vector<int>& nums1, vector<int>& nums2) {
   unordered_map<int, int> ctr;
    for (int i : a)
        ctr[i]++;
    vector<int> out;
    for (int i : b)
        if (ctr[i]-- > 0)
            out.push_back(i);
    return out;
}
