//Range Sum Query - Mutable
//Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
//The update(i, val) function modifies nums by updating the element at index i to val.
//Example:
//Given nums = [1, 3, 5]
//sumRange(0, 2) -> 9
//update(1, 2)
//sumRange(0, 2) -> 8
//Note:
//The array is only modifiable by the update function.
//You may assume the number of calls to update and sumRange function is distributed evenly.

//####################################### Segment tree ##############################################################
struct SegmentTreeNode {
    int start, end, sum;
    SegmentTreeNode* left;
    SegmentTreeNode* right;
    SegmentTreeNode(int a, int b):start(a),end(b),sum(0),left(nullptr),right(nullptr){}
};
class NumArray {

private : 
    SegmentTreeNode* root;

    SegmentTreeNode* buildTree(vector<int> &nums, int start, int end) {
        if(start > end) 
          return nullptr;
        SegmentTreeNode* root = new SegmentTreeNode(start,end);
        if(start == end) {
           //leaf node
            root->sum = nums[start];
            return root;
        }
        int mid = start + (end - start) / 2; //  (start,mid)<---X--->(mid+1,end)
        root->left = buildTree(nums,start,mid);
        root->right = buildTree(nums,mid+1,end);
        //For Non leaf node : sum = addition of leaf nodes
        root->sum = root->left->sum + root->right->sum;
        
        return root;
    }

    //Go from Top to bottom
    int modifyTree(int i, int val, SegmentTreeNode* root) {
        if(root == nullptr) 
          return 0;
        int diff;
        if(root->start == i && root->end == i) {
            diff = val - root->sum;
            root->sum = val;
            return diff; //+Ve or -Ve Offset value computed using the leaf node
        }
        int mid = (root->start + root->end) / 2;
        if(i > mid) {
            diff = modifyTree(i,val,root->right);
        } else {
            diff = modifyTree(i,val,root->left);
        }
        root->sum = root->sum + diff;
        return diff;
    }

    //
    int queryTree(int i, int j, SegmentTreeNode* root) {
        if(root == nullptr) return 0;
        if(root->start == i && root->end == j) {
          return root->sum;
        }
        int mid = (root->start + root->end) / 2;
        if(i > mid) { //start > mid then go right
          return queryTree(i,j,root->right);
        }
        if(j <= mid) {  //end <= mid then go left
          return queryTree(i,j,root->left);
        }
        return queryTree(i,mid,root->left) + queryTree(mid+1,j,root->right);
    }

public:
    NumArray(vector<int> nums) {
        int n = nums.size();
        root = buildTree(nums,0,n-1);
    }
   
    void update(int i, int val) {
        modifyTree(i,val,root);
    }

    int sumRange(int i, int j) {
        return queryTree(i, j, root);
    }

};

//######################################### BIT  ######################################### 
class NumArray {
    vector<int> bit;
    vector<int> NUMS;
public:
    NumArray(vector<int> &nums) : NUMS(nums) {
        int size_nums = nums.size();
        bit.resize(size_nums + 1);
        for(int i = 0; i < size_nums; i++) {
            add(i, nums[i]);
        }
    }

    void update(int i, int val) {
        if(val != NUMS[i]){
            add(i, val - NUMS[i]);
            NUMS[i] = val;
        }
    }

    int sumRange(int i, int j) {
        return sum(j) - sum(i-1);
    }
    
    int last_bit(int i) {
        return i & (-i);
    }
    
    void add(int i, int val) {
        i++;
        while(i < bit.size()) {
            bit[i] += val;
            i += last_bit(i);
        }
    }
    
    int sum(int i) {
        i++;
        int sum = 0;
        while(i > 0) {
            sum += bit[i];
            i -= last_bit(i);
        }
        return sum;
    }
};

//####################################################### pytonic ##############################################

//############################################## BIT (Binary Indexed Tree) ############################################## 
//
//Use self.c to represent Binary Indexed Tree. Section sums are stored in self.c[1..len(nums)]. x & -x is lowbit function, which will return x's rightmost bit 1, e.g. lowbit(7) = 1, lowbit(20) = 4.
//self.c[1] = nums[0]
//self.c[2] = nums[0] + nums[1]
//self.c[3] = nums[2]
//self.c[4] = nums[0] + nums[1] + nums[2] + nums[3]
//self.c[5] = nums[4]
//self.c[6] = nums[4] + nums[5]
//self.c[7] = nums[6]
//self.c[8] = nums[0] + nums[1] + nums[2] + nums[3] + nums[4] + nums[5] + nums[6] + nums[7]
//class NumArray(object):
//    def __init__(self, nums):
//        self.n = len(nums)
//        self.a, self.c = nums, [0] * (self.n + 1)
//        //O(n^2) to init the tree 
//        for i in range(self.n):
//            k = i + 1
//            while k <= self.n:
//                self.c[k] += nums[i]
//                k += (k & -k)
//
//    def update(self, i, val):
//        diff, self.a[i] = val - self.a[i], val
//        i += 1
//        while i <= self.n:
//            self.c[i] += diff
//            i += (i & -i) //update/increase the idx bottom-up
//
//    def sumRange(self, i, j):
//        res, j = 0, j + 1
//        while j:
//            res += self.c[j]
//            j -= (j & -j) //reduce idx top-down
//        while i:
//            res -= self.c[i]
//            i -= (i & -i)
//        return res

//class NumArray(object):
//    def __init__(self, nums):
//        """
//        :type nums: List[int]
//        """
//        self.update = nums.__setitem__
//        self.sumRange = lambda i, j: sum(nums[i:j+1])
//
//    def update(self, i, val):
//        """
//        :type i: int
//        :type val: int
//        :rtype: void
//        """
//    def sumRange(self, i, j):
//        """
//        :type i: int
//        :type j: int
//        :rtype: int
//        """
//# Your NumArray object will be instantiated and called as such:
//# obj = NumArray(nums)
//# obj.update(i,val)
//# param_2 = obj.sumRange(i,j)

// vim: set sw=2 sts=2 tw=120 et nospell : 
