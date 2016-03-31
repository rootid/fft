//Contains Duplicate 
//Given an array of integers, find if the array contains any duplicates. Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.
//TO : O(n lg n) + O(n)
//SO : O(k)
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool containsDuplicate(vector<int>& nums) {

  if( nums.size() <= 1) {
    return true;
  }
  sort(nums.begin(),nums.end()) ;
  int len = nums.size();
  
  for (int i=0;i<len-1;++i) {
    if(nums[i] == nums[i+1]) {
        return true;
    }
  }
 return false;
}

void containsWrapper(vector<int>& nums) {
  if (true == containsDuplicate(nums) ) {
      cout << "Found duplicate." << endl;
  } else {
      cout << "All elements are distinct." << endl;
  }
}

int main() {

  int a[] = {1,9,7,2,100,24,1,300};
  vector<int> nums(a,a+sizeof(a)/sizeof(a[0])) ;
  containsWrapper(nums);

}
