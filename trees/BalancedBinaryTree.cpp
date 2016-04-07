//Balanced Binary Tree
//Given a binary tree, determine if it is height-balanced.
//For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

#include<iostream>
#include<stdlib.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void getBothHeightByRef(TreeNode *root,int& ltHt,int& rtHt) {
  
  if(!root) {
    return ;
  } else {
    if(root->left) {
      ltHt = 1 + ltHt;
      getBothHeightByRef(root->left,ltHt,rtHt);
    }
    if (root->right) {
      rtHt = 1 + rtHt;
      getBothHeightByRef(root->right,ltHt,rtHt);
    }
  }
}

int getDepth(TreeNode *root) {
  
  int l = 0;
  int r = 0;
  if(!root) {
    return 0;
  } 
  if(root->left) {
    l += 1 + getDepth(root->left);
    //cout << "l = " << l << endl;
  }
  if (root->right) {
    r += 1 + getDepth(root->right);
    //cout << "r " << r << endl;
  }
  return abs(l- r) ;
  //return ( getDepth(root->left) - getDepth(root->right) ) + 1; Total idiotness
}

bool isBalanced(TreeNode* root) {
 
  if(!root) {
    return true;
  }
  if(getDepth (root) > 1) {
    return false;
  } 
  bool l = isBalanced(root->left);
  bool r = isBalanced(root->right);
  return l & r;
}

int main() {

  TreeNode* t = new TreeNode(1);
  //t->left = new TreeNode(2);
  //t->left->left = new TreeNode(3);
  //t->left->left->left = new TreeNode(4);
  //t->left->left->left->left = new TreeNode(5);
  //t->right = new TreeNode(5);
  //t->right->right = new TreeNode(5);
  //t->right->right = new TreeNode(5);
  //t->right->right->right = new TreeNode(5);
    
  //int ltHt = 0;
  //int rtHt = 0;
  //getHeightByRef(t,ltHt,rtHt );
   
  if( isBalanced(t) ) {
    cout << "IS BALANCED " << endl;
  } else {
    cout << "not  BALANCED " << endl;
  }

}
