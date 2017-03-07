//Find Mode in Binary Search Tree
//Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.
//Assume a BST is defined as follows:
//The left subtree of a node contains only nodes with keys less than or equal to the node's key.
//The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
//Both the left and right subtrees must also be binary search trees.
//For example:
//Given BST [1,nullptr,2,2],
//   1
//    \
//     2
//    /
//   2
//return [2].
//Note: If a tree has more than one mode, you can return them in any order.
//Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).

//############################################################################################################################
vector<int> modes;
vector<int> findMode(TreeNode* root) {
    inorder(root);
    modes(modeCount,0);
    modeCount = 0;
    currCount = 0;
    inorder(root);
    return modes;
}
int currVal;
int currCount = 0;
int maxCount = 0;
int modeCount = 0;
void handleValue(int val) {
    if (val != currVal) {
        currVal = val;
        currCount = 0;
    }
    currCount++;
    if (currCount > maxCount) {
        maxCount = currCount;
        modeCount = 1;
    } else if (currCount == maxCount) {
        if (modes != nullptr)
            modes[modeCount] = currVal;
        modeCount++;
    }
}
    
void inorder(TreeNode* root) {
    if (root == nullptr) return;
    inorder(root.left);
    handleValue(root.val);
    inorder(root.right);
}
//############################### O (n) T and O(n) s
 vector<int> findMode(TreeNode* root) {
        unordered_map<int, int> map;
        vector<int> result;
        int modeCount = getModeCount(root, map);
        
        for(pair<int,int> p : map) {
            if(p.second == modeCount) {
                result.push_back(p.first);
            }
        }
        
        return result;
        
    }
    
    /**
     * Traverse the tree using depth first search.
     * Return the mode count (i.e. The count of a repeated number that occurs the most.) of the tree.
     */
    int getModeCount(TreeNode* root, unordered_map<int, int> &map) {
        if(root == NULL)
            return 0;
        
        if(map.find(root->val) == map.end()) {
            map.insert(pair<int, int>(root->val, 1));
        }
        else {
            map[root->val]++;
        }
        
        return max(map[root->val], max(getModeCount(root->left, map), getModeCount(root->right, map)));
    }
