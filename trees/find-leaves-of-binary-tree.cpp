//Given a binary tree, collect a tree's nodes as if you were doing this: Collect and remove all leaves, repeat until the tree is empty.
//Example:
//Given binary tree 
//          1
//         / \
//        2   3
//       / \     
//      4   5    
//Returns [4, 5, 3], [2], [1].
//Explanation:
//1. Removing the leaves [4, 5, 3] would result in this tree:
//          1
//         / 
//        2          
//2. Now removing the leaf [2] would result in this tree:
//          1          
//3. Now removing the leaf [1] would result in the empty tree:
//          []         
//Returns [4, 5, 3], [2], [1].
int helper(TreeNode * root,vector< vector<int> >& result) {
    if(root == nullptr)
        return -1;
    if (root->left == nullptr && root->right == nullptr) {
        if (result.empty()) {
            result.emplace_back();
        }
        result[0].push_back(root->val);
        return 0;
    }
    int l = helper(root->left,result);
    int r = helper(root->right,result);
    int level = max(l, r) + 1;
    if (level >= result.size())
        result.emplace_back();
    result[level].push_back(root->val);
    return level;
}
vector<vector<int>> findLeaves(TreeNode* root) {
    vector< vector<int> > result;
    helper(root,result);
    return result;
}
void helper(TreeNode* parent,TreeNode* child,vector< vector<int> >& result,vector<int>& tmp) {
     if(child == NULL) {
         result.push_back(tmp);
         tmp.clear();
         return;
     }
     parent = child;
     if(parent->left == NULL && parent->right == NULL) {
         tmp.push_back(parent->val);
         parent = NULL;
     }
     helper(child,child->left,result,tmp);
     helper(child,child->right,result,tmp);
}
 
vector<vector<int>> findLeaves(TreeNode* root) {
     vector< vector<int> > result;
     vector<int> tmp;
     helper(NULL,root,result,tmp);
     return result;
 }
