//Given a binary tree
//    struct TreeLinkNode {
//      TreeLinkNode *left;
//      TreeLinkNode *right;
//      TreeLinkNode *next;
//    }
//Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
//Initially, all next pointers are set to NULL.
//Note:
//You may only use constant extra space.
//You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
//For example,
//Given the following perfect binary tree,
//         1
//       /  \
//      2    3
//     / \  / \
//    4  5  6  7
//After calling your function, the tree should look like:
//         1 -> NULL
//       /  \
//      2 -> 3 -> NULL
//     / \  / \
//    4->5->6->7 -> NULL


//######################################### Recursion  ######################################### 
    public void connectHelper(TreeLinkNode head, TreeLinkNode tail) {
        if(head == tail) return;
        head.next = tail;
        if(head != null && tail != null) {
            connectHelper(head.left, head.right);
            connectHelper(tail.left, tail.right);
            connectHelper(head.right, tail.left);
        }
    }
    
    public void connect(TreeLinkNode root) {
        if(root == null) return;
        connectHelper(root.left, root.right);
    }

//######################################### BFS ######################################### 
  public void connect(TreeLinkNode root) {
        if(root == null) return;
        Queue<TreeLinkNode> q = new ArrayDeque<>();
        q.offer(root);
        while(!q.isEmpty()) {
            int m = q.size();
            TreeLinkNode tmp = null;
            TreeLinkNode prev = null;
            for(int i=0; i<m;i++) {
                 tmp = q.poll();
                 if(tmp.left != null) {
                    if(prev != null) prev.next = tmp.left;
                    tmp.left.next = tmp.right;
                    q.offer(tmp.left);
                }
                if(tmp.right != null) {
                    q.offer(tmp.right);
                    prev = tmp.right;
                }
            }
            if(tmp != null) tmp.next = null;
        }
    }


//######################################### Recursive ######################################### 
void connect_helper(TreeLinkNode* head,TreeLinkNode *tail) {
    if(head == tail) {
        return;
    }
    head->next = tail;
    
    if(head != NULL && tail != NULL) {
        connect_helper(head->left,head->right);
        connect_helper(tail->left,tail->right);
        connect_helper(head->right,tail->left);
    }
}
void connect(TreeLinkNode *root) {
    if(!root) {
        return;
    }
    connect_helper(root->left,root->right);
}
