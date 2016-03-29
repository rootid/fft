//Binary Tree Paths
//Given a binary tree, return all root-to-leaf paths.
//For example, given the following binary tree:
//   1
// /   \
//2     3
// \
//  5
//All root-to-leaf paths are:
//["1->2->5", "1->3"]
//Explore at each node

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

//NOTE : if you use pass by reference always come to initial position by removing last added solution set eg. pop_back
//For pass by value : This is not necessary
void treeTraversalHelper(TreeNode *root,vector<string>& result,string& tmpStr) {
  if(root)  {
    tmpStr += to_string(root->val);
    if(root->left == NULL && root->right == NULL) {
      cout << tmpStr <<  endl;
      tmpStr.pop_back();
      return;
    }
    tmpStr += "->";
    treeTraversalHelper(root->left,result,tmpStr);
    treeTraversalHelper(root->right,result,tmpStr);
    tmpStr.pop_back();
  }
}

vector<string> binaryTreePaths(TreeNode* root) {
  vector<string> result;
  //vector<int> tmp;
  int cLen = 0;
  int vLen = 0;
  string tmp = "";
  treeTraversalHelper(root,result,tmp);
  return result;
}


int main() {

  TreeNode* t = new TreeNode(1);
  t->left = new TreeNode(2);
  t->right = new TreeNode(3);
  t->right->left = new TreeNode(5);
  t->right->right = new TreeNode(7);

  binaryTreePaths(t);

}
