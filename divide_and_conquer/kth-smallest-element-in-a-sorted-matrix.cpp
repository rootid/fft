//Kth Smallest Element in a Sorted Matrix
//Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.
//Note that it is the kth smallest element in the sorted order, not the kth distinct element.
//Example:
//matrix = [
//   [ 1,  5,  9],
//   [10, 11, 13],
//   [12, 13, 15]
//],
//k = 8,
//return 13.
//Note: 
//You may assume k is always valid, 1 ≤ k ≤ n2.


//########################################### Bin search ########################################### 

//TODO case fixx : matrix=[[2000000000]], k=1. Better start with INT_MIN/INT_MAX or matrix[0][0]/matrix[n-1][n-1]

//##############################################  Bin search O(log n) ############################################## 
int kthSmallest(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    int left = matrix[0][0];
    int right = matrix[n-1][n-1];
    while (left < right) {
        int midv = (left + right) / 2;
        int count = 0;  // number of elements no bigger than midv
        for (int i = 0; i < n; i++) {
            vector<int>& row = matrix[i];
            count += upper_bound(row.begin(), row.end(), midv) - row.begin();
        }
        if (count < k) {
            left = midv + 1;
        } else {
            right = midv;    
        }
    }
    return left;
}

//############################################## FAster O(n) ############################################## 
int kthSmallest(vector<vector<int>>& matrix, int k) {
  int n=matrix.size();
  int l=matrix[0][0], r=matrix[n-1][n-1], mid;
  while(l<r){
      mid = l+r>>1;
      int cnt=0, j=n-1;
      for(int i=0;i<n;i++){
          while(j>=0&&matrix[i][j]>mid)
              j--;
          cnt+=j+1;
      }
      if(cnt<k)
          l=mid+1;
      else
          r=mid;
  }
  return l;
}

//############################################## O(n) algo ############################################## 
//This thread is inspired by @StefanPochmann's thread, which mentioned Mirzaian and Arjoandi's paper.
//
//Preparations
//
//When n==1 (i.e. the matrix is 1x1. n is the number of row), the problem is trival. Hencefore we only consider the case n>=2.
//Rather than finding one k-th element from the matrix, we will select TWO elements (say, k0-th element and k1-th element) simultaneously, such that 0<=k0<=k1<n*n and k1-k0<=4n. Obviously, if we can complete the aforementioned selection in O(n), we can find the k-th element in O(n) by simply letting k=k0=k1.
//Let x0 denote the k0-th element; let x1 denote the k1-th element. Obviously we have x0<=x1.
//Now we will introduce how to select x0 and x1 in O(n).
//
//General idea:
//For an nxn matrix, where n is large, we try to select x0 and x1 in a recursive way.
//
//(Determine submatrix) This step constructs one submatrix, whose number of elements will be approximately a quarter of the original matrix. The submatrix is defined as every other row and every other column of the original matrix. The last row and the last column are included too (the reason will be stated in the sequel.) Then the dimension of the matrix is approximately (n/2) x (n/2). The submatrix is recorded by the indices in the original matrix.
//Example 1: the original matrix has indices {0, 1, 2, 3, 4}, then the submatrix has indices {0, 2, 4}.
//Example 2: the original matrix has indices {0,1, 2, 3, 4, 5}, then the submatrix has indices {0, 2,4, 5}.
//
//(Determine new k's) This step determines two new k's (denoted as k0_ and k1_) such that (i) k0_ is the largest possible integer to ensure k0_-th element in the new submatrix (denoted as x0_) is not greater than x0; (ii) k1_ is the smallest possible integer to ensure k1_-th element in the new submatrix (denoted as x1_) is not less than x1. This step is the most tricky step.
//
//k0_ = floor(k0 / 4)
//k1_ = floor(k1 / 4) + n + 1 (when n is even)
//      floor((k1 + 2 * n + 1) / 4) (when n is odd)
//The picture can also be founded here.
//
//Recall that we mentioned the last row and column shall always be included in the matrix. That is to ensure we can always found the x1_ such that x1_ >= x1.
//
//(Call recursively) Obtainx0_ and x1_ by recursion.
//(Partition) Partition all elements in the original nxn elements into three parts: P1={e: e < x0_}, P2={e: x0_ <= e < x1_ }, P3={e: x1_ < e}. We only need to record the cardinality of P1 and P2 (denoted as |P1| and |P2| respectively), and the elements in P2. Obviously, the cardinality of P2 is O(n).
//(Get x0 and x1) From the definition of k0_ and k1_, we have |P1| < k0 <= |P1|+|P2|. When |P1| < k0 < |P1|+|P2|, x0 is the k0-|P1|-th element of P2; otherwise x0=x1_. x1 can be determined in a similar way. This action is also O(n).
//Complexities:
//
//Time: O(n) ----- Apply T(n) = T(n/2) + O(n) in the Master's Theorem.
//Space: O(n)
class Solution {
public:
	int kthSmallest(const vector<vector<int>> & matrix, int k)
	{
		if (k == 1) // guard for 1x1 matrix
		{
			return matrix.front().front();
		}

		size_t n = matrix.size();
		vector<size_t> indices(n);
		iota(indices.begin(), indices.end(), 0);
		array<size_t, 2> ks = { k - 1, k - 1 }; // use zero-based indices
		array<int, 2> results = biSelect(matrix, indices, ks);
		return results[0];
	}

private:
	// select two elements from four elements, recursively
	array<int, 2> biSelect(
		const vector<vector<int>> & matrix,
		const vector<size_t> & indices,
		const array<size_t, 2> & ks)
	// Select both ks[0]-th element and ks[1]-th element in the matrix,
	// where k0 = ks[0] and k1 = ks[1] and n = indices.size() satisfie
	// 0 <= k0 <= k1 < n*n  and  k1 - k0 <= 4n-4 = O(n)   and  n>=2
	{
		size_t n = indices.size();		
		if (n == 2u) // base case of resursion
		{			
			return biSelectNative(matrix, indices, ks);
		}
		
		// update indices
		vector<size_t> indices_;
		for (size_t idx = 0; idx < n; idx += 2)
		{
			indices_.push_back(indices[idx]);
		}
		if (n % 2 == 0) // ensure the last indice is included
		{
			indices_.push_back(indices.back());
		}

		// update ks
		// the new interval [xs_[0], xs_[1]] should contain [xs[0], xs[1]]
		// but the length of the new interval should be as small as possible
		// therefore, ks_[0] is the largest possible index to ensure xs_[0] <= xs[0]
		// ks_[1] is the smallest possible index to ensure xs_[1] >= xs[1]
		array<size_t, 2> ks_ = { ks[0] / 4, 0 };
		if (n % 2 == 0) // even
		{
			ks_[1] = ks[1] / 4 + n + 1;
		}
		else // odd
		{
			ks_[1] = (ks[1] + 2 * n + 1) / 4;
		}

		// call recursively
		array<int, 2> xs_ = biSelect(matrix, indices_, ks_);

		// Now we partipate all elements into three parts:
		// Part 1: {e : e < xs_[0]}.  For this part, we only record its cardinality
		// Part 2: {e : xs_[0] <= e < xs_[1]}. We store the set elementsBetween
		// Part 3: {e : x >= xs_[1]}. No use. Discard.
		array<int, 2> numbersOfElementsLessThanX = { 0, 0 };
		vector<int> elementsBetween; // [xs_[0], xs_[1])

		array<size_t, 2> cols = { n, n }; // column index such that elem >= x
		 // the first column where matrix(r, c) > b
		 // the first column where matrix(r, c) >= a
		for (size_t row = 0; row < n; ++row)
		{
			size_t row_indice = indices[row];
			for (size_t idx : {0, 1})
			{
				while ((cols[idx] > 0)
					&& (matrix[row_indice][indices[cols[idx] - 1]] >= xs_[idx]))
				{
					--cols[idx];
				}
				numbersOfElementsLessThanX[idx] += cols[idx];
			}
			for (size_t col = cols[0]; col < cols[1]; ++col)
			{
				elementsBetween.push_back(matrix[row_indice][indices[col]]);
			}
		}

		array<int, 2> xs; // the return value
		for (size_t idx : {0, 1})
		{
			size_t k = ks[idx];
			if (k < numbersOfElementsLessThanX[0]) // in the Part 1
			{
				xs[idx] = xs_[0];
			}
			else if (k < numbersOfElementsLessThanX[1]) // in the Part 2
			{
				size_t offset = k - numbersOfElementsLessThanX[0];
				vector<int>::iterator nth = next(elementsBetween.begin(), offset);
				nth_element(elementsBetween.begin(), nth, elementsBetween.end());
				xs[idx] = (*nth);
			}
			else // in the Part 3
			{
				xs[idx] = xs_[1];
			}
		}
		return xs;
	}

	// select two elements from four elements, using native way
	array<int, 2> biSelectNative(
		const vector<vector<int>> & matrix,
		const vector<size_t> & indices,
		const array<size_t, 2> & ks)
	{
		vector<int> allElements;
		for (size_t r : indices)
		{
			for (size_t c : indices)
			{
				allElements.push_back(matrix[r][c]);
			}
		}
		sort(allElements.begin(), allElements.end());
		array<int, 2> results;
		for (size_t idx : {0, 1})
		{
			results[idx] = allElements[ks[idx]];
		}
		return results;
	}
};


//######################################## Pytonic ######################################## 
//class Solution(object):
//    def kthSmallest(self, matrix, k):
//
//        # The median-of-medians selection function.
//        def pick(a, k):
//            if k == 1:
//                return min(a)
//            groups = (a[i:i+5] for i in range(0, len(a), 5))
//            medians = [sorted(group)[len(group) / 2] for group in groups]
//            pivot = pick(medians, len(medians) / 2 + 1)
//            smaller = [x for x in a if x < pivot]
//            if k <= len(smaller):
//                return pick(smaller, k)
//            k -= len(smaller) + a.count(pivot)
//            return pivot if k < 1 else pick([x for x in a if x > pivot], k)
//
//        # Find the k1-th and k2th smallest entries in the submatrix.
//        def biselect(index, k1, k2):
//
//            # Provide the submatrix.
//            n = len(index)
//            def A(i, j):
//                return matrix[index[i]][index[j]]
//            
//            # Base case.
//            if n <= 2:
//                nums = sorted(A(i, j) for i in range(n) for j in range(n))
//                return nums[k1-1], nums[k2-1]
//
//            # Solve the subproblem.
//            index_ = index[::2] + index[n-1+n%2:]
//            k1_ = (k1 + 2*n) / 4 + 1 if n % 2 else n + 1 + (k1 + 3) / 4
//            k2_ = (k2 + 3) / 4
//            a, b = biselect(index_, k1_, k2_)
//
//            # Prepare ra_less, rb_more and L with saddleback search variants.
//            ra_less = rb_more = 0
//            L = []
//            jb = n   # jb is the first where A(i, jb) is larger than b.
//            ja = n   # ja is the first where A(i, ja) is larger than or equal to a.
//            for i in range(n):
//                while jb and A(i, jb - 1) > b:
//                    jb -= 1
//                while ja and A(i, ja - 1) >= a:
//                    ja -= 1
//                ra_less += ja
//                rb_more += n - jb
//                L.extend(A(i, j) for j in range(jb, ja))
//                
//            # Compute and return x and y.
//            x = a if ra_less <= k1 - 1 else \
//                b if k1 + rb_more - n*n <= 0 else \
//                pick(L, k1 + rb_more - n*n)
//            y = a if ra_less <= k2 - 1 else \
//                b if k2 + rb_more - n*n <= 0 else \
//                pick(L, k2 + rb_more - n*n)
//            return x, y
//
//        # Set up and run the search.
//        n = len(matrix)
//        start = max(k - n*n + n-1, 0)
//        k -= n*n - (n - start)**2
//        return biselect(range(start, min(n, start+k)), k, k)[0]
//
//
//t's O(n) where n is the number of rows (and columns), not the number of elements. So it's very efficient. The algorithm is from the paper Selection in X + Y and matrices with sorted rows and columns, which I first saw mentioned by @elmirap (thanks).
//The basic idea: Consider the submatrix you get by removing every second row and every second column. This has about a quarter of the elements of the original matrix. And the k-th element (k-th smallest I mean) of the original matrix is roughly the (k/4)-th element of the submatrix. So roughly get the (k/4)-th element of the submatrix and then use that to find the k-th element of the original matrix in O(n) time. It's recursive, going down to smaller and smaller submatrices until a trivial 2×2 matrix. For more details I suggest checking out the paper, the first half is easy to read and explains things well. Or @zhiqing_xiao's solution+explanation.
//Cool: It uses variants of saddleback search that you might know for example from the Search a 2D Matrix II problem. And it uses the median of medians algorithm for linear-time selection.
//Optimization: If k is less than n, we only need to consider the top-left k×k matrix. Similar if k is almost n2. So it's even O(min(n, k, n^2-k)), I just didn't mention that in the title because I wanted to keep it simple and because those few very small or very large k are unlikely, most of the time k will be "medium" (and average n2/2).
//Implementation: I implemented the submatrix by using an index list through which the actual matrix data gets accessed. If [0, 1, 2, ..., n-1] is the index list of the original matrix, then [0, 2, 4, ...] is the index list of the submatrix and [0, 4, 8, ...] is the index list of the subsubmatrix and so on. This also covers the above optimization by starting with [0, 1, 2, ..., k-1] when applicable.
//Application: I believe it can be used to easily solve the Find K Pairs with Smallest Sums problem in time O(k) instead of O(k log n), which I think is the best posted so far. I might try that later if nobody beats me to it (if you do, let me know :-). Update: I did that now.
//
//Now that I can find the kth smallest element in a sorted n×n matrix in time O(min(n, k)), I can finally solve this problem in O(k).
//
//The idea:
//
//If nums1 or nums2 are larger than k, shrink them to size k.
//Build a virtual matrix of the pair sums, i.e., matrix[i][j] = nums1[i] + nums2[j]. Make it a square matrix by padding with "infinity" if necessary. With "virtual" I mean its entries will be computed on the fly, and only those that are needed. This is necessary to stay within O(k) time.
//Find the kth smallest sum kthSum by using that other algorithm.
//Use a saddleback search variation to discount the pairs with sum smaller than kthSum. After this, k tells how many pairs we need whose sum equals kthSum.
//Collect all pairs with sum smaller than kthSum as well as k pairs whose sum equals kthSum.
//Each of those steps only takes O(k) time.
//
//The code (minus the code for kthSmallest, which you can copy verbatim from my solution to the other problem):
//
//class Solution(object):
//    def kSmallestPairs(self, nums1_, nums2_, k):
//        # Use at most the first k of each, then get the sizes.
//        nums1 = nums1_[:k]
//        nums2 = nums2_[:k]
//        m, n = len(nums1), len(nums2)
//        # Gotta Catch 'Em All?
//        if k >= m * n:
//            return [[a, b] for a in nums1 for b in nums2]
//        
//        # Build a virtual matrix.
//        N, inf = max(m, n), float('inf')
//        class Row:
//            def __init__(self, i):
//                self.i = i
//            def __getitem__(self, j):
//                return nums1[self.i] + nums2[j] if self.i < m and j < n else inf
//        matrix = map(Row, range(N))
//        # Get the k-th sum.
//        kthSum = self.kthSmallest(matrix, k)
//        # Discount the pairs with sum smaller than the k-th.
//        j = min(k, n)
//        for a in nums1:
//            while j and a + nums2[j-1] >= kthSum:
//                j -= 1
//            k -= j
//        # Collect and return the pairs.
//        pairs = []
//        for a in nums1:
//            for b in nums2:
//                if a + b >= kthSum + (k > 0):
//                    break
//                pairs.append([a, b])
//                k -= a + b == kthSum
//        return pairs
//    def kthSmallest(self, matrix, k):
//        
//        # copy & paste from https://discuss.leetcode.com/topic/53126/o-n-from-paper-yes-o-rows
//
//
//def kSmallestPairs(self, nums1, nums2, k):
//    del nums1[k:]
//    del nums2[k:]
//
//from timeit import timeit
//import gc
//
//codes = (
//    'del nums[10:]',
//    'nums = nums[:10]',
//    'x = nums; nums = nums[:10]'
//    )
//    
//for e in range(27):
//    n = 2**e
//    times = []
//    for code in codes:
//        gc.collect()
//        times.append(timeit(code, 'nums = range(%d)' % n, number=1))
//    print '{:8} {:.7f} {:.7f} {:.7f}'.format(n, *times)
