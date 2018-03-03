//Maximum Binary Tree
//Given an integer array with no duplicates. A maximum tree building on this
//array is defined as follow:
//The root is the maximum number in the array.
//The left subtree is the maximum tree constructed from left part subarray
//divided by the maximum number.
//The right subtree is the maximum tree constructed from right part subarray
//divided by the maximum number.
//Construct the maximum tree by the given array and output the root node of
//this tree.
//Example 1:
//Input: [3,2,1,6,0,5]
//Output: return the tree root node representing the following tree:
//      6
//    /   \
//   3     5
//    \    /
//     2  0
//       \
//        1
//Note:

//############################### Recursive ###############################
// O(n^2), the space complexity is O(1).
public TreeNode constructMaximumBinaryTree(int[] nums) {
        return helper(nums, 0, nums.length - 1);
}
//max_index denotes the index of the maximum number in range [left, right]
public TreeNode helper(int[] nums, int left, int right){
    if(left>right)return null;
    int max_index = left;
    for(int i = left; i <= right; i++){
        if(nums[i] > nums[max_index])max_index = i;
    }
    TreeNode root = new TreeNode(nums[max_index]);
    root.left = helper(nums, left, max_index - 1);
    root.right = helper(nums, max_index + 1, right);
    return root;
}

//############################### Recursive + cpp ###############################
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
	return helper(nums, 0, nums.size() - 1);
}

//max_index denotes the index of the maximum number in range [left, right]
TreeNode* helper(vector<int>& nums, int left, int right){
    if(left>right)return NULL;

    int max_index = left;
    for(int i = left; i<=right; i++){
        if(nums[i] > nums[max_index])max_index = i;
    }

    TreeNode* root = new TreeNode(nums[max_index]);
    root->left = helper(nums, left, max_index - 1);
    root->right = helper(nums, max_index + 1, right);
    return root;
}


//############################### Stack ###############################
//1.We scan numbers from left to right, build the tree one node by one step;
//2.We use a stack to keep some (not all) tree nodes and ensure a decreasing
//order;
//3. For each number, we keep pop the stack until empty or a bigger number; The
//bigger number (if exist, it will be still in stack) is current number's root,
//and the last popped number (if exist) is current number's right child
//(temporarily, this relationship may change in the future); Then we push
//current number into the stack.
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    vector<TreeNode*> stk;
    for (int i = 0; i < nums.size(); ++i) {
        TreeNode* cur = new TreeNode(nums[i]);
        while (!stk.empty() && stk.back()->val < nums[i]) {
            cur->left = stk.back();
            stk.pop_back();
        }
        if (!stk.empty())
            stk.back()->right = cur;
        stk.push_back(cur);
    }
    return stk.front();
}

//############################### Binary search ###############################
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    vector<TreeNode*> s { new TreeNode(nums[0]) };
    for (int i = 1; i < nums.size(); ++i) {
        TreeNode* cur = new TreeNode(nums[i]);
        auto it = upper_bound(s.rbegin(), s.rend(), cur,
                              [](const TreeNode* a, const TreeNode* b) { return a->val < b->val; });
        if (it != s.rend()) (*it)->right = cur;
        if (it != s.rbegin()) cur->left = *next(it, -1);
        s.resize(distance(it, s.rend()));
        s.push_back(cur);
    }
    return s.front();
}

//############################### With Sorted Map ###############################
//We populate right subtree if numbers are decreasing.
//If the current number is larger than any numbers in the right subtree,
//we find the first that is smaller, and make it a left subtree of the current
//number.
//The current number becomes a leaf of the right subtree.
//I use map as it provides the convenient insert operation,
//that returns the position of the inserted element in O (log n)
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    map<int, TreeNode*> q = { { nums[0], new TreeNode(nums[0]) } };
    for (auto i = 1; i < nums.size(); ++i) {
        auto it_b = q.insert({ nums[i], new TreeNode(nums[i]) });
        if (it_b.first != q.begin()) { // left tree.
            it_b.first->second->left = next(it_b.first, -1)->second;
            q.erase(q.begin(), it_b.first);
        }
        if (next(it_b.first, 1) != q.end()) // right tree.
            next(it_b.first, 1)->second->right = it_b.first->second;
    }
    return q.rbegin()->second;
}

//###############################  O(n) ###############################
public TreeNode constructMaximumBinaryTree(int[] nums) {
	LinkedList<TreeNode> lklist = new LinkedList<>();
    TreeNode left = null;
    for (int num: nums) {
		TreeNode cur = new TreeNode(num);
        while (!lklist.isEmpty() && lklist.peekFirst().val < cur.val){
            cur.left = lklist.pop();
        }
        if (!lklist.isEmpty()){
            lklist.peekFirst().right = cur;
        }
        lklist.push(cur);
    }
    return lklist.peekLast();
}


//############################### Recursion ###############################
def constructMaximumBinaryTree(self, nums):
    dummy = TreeNode(None)
    def d(root, nums):
        if not nums:
            return
        i = nums.index(max(nums))
        root.val = max(nums)
        if nums[:i]:
            root.left = TreeNode(None)
            d(root.left, nums[:i])
        if nums[i+1:]:
            root.right = TreeNode(None)
            d(root.right, nums[i+1:])
    d(dummy, nums)
    return dummy

//############################### Recursion shorter ###############################
class Solution(object):
    def constructMaximumBinaryTree(self, nums):
        if nums:
            pos = nums.index(max(nums))
            root = TreeNode(nums[pos])
            root.left = self.constructMaximumBinaryTree(nums[:pos])
            root.right = self.constructMaximumBinaryTree(nums[pos+1:])
            return root
