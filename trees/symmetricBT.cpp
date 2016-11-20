//Symmetric Tree
//Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
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
//Note:
//Bonus points if you could solve it both recursively and iteratively.
//confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
//

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
