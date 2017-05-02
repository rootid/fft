//Count of Smaller Numbers After Self
//You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].
//Example:
//Given nums = [5, 2, 6, 1]
//To the right of 5 there are 2 smaller elements (2 and 1).
//To the right of 2 there is only 1 smaller element (1).
//To the right of 6 there is 1 smaller element (1).
//To the right of 1 there is 0 smaller element.
//Return the array [2, 1, 1, 0].
//############################################# Binary search O(n log n) + Additional Space O(n)  #####################################
vector<int> countSmaller(vector<int>& nums) { 
  vector<int> ans(nums.size(), 0), sortedNums;
  for(int i = nums.size() - 1; i >= 0; i--){
      int idx = binarySearch(sortedNums, nums[i]);
      ans[i] = idx;
      sortedNums.insert(sortedNums.begin() + idx, nums[i]);
  }
  return ans;
}
// find the first position greater than or equal to target in sortedNums
int binarySearch(vector<int>& sortedNums, int target){
    int l = 0, r = sortedNums.size();
    while(l < r) {
        int m = l + (r - l) / 2; 
        if(sortedNums[m] < target) {
          l = m + 1;
        } else {
          r = m;
        }
    }
    return l;
}

//############################################# Binary search O(n log n) + Additional Space O(n) + In-built lower_bound function  #####################################
vector<int> countSmaller(vector<int>& nums) {
    vector<int> db;
    vector<int> result(nums.size());
    for(int i = nums.size()-1; i >= 0; i--) {
        auto it = lower_bound(db.begin(), db.end(), nums[i]);
        result[i] = it - db.begin();
        db.insert(it, nums[i]);
    }
    return result;
}

//############################################# D&C O(n log n) + Additional Space O(n) #####################################
void dandc(vector<int>& nums, vector<int>& vec, vector<int>& copy, int l, int r, int smaller[]) {
	if(l == r) return;
	int m = l+(r-l)/2;
	dandc(nums, vec, copy, l, m, smaller);
	dandc(nums, vec, copy, m+1, r, smaller);
	int i=l, j=m+1, k=l;
	while(i<=m || j<=r) {
	    if( j==r+1 || (i<=m &&  nums[vec[i]] <= nums[vec[j]])) {
	        copy[k++] = vec[i];
	        smaller[vec[i]] += j-m-1;
	        i++;
	    } else {
        copy[k++] = vec[j++];
      }
	}
	for(int i=l; i<=r; i++) {
		vec[i] = copy[i];
	}
}
vector<int> countSmaller(vector<int>& nums) {
	vector<int> res;
	if(nums.empty()) {
    return res;
  }
	vector<int> vec, copy;
	for(int i=0; i<nums.size(); i++) {
		vec.push_back(i);
		copy.push_back(i);
	}
	int smaller[nums.size()];
	for(int i=0; i<nums.size(); i++) {
		smaller[i] = 0;
	}
	dandc(nums, vec, copy, 0, vec.size()-1, smaller);
	for(int i: smaller) {
		res.push_back(i);
	}
	return res;
}
//############################################# same as above + divide and conquer + O(n log n) #####################################
vector<int> countSmaller(vector<int>& nums) {
    vector<int> res (nums.size(), 0);
    vector<pair<int, int>> v;
    for (int i = 0; i < nums.size(); i++) {
        v.emplace_back(nums[i], i); //keep <#,original idx>
    }
    mergeSort(v, res, 0, nums.size()-1);
    return res;
}
    
void mergeSort(vector<pair<int, int>>& v, vector<int>& res, int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    mergeSort(v, res, l, mid);
    mergeSort(v, res, mid+1, r);
    auto compare = [](pair<int, int> a, pair<int, int> b) { return a.first < b.first;};
    for (int i = mid; i >= l; i--) {
        auto it = lower_bound(v.begin()+mid+1, v.begin()+r+1, v[i], compare);
        int dis = distance(v.begin()+mid+1, it);
        if (dis == 0) break;
        res[v[i].second] += dis;
    }
    inplace_merge(v.begin()+l, v.begin()+mid+1, v.begin()+r+1, compare);
}
//############################################# same as above + divide and conquer + O(n log n) #####################################
void merge_countSmaller(vector<int>& indices, int first, int last, 
                        vector<int>& results, vector<int>& nums) {
    int count = last - first;
    if (count > 1) {
        int step = count / 2;
        int mid = first + step;
        merge_countSmaller(indices, first, mid, results, nums);
        merge_countSmaller(indices, mid, last, results, nums);
        vector<int> tmp;
        tmp.reserve(count);
        int idx1 = first;
        int idx2 = mid;
        int semicount = 0;
        while ((idx1 < mid) || (idx2 < last)) {
            if ((idx2 == last) || ((idx1 < mid) &&
                   (nums[indices[idx1]] <= nums[indices[idx2]]))) { 
                tmp.push_back(indices[idx1]);
                //update the precedence array i.e. results
                results[indices[idx1]] += semicount; 
                ++idx1;
            } else {
                //while choosing the element from the second array do not update the precedence arrar
			          tmp.push_back(indices[idx2]);
                ++semicount;
                ++idx2;
            }
        }
        move(tmp.begin(), tmp.end(), indices.begin()+first);
    }
}
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> results(n, 0);
        vector<int> indices(n, 0);
        iota(indices.begin(), indices.end(), 0);
        merge_countSmaller(indices, 0, n, results, nums);
        return results;
    }

//############################################# Naive O(n^2) #####################################
vector<int> countSmaller(vector<int>& nums) { 
  vector<int> res(nums.size(),0);
  // cout << nums.size() << endl;
  int len = nums.size();
  for(int i= len-2; i>=0;i--) {
      int n_idx = i+1;
      while( n_idx < len) {
          if(nums[i] > nums[n_idx++]) {
              res[i]++;
          }
      }
  }
  return res; 
}


//################################ Pytonic ################################ 
def countSmaller(self, nums):
    def sort(enum):
        half = len(enum) / 2
        if half:
            left, right = sort(enum[:half]), sort(enum[half:])
            for i in range(len(enum))[::-1]:
                if not right or left and left[-1][1] > right[-1][1]:
                    smaller[left[-1][0]] += len(right)
                    enum[i] = left.pop()
                else:
                    enum[i] = right.pop()
        return enum
    smaller = [0] * len(nums)
    sort(list(enumerate(nums)))
    return smaller

//################################ Pytonic ################################ 
def countSmaller(self, nums):
    def sort(enum):
        half = len(enum) / 2
        if half:
            left, right = sort(enum[:half]), sort(enum[half:])
            m, n = len(left), len(right)
            i = j = 0
            while i < m or j < n:
                if j == n or i < m and left[i][1] <= right[j][1]:
                    enum[i+j] = left[i]
                    smaller[left[i][0]] += j
                    i += 1
                else:
                    enum[i+j] = right[j]
                    j += 1
        return enum
    smaller = [0] * len(nums)
    sort(list(enumerate(nums)))
    return smaller

//####################
//class SegmentTreeNode(object):
//    def __init__(self, val, start, end):
//        self.val = val
//        self.start = start
//        self.end = end
//        self.children = []
//
////###################################### SegmentTree ###################################### 
//class SegmentTree(object):
//    def __init__(self, n):
//        self.root = self.build(0, n - 1)
//
//    def build(self, start, end):
//        if start > end:
//            return
//
//        root = SegmentTreeNode(0, start, end)
//        if start == end:
//            return root
//
//        mid = start + end >> 1
//        root.children = filter(None, [
//            self.build(start, end)
//            for start, end in ((start, mid), (mid + 1, end))])
//        return root
//
//    def update(self, i, val, root=None):
//        root = root or self.root
//        if i < root.start or i > root.end:
//            return root.val
//
//        if i == root.start == root.end:
//            root.val += val
//            return root.val
//
//        root.val = sum([self.update(i, val, c) for c in root.children])
//        return root.val
//
//    def sum(self, start, end, root=None):
//        root = root or self.root
//        if end < root.start or start > root.end:
//            return 0
//
//        if start <= root.start and end >= root.end:
//            return root.val
//
//        return sum([self.sum(start, end, c) for c in root.children])
//
//
//class Solution(object):
//    def countSmaller(self, nums):
//        hashTable = {v: i for i, v in enumerate(sorted(set(nums)))}
//
//        tree, r = SegmentTree(len(hashTable)), []
//        for i in xrange(len(nums) - 1, -1, -1):
//            r.append(tree.sum(0, hashTable[nums[i]] - 1))
//            tree.update(hashTable[nums[i]], 1)
//        return r[::-1]
////####################### Binary indexed tree
//
//class BinaryIndexedTree(object):
//    def __init__(self, n):
//        self.sums = [0] * (n + 1)
//
//    def update(self, i, val):
//        while i < len(self.sums):
//            self.sums[i] += 1
//            i += i & -i
//
//    def sum(self, i):
//        r = 0
//        while i > 0:
//            r += self.sums[i]
//            i -= i & -i
//        return r
//
//
//class Solution(object):
//    def countSmaller(self, nums):
//        hashTable = {v: i for i, v in enumerate(sorted(set(nums)))}
//
//        tree, r = BinaryIndexedTree(len(hashTable)), []
//        for i in xrange(len(nums) - 1, -1, -1):
//            r.append(tree.sum(hashTable[nums[i]]))
//            tree.update(hashTable[nums[i]] + 1, 1)
//        return r[::-1]
//
//
////#################################### BST 
//
//class BinarySearchTreeNode(object):
//    def __init__(self, val):
//        self.val = val
//        self.left = None
//        self.right = None
//        self.count = 1
//        self.leftTreeSize = 0
//
//
//class BinarySearchTree(object):
//    def __init__(self):
//        self.root = None
//
//    def insert(self, val, root):
//        if not root:
//            self.root = BinarySearchTreeNode(val)
//            return 0
//
//        if val == root.val:
//            root.count += 1
//            return root.leftTreeSize
//
//        if val < root.val:
//            root.leftTreeSize += 1
//
//            if not root.left:
//                root.left = BinarySearchTreeNode(val)
//                return 0
//            return self.insert(val, root.left)
//
//        if not root.right:
//            root.right = BinarySearchTreeNode(val)
//            return root.count + root.leftTreeSize
//
//        return root.count + root.leftTreeSize + self.insert(
//            val, root.right)
//
//
//class Solution(object):
//    def countSmaller(self, nums):
//        tree = BinarySearchTree()
//        return [
//            tree.insert(nums[i], tree.root)
//            for i in xrange(len(nums) - 1, -1, -1)
//        ][::-1]
//
//#########################  BST Rank tree ################### 
//class TreeNode(object):
//    def __init__(self, x):
//        self.val = x
//        self.left = None
//        self.right = None
//        self.rank = 0
//
//class RankTree(object):
//    def __init__(self):
//        self.root = None
//    def insert(self, val):
//        def _insert(root, val):
//            if not root:
//                return TreeNode(val)
//            if val <= root.val:
//                root.left = _insert(root.left, val)
//                root.rank += 1
//            if val > root.val:
//                root.right = _insert(root.right, val)
//            return root
//        self.root = _insert(self.root, val)
//    
//    def get_rank(self, val):
//        def _get_rank(root, val):
//            if not root:
//                return 0
//            if root.val >= val:
//                # Go left and look for rank of predecessor
//                return _get_rank(root.left, val)
//            else:
//                # Go right and look for rank of successor
//                return 1 + root.rank + _get_rank(root.right, val)
//        return _get_rank(self.root, val)
//
//class Solution(object):
//    def countSmaller(self, nums):
//        R, res = RankTree(), []
//        for elem in nums[::-1]:
//            R.insert(elem)
//            res.insert(0, R.get_rank(elem))
//        return res
