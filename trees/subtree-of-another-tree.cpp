//Subtree of Another Tree
//Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. A subtree of s is a tree consists of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.
//Example 1:
//Given tree s:
//     3
//    / \
//   4   5
//  / \
// 1   2
//Given tree t:
//   4 
//  / \
// 1   2
//Return true, because t has the same structure and node values with a subtree of s.
//Example 2:
//Given tree s:
//     3
//    / \
//   4   5
//  / \
// 1   2
//    /
//   0
//Given tree t:
//   4
//  / \
// 1   2
//Return false.

//#################################################### recursion #################################################### 
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        return !t || s && (isSameTree(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t));
    }
private:
    bool isSameTree(TreeNode* s, TreeNode* t) {
        return !s ? !t : t && s->val == t->val && isSameTree(s->left, t->left) && isSameTree(s->right, t->right);
    }


//#################################################### recursion #################################################### 
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        return !t || s && (same(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t));
    }
private :
  bool same(TreeNode* s, TreeNode* t) {
    return (!s && !t) || (s && t) && (s->val == t->val) && same(s->left, t->left) && same(s->right, t->right);
  }
  bool same(TreeNode* s, TreeNode* t) { 
    return (!s || !t) ? (s == t) : (s->val == t->val) && same(s->left, t->left) && same(s->right, t->right);
  }

//######################################## Linear  ######################################## 
//
//######################## Use of Preorder  ######################## 
//
//public class Solution {
//    StringBuilder spre = new StringBuilder();
//    StringBuilder tpre = new StringBuilder();
//    public boolean isSubtree(TreeNode s, TreeNode t) {
//        preOrder(s, spre.append(","));
//        preOrder(t, tpre.append(","));
//        return spre.toString().contains(tpre.toString());
//    }
//    public void preOrder(TreeNode root, StringBuilder str){
//        if(root == null){
//            str.append("#,");
//            return;
//        }
//        str.append(root.val).append(",");
//        preOrder(root.left, str);
//        preOrder(root.right, str);
//    }
//}
//
////######################### Conversion + KMP  ######################### 
//NOTE : find api may not be linear
//The key idea is to serialize the tree into a string so that any subtree in that tree will be a consecutive substring. Then the problem turns into substring finding problem. Here is the non-recursive code in case the tree is quite deep (depth > 10000) to prevent stack overflow.

class
class Solution {
public:
    vector<int> preKMP(string substr) {
        int m = substr.size();
        vector<int> f(m);        
        int k;
        f[0] = -1;
        for (int i = 1; i < m; i++) {
            k = f[i - 1];
            while (k >= 0) {
                if (substr[k] == substr[i - 1])
                    break;
                else
                    k = f[k];
            }
            f[i] = k + 1;
        }
        return f;
    }
 
    bool KMP(string substr, string str) {
        int m = substr.size();
        int n = str.size();
        vector<int> f;
        f = preKMP(substr);     
        int i = 0;
        int k = 0;        
        while (i < n) {
            if (k == -1) {
                i++;
                k = 0;
            }
            else if (str[i] == substr[k]) {
                i++;
                k++;
                if (k == m) {
                    return true;
                }
            }
            else {
                k = f[k];
            }
        }
        return false;
    }

    string postOrderTraversal(TreeNode* root) {
        string str;
        stack<pair<TreeNode*, int>> s;
        s.push(pair<TreeNode*, int>(root, 0));
        while (!s.empty()) {
            pair<TreeNode*, int> p = s.top();
            TreeNode* node = p.first;
            int idx = p.second;
            if (node == NULL) {
                s.pop();
                continue;
            }
            if (idx == 0) {
                str.push_back('(');
                s.top().second++;
                s.push(pair<TreeNode*, int>(node->left, 0));
            } else if (idx == 1) {
                s.top().second++;
                s.push(pair<TreeNode*, int>(node->right, 0));
            } else {
                str += to_string(node->val);
                str.push_back(')');
                s.pop();
            }
        }
        return str;
    }
    
    bool isSubtree(TreeNode* s, TreeNode* t) {
        string post_t = postOrderTraversal(t);
        string post_s = postOrderTraversal(s);
        //int pos = post_s.find(post_t);
        //return (pos != string::npos);
        return KMP(post_t, post_s);
    }
};

//######################################### pytonic ######################################### 
//######################################### Serialization  ######################################### 
//class Solution(object):
//    def isSubtree(self, s, t):
//        """
//        :type s: TreeNode
//        :type t: TreeNode
//        :rtype: bool
//        """
//        def serialize(root):
//            ans = []
//            stack = [(root, 1)]
//            while stack:
//                node, p = stack.pop()
//                if not node:
//                    ans.append("#")
//                    continue
//                if p == 0:
//                    ans.append("|" + str(node.val))
//                else:
//                    stack.append((node.right, 1))
//                    stack.append((node.left, 1))
//                    stack.append((node, 0))
//            return ",".join(ans)
//        return serialize(t) in serialize(s)
//class Solution(object):
//    def isSubtree(self, s, t):
//        """
//        :type s: TreeNode
//        :type t: TreeNode
//        :rtype: bool
//        """
//        def convert(p):
//            return "^" + str(p.val) + "#" + convert(p.left) + convert(p.right) if p else "$"
//        
//        return convert(t) in convert(s)
//
//@TIME
//def test(s, t):
//    return s in t
//
//for i in range(4,9):
//    n = 10**i
//    print(test("Done" * n, "WTF" * (n*10)))
//
////############## Qudratic time proof
//>>> from timeit import timeit
//>>> for e in range(10, 16):
//	n = 2**e
//	print(timeit('s in t',
//		     's = "a" * %d + "ba"; t = "aa" * %d' % (n, n),
//		     number=100))
//
//0.02283171976600329
//0.08677567873640157
//0.31249382161108485
//1.2718506141431192
//5.134004260046098
//20.76774636109795

//######################################### Merkel hashing ######################################### 
// O(|s| + |t|) (Merkle hashing):
// hashing the concatenation of the merkle of the left child, the node's value, and the merkle of the right child. Then, two trees are identical if and only if the merkle hash of their roots are equal 
def isSubtree(self, s, t):
    from hashlib import sha256
    def hash_(x):
        S = sha256()
        S.update(x)
        return S.hexdigest()
        
    def merkle(node):
        if not node:
            return '#'
        m_left = merkle(node.left)
        m_right = merkle(node.right)
        node.merkle = hash_(m_left + str(node.val) + m_right)
        return node.merkle
        
    merkle(s)
    merkle(t)
    def dfs(node):
        if not node:
            return False
        return (node.merkle == t.merkle or 
                dfs(node.left) or dfs(node.right))
                    
    return dfs(s)

//######################################### Naive ######################################### 
// Naive approach, O(|s| * |t|)
//For each node of s, let's check if it's subtree equals t. 
//We can do that in a straightforward way by an isMatch function: 
//1. check if s and t match at the values of their roots, plus their subtrees match. 
//2. Then, in our main function, we want to check if s and t match, or if t is a subtree of a child of s.
//def isMatch(self, s, t):
//    if not(s and t):
//        return s is t
//    return (s.val == t.val and 
//            self.isMatch(s.left, t.left) and 
//            self.isMatch(s.right, t.right))
//
//def isSubtree(self, s, t):
//    if self.isMatch(s, t): 
//      return True
//    if not s: 
//      return False
//    return self.isSubtree(s.left, t) or self.isSubtree(s.right, t)
