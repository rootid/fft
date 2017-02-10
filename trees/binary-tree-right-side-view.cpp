//Binary Tree Right Side View
//Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.
//For example:
//Given the following binary tree,
//   1            <---
// /   \
//2     3         <---
// \     \
//  5     4       <---
//You should return [1, 3, 4].
//
//
//Variation :
//print a tree one level at a time.
//################################# Recursive ################################# 
vector<int> rightSideView(TreeNode* root) {
   vector<int> result;
   if(!root)  return result;
   helper(result, 0, root);
   return result;
}
  
void helper(vector<int>& result, int level, TreeNode* root){
    if(!root)  return;
    if(level == result.size()) {
        result.push_back(root->val); 
    }
    helper(result, level+1, root->right);
    helper(result, level+1, root->left);
}

//################################# ITerative ################################# 
//Push at the back and retreive from front
vector<int> rightSideView(TreeNode* root) {
    deque<TreeNode*> dq;
    vector<int> result;
    if (!root)  return result;
    dq.push_back(root);
    while (!dq.empty()) {
        result.push_back(dq.back()->val);
        for (int i = dq.size(); i > 0; i--) {
            TreeNode* cur = dq.front();
            dq.pop_front();
            if (cur->left)  { 
              dq.push_back(cur->left);
            }if (cur->right)  { 
              dq.push_back(cur->right);
            }
        }
    }
    return result;
}

//###################### Iterative ###################### 
vector<int> rightSideView(TreeNode* root) {
   queue<TreeNode*>mQ;
   vector<int> ret;
   if(!root)return ret;
   mQ.push(root);
   while(!mQ.empty()){
       ret.push_back(mQ.back()->val);
       for(int i=mQ.size();i>0;i--){
           TreeNode *tn=mQ.front();
           mQ.pop();
           if(tn->left)mQ.push(tn->left);
           if(tn->right)mQ.push(tn->right);
       }
   }
   return ret;
}

//###################### Divide and Conquer ###################### 
//solving the right tree side view and left tree side view ,and then merge
the results
vector<int> rightSideView(TreeNode* root) { 
  vector<int> r;
  if(root == NULL){
      return r;
  }
  r.push_back(root.val);
  vector<int> rt = rightSideView(root.right);
  vector<int> lt = rightSideView(root.left);
  for(int i=rt.size();i<lt.size();i++){
      rt.push_back(lt[i]);
  }    
  for(auto num:rt) {
    r.push_back(num);
  }
  return r;
}
