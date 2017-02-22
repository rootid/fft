//Construct Binary Tree from Preorder and Inorder Traversal
//Given preorder and inorder traversal of a tree, construct the binary tree.
//Note:
//You may assume that duplicates do not exist in the tree.

#include "../headers/global.hpp"
#include "../headers/treenode.h"

//############################  ############################ 
//helper : Need state is stored in n
TreeNode* helper(vector<int>& preorder, vector<int>& inorder, int n) {
    if(n == 0) {
        return NULL;
    }
    TreeNode *root = new TreeNode(preorder[0]); 
    int rootIndex;
    //search 
    //TODO : use unordered_map
    for(rootIndex=0; inorder[rootIndex] != root->val; ++rootIndex);
    vector<int>pre(preorder.begin()+1,preorder.end());
    root->left = rootIndex == 0 ? NULL : helper(pre, inorder, rootIndex);
    vector<int>npre(preorder.begin()+rootIndex+1,preorder.end());
    vector<int>nino(inorder.begin()+rootIndex+1,inorder.end());
    root->right = rootIndex == n-1 ? NULL : helper(npre, nino, n-rootIndex-1);
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
  int n = preorder.size();
  return helper(preorder,inorder,n);
}
