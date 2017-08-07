//Two Sum IV - Input is a BST
//Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.
//Example 1:
//Input: 
//    5
//   / \
//  3   6
// / \   \
//2   4   7
//Target = 9
//Output: True
//Example 2:
//Input: 
//    5
//   / \
//  3   6
// / \   \
//2   4   7
//Target = 28
//Output: False



//############################################# Recursive DFS ############################################# 
class Solution {
    set<int> s;
    bool dfs(TreeNode *cur, int k) {
        if (!cur) return false;
        if (s.count(k - cur->val)) return true;
        s.insert(cur->val);
        return dfs(cur->left, k) || dfs(cur->right, k);
    }
public:
    bool findTarget(TreeNode* root, int k) {
        s.clear();
        return dfs(root, k);
    }
};


// T: O(n) , S : O(n)
//############################################# Inorder traversal + Binary Search ############################################# 
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> nums;
        inorder(root, nums); // S : O(n)
        return findTargetInSortedArray(nums, k); T : O(n log n)
    }

private:
    void inorder(TreeNode* node, vector<int>& nums) {
        if (!node) return;
        inorder(node->left, nums);
        nums.push_back(node->val);
        inorder(node->right, nums);
    }
    bool findTargetInSortedArray(vector<int> a, int target) {
        for (int i = 0, j = a.size() - 1; i < j;) {
            int sum = a[i] + a[j];
            if (sum == target) {
                return true;
            }
            else if (sum < target) {
                i++;
            }
            else {
                j--;
            }
        }

        return false;
    }
};

//T :O(n) , S:(n)
//############################################# Operator overloading + Inorder traversal + Binary Search ############################################# 
class BSTIterator {
    stack<TreeNode*> s;
    TreeNode* node;
    bool forward;
    int cur;
public:
    BSTIterator(TreeNode *root, bool forward) : node(root), forward(forward) { (*this)++; };
    int operator*() { return cur; }
    void operator++(int) {
        while (node || !s.empty()) {
            if (node) {
                s.push(node);
                node = forward ? node->left : node->right;
            }
            else {
                node = s.top();
                s.pop();
                cur = node->val;
                node = forward ? node->right : node->left;
                break;
            }
        }
    }
};
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        if (!root) return false;
        BSTIterator l(root, true);
        BSTIterator r(root, false);
        while (*l < *r) {
            if (*l + *r == k) return true;
            else if (*l + *r < k) l++;
            else r++;
        }
        return false;
    }
};

//######################################### Pythonic ######################################### 
//######################################### BFS  ######################################### 
def findTarget(self, root, k):
        if not root: return False
        bfs, s = [root], set()
        for i in bfs:
            if k - i.val in s: return True
            s.add(i.val)
            if i.left: bfs.append(i.left)
            if i.right: bfs.append(i.right)
        return False
