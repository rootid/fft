//Convert Sorted Array to Binary Search Tree
//Given an array where elements are sorted in ascending order, convert it to a
//height balanced BST.
TreeNode* sortedArrayToBST(vector<int>& nums) {
    TreeNode *root;
    if(nums.size() == 0) {
        return NULL;
    }
    // if(nums.size() == 1) {
    //     return new TreeNode(nums[0]);
    // }
    int mid = nums.size()/2;
    root = new TreeNode(nums[mid]);  //Think of base case with 0 elements
    vector<int> upto_mid(nums.begin(),nums.begin() + mid);
    vector<int> after_mid(nums.begin()+mid+1,nums.end());
    root->left = sortedArrayToBST(upto_mid);
    root->right = sortedArrayToBST(after_mid);
    return root;
}

int main() {

}
