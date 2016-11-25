//Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
//
//Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.
//
//For example, you may serialize the following tree
//
//    1
//   / \
//  2   3
//     / \
//    4   5
//as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
//Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
//Use of delimiter ","
//
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
//
class Codec {
public:
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
};
