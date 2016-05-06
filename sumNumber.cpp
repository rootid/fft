//Sum Root to Leaf Numbers 
//Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
//An example is the root-to-leaf path 1->2->3 which represents the number 123.
//Find the total sum of all root-to-leaf numbers.
//For example,
//    1
//   / \
//  2   3
//The root-to-leaf path 1->2 represents the number 12.
//The root-to-leaf path 1->3 represents the number 13.
//Return the sum = 12 + 13 = 25.
#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void printVec (vector<int>& s) {
    for(int i=0;i<s.size();i++) {
      cout << s[i] << " ";
    }
    cout << endl;
}

void sumPathWithRef(TreeNode *root,vector<int>& s) {
  if(!root) {
    return;
  }

  s.push_back(root->val);
  if(root->left == NULL && root->right == NULL) {
    printVec(s);
  }
  sumPathWithRef(root->left,s);
  sumPathWithRef(root->right,s);
  s.pop_back();
}

void sumPathHelper(TreeNode *root,vector<int> s,int &sum) {
  if(!root) {
    return;
  }
  s.push_back(root->val);
  if(root->left == NULL && root->right == NULL) {
    int len = s.size();
    int localSum = 0;
    for(int i=len -1;i>=0;i--) {
      //cout << s[len-1-i] << " ";
      localSum += s[len-1-i] * pow(10,i);
      //cout << localSum  << " ";
    }
    cout << endl;
    sum += localSum;
    //printVec(s);
  }
  sumPathHelper(root->left,s,sum);
  sumPathHelper(root->right,s,sum);
}


int sumNumbers(TreeNode* root) {

  vector<int> s;
  int sum = 0;
  if(!root) {
    return sum;
  }
  sumPathHelper(root,s,sum);
  return sum;
}


int main(int argc, char *argv[])
{

  TreeNode* t = new TreeNode(1);
  t->left = new TreeNode(2);
  t->left->left = new TreeNode(4);
  t->right = new TreeNode(3);
  vector<int> s;
  int sum = 0;
  sumPathHelper(t,s,sum);
  cout << "Result " << sum << endl;
  return 0;
}






//Recursive
public class Solution {
    public int sumNumbers(TreeNode root) {
        if (root == null)
            return 0;
        return sumR(root, 0);
    }
    public int sumR(TreeNode root, int x) {
        if (root.right == null && root.left == null)
            return 10 * x + root.val;
        int val = 0;
        if (root.left != null)
            val += sumR(root.left, 10 * x + root.val);
        if (root.right != null)
            val += sumR(root.right, 10 * x + root.val);
        return val;
    }
}


//BFS : store sum at each level


public class Solution {
public int sumNumbers(TreeNode root) {
    int total = 0;
    LinkedList<TreeNode> q = new LinkedList<TreeNode>();
    LinkedList<Integer> sumq = new LinkedList<Integer>();
    if(root !=null){
        q.addLast(root);
        sumq.addLast(root.val);
    }
    while(!q.isEmpty()){
        TreeNode current = q.removeFirst();
        int partialSum = sumq.removeFirst();
        if(current.left == null && current.right==null){
            total+=partialSum;
        }else{
            if(current.right !=null){
                q.addLast(current.right);
                sumq.addLast(partialSum*10+current.right.val);
            }
            if(current.left !=null){
                q.addLast(current.left);
                sumq.addLast(partialSum*10+current.left.val);
            }

        }

    }
    return total;
}
}

//recursive
class Solution {
public:
    int sumNumbers(TreeNode *root) {
        if(!root)
            return 0;
        sum=0;
        DFS(root, 0);
        return sum;
    }

    void DFS(TreeNode *&node, int currentSum)
    {
        currentSum=currentSum*10+node->val;
        if(!node->left&&!node->right)
            sum+=currentSum;
        if(node->left)
            DFS(node->left, currentSum);
        if(node->right)
            DFS(node->right, currentSum);
    }
private:
    int sum;
};

