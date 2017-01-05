//Path Sum II  
//Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
//For example:
//Given the below binary tree and sum = 22,
//              5
//             / \
//            4   8
//           /   / \
//          11  13  4
//         /  \    / \
//        7    2  5   1
//return
//[
//   [5,4,11,2],
//   [5,8,4,5]
//]

#include "../headers/global.hpp"
#include "../headers/treenode.h"

void sumPathHelper(TreeNode *root,vector<int> s,vector<vector <int> >& s1,int sum) {
  if(!root) {
    return;
  }
  s.push_back(root->val);
  if(root->left == NULL && root->right == NULL) {
    int len = s.size();
    int localSum = 0;
    for(int i=0;i<len;i++) {
      //cout << s[len-1-i] << " ";
      localSum += s[i];
      cout << localSum  << " ";
    }
    //cout << endl; 
    if(sum == localSum) {
       //cout << "GOT SUM" << endl;
        s1.push_back(s);
    }
    //printVec(s);
  }
  sumPathHelper(root->left,s,s1,sum);
  sumPathHelper(root->right,s,s1,sum);
}

vector<vector<int> > pathSum(TreeNode* root, int sum) {
    vector<vector<int> > s1;
    vector<int> s;
    sumPathHelper(root,s,s1,sum);
    return s1;
}

int main(int argc, char *argv[])
{

  TreeNode* t = new TreeNode(1);
  t->left = new TreeNode(2);
  int sum = 3;
  pathSum(t,sum);
  return 0;
}

