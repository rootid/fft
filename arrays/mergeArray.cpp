//Merge Sorted Array
//Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
//Note:
//You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n respectively.
#include<vector>
#include<iostream>
using namespace std;


void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
      
      int lm = nums1.size() - 1;
      m--;
      n--;
      while(m >= 0 && n >= 0) {
          if(nums1[m] > nums2[n]) {
              nums1[lm--] = nums1[m--];
          } else {
             nums1[lm--] = nums2[n--];
          }
      }
      while (n >= 0) {
            nums1[lm--] = nums2[n--]; 
      }
}
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
     
     int idx = m + n -1;
     m = m -1;
     n = n -1;
     while(m >= 0 && n >= 0) {
         if(nums1[m] > nums2[n]) {
             nums1[idx] = nums1[m];
             m = m -1;
         } else {
             nums1[idx] = nums2[n];
             n = n -1;
         }
         idx = idx -1;
     }
     //cout << "count " << endl;
     for(int i=n;i>=0;i--) {
         nums1[idx] = nums2[i];
         idx -= 1;
     }
     
}
  //void merge(int A[], int m, int B[], int n) {
  //      int i=m-1;
  //      int j=n-1;
  //      int k = m+n-1;
  //      while(i >=0 && j>=0)
  //      {
  //          if(A[i] > B[j])
  //              A[k--] = A[i--];
  //          else
  //              A[k--] = B[j--];
  //      }
  //      while(j>=0)
  //          A[k--] = B[j--];
  //  }
int main(int argc, char *argv[])
{
  vector<int> av( {1,2,3,4,5} );
  vector<int> bv;
  int m = av.size();
  int n = bv.size();
  merge(av,m,bv,n);
  return 0;
}
