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
  int maxP[len];
  int minP[len];
  maxP[0] = nums[0];
  minP[0] = nums[0];
  maxProduct = nums[0];
  for(int i=1;i<len;i++) {
    //NOTE : it can be solved with 2 variables only 
    maxP[i] = max( max (minP[i-1] * nums[i], maxP[i-1]*nums[i]) , nums[i]);;
    minP[i] = min( min (minP[i-1] * nums[i], maxP[i-1]*nums[i]) , nums[i]);
    maxProduct = max(maxProduct,maxP[i]);
  }
 return maxProduct;
}

//maxp(0--n) : max (maxp(0--n-1)*n or minp(0--n-1) *n )
//int lmin=nums[0];
//int lmax=lmin;
//int gmax=lmax;
//
//for( int i=1;i<nums.size();i++)
//{
//    int t1 = nums[i]*lmax;
//    int t2 = nums[i]*lmin;
//
//    lmax = max( max(t1,t2), nums[i] );
//    lmin = min( min(t1,t2), nums[i]);
//    gmax =max(gmax, lmax);
//
//}
//return gmax;

int main() {

 //int a[] = {-6,12,-7,0,14,-7,5}; 

 int a[] = {2,-5,-2,-4,3}; 
 vector<int>  av (a,a+sizeof(a)/sizeof(a[0]));
 int maxP = maxProduct(av);
 cout << "MAX product = " << maxP << endl;
}
