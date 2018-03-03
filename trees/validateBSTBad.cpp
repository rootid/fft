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


class Solution {
private:
    TreeNode* prev=NULL;
public:
    bool isValidBST(TreeNode* root) {
        if(!root)   return true;
        return isValidBST(root->left)  && help(root) && isValidBST(root->right);
    }

    bool help(TreeNode* root){
        if(!prev){
            prev=root;
            return true;
        }
        if(prev->val >= root->val)   return false;
        prev=root;
        return true;
    }
};


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
