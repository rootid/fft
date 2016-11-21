//Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).
//For example:
//Given binary tree [3,9,20,null,null,15,7],
//    3
//   / \
//  9  20
//    /  \
//   15   7
//return its zigzag level order traversal as:
//[
//  [3],
//  [20,9],
//  [15,7]
//]

#include "../headers/global.hpp"
#include "treenode.h"
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
       vector<vector <int> > result;
       if(!root) {
           return result;
       }
       queue<TreeNode* > q;
       q.push(root);
       vector<int> tmp;
       int visited = 1;
       int level = 0;
       int nxt_visited = 0;
       while(!q.empty()) {
           TreeNode *next = q.front();
           q.pop();
           visited--;
           if(next->left != NULL) {
               q.push(next->left);
               nxt_visited += 1;
           }
           if(next->right != NULL) {
               q.push(next->right);
               nxt_visited += 1;
           }
           tmp.push_back(next->val);
           if(visited == 0) {
               visited =  nxt_visited;
               nxt_visited = 0;
               if(level % 2 != 0) {
                   reverse(tmp.begin(),tmp.end());
               }
               level++;
               result.push_back(tmp);
               tmp.clear();
           }
       }
       return result;
}

int main() {
//[3,9,20,null,null,15,7]
//
  TreeNode *root= new TreeNode (3);
  root->left= new TreeNode (9);
  root->right= new TreeNode (20);
  root->right->left =  new TreeNode (15);
  root->right->right = new TreeNode (7);
  zigzagLevelOrder(root);
}
