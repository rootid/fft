//Given a binary tree, return all root-to-leaf paths.
//
//For example, given the following binary tree:
//
//   1
// /   \
//2     3
// \
//  5
//All root-to-leaf paths are:
//
//["1->2->5", "1->3"]
//
//


//2 solutions
//1. Pass by reference
//2. Pass by copy

vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> result;
    if(!root) { 
      return result;
    }
    string path="";
    dfs(root,path,result);
    return result;
}

void dfs(TreeNode* root,string path,vector<string>& result) {
  if(!root) {
    return;
  }
  append(path,root->val);
  if(!root->left && !root->right) {
       result.push_back(path);
       return;
  } 
  dfs(root->left,path,result);
  dfs(root->right,path,result);
}

void append(string &p, int val) {
    if(p.empty()) {
        p = to_string(val);
    }else {
        p = p + "->" + to_string(val);
    } 
}


void dfs(TreeNode* root,string& path,vector<string>& result) {
  if(!root) {
    return;
  }
  append(path,root->val);
  if(!root->left && !root->right) {
       result.push_back(path);
       return;
  } 
  dfs(root->left,path,result);
  dfs(root->right,path,result);
}

void append(string &p, int val) {
    if(p.empty()) {
        p = to_string(val);
    }else {
        p = p + "->" + to_string(val);
    } 
}
