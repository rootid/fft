//Minimum Depth of Binary Tree
//Given a binary tree, find its minimum depth.
//The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
#include<iostream>
//This solution o/p  {1,2} = 2 : as it thinks shortest path is from 
//root->NON-NULL NODE


//######################################### Update height when leaf node found ######################################### 
// Trick : leaf node has height = 0, non leaf node ht = leftHt + rightHt + 1
public int minDepth(TreeNode root) {
    if(root == null) return 0;
    int left = minDepth(root.left);
    int right = minDepth(root.right);
    return (left == 0 || right == 0) ? left + right + 1: Math.min(left,right) + 1;
}

//######################################### Update height when leaf node found ######################################### 
class Solution {
	int minHt = Integer.MAX_VALUE;
    
    private void minDepthHelper(TreeNode root,int ht) {
        if(root == null) return;
        ht = ht + 1;
        if(root.left == null && root.right == null) 
            minHt = Math.min(ht, minHt);  
        minDepthHelper(root.left,ht);
        minDepthHelper(root.right,ht);
    }
    
    public int minDepth(TreeNode root) {
        if(root == null) return 0;
        minDepthHelper(root,0);
        return minHt;
    }
}

//######################################### Update height when leaf node found ######################################### 
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
