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

//With the reference : path variable
//Issue : remove function is not removing the dashes correctly
void dfs(TreeNode* root,string& path,vector<string>& result) {
  if(!root) {
    return;
  }
  append(path,root->val);
  if(!root->left && !root->right) {
       result.push_back(path);
  } 
  dfs(root->left,path,result);
  dfs(root->right,path,result);
  remove(path,root->val);
}

void append(string &p, int val) {
    if(p.empty()) {
        p = to_string(val);
    }else {
        p = p + "->" + to_string(val);
    } 
}

void remove(string &p, int val) {
    if(!p.empty()) {
        if(p.size() == 1) {
            p.pop_back();
        } else {
            p.pop_back();
            p.pop_back();
            p.pop_back();
        }
    } 
}
