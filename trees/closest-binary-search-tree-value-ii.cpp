//Closest Binary Search Tree Value II
//Given a non-empty binary search tree and a target value, find k values in the
//BST that are closest to the target.
//Note:
//Given target value is a floating point.
//You may assume k is always valid, that is: k ≤ total nodes.
//You are guaranteed to have only one unique set of k values in the BST that
//are closest to the target.
//Follow up:
//Assume that the BST is balanced, could you solve it in less than O(n) runtime
//(where n = total nodes)?
//Hint:
//Consider implement these two helper functions:
//getPredecessor(N), which returns the next smaller node to N.
//getSuccessor(N), which returns the next larger node to N.
//Try to assume that each node has a parent pointer, it makes the problem much
//easier.
//Without parent pointer we just need to keep track of the path from the root
//to the current node using a stack.
//You would need two stacks to track the path in finding predecessor and
//successor node separately.
//
//
//######################################### Heap + O(n log n) #########################################
void dfs(TreeNode* root, priority_queue<pair<double, int>>& pq, double target, int k) {
    if(!root) return;

    pq.push(make_pair(fabs(target - double(root->val)), root->val));

    if(pq.size() > k)
        pq.pop();

    dfs(root->left, pq, target, k);
    dfs(root->right, pq, target, k);
}

vector<int> closestKValues(TreeNode* root, double target, int k) {
    priority_queue<pair<double, int>> pq;
    vector<int> result;

    dfs(root, pq, target, k);
    while(!pq.empty()) {
        result.push_back(pq.top().second);
        pq.pop();
    }

    return result;
}

//######################################### O(log(n) + k) #########################################
//Building each of the stacks takes O(log(n)) assuming BST is balanced.
//Each call to getNextPred/Succ has an amortized cost of O(1), since every node
//is pushed and popped at most once.
class Solution {
public:
    stack<TreeNode*> pre;
    stack<TreeNode*> suc;
    TreeNode* root;
    double target;
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        this->root = root;
        this->target = target;
        buildPre();
        buildSuc();
        // in case there exists a node with val == target
        if (!pre.empty() && !suc.empty() && pre.top() == suc.top()) getPre();

        vector<int> res;
        for (int i = 0; i < k; i++) {
            if      (pre.empty()) res.push_back(getSuc());
            else if (suc.empty()) res.push_back(getPre());
            else {
                double preDiff = fabs(double(pre.top()->val) - target);
                double sucDiff = fabs(double(suc.top()->val) - target);
                res.push_back(preDiff < sucDiff ? getPre() : getSuc());
            }
        }
        return res;
    }

    // build pre stack (contains only elements smaller than target)
    void buildPre() {
        TreeNode* t = root;
        while (t) {
            if      (t->val == target) { pre.push(t); break; }
            else if (t->val <  target) { pre.push(t); t = t->right; }
            else                       {              t = t->left; }
        }
    }

    // build suc stack (contains only elements greater than target)
    void buildSuc() {
        TreeNode* t = root;
        while (t) {
            if      (t->val == target) { suc.push(t); break; }
            else if (t->val >  target) { suc.push(t); t = t->left; }
            else                       {              t = t->right; }
        }
    }

    // get the biggest element that's smaller
    int getPre() {
        TreeNode* node = pre.top(); pre.pop();
        int res = node->val;
        node = node->left;
        while (node) { pre.push(node); node = node->right; }
        return res;
    }

    // get the smallest element that's bigger
    int getSuc() {
        TreeNode* node = suc.top(); suc.pop();
        int res = node->val;
        node = node->right;
        while (node) { suc.push(node); node = node->left; }
        return res;
    }
};


//######################################### Inorder O(n) + Window size k #########################################
public class Solution {

    public List<Integer> closestKValues(TreeNode root, double target, int k) {
        LinkedList<Integer> res = new LinkedList<>();
        collect(root, target, k, res);
        return res;
    }

    public void collect(TreeNode root, double target, int k, LinkedList<Integer> res) {
        if (root == null) return;
        collect(root.left, target, k, res);

        if (res.size() == k) {
            //if size k, add curent and remove head if it's optimal, otherwise return
            if (Math.abs(target - root.val) < Math.abs(target - res.peekFirst()))
                res.removeFirst();
            else return;
        }
        res.add(root.val);
        collect(root.right, target, k, res);
    }
}


//######################################### O(k + logN) #########################################
public class Solution {
    public List<Integer> closestKValues(TreeNode root, double target, int k) {
        List<Integer> ret = new LinkedList<>();
        Stack<TreeNode> succ = new Stack<>();
        Stack<TreeNode> pred = new Stack<>();
        initializePredecessorStack(root, target, pred);
        initializeSuccessorStack(root, target, succ);
        if(!succ.isEmpty() && !pred.isEmpty() && succ.peek().val == pred.peek().val) {
            getNextPredecessor(pred);
        }
        while(k-- > 0) {
            if(succ.isEmpty()) {
                ret.add(getNextPredecessor(pred));
            } else if(pred.isEmpty()) {
                ret.add(getNextSuccessor(succ));
            } else {
                double succ_diff = Math.abs((double)succ.peek().val - target);
                double pred_diff = Math.abs((double)pred.peek().val - target);
                if(succ_diff < pred_diff) {
                    ret.add(getNextSuccessor(succ));
                } else {
                    ret.add(getNextPredecessor(pred));
                }
            }
        }
        return ret;
    }

    private void initializeSuccessorStack(TreeNode root, double target, Stack<TreeNode> succ) {
        while(root != null) {
            if(root.val == target) {
                succ.push(root);
                break;
            } else if(root.val > target) {
                succ.push(root);
                root = root.left;
            } else {
                root = root.right;
            }
        }
    }

    private void initializePredecessorStack(TreeNode root, double target, Stack<TreeNode> pred) {
        while(root != null){
            if(root.val == target){
                pred.push(root);
                break;
            } else if(root.val < target){
                pred.push(root);
                root = root.right;
            } else{
                root = root.left;
            }
        }
    }

    private int getNextSuccessor(Stack<TreeNode> succ) {
        TreeNode curr = succ.pop();
        int ret = curr.val;
        curr = curr.right;
        while(curr != null) {
            succ.push(curr);
            curr = curr.left;
        }
        return ret;
    }

    private int getNextPredecessor(Stack<TreeNode> pred) {
        TreeNode curr = pred.pop();
        int ret = curr.val;
        curr = curr.left;
        while(curr != null) {
            pred.push(curr);
            curr = curr.right;
        }
        return ret;
    }
}


//###
//For the follow-up question, this is O(k log n) and maybe O(k + log n),
//haven't thought it through yet. Probably by far the longest solution I've
//posted here, I even felt the need to include comments :-P
//Imagine you didn't have a BST but a simple sorted array. How would you find
//the k values closest to the target value? You could do binary search to find
//the closest value and then move outwards with two index variables, collecting
//the k closest values. That's what I do here, except instead of simple array
//indexes I have two tree iterators in the form of root-to-node paths.
//Finding the initial iterator=path to the closest value takes O(h) time, where
//h is the height of the tree. Increasing or decreasing these iterators=paths
//also takes O(h) time. So O(kh) overall. And maybe better, as moving an
//iterator=path will often be quick. I mean, it's just an inorder traversal, so
//I'd expect O(1) amortized moving time at least if we're traversing the entir
def closestKValues(self, root, target, k):

    # Helper, takes a path and makes it the path to the next node
    def nextpath(path, kid1, kid2):
        if path:
            if kid2(path):
                path += kid2(path),
                while kid1(path):
                    path += kid1(path),
            else:
                kid = path.pop()
                while path and kid is kid2(path):
                    kid = path.pop()

    # These customize nextpath as forward or backward iterator
    kidleft = lambda path: path[-1].left
    kidright = lambda path: path[-1].right

    # Build path to closest node
    path = []
    while root:
        path += root,
        root = root.left if target < root.val else root.right
    dist = lambda node: abs(node.val - target)
    path = path[:path.index(min(path, key=dist))+1]

    # Get the path to the next larger node
    path2 = path[:]
    nextpath(path2, kidleft, kidright)

    # Collect the closest k values by moving the two paths outwards
    vals = []
    for _ in range(k):
        if not path2 or path and dist(path[-1]) < dist(path2[-1]):
            vals += path[-1].val,
            nextpath(path, kidright, kidleft)
        else:
            vals += path2[-1].val,
            nextpath(path2, kidleft, kidright)
    return vals
