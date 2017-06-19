//Add One Row to Tree
//Given the root of a binary tree, then value v and depth d, you need to add a row of nodes with value v at the given depth d. The root node is at depth 1.
//The adding rule is: given a positive integer depth d, for each NOT null tree nodes N in depth d-1, create two tree nodes with value v as N's left subtree root and right subtree root. And N's original left subtree should be the left subtree of the new left subtree root, its original right subtree should be the right subtree of the new right subtree root. If depth d is 1 that means there is no depth d-1 at all, then create a tree node with value v as the new root of the whole original tree, and the original tree is the new root's left subtree.
//Example 1:
//Input: 
//A binary tree as following:
//       4
//     /   \
//    2     6
//   / \   / 
//  3   1 5   
//v = 1
//d = 2
//Output: 
//       4
//      / \
//     1   1
//    /     \
//   2       6
//  / \     / 
// 3   1   5   
//Example 2:
//Input: 
//A binary tree as following:
//      4
//     /   
//    2    
//   / \   
//  3   1    
//v = 1
//d = 3
//Output: 
//      4
//     /   
//    2
//   / \    
//  1   1
// /     \  
//3       1
//Note:
//The given d is in range [1, maximum depth of the given tree + 1].
//The given binary tree has at least one tree node.

//################################### Recursive + reduce depth at each level ################################### 
//0 : attach to right
//1 : attach to left 
TreeNode* addOneRow(TreeNode* root, int v, int d) {
    if (d == 1) {
        TreeNode* newroot = new TreeNode(v);
        newroot->left = root;
        return newroot;
    } else if (d == 0) {
        TreeNode* newroot = new TreeNode(v);
        newroot->right = root;
        return newroot;
    }
    if (!root) {
        return nullptr;
    } else if (d == 2) { //add node next to root
        root->left  = addOneRow(root->left,  v, 1);
        root->right = addOneRow(root->right, v, 0);
        return root;
    } else if (d > 2) {
        root->left  = addOneRow(root->left,  v, d - 1);
        root->right = addOneRow(root->right, v, d - 1);
    }
    return root;
}


//########################################### DFS  ########################################### 
public:
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
          //Given : depth d is 1 that means there is no depth d-1 at all, then create a tree node with value v as the new root of the whole original tree
        if (d == 1) {
            TreeNode *p = new TreeNode(v);
            p->left = root;
            return p;
        }
        dfs(root, v, d-1);
        return root;
    }
private:
    void dfs(TreeNode* p, int v, int d) {
        if (p == nullptr) return;
        if (d == 1) {
            TreeNode *pl = new TreeNode(v), *pr = new TreeNode(v);
            //adjust the ptr, p : actual node
            pl->left = p->left; 
            pr->right = p->right;
            p->left = pl;
            p->right = pr;
        }
        else {
           dfs(p->left, v, d-1);
           dfs(p->right, v, d-1);
        }
    }

//########################################### Bad  ########################################### 
TreeNode* addOneRow(TreeNode* root, int v, int d) { 
  if (d == 0 || d == 1) { 
    TreeNode* newroot = new TreeNode(v);
    (d ? newroot->left : newroot->right) = root;
    return newroot;
  }
  if (root && d >= 2) {
      root->left  = addOneRow(root->left,  v, d > 2 ? d - 1 : 1);
      root->right = addOneRow(root->right, v, d > 2 ? d - 1 : 0);
  }
  return root; 
}

//########################################### Good  ########################################### 
TreeNode* addOneRow(TreeNode* root, int v, int d) {
    if (d < 2) {
        TreeNode* newroot = new TreeNode(v);
        (d ? newroot->left : newroot->right) = root;
        return newroot;
    }
    if (root) {
        root->left = addOneRow(root->left, v, d - 1);
        root->right = addOneRow(root->right, v, d - 1 - (d == 2));
    }
    return root;
}


//########################################### BFS  ########################################### 
TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if (d == 1) {
            TreeNode *newRoot = new TreeNode(v);
            newRoot->left = root;
            return newRoot;
        }
        --d;
        queue<TreeNode*> q;
        TreeNode *t = nullptr;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            if (--d == 0) {
                while (size--) {
                    t = q.front(); q.pop();
                    TreeNode *l = new TreeNode(v);
                    TreeNode *r = new TreeNode(v);
                    l->left = t->left; t->left = l;
                    r->right = t->right; t->right = r;
                }
                break;
            }
            while (size--) {
                t = q.front(); q.pop();
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
        }
        return root;
    }


//######################################## pytonic ######################################## 
//Go row by row to the row at depth d-1, then insert the new nodes there.
//def addOneRow(self, root, v, d):
//    dummy, dummy.left = TreeNode(None), root
//    row = [dummy]
//    for _ in range(d - 1):
//        row = [kid for node in row for kid in (node.left, node.right) if kid]
//    for node in row:
//        node.left, node.left.left = TreeNode(v), node.left
//        node.right, node.right.right = TreeNode(v), node.right
//    return dummy.left
//
//class Solution(object):
//    def addOneRow(self, root, v, d):
//        if d < 2:
//            node = TreeNode(v)
//            node.left = root if d == 1 else None
//            node.right = root if d == 0 else None
//            return node
//        elif root:
//            root.left = self.addOneRow(root.left, v, d - 1 if d > 2 else 1)
//            root.right = self.addOneRow(root.right, v, d - 1 if d > 2 else 0)
//            return root
//##############################  Recursive  ##############################  
//When d is 1, depending on the direction we went previously (default is left), we need to make a node with value v and put the rest of the tree as either the left or right child.
//Otherwise, we'll recursively perform our operation on the children of our node, with the depth decremented by 1.
//def addOneRow(self, root, v, d, direction = 'left'):
//    if d == 1:
//        ans = TreeNode(v)
//        setattr(ans, direction, root)
//        return ans
//    elif root:
//        root.left = self.addOneRow(root.left, v, d-1, 'left')
//        root.right = self.addOneRow(root.right, v, d-1, 'right')
//        return root
//
//########################################## BFS ########################################## 
//def addOneRow(self, root, v, d):
//    # special case where depth is one
//    if d == 1:
//        new_root = TreeNode(v)
//        new_root.left = root
//        return new_root
//    queue = collections.deque([root])
//    level = 1
//    while queue:
//        size = len(queue)
//        # level order traversal
//        for i in range(size):
//            curr = queue.popleft()
//            # insert nodes if we reach 1 level before d
//            if level == d-1:
//                old_left, old_right = curr.left, curr.right
//                curr.left, curr.right = TreeNode(v), TreeNode(v)
//                curr.left.left, curr.right.right = old_left, old_right
//            else:
//                if curr.left: 
//                    queue.append(curr.left)
//                if curr.right:
//                    queue.append(curr.right)
//        # return root once we've appended
//        if level == d-1:
//            return root
//        level += 1
//    return None
