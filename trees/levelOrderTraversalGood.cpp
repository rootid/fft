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
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


vector<vector<int> > levelOrder(TreeNode* root) {

  vector<vector<int> > result;
  vector <int> tmp;
  queue<TreeNode* > qStore;
  
  if(root) {
    qStore.push(root);
  }
  
  int crtVisited = 1;
  int nxtVisited= 0;

  while(!qStore.empty()) {
    TreeNode* nxtNode = qStore.front();
    crtVisited -= 1;
    tmp.push_back(nxtNode->val);
    qStore.pop();
    if(nxtNode->left) {
      qStore.push(nxtNode->left);
      nxtVisited += 1;
    } 
    if(nxtNode->right) {
      qStore.push(nxtNode->right);
      nxtVisited += 1;
    }
    //cout << crtVisited << " = " << nxtNode->val << " clevel " << nxtVisited<< endl;
    if(crtVisited == 0) {
      crtVisited = nxtVisited;
      nxtVisited = 0;
      result.push_back(tmp);
      tmp.clear();
    }
  }

  return result;
}

int main() {

  TreeNode* t = new TreeNode(3);
  t->left = new TreeNode(9);
  t->right = new TreeNode(20);
  t->right->left = new TreeNode(15);
  t->right->right = new TreeNode(7);

  vector<vector<int> > result= levelOrder(t);
  for(auto &t : result) {
    for(auto &t1 : t) {
      cout << t1 << "\t";
    }
    cout << endl;
  }
    cout << endl;

}
