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

void treeTraversalHelper(TreeNode *root,vector<string>& result,vector<int>& tmp) {
  if(root)  {
    tmp.push_back(root->val);
    if(root->left == NULL && root->right == NULL) {
      string tmpStr = "";
      for(auto &it : tmp) {
         ostringstream ss;
         ss << it;
         tmpStr += ss.str();
         tmpStr += "->";
      }
      tmpStr = tmpStr.substr(0,tmpStr.size() -2);
      result.push_back(tmpStr);
      cout << tmpStr <<  endl;
    }
    treeTraversalHelper(root->left,result,tmp);
    treeTraversalHelper(root->right,result,tmp);
    tmp.pop_back();
  }
}

vector<string> binaryTreePaths(TreeNode* root) {
  vector<string> result;
  vector<int> tmp;
  int cLen = 0;
  int vLen = 0;
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
