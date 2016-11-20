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
//
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
