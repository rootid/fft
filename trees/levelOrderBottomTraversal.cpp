#include<iostream>
#include<vector>
#include<queue>
#include "../headers/treenode.h"

using namespace std;

void DFSHelper(TreeNode* root,vector< vector<int> >& result, int level) {
  
  if(!root) {
    return;
  }
  //create a new vector for each current level
	if (result.empty() || level > (result.size() - 1)) {
		result.push_back(vector<int>());
	}
  result[level].push_back(root->val);
  DFSHelper(root->left,result,level+1);
  DFSHelper(root->right,result,level+1);
}

vector<vector<int> > levelOrderBottom(TreeNode* root) {

  vector< vector<int> > result;
  int level = 0;
  DFSHelper(root,result,level);
  reverse(result.begin(),result.end());
  return result;

}

vector<vector<int> > levelOrderBottom(TreeNode* root) {

  vector< vector<int> > result;
  
  if(!root) {
    return result;
  }
  queue<TreeNode* > qStore;
  qStore.push(root);

  while(!qStore.empty()) {
    int level = qStore.size();
    vector<int> visited;
    while(level-- > 0){
        TreeNode *tmp = qStore.front();
        visited.push_back(tmp->val);
        qStore.pop();
        if(tmp->left) {
          qStore.push(tmp->left);
        }
        if(tmp->right) {
          qStore.push(tmp->right);
        }
    }
    result.push_back(visited);
    visited.clear();
  }
  reverse(result.begin(),result.end());
  return result;

}
