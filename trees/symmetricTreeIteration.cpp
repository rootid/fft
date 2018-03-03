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
#include<queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//Use queue


bool isSymmetric(TreeNode* root) {
  if(!root) {
    return true;
  }
  queue<TreeNode *> q1;
  queue<TreeNode *> q2;
  TreeNode* l;
  TreeNode* r;
  q1.push(root->left);
  q2.push(root->right);
  while (!q1.empty() && !q2.empty()) {
    l = q1.front();
    r = q2.front();
    q1.pop();
    q2.pop();
    if(l == NULL && r == NULL) {
      //No elements in the queue
      return true;
    }
    if(l == NULL || r == NULL) {
      return false;
    }
    if(l->val != r->val) {
      return false;
    }
    //Opposite substree store
    q1.push(l->left);
    q1.push(l->right);

    q2.push(r->right);
    q2.push(r->left);
  }

  return true;
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
