//Merge Sorted Array 
//
//Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
//
//Note:
//You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n respectively.
//
//
//1 3 4 9
//4 5 9 30 31


#include<iostream>
#include<vector>
using namespace std;

void printVector(vector<int>& nums1) {

  for(auto& i:nums1) {
    cout << i << "\t";
  }
  cout << endl;
}

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

  int idx = m+n-1;

  printVector(nums1);
  printVector(nums2);
  for(int i=m-1,j=n-1;i>=0 || j>=0;) {
    if(nums1[i] > nums2[j]) {
      nums1[idx] = nums1[i];
      i -= 1;
    } else {
      nums1[idx] = nums2[j];
      j -= 1;
    }
    idx -= 1;
  }

  printVector(nums1);
}

int main() {

  int a[]= {1,3,4,9,4,5,9,30,31};
  int b[] = {4,5,9,30,31};
  vector<int> av(a,a+sizeof(a)/sizeof(a[0]));
  vector<int> bv(b,b+sizeof(b)/sizeof(b[0]));
  int m = sizeof(a)/sizeof(a[0]);
  int n = sizeof(b)/sizeof(b[0]);
  m = m - n;
  cout << "m = " << m << " n = " << n << endl;
  merge(av,m,bv,n);

}
