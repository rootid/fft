//Binary Tree Maximum Path Sum
//Given a binary tree, find the maximum path sum.
//For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.
//For example:
//Given the below binary tree,
//       1
//      / \
//     2   3
//Return 6.

#include "../headers/global.hpp"
#include "../headers/treenode.h"


//maxValue = max(maxValue, left + right + node->val);
//return max(left, right) + node->val;
//maxValue is the value which recording whether this current root is the final root, 
//so we use left + right + node.val. 
//But to the //upper layer(after return statement), we cannot choose both left and right branches, so we need to select the larger one, so we use max(left, right) + node.val to prune the lower branch.

int depth(TreeNode *root,int &res) { 
  if(root == NULL) 
    return 0;
  int a = depth(root->left,res); 
  int b = depth(root->right,res);
  res = max(res,a+b+root->val);//if *root is the top node in the path (left+right+root)
  return max(0,max(a, b)+root->val);//if *root is in the path, if this branch a burden or a plus (left/right + root)
}

int maxPathSum(TreeNode *root) { 
  if(root == NULL) {
    return 0;
  }
  res = root->val;
  depth(root,res);
  return res;
}

//######################################## Bottom-up solution I ######################################## 
int maxPathSum(TreeNode *root) {
    int max = numeric_limits<int>::min();
    helper(root, max);
    return max;
}
int helper(TreeNode *root, int& global_max) {
    if (root == nullptr) return 0;
    int l = max(0, helper(root->left, global_max));
    int r = max(0, helper(root->right, global_max));
    global_max = max(global_max, l + r + root->val); //Choose the current root with left and right subtree
    return root->val + max(l, r); //Choose the either of left/right subtree
}

//######################################## Bottom-up solution II ######################################## 
int helper(TreeNode *root, int &re) {
    if (!root) return 0;
    int l = helper(root->left, re);
    int r = helper(root->right, re);
    if (l < 0) l = 0;
    if (r < 0) r = 0;
    if (l + r + root->val > re) {
      re = l + r + root->val; //update the max
    }
    //return root->val += max(l, r); //update the root value
    return root->val + max(l, r); //return max root value
}
int maxPathSum(TreeNode *root) {
    int max = numeric_limits<int>::min();
    helper(root, max);
    return max;
}


//Not many problems exhibit such a clear sub-structure. Here we need to simply solve the problem for a tree with up to two levels and then recursively repeat that logic.
//Maximum path can be formed only in a few ways:
//1. Root + Left sub-tree
//2. Root + Right sub-tree
//3. Just the Root, in case left and right sums are -ve.
//4. Root + Left + Right sub-trees, this is closed path
//Only greater of the first three values can move up the ladder. Repeat this at every step, and we have a bottom up solution. More comments with C implementation given below
int maxValSum(TreeNode* root, int *maxVal) {
    int ml, mr, mx;
    if (!root) return 0;

    /* Get the maxValimum values from the left and right sub-trees */
    ml = maxValSum(root->left, maxVal);
    mr = maxValSum(root->right, maxVal);

    /* Maximum can be either
       1. The whole sub-tree, or
       2. Just the left subtree + root or
       3. Right sub-tree + root. */
    *maxVal = *maxVal < (mx = max(root->val + ml + mr, root->val + ml, 
                            root->val + mr)) ? mx : *maxVal;

    /* Return the larger of the two sub-trees + root or just the root. */
    return max(root->val, root->val + ml, root->val + mr);
}

int maxPathSum(struct TreeNode* root) {
    int sum1 = MIN_INT, sum2;
    sum2 = maxSum(root, &sum1);
    return sum1 > sum2 ? sum1 : sum2;
}
        

