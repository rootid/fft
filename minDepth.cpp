//Minimum Depth of Binary Tree
//Given a binary tree, find its minimum depth.
//The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
#include<iostream>
//This solution o/p  {1,2} = 2 : as it thinks shortest path is from 
//root->NON-NULL NODE
int minDepth(TreeNode* root) {
  if(!root) {
    return 0;
  }
  int ltHt = 1 + minDepth(root->left);
  int rtHt = 1 + minDepth(root->right);
   if (root->left != NULL && root->right != NULL)
        return min(ltHt,rtHt);
    else
         return max(ltHt,rtHt);
    }
//This solution o/p  {1,2} = 1 : as it thinks shortest path is from root->NULL
//NODE
int minDepth(TreeNode* root) {
  if(!root) {
    return 0;
  }
  int ltHt = 1 + minDepth(root->left);
  int rtHt = 1 + minDepth(root->right);
  return min(ltHt,rtHt);
}
//with BFS
// 
int minDepth(TreeNode* root) {
  if(!root) {
    return 0;
  }
  int level = 0;
  queue<TreeNode*> q;
  q.push(root);
  while(!q.empty()) {
    int bredth = q.size();
    level += 1;
    for(int j=0;j<bredth;j++) {
      TreeNode *tmp = q.front();
      if(tmp->left) {
        q.push(tmp->left);
      }
      if(tmp->right) {
        q.push(tmp->right);
      }
      q.pop();
      if(tmp->left == NULL && tmp->right == NULL) {
        return level;
      }
    }
  }
 return level; //TO make compiler :) 
}
// TODO  : FIXME 
// with BFS ugly
int minDepth(TreeNode* root) {
    if(!root) {
    return 0;
  }
  queue<TreeNode *> tQ;
  tQ.push(root);
  int currVisited = 1;
  int nextVisited = 0;
  int level = 0;
  while (!tQ.empty()) {
      TreeNode *tmp = tQ.front();
      if ( tmp->left == NULL && tmp->right == NULL) {
              return level + 1;
         }
      if (tmp->left) {
          tQ.push(tmp->left);
          nextVisited++;
      }
      if (tmp->right) {
          tQ.push(tmp->right);
          nextVisited++;
      }
      tQ.pop();
      currVisited--;
      if (currVisited == 0) {
          currVisited = nextVisited;
          level += 1;
          nextVisited = 0;
      }  
  }
    return level;
}
