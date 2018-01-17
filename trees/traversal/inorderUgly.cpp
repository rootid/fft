//Binary Tree Inorder Traversal
//Given a binary tree, return the inorder traversal of its nodes' values.
//For example:
//Given binary tree {1,#,2,3},
//   1
//    \
//     2
//    /
//   3
//return [1,3,2].
//
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<int> inorderTraversal(TreeNode* root) {
  
  stack<TreeNode*> s;
  vector<int> result;
  TreeNode *t = root;
  if(root) {
    s.push(root);
  }
  while(!s.empty()) {
    if(t && t->left) { // in case left skwed with only 2 elements
      s.push(t->left);
      //cout << "lt = " << t->left->val << endl;
      t = t->left;
      continue;
    }
    t = s.top();
    s.pop();
    result.push_back(t->val);
    //cout << "t = " << t->val << endl;
    if(t->right) {
      //cout << "Rt = " << t->right->val << endl;
      s.push(t->right);
    }
    t = t->right; // in case left skwed with more than  2 elements
  }
  return result;

}

int main() {

  TreeNode* t = new TreeNode(1);
  t->right = new TreeNode(2);
  t->right->left = new TreeNode(3);

  inorderTraversal(t);
}
