//Largest BST Subtree
//
//Given a binary tree, find the largest subtree which is a Binary Search Tree (BST), where largest means subtree with largest number of nodes in it.
//Note:
//A subtree must include all of its descendants.
//Here's an example:
//    10
//    / \
//   5  15
//  / \   \ 
// 1   8   7
//The Largest BST Subtree in this case is the highlighted one. (5,1,8)
//The return value is the subtree's size, which is 3.
//Hint:
//You can recursively use algorithm similar to 98. Validate Binary Search Tree at each node of the tree, which will result in O(nlogn) time complexity.
//Follow up:
//Can you figure out ways to solve it with O(n) time complexity?
//
//
//################################################################## O(N) ################################################################## 
//it visits every node exactly once and does a constant amount of work for each.
int largestBSTSubtree(TreeNode* root) {
     int res = 0; //Total # of nodes
     int mini, maxi;
     bool b = isBST(root, res, mini, maxi);
     return res;
}

bool isBST(TreeNode* node, int& res, int& mini, int& maxi) {
    if (!node)
        return true;
    int left_size=0, right_size=0;
    int left_mini, left_maxi, right_mini, right_maxi;
    
    bool leftB = isBST(node->left, left_size, left_mini, left_maxi);
    bool rightB = isBST(node->right, right_size, right_mini, right_maxi);
    if (leftB && rightB) {
        //(left_mini,left_maxi)  node->val  (right_mini,right_maxi)
        if ( (!node->left || node->val >= left_maxi) && (!node->right || node->val <= right_mini) ) {
            /* The tree rooted at this node is a binary search tree */
            res = left_size+right_size+1;  
            mini = node->left ? left_mini : node->val;
            maxi = node->right ? right_maxi : node->val;
            return true;
        }
    }
    /* The tree rooted at this node is not a binary search tree, so take the maximum size of the BST in the left or right subtrees  */
    res = max(left_size, right_size);
    return false;
}

//################################################  O(n log N)  ################################################  
int largestBSTSubtree(TreeNode* root) {
     if(!root)
         return 0;
     bool result = helper(root);
     if(result){
         int result = countnodes(root);
         return result;
     } else {
         int n1 = largestBSTSubtree(root->left);
         int n2 = largestBSTSubtree(root->right);
         return max(n1,n2);
     } 
}
bool helper(TreeNode* root){
    stack<TreeNode*> s;
    TreeNode* wrongnode = NULL;
    TreeNode* current = root;
    while(1){
        while(current){
            s.push(current);
            current = current->left;
        }
        if(s.empty())
            break;
        TreeNode* node = s.top();
        s.pop();
        if(wrongnode == NULL){
            wrongnode = node;
        } else {
            if(wrongnode->val >= node->val) {
                return false;
            } else {
                wrongnode = node;
            }
        }
        current = node->right;
    }
    return true;
}

int countnodes(TreeNode* root){
    if(!root)
        return 0;
    return 1+countnodes(root->left)+countnodes(root->right);
}

//################################################  pytonic  ################################################  

//def largestBSTSubtree(self, root):
//    def dfs(root):
//        if not root:
//            return 0, 0, float('inf'), float('-inf')
//        N1, n1, min1, max1 = dfs(root.left)
//        N2, n2, min2, max2 = dfs(root.right)
//        n = n1 + 1 + n2 if max1 < root.val < min2 else float('-inf')
//        return max(N1, N2, n), n, min(min1, root.val), max(max2, root.val)
//    return dfs(root)[0]
//My dfs returns four values:
//N is the size of the largest BST in the tree.
//If the tree is a BST, then n is the number of nodes, otherwise it's -infinity.
//If the tree is a BST, then min and max are the minimum/maximum value in the tree.
//
//
//class Solution(object):
//    def largestBSTSubtree(self, root):
//        def solve(root, maxval):
//            if not root: return 0, float('inf'), -float('inf')
//            left,  minvl, maxvl = solve(root.left, maxval)
//            right, minvr, maxvr = solve(root.right, maxval)
//            if left == -1 or right == -1 or not maxvl < root.val < minvr:
//                return -1, 0, 0
//            maxval[0] = max(maxval[0], 1 + left + right)
//            return 1 + left + right, min(root.val, minvl, minvr), max(root.val, maxvr, maxvl)
//        
//        maxval = [0]
//        solve(root, maxval)
//        return maxval[0]
//
//# 71 / 71 test cases passed.
//# Status: Accepted
//# Runtime: 100 ms
//
//#############################################  Bottom up solution #############################################  
//
//public class Solution {
//    class Result {  // (size, rangeLower, rangeUpper) -- size of current tree, range of current tree [rangeLower, rangeUpper]
//        int size;
//        int lower;
//        int upper;
//        Result(int size, int lower, int upper) {
//            this.size = size;
//            this.lower = lower;
//            this.upper = upper;
//        }
//    }
//    int max = 0;
//    public int largestBSTSubtree(TreeNode root) {
//        if (root == null) { return 0; }    
//        traverse(root);
//        return max;
//    }
//    private Result traverse(TreeNode root) {
//        if (root == null) { return new Result(0, Integer.MAX_VALUE, Integer.MIN_VALUE); }
//        Result left = traverse(root.left);
//        Result right = traverse(root.right);
//        if (left.size == -1 || right.size == -1 || root.val <= left.upper || root.val >= right.lower) {
//            return new Result(-1, 0, 0);
//        }
//        int size = left.size + 1 + right.size;
//        max = Math.max(size, max);
//        return new Result(size, Math.min(left.lower, root.val), Math.max(right.upper, root.val));
//    }
//}
//
//
///*
//    in brute-force solution, we get information in a top-down manner.
//    for O(n) solution, we do it in bottom-up manner, meaning we collect information during backtracking. 
//*/
//public class Solution {
//    
//    class Result {  // (size, rangeLower, rangeUpper) -- size of current tree, range of current tree [rangeLower, rangeUpper]
//        int size;
//        int lower;
//        int upper;
//        
//        Result(int size, int lower, int upper) {
//            this.size = size;
//            this.lower = lower;
//            this.upper = upper;
//        }
//    }
//    int max = 0;
//    public int largestBSTSubtree(TreeNode root) {
//        if (root == null) { return 0; }    
//        traverse(root, null);
//        return max;
//    }
//    private Result traverse(TreeNode root, TreeNode parent) {
//        if (root == null) { return new Result(0, parent.val, parent.val); }
//        Result left = traverse(root.left, root);
//        Result right = traverse(root.right, root);
//        if (left.size==-1 || right.size==-1 || root.val<left.upper || root.val>right.lower) {
//            return new Result(-1, 0, 0);
//        }
//        int size = left.size + 1 + right.size;
//        max = Math.max(size, max);
//        return new Result(size, left.lower, right.upper);
//    }
//}
//
//
//
//

//#################################################### O(n log n) #################################################### 
//public boolean isValidBST(TreeNode root) {
//  if(root ==  null) return  true;
//  return helper(root.left, null, root.val) && helper(root.right, root.val, null);        
//}
//
//
//private boolean helper(TreeNode node, Integer loBound, Integer hiBound){
//  if(node == null) return true;
//  if(loBound != null && node.val <= loBound) return false;
//  if(hiBound != null && node.val >= hiBound) return false;
//  return helper(node.left, loBound, node.val) && helper(node.right, node.val, hiBound);   
//}
//
//
//class Result{
//      boolean isBST;
//      int count;
//      Result(boolean b, int c){
//        isBST = b;
//        count = c;
//      }
//    }
//    
//    int res = 0;
//    
//    public int largestBSTSubtree(TreeNode root) {
//      if(root == null) return res;
//      Result left = isBST(root.left, null, root.val);
//      Result right = isBST(root.right, root.val, null);
//      if(left.isBST && right.isBST) res = Math.max(res, 1 + left.count + right.count);
//      largestBSTSubtree(root.left);
//      largestBSTSubtree(root.right);
//      return res;
//    }
//    
//    Result isBST(TreeNode root, Integer low, Integer high){
//      if(root == null) return new Result(true, 0);
//      if(low != null && root.val < low) return new Result(false, 0);
//      if(high != null && root.val > high) return new Result(false, 0);
//      else {
//          Result left = isBST(root.left, low, root.val);
//          Result right = isBST(root.right, root.val, high);
//          return new Result(left.isBST && right.isBST, 1 + left.count + right.count);
//      }
//    }
//
//################################ Iterative  ################################ 
//
//public int largestBSTSubtree(TreeNode root) {
//    Stack<TreeNode> stack1 = new Stack<>(), stack2 = new Stack<>();
//    Stack<int[]> stack3 = new Stack<>();
//    stack1.push(root);
//    int maxSize = 0;
//    while (!stack1.isEmpty()) {
//        TreeNode cur = stack1.pop();
//        if (cur == null) stack3.push(new int[]{Integer.MAX_VALUE,Integer.MIN_VALUE,0});
//        else if (!stack2.isEmpty() && stack2.peek() == cur) {
//            stack2.pop();
//            int[] rightRes = stack3.pop();
//            int[] leftRes = stack3.pop();
//            if (leftRes[2] < 0 || rightRes[2] < 0 || leftRes[1] >= cur.val || rightRes[0] <= cur.val) 
//                stack3.push(new int[]{0, 0, -1});
//            else {
//                stack3.push(new int[]{Math.min(leftRes[0], cur.val), Math.max(rightRes[1], cur.val), leftRes[2]  + rightRes[2] + 1});
//                maxSize = Math.max(maxSize, leftRes[2] + rightRes[2] + 1);
//            }
//        }
//        else {
//            stack2.push(cur);
//            stack1.push(cur);
//            stack1.push(cur.right);
//            stack1.push(cur.left);
//        }
//    }
//    return maxSize;
//}
