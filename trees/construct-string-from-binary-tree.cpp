//Construct String from Binary Tree
//You need to construct a string consists of parenthesis and integers from a
//binary tree with the preorder traversing way.
//The null node needs to be represented by empty parenthesis pair "()". And you
//need to omit all the empty parenthesis pairs that don't affect the one-to-one
//mapping relationship between the string and the original binary tree.
//Example 1:
//Input: Binary tree: [1,2,3,4]
//       1
//     /   \
//    2     3
//   /
//  4
//Output: "1(2(4))(3)"
//Explanation: Originallay it needs to be "1(2(4)())(3()())",
//but you need to omit all the unnecessary empty parenthesis pairs.
//And it will be "1(2(4))(3)".
//Example 2:
//Input: Binary tree: [1,2,3,null,4]
//       1
//     /   \
//    2     3
//     \
//      4
//Output: "1(2()(4))(3)"
//Explanation: Almost the same as the first example,
//except we can't omit the first parenthesis pair to break the one-to-one
//mapping relationship between the input and the output.
//############################# Recursive preorder traversal ##########################
string tree2str(TreeNode* t) {
  return !t ? "" : to_string(t->val)
    + (t->left ? "(" + tree2str(t->left) + ")" : t->right ? "()" : "")
    + (t->right ? "(" + tree2str(t->right) + ")" : "");
}

//############################# Recursive preorder traversal + extended ##########################
string tree2str(TreeNode* t) {
    if (!t) return "";
    string s = to_string(t->val);
    if (t->left) {
        s += "(" + tree2str(t->left) + ")";
    } else if (t->right) {
        s += "()";
    }
    if (t->right) {
        s += "(" + tree2str(t->right) + ")";
    }
    return s;
}

//
//
//
//###################################### pytonic ######################################
//class Solution(object):
//    def tree2str(self, t):
//        """
//        :type t: TreeNode
//        :rtype: str
//        """
//        if not t:
//            return ""
//        res = ""
//        left = self.tree2str(t.left)
//        right = self.tree2str(t.right)
//        if left or right:
//            res += "(%s)" % left
//        if right:
//            res += "(%s)" % right
//        return str(t.val) + res
//
//
//###################################### pytonic bad ######################################
//class Solution(object):
//    def tree2str(self, t):
//        """
//        :type t: TreeNode
//        :rtype: str
//        """
//        if not t: return ""
//        s, l, r = str(t.val), "(" + self.tree2str(t.left) + ")", "(" + self.tree2str(t.right) + ")"
//        return s + l + r if t.left and t.right else \
//               s + l if t.left and not t.right else \
//               s + "()" + r if not t.left and t.right else s
//
//###################################### pytonic ugly ######################################
//class Solution(object):
//    def tree2str(self, t):
//        """
//        :type t: TreeNode
//        :rtype: str
//        """
//        def preorder(root):
//            if root is None:
//                return ""
//            s=str(root.val)
//            l=preorder(root.left)
//            r=preorder(root.right)
//            if r=="" and l=="":
//                return s
//            elif l=="":
//                s+="()"+"("+r+")"
//            elif r=="":
//                s+="("+l+")"
//            else :
//                s+="("+l+")"+"("+r+")"
//            return s
//        return preorder(t)
//
