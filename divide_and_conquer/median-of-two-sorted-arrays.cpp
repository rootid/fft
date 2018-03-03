//Median of Two Sorted Arrays
//There are two sorted arrays nums1 and nums2 of size m and n respectively.
//Find the median of the two sorted arrays. The overall run time complexity
//should be O(log (m+n)).
//Example 1:
//nums1 = [1, 3]
//nums2 = [2]
//The median is 2.0
//Example 2:
//nums1 = [1, 2]
//nums2 = [3, 4]
//The median is (2 + 3)/2 = 2.5
//####################### log(m+m) with log base 4/3 #######################
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
     int len1 = nums1.size(), len2 = nums2.size();
     int k = (len1 + len2 + 1) / 2; // for odd total it is the mid one, for even it is the left mid
     int num1 = findKth(nums1, 0, len1 - 1, nums2, 0, len2 - 1, k);
     if ((len1 + len2) & 1) return num1; //for odd size only k is required
     int num2 = findKth(nums1, 0, len1 - 1, nums2, 0, len2 - 1, k + 1);
     return (num1 + num2) / 2.0;
}
int findKth(vector<int>& nums1, int L1, int R1, vector<int>& nums2, int L2, int R2, int k) {
    if (L1 > R1)  //nums1 finished
      return nums2[L2 + k - 1];
    if (L2 > R2)  //nums2 finished
      return nums1[L1 + k - 1];
    int mid1 = L1 + (R1 - L1) / 2, mid2 = L2 + (R2 - L2);
    //K is in the first half (A/2-B/2)
    if (k <= (mid1 - L1) + (mid2 - L2) + 1) {
        if (nums1[mid1] <= nums2[mid2]) {
          //A-B(mid2-1--k) pick lt(B)
          return findKth(nums1, L1, R1, nums2, L2, mid2 - 1, k);
        }
      //pick lt(A)
      return findKth(nums1, L1, mid1 - 1, nums2, L2, R2, k);
    }
    //K is in the 2nd half (mid1+1-mid2+1)
    if (nums1[mid1] <= nums2[mid2]) {
      //NOTE : Need to update k while searching in the right half (pick rt(A))
      return findKth(nums1, mid1 + 1, R1, nums2, L2, R2, k - (mid1 - L1) - 1);
    }
    //NOTE : Need to update k while searching in the right half (pick rt(B))
    return findKth(nums1, L1, R1, nums2, mid2 + 1, R2, k - (mid2 - L2) - 1);
}
//##################################################################################################
//O(m+n)
int ans(vector<int>& nums1,vector<int>& nums2,int k){
    int n = nums1.size();
    int m = nums2.size();
    if(n > m){
        return ans(nums2,nums1,k);
    }
    if(n == 0) return nums2[k-1];
    if(k == 1) return min(nums1[0],nums2[0]);

    int pa = min(k/2,n),pb = k - pa;
    if(nums1[pa - 1] < nums2[pb - 1] ){
         vector<int> a(nums1.begin() + pa, nums1.end());
         return ans(a,nums2,k - pa);
    }
    else if(nums1[pa - 1] > nums2[pb - 1]){
        vector<int> b(nums2.begin() + pb,nums2.end());
        return ans(nums1,b,k - pb);
    }
    else return nums1[pa-1];
}
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
       int n = nums1.size();
        int m = nums2.size();
        int k = (n + m)/2;
        int t = m+n;
        if(t & 0x01) {
            return ans(nums1,nums2,k + 1);
        }
        else {
            return (ans(nums1,nums2,k) + ans(nums1,nums2,k+1))/2.0;
        }
 }
// T(m+n) <= T(3/4*(m+n)) + O(1)
//###########################################################################################
 double findMedianSortedArrays(int A[], int m, int B[], int n) {
        if ((m+n) % 2 == 1)
            return findkthElement(A, m, B, n, (m+n)/2+1);
        else
            return (findkthElement(A, m, B, n, (m+n)/2) + findkthElement(A, m, B, n, (m+n)/2+1))/2.0;
    }

    int findkthElement(int A[], int m, int B[], int n, int k) {
        if (m == 0) return B[k-1];
        if (n == 0) return A[k-1];
        if (k == 1) return min(A[0], B[0]);
        if (m < n) return findkthElement(B, n, A, m, k);
        int i = m/2;
        int low = 0, high = n-1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (B[mid] <= A[i]) low = mid + 1; else high = mid - 1;
        }
        int j = high; //B[j] is the maximum number which <= A[i]
        if (i+j+2 == k) //i+j+2 is the rank of A[i]
            return A[i];
        else if (i+j+2 < k)
            return findkthElement(A+i+1, m-i-1, B+j+1, n-j-1, k-i-j-2);
        else
            return findkthElement(A, i, B, j+1, k);
    }
//int main() {
//    Solution sln;
//
//    int a[] = {};
//    int m = sizeof(a) / sizeof(int);
//    int b[] = {1};
//    int n = sizeof(b) / sizeof(int);
//
//    cout << sln.findMedianSortedArrays(a, m, b, n) << endl;
//    return 0;
