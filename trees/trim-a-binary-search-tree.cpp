//Trim a Binary Search Tree
//Given a binary search tree and the lowest and highest boundaries as L and R, trim the tree so that all its elements lies in [L, R] (R >= L). You might need to change the root of the tree, so the result should return the new root of the trimmed binary search tree.
//Example 1:
//Input: 
//    1
//   / \
//  0   2
//  L = 1
//  R = 2
//Output: 
//    1
//      \
//       2
//Example 2:
//Input: 
//    3
//   / \
//  0   4
//   \
//    2
//   /
//  1
//  L = 1
//  R = 3
//Output: 
//      3
//     / 
//   2   
//  /
// 1

//######################################### O(n) + O(log n) ######################################### 
public TreeNode trimBST(TreeNode root, int L, int R) {

  if (root == null) return null;
  if (root.val < L) return trimBST(root.right, L, R);
  if (root.val > R) return trimBST(root.left, L, R);
  root.left = trimBST(root.left, L, R);
  root.right = trimBST(root.right, L, R);
  return root;
    
}

///If the root value in the range [L, R]
///      we need return the root, but trim its left and right subtree;
///else if the root value < L
///      because of binary search tree property, the root and the left subtree are not in range;
///      we need return trimmed right subtree.
///else
///      similarly we need return trimmed left subtree.
//
//######################################### Memory leak ######################################### 
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if (root == NULL) return NULL;
        if (root->val < L) return trimBST(root->right, L, R);
        if (root->val > R) return trimBST(root->left, L, R);
        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);
        return root;
    }
};

//######################################### No memory leak ######################################### 
TreeNode* trimBST(TreeNode* root, int L, int R, bool top=true) {
    if (!root)
        return root;
    root->left = trimBST(root->left, L, R, false);
    root->right = trimBST(root->right, L, R, false);
    if (root->val >= L && root->val <= R)
        return root;
    auto result = root->val < L ? root->right : root->left;
    if (!top)
        delete root;
    return result;
}

//######################################### python ######################################### 
class Solution(object):
    def trimBST(self, root, L, R):
        """
        :type root: TreeNode
        :type L: int
        :type R: int
        :rtype: TreeNode
        """
        if not root:
            return None
        if L > root.val:
            return self.trimBST(root.right, L, R)
        elif R < root.val:
            return self.trimBST(root.left, L, R)
        root.left = self.trimBST(root.left, L, R)
        root.right = self.trimBST(root.right, L, R)
        return root


//######################################### python - Recursion ######################################### 
//Let trim(node) be the answer for the subtree at that node.
//When node.val > R, we know the trimmed binary tree must occur to the left of the node.
//Similarly, when node.val < L, the trimmed binary tree occurs to the right of the node. Otherwise, we will trim both sides of the tree.
def trimBST(self, root, L, R):
    def trim(node):
        if node:
            if node.val > R:
                return trim(node.left)
            elif node.val < L:
                return trim(node.right)
            else:
                node.left = trim(node.left)
                node.right = trim(node.right)
                return node

    return trim(root)
