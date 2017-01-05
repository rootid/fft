//Binary Tree Level Order Traversal
//Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

//For example:
//Given binary tree {3,9,20,#,#,15,7}
//    3
//   / \
//  9  20
//    /  \
//   15   7
//[
//  [3],
//  [9,20],
//  [15,7]
//]
//
#include<iostream>
#include<vector>
#include<queue>
#include "../headers/treenode.h"

using namespace std;

vector<vector<int> > levelOrder(TreeNode* root) {

  vector<vector<int> > result;
  vector <int> tmp;
  queue<TreeNode* > qStore;
  qStore.push(root);
  int crtLevel = 1;
  int nxtLevel = 1;

  while(!qStore.empty()) {
    TreeNode* nxtNode = qStore.front();
    if(!nxtNode->left && !nxtNode->right) {
      crtLevel = nxtLevel;
    } else {
      nxtLevel += 1;
    }
    if(nxtNode->left) {
      qStore.push(nxtNode->left);
    } 
    if(nxtNode->right) {
      qStore.push(nxtNode->right);
    }
    qStore.pop();
    cout << nxtLevel << " = " << nxtNode->val << " clevel " << crtLevel << endl;
  }

  return result;
}

int main() {

  TreeNode* t = new TreeNode(3);
  t->left = new TreeNode(9);
  t->right = new TreeNode(20);
  t->right->left = new TreeNode(15);
  t->right->right = new TreeNode(7);

  levelOrder(t);
}
