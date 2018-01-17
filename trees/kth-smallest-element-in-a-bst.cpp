//Kth Smallest Element in a BST
//Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
//Note: 
//You may assume k is always valid, 1 ≤ k ≤ BST's total elements.
//Follow up:
//What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?
//Hint:
//Try to utilize the property of a BST.
//What if you could modify the BST node's structure?
//The optimal runtime complexity is O(height of BST).

//###### Inorder traversal + With instance variable  ######################################### 
class Solution {
  int count = 0;
  int result = Integer.MIN_VALUE;

  public int kthSmallest(TreeNode root, int k) {
      traverse(root, k);
      return result;
  }

  public void traverse(TreeNode root, int k) {
      if(root == null) return;
      traverse(root.left, k);
      count ++;
      if(count == k) {
          result = root.val;
          return;
      }
      traverse(root.right, k);       
  }
}

//######################################### With Stack (Iterative) ######################################### 
public int kthSmallest(TreeNode root, int k) {
     Stack<TreeNode> stack = new Stack<TreeNode>();
     TreeNode p = root;
     int count = 0;
     
     while(!stack.isEmpty() || p != null) {
         if(p != null) {
             stack.push(p);  // Just like recursion
             p = p.left;   
             
         } else {
            TreeNode node = stack.pop();
            if(++count == k) return node.val; 
            p = node.right;
         }
     }
     
     return Integer.MIN_VALUE;
 }


//######################################### D&C ######################################### 
public class Solution {
  public int kthSmallest(TreeNode root, int k) { 
    int left = nodeCount(root.left);  // this value can be saved in the root node
    if(left + 1 == k) {
        return root.val;
    } else if (left + 1 < k) {
        return kthSmallest(root.right, k - left - 1);
    } else {
        return kthSmallest(root.left, k);
    }
  }

  private int nodeCount(TreeNode root) {
    if(root == null) {
        return 0;
    }
    return 1 + nodeCount(root.left) + nodeCount(root.right);
  }
}

//######################################### With reference ######################################### 
//Try the left subtree first. If that made k zero, then its answer is the overall answer and we return it right away. Otherwise, decrease k for the current node, and if that made k zero, then we return the current node's value right away. Otherwise try the right subtree and return whatever comes back from there.
int kthSmallestHelper(TreeNode* root, int k,int& l) {
  if(root) {
    int lval = kthSmallestHelper(root->left,k,l);
    cout <<  "L = " << l << " V = " << root->val << endl;
    //l = l + 1;
    if(l == k) {
      return lval; //verifying left subtree
    } else {
      l = l + 1;
      if(l == k) {
        return root->val; //verifying right subtree
      } else {
        int rval = kthSmallestHelper(root->right,k,l);
      }
    }
  }
  //cout <<  "L = " << l << " V = " << root->val << endl;
}
int find(TreeNode* root, int& k) {
    if (!root) {
        return -1;
    }
        int x = find(root->left, k);
        //return !k ? x : !--k ? root->val : find(root->right, k);
        if (!k) {
          return x;
        } else { 
          if(!--k) { 
              return root->val;
          } else  {
             return find(root->right, k);
          }
        }
}

int kthSmallest(TreeNode* root, int k) {
  int l = 0;
  return kthSmallestHelper(root,k,l);
  //return find(root,k);
}

//######################################### With stack ######################################### 
//Contrainted inorder traversal with MAX k memory location instead of stack
//Solution 2, C++ with circular vector
//Using a vector of fixed size k and a stack pointer i into it which will be used modulo k.
int kthSmallest(TreeNode* root, int k) {
    vector<TreeNode*> stac(k);
    int i = 0, j = k;
    while (true) {
        while (root) {
            stac[i++%k] = root;
            root = root->left;
        }
        root = stac[--i%k];
        if (! --j)
            return root->val;
        root = root->right;
    }
}

//######################################### With Deque ######################################### 
//Solution 3, C++ with deque
//I really like the previous version, but the fixed size k isn't always necessary, so here's a version using a deque:
int kthSmallest(TreeNode* root, int k) {
    deque<TreeNode*> stac;
    while (true) {
        while (root) {
            stac.push_front(root);
            while (stac.size() > k)
                stac.pop_back();
            root = root->left;
        }
        root = stac.front();
        stac.pop_front();
        if (! --k)
            return root->val;
        root = root->right;
    }
//ANS : with morris traversal
//https://leetcode.com/discuss/43299/o-k-space-o-n-time-10-short-lines-3-solutions?show=43556#a43556




/* vim: set ts=2 sw=2 sts=2 tw=120 et: */
