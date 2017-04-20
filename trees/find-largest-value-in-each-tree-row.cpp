//Find Largest Value in Each Tree Row
//You need to find the largest value in each row of a binary tree.
//Example:
//Input: 
//          1
//         / \
//        3   2
//       / \   \  
//      5   3   9 
//Output: [1, 3, 9]

//######################################################## BFS ######################################################## 
vector<int> largestValues(TreeNode* root) {
    vector<int> res;
    if (root == nullptr) return res;
    queue<TreeNode*> q;
    q.push(root);
    res.push_back(INT_MIN);
    int currVisited = 1, toBeVisited = 0;
    while (!q.empty()) {
        TreeNode *node = q.front();
        q.pop();
        --currVisited;
        res.back() = max(node->val, res.back());
        if (node->left != nullptr) {
            q.push(node->left);
            ++toBeVisited;
        }
        if (node->right != nullptr) {
            q.push(node->right);
            ++toBeVisited;
        }
        if (currVisited == 0) {
            currVisited = toBeVisited;
            toBeVisited = 0;
            if (!q.empty()) {
              res.push_back(INT_MIN);
            }
        }
    }
    return res;
}

//######################################################## Preorder traversal ######################################################## 
private:
void preorder(TreeNode* root, int height,vector<int>& ans) {
  if (!root) return;
  if (ans.size() < height) { //first element
    ans.push_back(root->val); // each idx = ht of tree 
  } else {
    ans[height - 1] = max(ans[height - 1], root->val);
  }
  preorder(root->left, height + 1,ans);
  preorder(root->right, height + 1,ans);
}
public:
vector<int> largestValues(TreeNode* root) {
  vector<int> ans;
  preorder(root, 1,ans);
  return ans;
}


//def findValueMostElement(self, root):
//    maxes = []
//    row = [root]
//    while any(row):
//        maxes.append(max(node.val for node in row))
//        row = [kid for node in row for kid in (node.left, node.right) if kid]
//    return maxes
//
//row = [a,b,c,d...]
//xxx = []
//for node in row:
//    for kid in (node.left, node.right):
//        if kid:
//            xxx += kid,
//row = xxx
//Divide and conquer
//def largestValues(self, root):
//    if not root:
//        return []
//    left = self.largestValues(root.left)
//    right = self.largestValues(root.right)
//    return [root.val] + map(max, left, right)
//def largestValues(self, root):
//    return [root.val] + map(max, *map(self.largestValues, (root.left, root.right))) if root else []
