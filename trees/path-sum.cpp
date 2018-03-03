//Path Sum
//Given a binary tree and a sum, determine if the tree has a root-to-leaf path
//such that adding up all the values along the path equals the given sum.
//For example:
//Given the below binary tree and sum = 22,
//              5
//             / \
//            4   8
//           /   / \
//          11  13  4
//         /  \      \
//        7    2      1
//return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.

#include "../headers/global.hpp"
#include "../headers/treenode.h"


//######################################### Path Sum Preorder recursion #########################################
public boolean hasPathSum(TreeNode root, int sum) {
    if(root == null) return false;
    if(root.left == null && root.right == null && sum - root.val == 0 ) return true;
    return hasPathSum(root.left, sum - root.val) || hasPathSum(root.right, sum - root.val);
}

//######################################### Recursion #########################################
public boolean hasPathSum(TreeNode root, int sum) {
    return hasPathSumHelper(root, sum);
}

boolean hasPathSumHelper(TreeNode root, int targetSum) {
    if(root != null) {
        if(targetSum - root.val == 0 && root.left == null && root.right == null) return true;
        return hasPathSumHelper(root.left, targetSum - root.val) || hasPathSumHelper(root.right, targetSum - root.val);
    }
    return false;
}


//######################################### Recursion #########################################
bool hasPathSum(TreeNode* root, int sum) {
      if(!root) {
          return false;
      }
      if(!root && sum != 0) {
          return false;
      }
      if(root->left == NULL && root->right == NULL && sum == root->val) {
          return  true;
      }
      return ( hasPathSum(root->left,sum-root->val) || hasPathSum(root->right,sum-root->val) );
}
