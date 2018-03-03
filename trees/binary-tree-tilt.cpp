//Binary Tree Tilt
//Given a binary tree, return the tilt of the whole tree.
//The tilt of a tree node is defined as the absolute difference between the sum
//of all left subtree node values and the sum of all right subtree node values.
//Null node has tilt 0.
//The tilt of the whole tree is defined as the sum of all nodes' tilt.
//Example:
//Input:
//         1
//       /   \
//      2     3
//Output: 1
//Explanation:
//Tilt of node 2 : 0
//Tilt of node 3 : 0
//Tilt of node 1 : |2-3| = 1
//Tilt of binary tree : 0 + 0 + 1 = 1
//Note:
//The sum of node values in any subtree won't exceed the range of 32-bit
//integer.
//All the tilt values won't exceed the range of 32-bit integer
//

//################################### recursive post order ###################################
int findTilt(TreeNode* root) {
      if(root == NULL) return 0;
      int res = 0;
      postorder(root, res);
      return res;
  }
private:
int postorder(TreeNode* root, int& res){
    if(root == NULL) return 0;
    int leftsum= postorder(root->left,res);
    int rightsum = postorder(root->right,res);
    res += abs(leftsum - rightsum);
    return leftsum + rightsum + root->val;
}
//################################### store the sum in map + decreased performance  ###################################
unordered_map<TreeNode*, int> m;
int findTilt(TreeNode* root) {
    if (!root) return 0;
    int tilt = abs(getSum(root->left, m) - getSum(root->right, m));
    return tilt + findTilt(root->left) + findTilt(root->right);
}
int getSum(TreeNode* node, unordered_map<TreeNode*, int>& m) {
    if (!node) return 0;
    if (m.count(node)) return m[node];
    return m[node] = getSum(node->left, m) + getSum(node->right, m) + node->val;
}
