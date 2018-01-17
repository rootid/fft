//Maximum Product Subarray
//
//Find the contiguous subarray within an array (containing at least one number) which has the largest product.
//For example, given the array [2,3,-2,4],
//the contiguous subarray [2,3] has the largest product = 6.
#include<iostream>
#include<limits.h>
#include<vector>
using namespace std;

int maxProduct(vector<int>& nums) {
  int len = nums.size();
  int maxProduct = INT_MIN;
  int lrp = 1;
  int rlp = 1;
  
  for(int i=0;i<len;i++) {
    lrp *= nums[i];
    rlp *= nums[ len-1-i ];
    maxProduct = max(maxProduct, max(lrp,rlp));  //{3,-1,4}
    if(lrp == 0) {
      lrp = 1;
    }
    if(rlp == 0) {
      rlp = 1;
    }
  }
  return maxProduct;
}

int main() {

 //int a[] = {-6,12,-7,0,14,-7,5}; 
 int a[] = {2,-5,-2,-4,3}; 
 vector<int>  av (a,a+sizeof(a)/sizeof(a[0]));
 int maxP = maxProduct(av);
 cout << "MAX product = " << maxP << endl;
}
