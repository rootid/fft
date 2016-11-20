//Given a binary tree, flatten it to a linked list in-place.
//For example,
//Given
//         1
//        / \
//       2   5
//      / \   \
//     3   4   6
//The flattened tree should look like:
//   1
//    \
//     2
//      \
//       3
//        \
//         4
//          \
//           5
//            \
//             6
//If you notice carefully in the flattened tree, each node's right child points to the next node of a pre-order traversal.
//
//
//
void flatten(TreeNode* root) {
    if(!root) {
        return;
    }
    TreeNode *tmp = root;
    TreeNode *prev_right = root->right;
    root->right = root->left;
    root->left = NULL;
    while(tmp->right != NULL) {
        tmp = tmp->right;
    }
    tmp->right = prev_right;
    flatten(root->right);
    return;
}

int main() {

}
