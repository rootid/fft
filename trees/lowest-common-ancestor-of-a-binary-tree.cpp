//Lowest Common Ancestor of a Binary Tree
//Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
//According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”
//        _______3______
//       /              \
//    ___5__          ___1__
//   /      \        /      \
//   6      _2       0       8
//         /  \
//         7   4
//For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

//######################################### LCA ######################################### 
//Go untill node is not found
public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
     if(root == null 
        || root == p 
        || root == q) 

        return root; 
     TreeNode rL = lowestCommonAncestor(root.left, p, q);
     TreeNode rR = lowestCommonAncestor(root.right, p, q);
     //if(rL == p && rR == q || (rL == q && rR == p) ) return root; //if p and q are on opposite sides of root
     if(rL != null && rR != null) return root; //if p and q are on opposite sides of root
     if(rL == null) //rL is after the rR (rR-->rL)
         return rR;
     return rL; 
}


//######################################### Recursion ######################################### 
//O(n) - Verfiy whether it's O(n) or O(h)
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  if(!root || p == root || q == root) {
    return root;
  }
  TreeNode *left = lowestCommonAncestor(root->left,p,q);
  TreeNode *right = lowestCommonAncestor(root->right,p,q);
  if(left != NULL && right != NULL) {
    return root;
  }
  if(right == NULL) {
    return left;
  }
  return right;
}
//this might go into each subtree twice. Which means you might go into each subsubtree four times. And into each subsubsubtree eight times. And so on. That takes exponential time, which is very slow.
//
//def lowestCommonAncestor(self, root, p, q):
//    if not root or p == root or q == root:
//        return root
//    if self.lowestCommonAncestor(root.left, p, q) and self.lowestCommonAncestor(root.right, p, q):
//        return root
//    return self.lowestCommonAncestor(root.left, p, q) or self.lowestCommonAncestor(root.right, p, q)


//######################################### left + right ######################################### 
def lowestCommonAncestor(self, root, p, q):
    if root in (None, p, q): return root
    left, right = (self.lowestCommonAncestor(kid, p, q)
                   for kid in (root.left, root.right))
    return root if left and right else left or right

//######################################### children ######################################### 
def lowestCommonAncestor(self, root, p, q):
    if root in (None, p, q): return root
    subs = [self.lowestCommonAncestor(kid, p, q)
            for kid in (root.left, root.right)]
    return root if all(subs) else max(subs)

//######################################### Iterative  ######################################### 
//Python
def lowestCommonAncestor(self, root, p, q):
    stack = [root]
    parent = {root: None}
    while p not in parent or q not in parent:
        node = stack.pop()
        if node.left:
            parent[node.left] = node
            stack.append(node.left)
        if node.right:
            parent[node.right] = node
            stack.append(node.right)
    ancestors = set()
    while p:
        ancestors.add(p)
        p = parent[p]
    while q not in ancestors:
        q = parent[q]
    return q

# 31 / 31 test cases passed.
# Status: Accepted
# Runtime: 108 ms
# 99.14%
//######################################### Iterative  ######################################### 
//Java

public class Solution {
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        Map<TreeNode, TreeNode> parent = new HashMap<>();
        Deque<TreeNode> stack = new ArrayDeque<>();
        parent.put(root, null);
        stack.push(root);
        while (!parent.containsKey(p) || !parent.containsKey(q)) {
            TreeNode node = stack.pop();
            if (node.left != null) {
                parent.put(node.left, node);
                stack.push(node.left);
            }
            if (node.right != null) {
                parent.put(node.right, node);
                stack.push(node.right);
            }
        }
        Set<TreeNode> ancestors = new HashSet<>();
        while (p != null) {
            ancestors.add(p);
            p = parent.get(p);
        }
        while (!ancestors.contains(q))
            q = parent.get(q);
        return q;
    }
}
//To find the lowest common ancestor, we need to find where is p and q and a way to track their ancestors. A parent pointer for each node found is good for the job. After we found both p and q, we create a set of p's ancestors. Then we travel through q's ancestors, the first one appears in p's is our answer.


//https://leetcode.com/discuss/45603/iterative-solution
class Solution {
    struct Frame {
        TreeNode* node;
        Frame* parent;
        vector<TreeNode*> subs;
    };
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        Frame answer;
        stack<Frame> stack;
        stack.push({root, &answer});
        while (stack.size()) {
            Frame *top = &stack.top(), *parent = top->parent;
            TreeNode *node = top->node;
            if (!node || node == p || node == q) {
                parent->subs.push_back(node);
                stack.pop();
            } else if (top->subs.empty()) {
                stack.push({node->right, top});
                stack.push({node->left, top});
            } else {
                TreeNode *left = top->subs[0], *right = top->subs[1];
                parent->subs.push_back(!left ? right : !right ? left : node);
                stack.pop();
            }
        }
        return answer.subs[0];
    }
};


public class MyNode{
    TreeNode node;
    MyNode parent;
    boolean visited;
    List<TreeNode> result = new ArrayList<TreeNode>();

    public MyNode(TreeNode node, MyNode parent){
        this.node = node;
        this.parent = parent;
    }
}
public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
    MyNode dummy = new MyNode(null, null);//used to retrive global result
    MyNode rootNode = new MyNode(root, dummy);
    Stack<MyNode> stack = new Stack<MyNode>();
    stack.push(rootNode);

    while(!stack.isEmpty()){
        MyNode curr = stack.peek();
        TreeNode node = curr.node;
        MyNode parent = curr.parent;
        //if we reach bottom or we found target
        if(node == null || node == p || node == q){
            parent.result.add(node);
            stack.pop();//we are done with this node, pop out
        }else if(!curr.visited){
            //have not visited curr node, push right first then left
            curr.visited = true;
            stack.push(new MyNode(node.right, curr));
            stack.push(new MyNode(node.left, curr));
        }else if(curr.visited){
            //if visited, update result
            TreeNode left = curr.result.get(0);
            TreeNode right = curr.result.get(1);
            if(left != null && right != null){
                parent.result.add(node);//curr treeNode is LCA
            }else if(left != null){
                parent.result.add(left);
            }else{
                parent.result.add(right);
            }

            stack.pop();//we are done with this node, pop out
        }
    }

    return dummy.result.get(0);

}


class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //iterative, path comparing
        if(!root || root==p || root==q) return root;
        vector<TreeNode*> pathp, pathq, temp;
        temp.push_back(root);
        TreeNode* prev=NULL;
        while(pathp.empty() || pathq.empty()){
            root=temp.back();
            if(root==p) pathp=temp;
            if(root==q) pathq=temp;
            if(!root->left && !root->right || !root->right && prev==root->left || root->right && prev==root->right){
                temp.pop_back();
                prev=root;
            }
            else{
                if(!root->left || prev==root->left) temp.push_back(root->right);
                else temp.push_back(root->left);
            }
        }
        int n=min(pathp.size(),pathq.size());
         for(int i=1; i<n; i++){
            if(pathp[i]!=pathq[i]) return pathp[i-1];
        }
        return pathp[n-1];
    }
};

// vim: set sw=2 sts=2 tw=120 et nospell : 
