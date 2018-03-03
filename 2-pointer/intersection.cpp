//Intersection of Two Arrays II
//Given two arrays, write a function to compute their intersection.
//Example:
//Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].
//Note:
//    Each element in the result must be unique.
//    The result can be in any order.
//

//Cnstrnt
//1. range of numbers
//2. duplicates? rules to handle duplicate?

//Ida
//1. use of right DS
//2. Use of sorting alg
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {

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
                while( l1 >= 0 && l2 >= 0 && nums1[l1] == nums2[l2] ) {
                    if(nums3.size() == 0 || nums3[nums3.size() - 1] != nums1[l1] ) {
                        nums3.push_back(nums1[l1]);
                    }
                    l1 -= 1;
                    l2 -= 1;
                }
            }
        }
        return nums3;
    }
    vector<int> intersectionGood(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> tmp(nums1.begin(),nums1.end());
        vector<int> nums3;
        for(int x:nums2) {
          if(tmp.erase(x)) {
            nums3.push_back(x);
          }
        }
        return nums3;
    }
};
