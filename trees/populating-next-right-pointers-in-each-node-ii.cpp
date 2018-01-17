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


//######################################### BFS with dummy node  ######################################### 
  public static void connect(TreeLinkNode root) {
    TreeLinkNode dummy = new TreeLinkNode(0);
    TreeLinkNode pre = dummy; // pre : only used to traverse the nodes
    while(root != null) {
      if(root.left != null) {
        pre.next = root.left; //Magic : dummy.next and pre.next gets updated.
        pre = pre.next; //overwrites pre with pre.next and no change in dummy.next
      }
      if(root.right != null) {
        pre.next = root.right;
        pre = pre.next;
      }
      root = root.next;
      if(root == null) {
        System.out.println(dummy.val);
        pre = dummy;
        root = dummy.next;
        dummy.next = null;
      }
    }
  }


//######################################### BFS ######################################### 
public void connect(TreeLinkNode root) {
        if(root == null)return;
        Queue<TreeLinkNode> nodes = new LinkedList<>();
        nodes.offer(root);
        while(!nodes.isEmpty()){
            int size = nodes.size();
            for(int i = 0; i < size; i++){
                TreeLinkNode cur = nodes.poll();
                TreeLinkNode n = null;
                if(i < size - 1){
                    n = nodes.peek();
                }
                cur.next = n;
                if(cur.left != null)nodes.offer(cur.left);
                if(cur.right != null)nodes.offer(cur.right);
            }
            
        }
    }

//######################################### Iteration ######################################### 
def connect(self, node):
    tail = dummy = TreeLinkNode(0)
    while node:
        tail.next = node.left
        if tail.next:
            tail = tail.next
        tail.next = node.right
        if tail.next:
            tail = tail.next
        node = node.next
        if not node:
            tail = dummy
            node = dummy.next



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
   
