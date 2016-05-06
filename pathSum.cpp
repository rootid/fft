  bool hasPathSum(TreeNode* root, int sum) {
        if(!root) {
            return false;
        }
        if(!root && sum != 0) {
            return false;
        }
        if(root->left == NULL && root->right == NULL && sum == root->val) {
            return  true;
        }
        return ( hasPathSum(root->left,sum-root->val) || hasPathSum(root->right,sum-root->val) );
    }
