//Follow up for problem "Populating Next Right Pointers in Each Node".
//What if the given tree could be any binary tree? Would your previous solution still work?
//Note:
//You may only use constant extra space.
//For example,
//Given the following binary tree,
//         1
//       /  \
//      2    3
//     / \    \
//    4   5    7
//After calling your function, the tree should look like:
//         1 -> NULL
//       /  \
//      2 -> 3 -> NULL
//     / \    \
//    4-> 5 -> 7 -> NULL
//
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
void connect(TreeLinkNode *root) {
    for (auto head = root; head != NULL; ) {  // explore each level
      TreeLinkNode* next_head = new TreeLinkNode(0), *next_tail = next_head; 
      for (auto cur = head; cur != NULL; cur = cur->next) {  // at each level
        if (cur->left != NULL) { 
          next_tail->next = cur->left; 
          next_tail = cur->left; 
        } 
        if (cur->right != NULL) { 
          next_tail->next = cur->right;
          next_tail = cur->right; //update next tail; 
        } 
      } 
      head = next_head->next; 
    }
}

//W/o Extran node
static void Append(TreeLinkNode** head, TreeLinkNode** tail, TreeLinkNode* node)
{   if(!*tail)
        *head = node;
    else
        (*tail)->next = node;
    *tail = node;
}
static void connect(TreeLinkNode *root)
{   for(TreeLinkNode* head = root; head != NULL;)
    {   TreeLinkNode* nextHead = NULL;
        TreeLinkNode* nextTail = NULL;
        for(TreeLinkNode* node = head; node != NULL; node = node->next)
        {   if(node->left)
                Append(&nextHead, &nextTail, node->left);
            if(node->right)
                Append(&nextHead, &nextTail, node->right);
        }
        head = nextHead;
   
