//Serialize and Deserialize BST
//Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
//Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary search tree can be serialized to a string and this string can be deserialized to the original tree structure.
//The encoded string should be as compact as possible.
//Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

// Deserialize = Preorder + Inorder 
// Serialize = Preorder
class Codec {
public:

  //Serialize with implicit stack
  void preorder(TreeNode* root, string& s){
    if(!root)
        return;
        s = s + to_string(root->val) + ",";
        preorder(root->left,s);
        preorder(root->right,s);
    }
    string serialize(TreeNode* root) {
        string s;
        if(!root)
            return s;
         preorder(root,s);
        return s;
    }

  //Seralize with stack
  string serialize(TreeNode* root) {
		// preorder traversal
		string ret;
		if(!root) return ret;
		
		stack<TreeNode*> stk;
		stk.push(root);
		while(!stk.empty()){
			TreeNode *r = stk.top();
			stk.pop();
			ret += to_string(r->val) + ",";
			if(r->right) stk.push(r->right);
			if(r->left) stk.push(r->left);

		}
		return ret.substr(0, ret.size()-1);
	}

  // Decodes your encoded data to tre.
	TreeNode* deserialize(string data) {
	    if(data.size() == 0) return nullptr;
	    
		int id = 0;
		// take root at first
		int r = id;
		while(isdigit(data[r])) {
		    r++;
		}
		int v = stoi(data.substr(id, r-id));
		id = r+1;
		TreeNode *root = new TreeNode(v);
		stack<TreeNode*> stk;
		stk.push(root);
		while(id < (int) data.size()) {
			int r = id;
			while(isdigit(data[r]))	r++;
			int v = stoi(data.substr(id, r - id));
			id = r + 1;
			TreeNode *node = nullptr;
			while(!stk.empty() && v > stk.top()->val) {
				node = stk.top();
				stk.pop();
			}
			if(node) {
				node->right = new TreeNode(v);
				stk.push(node->right);
			} else {
				stk.top()->left = new TreeNode(v);
				stk.push(stk.top()->left);
			}
		}
		return root;
	}
};
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
