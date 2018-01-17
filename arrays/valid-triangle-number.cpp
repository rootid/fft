//Valid Triangle Number
//Given an array consists of non-negative integers, your task is to count the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.
//Example 1:
//Input: [2,2,3,4]
//Output: 3
//Explanation:
//Valid combinations are: 
//2,3,4 (using the first 2)
//2,3,4 (using the second 2)
//2,2,3
//Note:
//The length of the given array won't exceed 1000.
//The integers in the given array are in the range of [0, 1000].

// a+b>c : triangle number constraint
//after soring the array, if a<b<c, it only need to find (a,b) pairs their sum is greater than c
//################################### O(n^2) ################################### 

/** we need to find 3 number, i < j < k, and a[i] + a[j] > a[k];
* if we sort the array, then we can easily use two pointer to find all the pairs we need.
* if at some point a[left] + a[right] > a[i], all the elements from left to right-1 are valid.
* because they are all greater then a[left];
* so we do count += right - left; and right--
*
* otherwise, we increment left till we get a valid pair.
*/

//A pointer is allowed to be NULL but a reference is not
int triangleNumber(vector<int>& nums) {
	if (nums.size() <= 2) {
		return 0;
	}
    	sort(nums.begin(), nums.end());
	int count = 0;
	
	for (int i = 0; i < nums.size(); i++) {
		int left = 0, right = i-1;
		while (left < right) {
			if (nums[left] + nums[right] > nums[i]) {
				count += right - left;
				right--;
			} else {
				left++;
			}
		}
	}
	
	return count;
}

//r-l keeps track of number of pairs from r to l 
//that forms a valid triplet (follows triangle inequality property) with the third side represented by i
//In this case -> [2,4] and [2,4] are the two pairs (using first 2 and second 2)
int triangleNumber(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int count = 0, n = nums.size();
    for (int i=n-1;i>=2;i--) {
        int l = 0, r = i-1;
        while (l < r) {
            if (nums[l] + nums[r] > nums[i]) {
                count += r-l;
                r--;
            } else {
		l++; 
	   }
	}
    }
    return count;
}
//use [2,2,4,5], (2(index 0)+4(index 2)) > 5. Why to increase the count by 2 rather than 1?
//1. The array is sorted.
//2. By (1), the elements at the right side of the first 2 are guaranteed to be larger than or equal to the first 2.
//3. By (2), if the sum of the first 2 and 4 is larger than 5, it implies that the sum of 4 and the numbers to the right of the first 2 is larger than 5.
//4. By (3), you can safely include all pairs between r-l to the solution.

//################################### sort  ################################### 

//################################### O(n^2) ################################### 

//def triangleNumber(self, nums):
//    n, res = len(nums), 0
//    if n < 3:
//        return 0
//    nums.sort()
//    for i in range(2, n):
//        left, right = 0, i-1
//        while left < right:
//            if nums[left] + nums[right] > nums[i]:
//                res += right - left
//                right -= 1
//            else:
//                left += 1
//    return res
//def triangleNumber(self,nums):
//    """
//    :type nums: List[int]
//    :rtype: int
//    """
//    final = 0
//    nums = sorted(nums)
//    for i in range(2,len(nums))[::-1]:
//        l = 0
//        r = i-1
//        while (r>l):
//            if nums[l]+nums[r] > nums[i]:
//                final += r-l
//                r-=1
//            else:
//                l+=1
//    return final

//def triangleNumber(self, A):
//    C = collections.Counter(A)
//    C.pop(0, None)
//    B = sorted(C.keys())
//    P = [0]
//    for x in B:
//        P.append(P[-1] + C[x])
//        
//    ans = 0
//    for j, v in enumerate(B):
//        k = len(B) - 1
//        i = j
//        while 0 <= i <= j <= k:
//            while k > j and B[i] + B[j] <= B[k]:
//                k -= 1
//            if i < j:
//                ans += C[B[i]] * C[B[j]] * (P[k+1] - P[j+1])
//                ans += C[B[i]] * C[B[j]] * (C[B[j]] - 1) / 2
//            else:
//                ans += C[B[i]] * (C[B[i]] - 1) / 2 * (P[k+1] - P[j+1])
//                ans += C[B[i]] * (C[B[i]] - 1) * (C[B[i]] - 2) / 6
//            i -= 1
//    return ans
