//Validate Binary Search Tree
//
//Given a binary tree, determine if it is a valid binary search tree (BST).
//Assume a BST is defined as follows:
//The left subtree of a node contains only nodes with keys less than the node's
//key.
//The right subtree of a node contains only nodes with keys greater than the
//node's key.
//Both the left and right subtrees must also be binary search trees.
//

#include<iostream>
#include<stdlib.h>
#include<limits.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool bstValidCheckHelper(TreeNode* root,int max,int min) {

  if(!root) {
    return true;
  }
  bool isLeft = bstValidCheckHelper(root->left,root->val,min);
  bool isRight = bstValidCheckHelper(root->right,max,root->val);
  cout << " ROOT = " << root->val << " MIN = " << min << " MAX = " << max << endl;
  if(root->val >= min && root->val < max) {

    if(isLeft && isRight) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }

}

bool isValidBST(TreeNode* root) {
  if(!root) {
    return true;
  }
  return bstValidCheckHelper(root,INT_MAX,INT_MIN);
}

int main() {

  TreeNode* t = new TreeNode(3);
  t->left = new TreeNode(1);
  t->right = new TreeNode(9);
  t->right->left = new TreeNode(4);
  t->right->right = new TreeNode(15);
  //t->right = new TreeNode(2);
  //t->right->right = new TreeNode(3);
  //t->left->right = new TreeNode(3);
  ////t->left->left = new TreeNode(3);
  ////t->left->right = new TreeNode(4);
  ////t->right->left = new TreeNode(4);
  ////t->right->right = new TreeNode(3);
  if ( true == isValidBST(t) ) {
    cout << "IS VALID " << endl;
  } else {

    cout << "NOT VALID " << endl;
  }

}
