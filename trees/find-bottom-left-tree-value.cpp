//Find Bottom Left Tree Value
//Given a binary tree, find the leftmost value in the last row of the tree.
//Example 1:
//Input:
//    2
//   / \
//  1   3
//Output:
//1
//Example 2: 
//Input:
//        1
//       / \
//      2   3
//     /   / \
//    4   5   6
//       /
//      7
//Output:
//7


//##################### Preorder recursion  ##################### 
class Solution {
    int maxIdx = -1;
    int maxValue;
    
    public int findBottomLeftValue(TreeNode root) {
        findBottomLeftValueHelper(root, true, 0);
        return maxValue;
    }
    
    private void findBottomLeftValueHelper(TreeNode root, boolean isLeftNode,int k) {
        if(root == null) return; 
        if(++k > maxIdx) {
            maxValue = root.val;
            maxIdx = k;
        }
        findBottomLeftValueHelper(root.left, true, k);
        findBottomLeftValueHelper(root.right, false,k);
    }  
}

//##################### BFS traversal ( R-L) ##################### 
public int findLeftMostNode(TreeNode root) {
    Queue<TreeNode> queue = new LinkedList<>();
    queue.add(root);
    while (!queue.isEmpty()) {
        root = queue.poll();
        if (root.right != null)
            queue.add(root.right);
        if (root.left != null)
            queue.add(root.left);
    }
    return root.val;
}

//##################### Keep track of state globally ##################### 
class Solution {
   	TreeNode leftNode = null;
    int maxLevel = -1;
    public int findBottomLeftValue(TreeNode root) {
        findBottomLeftValueHelper(root,0);
        return leftNode == null ? -1 : leftNode.val;
    }
    private void findBottomLeftValueHelper(TreeNode root, int level) {
        if(root != null) {
            if(level > maxLevel) {
                maxLevel = level;
                leftNode = root;
            }
            findBottomLeftValueHelper(root.left, level+1);
            findBottomLeftValueHelper(root.right, level+1);
      }
    }
}

//##################### DFS ##################### 
void dfsHelper(TreeNode* root, int level,pair<int, int>& res){
    if(root == nullptr) 
      return;
    if(level > res.first) {
        res.first = level;
        res.second = root->val;
    }
    dfsHelper(root->left, level+1,res); //left->right
    dfsHelper(root->right, level+1,res);
}
int findBottomLeftValue(TreeNode* root) {
    pair<int, int> res({0,root->val});
    dfsHelper(root, 0,res);
    return res.second;
}


void findBottomLeftValue(TreeNode* root, int& maxDepth, int& leftVal, int depth) { 
  if (root == NULL) { 
    return; 
  }
  //Go to the left and right of each node 
  findBottomLeftValue(root->left, maxDepth, leftVal, depth+1);
  findBottomLeftValue(root->right, maxDepth, leftVal, depth+1);
  
  //Update leftVal and maxDepth
  if (depth > maxDepth) {
      maxDepth = depth;
      leftVal = root->val;
  } 
}
//Entry function
int findBottomLeftValue(TreeNode* root) {
    int maxDepth = 0;
    //Initialize leftVal with root's value to cover the edge case with single node
    int leftVal = root->val;
    findBottomLeftValue(root, maxDepth, leftVal, 0);
    return leftVal;
}

//##################### BFS from Right to left ##################### 
int findBottomLeftValue(TreeNode* root) {
    queue<TreeNode*> queue;
    queue.push(root);
    while (!queue.empty()) {
        root = queue.front();
        queue.pop(); //1
        if (root->right != nullptr)
            queue.push(root->right); //3 | 6 | 7
        if (root->left != nullptr)
            queue.push(root->left); //3,2,6,5,4,7
    }
    return root->val;
}
