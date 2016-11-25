//Use of delimiter ","
string serialize() {
      if (root == NULL)  { 
        return "#";
      }
      return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
}
string serialize_ugly(TreeNode* root) {
      string tmp = "";
      if(root == NULL) {
          tmp += "#";
          return tmp;
      }
      tmp += to_string(root->val);
      tmp += "," + serialize(root->left);
      tmp += "," + serialize(root->right);
      return tmp;
}
TreeNode* deserialize(string data) {
  stringstream ss(data);
  return deserialize_helper(data);
}
TreeNode* deserialize_helper(istringstream& in) {
    string tmp_v;
    geline(in,tmp_v,',');
    if(tmp_v == "#") {
      return NULL;
    }
    TreeNode *root = new TreeNode(stoi(tmp_v)); 
    root->left = deserialize_helper(in);
    root->right = deserialize_helper(in);
    return root;
}

// Use of delimiiter " "
string serialize(TreeNode* root) {
      if(root == NULL) {
          return "#";
      }
      return  to_string(root->val) + " " + serialize(root->left) + " " + serialize(root->right);
}
  
  
TreeNode* deserialize(string data) {
   if (data == "#") return NULL;
   istringstream s(data);
   return deserialize_helper(s);
}
  
TreeNode* deserialize_helper(istringstream& in) {
    string tmp_v;
    in >> tmp_v;
    if(tmp_v == "#") {
        return NULL;
    }
    TreeNode *root = new TreeNode(stoi(tmp_v)); 
    root->left = deserialize_helper(in);
    root->right = deserialize_helper(in);
    return root;
}
