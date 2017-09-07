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

//Idea : 
//traversal every nodes as the top of sub tree and calculate left max and right max individually, then keep update max. T
//A path, in this problem, refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. 
//In the example, you start at either the 2 or 3, then traverse to its parent, the 1 at the root, then finish at the root's other child. That gives 2+1+3 = 3+1+2 = 6.
//
//					  1
//        **2**                   1
//  10          10           1          1
//  Ans = 22 not 26

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

//									root 
//                                 /      \   
//                  left max value        right max value
  //From the bottom of the tree to the top, it's in post-order manner.
  return max(0,max(a, b)+root->val);//if *root is in the path, if this branch a burden or a plus (left/right + root)
  //At every node, we need to make a decision, if the sum comes from the left path larger than the right path, we pick the left path and plus the current node's value, this recursion goes all the way up to the root node.
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

//######################################### Top-down ######################################### 
public static int maxSumPath(TreeNode root) {
    int[] res = new int[1];
    helper(root,res);
    return res[0];
}
public static int helper(TreeNode root, int[] res) {
    if(root == null) return 0;
    int l = helper(root.left, res);
    int r = helper(root.right, res);
    res[0] = Math.max(res[0],l+r+root.data);
    return Math.max(0, Math.max(l,r) + root.data);
}

//######################################### Top-down ######################################### 
    def maxPathSum(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        maxSeen = [float('-INF')]
        self.maxSumIfNodeIsHighestEnd(root, maxSeen)
        return maxSeen[0]
        
    
    def maxSumIfNodeIsHighestEnd(self, node, maxSeen):
        if not node:
            return 0
        leftSeen = max(0, self.maxSumIfNodeIsHighestEnd(node.left, maxSeen))
        rightSeen = max(0, self.maxSumIfNodeIsHighestEnd(node.right, maxSeen))
        maxSeen[0] = max(maxSeen[0], leftSeen + rightSeen + node.val)
        return max(leftSeen, rightSeen) + node.val


//######################################### Top-down ######################################### 
class Solution(object):
    def maxPathSum(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        self.sum = root.val
        def dfs(root):
            if not root: return 0
            l = dfs(root.left)
            r = dfs(root.right)
            self.sum = max(self.sum, root.val + max(l, r), root.val, root.val + l + r)
            return max(root.val, root.val + max(l, r))
        return max(dfs(root), self.sum)


//A path from start to end, goes up on the tree for 0 or more steps,
//then goes down for 0 or more steps. 
//Once it goes down, it can't go up. 
//Each path has a highest node, which is also the lowest common ancestor of all other nodes on the path.
//A recursive method maxPathDown(TreeNode node) 
//(1) computes the maximum path sum with highest node is the input node, update maximum if necessary 
//(2) returns the maximum sum of the path that can be extended to input node's parent.
//
//######################################### DFS  ######################################### 
class Solution {
private:
    int dfs(TreeNode* root, int& maxsum) {
        if(!root) return 0;
        int l = max(0,dfs(root->left,maxsum));
        int r = max(0,dfs(root->right,maxsum));
        maxsum = max(l+r+root->val, maxsum);
        return root->val + max(l,r);
    }
public:
    int maxPathSum(TreeNode* root) {
        int maxsum = INT_MIN;
        dfs(root,maxsum);
        return maxsum;
    }
};
