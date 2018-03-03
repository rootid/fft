//Construct Binary Tree from String
//You need to construct a binary tree from a string consisting of parenthesis
//and integers.
//The whole input represents a binary tree. It contains an integer followed by
//zero, one or two pairs of parenthesis. The integer represents the root's
//value and a pair of parenthesis contains a child binary tree with the same
//structure.
//You always start to construct the left child node of the parent first if it
//exists.
//Example:
//Input: "4(2(3)(1))(6(5))"
//Output: return the tree root node representing the following tree:
//       4
//     /   \
//    2     6
//   / \   /
//  3   1 5
//Note:
//There will only be '(', ')', '-' and '0' ~ '9' in the input string.
//
//######################################### Recursion #########################################
//For example, we have string 4(2(3)(1))(6(5)), to construct a binary tree, we
//can split the string to 3 parts:
//4
//(2(3)(1))
//(6(5))
//4 is the root val;
//(2(3)(1)) is left tree;
//(6(5)) is right tree;
//Left subtree determined by # of parenthesis

//######################################### Recursion #########################################
public TreeNode str2tree(String s) {
    if (s == null || s.length() == 0) return null;
    int firstParen = s.indexOf("(");
    int val = firstParen == -1 ? Integer.parseInt(s) : Integer.parseInt(s.substring(0, firstParen));
    TreeNode cur = new TreeNode(val);
    if (firstParen == -1) return cur;
    int start = firstParen, leftParenCount = 0;
    for (int i = start;i<s.length();i++) {
        if (s.charAt(i) == '(') leftParenCount++;
        else if (s.charAt(i) == ')') leftParenCount--;
        if (leftParenCount == 0 && start == firstParen) {cur.left = str2tree(s.substring(start+1,i)); start = i+1;}
        else if (leftParenCount == 0) cur.right = str2tree(s.substring(start+1,i));
    }
    return cur;
}


//######################################### Recursion with Q  #########################################
public TreeNode str2tree(String s) {
	if(s.length()==0) return null;
    Queue<Character> queue = new LinkedList<Character>();
    for(int i=0;i<s.length();i++) {
        queue.offer(s.charAt(i));
    }
    return buildTree(queue);
}
public TreeNode buildTree(Queue<Character> queue) {
    if(queue.isEmpty()) return null;
    TreeNode node = new TreeNode(0); //create empty node
    int value = 0;
    int sign = 1;
    while(!queue.isEmpty()) {
        char top = queue.poll();
        if(top == '(') { //start of subtree
            if(node.left == null) node.left = buildTree(queue);
            else node.right = buildTree(queue);
        } else if(top==')') {
            break; // visited node already
        } else {
			if(top=='-') {
				sign=-1;
                continue;
            }
			value=value*10+(top-'0');
        }
    }
    node.val = sign*value;
    return node;
}

//######################################### Reverse preorder + Iterative version #########################################
public TreeNode str2tree(String s) {
	Stack<TreeNode> stack = new Stack<>();
    for(int i = 0, j = i; i < s.length(); i++, j = i){
        char c = s.charAt(i);
        if(c == ')') stack.pop();
        else if(c >= '0' && c <= '9' || c == '-') {
            while(i + 1 < s.length() && s.charAt(i + 1) >= '0' && s.charAt(i + 1) <= '9') i++;
            TreeNode currentNode = new TreeNode(Integer.valueOf(s.substring(j, i + 1)));
            if(!stack.isEmpty()){
                TreeNode parent = stack.peek();
                if(parent.left != null) parent.right = currentNode;
                else parent.left = currentNode;
            }
            stack.push(currentNode);
        }
    }
    return stack.isEmpty() ? null : stack.peek();
}


//######################################### Reverse preorder + Iterative version #########################################
 TreeNode* str2tree(string s) {
	 if (s == "") return nullptr;
     stack<TreeNode*> sk;
     int n = s.size(), i = 0;
     while(i < n && s[i] != '(' && s[i] != ')')
         i++;
     TreeNode *root = new TreeNode(stoi(s.substr(0, i)));
     sk.push(root);
     while (i < n) {
         if (s[i++] == ')')
             sk.pop();
         else {
             int j = i;
             while(i < n && s[i] != '(' && s[i] != ')')
                i++;
             TreeNode *p = new TreeNode(stoi(s.substr(j, i-j)));
             if (sk.top()->left)
                 sk.top()->right = p;
             else
                 sk.top()->left = p;
             sk.push(p);
         }
     }
     return root;
 }



//######################################### Recursive version #########################################
class Solution {
    int i;
    public TreeNode str2tree(String s) {
        i = 0;
        return construct(s);
    }
    private TreeNode construct(String s) {
        // parse number
        StringBuilder numStr = new StringBuilder();
        while (i < s.length() && (s.charAt(i) == '-' || Character.isDigit(s.charAt(i)))) {
            numStr.append(s.charAt(i));
            i++;
        }
        if (numStr.length() == 0) return null;
        TreeNode root = new TreeNode(Integer.parseInt(numStr.toString()));
        // left subtree
        if (i < s.length() && s.charAt(i) == '(') {
            i++; // skip '('
            root.left = construct(s);
            i++; // skip ')'
        }
        // right subtree
        if (i < s.length() && s.charAt(i) == '(') {
            i++; // skip '('
            root.right = construct(s);
            i++; // skip ')'
        }
        return root;
    }
}

//######################################### Python #########################################
//We perform a recursive solution. There are four cases for what the string
//might look like:
//empty
//[integer]
//[integer] ( [tree] )
//[integer] ( [tree] ) ( [tree] )
//When there is no '(', we are in one of the first two cases and proceed
//appropriately.
//Else, we find the index "jx" of the ')' character that marks the end of the
//first tree. We do this by keeping a tally of how many left brackets minus
//right brackets we've seen. When we've seen 0, we must be at the end of the
//first tree. The second tree is going to be the expression S[jx + 2: -1],
//which might be empty if we are in case #3.

def str2tree(self, S):
    ix = S.find('(')
    if ix < 0:
        return TreeNode(int(S)) if S else None

    bal = 0
    for jx, u in enumerate(S):
        if u == '(': bal += 1
        if u == ')': bal -= 1
        if jx > ix and bal == 0:
            break

    root = TreeNode(int(S[:ix]))
    root.left = self.str2tree(S[ix+1:jx])
    root.right = self.str2tree(S[jx+2:-1])
    return root
