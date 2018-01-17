//Invert a binary tree.
//     4
//   /   \
//  2     7
// / \   / \
//1   3 6   9
//
// to
//     4
//   /   \
//  7     2
// / \   / \
//9   6 3   1
//

#include<iostream>
using namespace std;

struct TreeNode {
    TreeNode *left;
    TreeNode *right;
    int val;
    TreeNode (int aVal) : val(aVal),left(NULL),right(NULL) {

    }
};


TreeNode* invertTree (TreeNode *root) {

  if (!root) {
    return NULL;
  } 
 
  TreeNode *tmp = invertTree(root->left);
  root->left = invertTree(root->right);
  //Wrong o/p
  //TreeNode *tmp = (root->left);
  //root->left = (root->right);
  root->right = tmp;
  return root;
}


void printTree(TreeNode *root) {

    if (!root) {
      return;
    }
    printTree(root->left);
    cout << root->val << " " ;
    printTree(root->right);

}

int main() {

  //TreeNode *t;
  //TreeNode *t = new TreeNode(26);
  TreeNode *t = new TreeNode(4);
  t->left = new TreeNode(2);
  t->left->left = new TreeNode(1);
  t->left->right = new TreeNode(3);
  t->right = new TreeNode(7);
  t->right->left = new TreeNode(6);
  t->right->right= new TreeNode(9);

  printTree(t);
  TreeNode *t1 = invertTree (t);
  cout << endl;
  printTree(t1);
}

