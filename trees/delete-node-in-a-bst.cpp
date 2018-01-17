//Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.
//Basically, the deletion can be divided into two stages:
//Search for a node to remove.
//If the node is found, delete the node.
//Note: Time complexity should be O(height of tree).
//Example:
//root = [5,3,6,2,4,null,7]
//key = 3
//    5
//   / \
//  3   6
// / \   \
//2   4   7
//Given key to delete is 3. So we find the node with value 3 and delete it.
//One valid answer is [5,4,6,2,null,null,7], shown in the following BST.
//    5
//   / \
//  4   6
// /     \
//2       7
//Another valid answer is [5,2,6,null,4,null,7].
//    5
//   / \
//  2   6
//   \   \
//    4   7
//############################################# Good ############################################# 
TreeNode* deleteNode(TreeNode* root, int key) {
      if(!root) {
         return root;
     }
     if(root->val == key) {
         if(root->right) {
     		TreeNode* p = root->right;
     		while(p->left) {
     		    p = p->left;
     		}
     		p->left = root->left;
     		return root->right;
     	}
     	else if(root->left) {
     		return root->left;
     	}
     	else return NULL;
     } else if(root->val < key) {
         root->right = deleteNode(root->right,key);
     } else {
        root->left = deleteNode(root->left,key);
     }
     return root;
}

//######################################### Python ######################################### 
def deleteNode(self, root, key):
    def getNodes(root):
        if root:
            getNodes(root.left)
            if root.val != key:
                nodes.append(root)
            getNodes(root.right)
    nodes = []
    getNodes(root)
    root = None
    while nodes:
        root, root.left, root.right = nodes.pop(), None, root
    return root


//We will only do deletion when root->val == NULL, so if root->val > key we can know that the key is in the left subtree, then root->left = deleteNode(root->left, key), if root->val < key should do root->right = deleteNode(root->right, key).
//When root->val == NULL we need to delete root. If root->left == NULL && root->right == NULL we can just delete root and return NULL, else we can chose root->left or root->right to be the new root in case it is not NULL.
//


//############################################# GENERAL BT DELETE ############################################# 

 TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;
        if (root->val == key) {
            if (!root->right) {
                TreeNode* left = root->left;
                delete root;
                return left;
            }
            else {
                TreeNode* right = root->right;
                while (right->left)
                    right = right->left;
                swap(root->val, right->val);    
            }
        }
        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);
        return root;
}

//############################################# Log GENERIC ############################################# 

TreeNode* deleteNode(TreeNode* root, int key) {
    if( !root )
        return nullptr;
    
    if( root->val == key ){
        if( !root->right )
            return root->left;
        else{
            TreeNode* n = root->right;
            while( n->left )
                n = n->left;
            swap( n->val , root->val );
            
            root->right = deleteNode( root->right , key );
            return root;
        }
    }
    if( root->val > key )
        root->left = deleteNode( root->left , key );
    if( root->val < key )
        root->right = deleteNode( root->right , key );
    return root;
}

//############################################# FIX ME  ############################################# 
void helperDel(TreeNode* sRoot,TreeNode *root, int key) {
     if(!root) {
        return ;
    }
    if(root->val == key) {
        if(root->left == NULL && root->right == NULL) {
            root = NULL;
        } else {
            TreeNode *tmp = root->right;
            while( !tmp && tmp->left != NULL) {
                tmp = tmp->left;
            }
            root->val = tmp->val;
        }
        return ;
    } else if(root->val < key) {
        helperDel(sRoot,root->left,key);
    } else {
        helperDel(sRoot,root->right,key);
    }
}
TreeNode* deleteNode(TreeNode* root, int key) {
     helperDel(root,root,key);
     return root;
}
