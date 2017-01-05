//Sum of Left Leaves
//
//Find the sum of all left leaves in a given binary tree.
//Example:
//    3
//   / \
//  9  20
//    /  \
//   15   7
//There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.

#include<iostream>
#include "../headers/treenode.h"
using namespace std;

int sumOfLeftLeavesHelper(TreeNode *root,bool isLeftLeaf) {

  if(!root) {
    return 0;
  }
  if(!root->left && !root->right) {
    if(isLeftLeaf == true) {
      return root->val;
    } 
    return 0;
  }
  return sumOfLeftLeavesHelper(root->left,true) + sumOfLeftLeavesHelper(root->right,false);
}

int sumOfLeftLeaves(TreeNode* root) {
  return sumOfLeftLeavesHelper(root,false);
}

int sumOfLeftLeaves_1(TreeNode* root) {
  if(!root) {
    return 0;
  }
  if( root->left != NULL  && root->left->left == NULL && root->left->right == NULL) {
      return root->left->val + sumOfLeftLeaves_1(root->right);
  } 
  return sumOfLeftLeaves_1(root->left) + sumOfLeftLeaves_1(root->right);
}

int BFSSoln (TreeNode* root) {
   
  if(root == NULL || root->left == NULL && root->right == NULL)  {
    return 0;
  }
  int res = 0;
  queue<TreeNode*> queue;
  queue.push(root);
  
  while(!queue.empty()) {
      TreeNode* curr = queue.front();
      queue.pop();
      if(curr->left != NULL  && curr->left->left == NULL && curr->left->right == NULL) {
        res += curr->left->val;
      }
      if(curr->left != null) {
        queue.push(curr->left);
      }
      if(curr->right != null) { 
        queue.push(curr->right);
      }
  }
  return res;
}


int main() {

}

