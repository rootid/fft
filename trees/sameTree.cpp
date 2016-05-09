//Same Tree
//Given two binary trees, write a function to check if they are equal or not.
//Two binary trees are considered equal if they are structurally identical and the nodes have the same value.
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool isSameTree(TreeNode* p, TreeNode* q) {
    
    if (!p && !q) {
        return true;
    } 
    if(!p || !q) {
        return false;
    }
    if(p->val == q->val) {
        return isSameTree(p->left,q->left) && isSameTree(p->right,q->right);
    } else {
        return false;
    }
    
}


bool isSymmetricHelper(TreeNode* p,TreeNode* q) {
 if(!p && !q ) {
   return true;
 }
 if((!p && q) || (p && !q) ) {
   return false;
 }
 return ( p->val == q->val && isSymmetricHelper(p->left,q->right) && isSymmetricHelper(p->right,q->left) );
}
bool isSymmetric(TreeNode* root) {
  
  if (!root) {
    return true;
  }
  return isSymmetricHelper(root->left,root->right);
}
int main() {
  TreeNode* t = new TreeNode(1);
  t->left = new TreeNode(2);
  t->right = new TreeNode(3);
  t->right->left = new TreeNode(5);
  t->right->right = new TreeNode(7);
  binaryTreePaths(t);
}
