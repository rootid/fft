//Minimum Absolute Difference in BST
//Given a binary search tree with non-negative values, find the minimum
//absolute difference between values of any two nodes.
//Example:
//Input:
//   1
//    \
//     3
//    /
//   2
//Output:
//1
//Explanation:
//The minimum absolute difference is 1, which is the difference between 2 and 1
//(or between 2 and 3).
//Note: There are at least two nodes in this BST.

#include "../headers/global.hpp"

//######################## Keep track of predecessor value ########################
class Solution {
    int minDiff = Integer.MAX_VALUE;
    int preVal =  Integer.MAX_VALUE;

    public void getMinimumDifferenceHelper(TreeNode root) {
         if(root == null) return;
         getMinimumDifferenceHelper(root.left);
         minDiff = Math.min(minDiff , Math.abs(preVal - root.val));
         preVal = root.val;
         getMinimumDifferenceHelper(root.right);

    }

    public int getMinimumDifference(TreeNode root) {
       getMinimumDifferenceHelper(root);
       return minDiff;
    }
}

//######################## Keep track of predecessor value ########################
public class Solution {
    private int min = Integer.MAX_VALUE;
    private TreeNode pre = null;
    public int getMinimumDifference(TreeNode root) {
        inorder(root);
        return min;
    }
    public void inorder(TreeNode root){
        if(root == null) return;
        inorder(root.left);
        if(pre != null){
            min = Math.min(min, root.val-pre.val);
        }
        pre = root;
        inorder(root.right);
    }
}


//######################## With only predecessor ########################
void helper(TreeNode *node, TreeNode *&prev, int &ans) {
       if (!node)
           return;
       helper(node->left, prev, ans);
       if (prev) {
           ans = min(ans, node->val - prev->val);
       }
       prev = node;
       helper(node->right, prev, ans);
}

int getMinimumDifference(TreeNode* root) {
    int ans = INT_MAX;
    TreeNode *prev = NULL;
    helper(root, prev, ans);
    return ans;
}

//############################# With explicit stack (take min between curr-pred and curr-succ)
int getMinimumDifference(TreeNode* root) {
    int res = INT_MAX;
    if(root == nullptr) return res;
    stack<TreeNode*> sk;
    TreeNode* pre = nullptr;
    TreeNode* suc = nullptr;
    while(true){
        while(root){
            sk.push(root);
            root = root->left;
        }
        if(sk.empty()) {
          break;
        }
        root = sk.top();
        sk.pop();
        //suc = (!sk.empty()) ? sk.top() : nullptr;
        if (!sk.empty()) {
          suc = sk.top();
        } else {
          suc = nullptr;
        }
        if(pre){
            res = min(res, abs(root->val - pre->val));
        }
        if(suc){
            res = min(res, abs(root->val - suc->val));
        }
        pre = root;
        root = root->right;
    }
    return res;
}
