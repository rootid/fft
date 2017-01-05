//Path Sum III
//You are given a binary tree in which each node contains an integer value.
//Find the number of paths that sum to a given value.
//The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).
//The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.
//Example:
//root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
//      10
//     /  \
//    5   -3
//   / \    \
//  3   2   11
// / \   \
//3  -2   1
//Return 3. The paths that sum to 8 are:
//1.  5 -> 3
//2.  5 -> 2 -> 1
//3. -3 -> 11
//

#include "../headers/global.hpp"
#include "../headers/treenode.h"

void helper(TreeNode *root,int sum,int org_sum,int& cnt ) {
  if(!root) {
    return;
  }
  int l_val = root->val;
  if(sum == 0) {
    cnt += 1;
    sum = org_sum;
  }  
  helper(root->left,sum-l_val,org_sum,cnt);
  helper(root->right,sum-l_val,org_sum,cnt);

}

int pathSum(TreeNode* root, int sum) {
    int cnt = 0;
    helper(root,sum,sum,cnt);
}




int rootSum(TreeNode* root, int sum) {
      if (root == nullptr)
          return 0;
      return (sum == root->val) + rootSum(root->left, sum - root->val) + rootSum(root->right, sum - root->val);
}
  
int pathSum(TreeNode* root, int sum) {
      if (root == nullptr)
          return 0;
      return rootSum(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
}
