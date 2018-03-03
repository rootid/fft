//Symmetric Tree
//Given a binary tree, check whether it is a mirror of itself (ie, symmetric
//around its center).
//For example, this binary tree is symmetric:
//    1
//   / \
//  2   2
// / \ / \
//3  4 4  3
//But the following is not:
//    1
//   / \
//  2   2
//   \   \
//   3    3

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

bool isSymmetricHelper(TreeNode* left,TreeNode *right) {

  if(left && right) {
    if(left->val == right->val) {
      return isSymmetricHelper(left->left,right->right) && isSymmetricHelper(left->right,right->left);
    }
    return false;
  } else if(!left && !right) {
    return true;
  } else {
    return false;
  }
  //cout << "isSymmetricHelper" << endl;
}

bool isSymmetric(TreeNode* root) {
  if(!root) {
    return true;
  }
  return isSymmetricHelper(root->left,root->right);
}

int main() {

  TreeNode* t = new TreeNode(1);
  t->left = new TreeNode(2);
  //t->right = new TreeNode(2);
  //t->right->right = new TreeNode(3);
  //t->left->right = new TreeNode(3);
  ////t->left->left = new TreeNode(3);
  ////t->left->right = new TreeNode(4);
  ////t->right->left = new TreeNode(4);
  ////t->right->right = new TreeNode(3);
  if ( true == isSymmetric(t) ) {
    cout << "IS symmetric " << endl;
  } else {

    cout << "NOT symmetric " << endl;
  }

}
