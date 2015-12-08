
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



class Solution {
public:
    vector<string> r;
    vector<string> binaryTreePaths(TreeNode* root) {
        // method 1 - dfs with a queue recording current path
        // vector<int> v;
        // dfs1(root,v);

        // method 2 - dfs but with no queue
        if(!root) return r;
        dfs2(root,"");
        return r;
    }

    //method 1 - dfs with a queue recording current path
    // root - the node we will visit
    // v    - a vector recording current path
    void dfs1(TreeNode *root, vector<int> &v) {
        if (!root) return;
        if (!root->left && !root->right) {
            string path = stringlize(v) + to_string(root->val);
            r.push_back(path);
            return;
        }

        v.push_back(root->val);
        dfs1(root->left,v);
        dfs1(root->right,v);
        v.pop_back();
    }

    string stringlize(vector<int> &values) {
        string s;
        for (int i = 0 ; i < values.size(); i++) {
            s += to_string(values[i]) + "->";
        }
        return s;
     }

    //method 2 - dfs with no queue recording current path
    //root: the node we will visit
    //p   : the path before root is visited
    void dfs2(TreeNode *root, string p) {
        if (!root) return;

        if (!root->left && !root->right) {
            string path = append(p,root->val);
            r.push_back(path);
            return;
        }

        dfs2(root->left, append(p,root->val));
        dfs2(root->right,append(p,root->val));
    }

    string append(string &p, int val) {
        return p.empty() ? to_string(val) : p + "->" + to_string(val);
    }

};
