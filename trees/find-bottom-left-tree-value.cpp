//Find Bottom Left Tree Value
//Given a binary tree, find the leftmost value in the last row of the tree.
//Example 1:
//Input:
//    2
//   / \
//  1   3
//Output:
//1
//Example 2: 
//Input:
//        1
//       / \
//      2   3
//     /   / \
//    4   5   6
//       /
//      7
//Output:
//7
//##################### DFS ##################### 
int findBottomLeftValue(TreeNode* root) {
    pair<int, int> res({0,root->val});
    dfs(root, 0,res);
    return res.second;
}
void dfs(TreeNode* root, int level,pair<int, int>& res){
    if(root == nullptr) 
      return;
    if(level > res.first) {
        res.first = level;
        res.second = root->val;
    }
    dfs(root->left, level+1,res);
    dfs(root->right, level+1,res);
}

//##################### BFS ##################### 
int findBottomLeftValue(TreeNode* root) {
    queue<TreeNode*> queue;
    queue.push(root);
    while (!queue.empty()) {
        root = queue.front();
        queue.pop();
        if (root->right != nullptr)
            queue.push(root->right);
        if (root->left != nullptr)
            queue.push(root->left);
    }
    return root->val;
}
