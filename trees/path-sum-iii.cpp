//Path Sum III
//You are given a binary tree in which each node contains an integer value.
//Find the number of paths that sum to a given value.
//The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).
//The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.
//Example:
//root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
//      10
//     /  \
//    5   -3
//   / \    \
//  3   2   11
// / \   \
//3  -2   1
//Return 3. The paths that sum to 8 are:
//1.  5 -> 3
//2.  5 -> 2 -> 1
//3. -3 -> 11
//

#include "../headers/global.hpp"
#include "../headers/treenode.h"


//####################################### Recursive ####################################### 
//T: O(n^2) ,  O(nlogn) in best case (balanced tree).
//S : O(n)

//
//            1
//      2           3
//   4     5     6     7

//Analysis of pathSum
//Firstly, pathSum() will be called O(n) times, which is O(n) to traverse the tree.
//Analysis of pathSumFrom
//Then, on every node, we call pathSumFrom(), but notice, the time of this call is different on different node. 
//Consider node 2 and node 3 in above tree, they have O(3) and O(3) respectfully. Which means,
//the sum time of pathSumFrom() from a layer is <= O(n).
//Overall, the time complexity is: O(n) + height * O(n)
//Best case = O(n) + logn * O(n) = O(nlogn)
//Worst case = O(n) + n * O(n) = O(n^2)

public int pathSum(TreeNode root, int sum) {       
    if(root == null) return 0;
    return pathSumFrom(root , sum) + pathSum(root.left , sum) + pathSum(root.right, sum);
	
	//Problem : pathSum(root.left, sum)  and pathSum(root.left, sum-root.val) : count path sum twice
    //pathSum(root.left, sum) + pathSum(root.right, sum) +  //The sum without root.val. 
    //pathSum(root.left, sum-root.val) + pathSum(root.right, sum-root.val); //The sum with root.val.
}

private int pathSumFrom(TreeNode root, int sum) {
    if(root == null) return 0;
	//NOTE : ? => precedance (R-L)
    return (root.val == sum ? 1 : 0) + pathSumFrom(root.left, sum - root.val) 
			+ pathSumFrom(root.right, sum - root.val);
}


//####################################### Recursive ####################################### 
int rootSum(TreeNode* root, int sum) { 
  if (root == nullptr) { 
    return 0; 
  }
  return (sum == root->val) + rootSum(root->left, sum - root->val) + rootSum(root->right, sum - root->val);
}

int pathSum(TreeNode* root, int sum) { 
  if (root == nullptr) 
    return 0;
  return rootSum(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
}

//######################### Use Dynamic root/head  ######################### 
//
///For example, the total sum is 8, root value is 3, in this case, you can pass either 8 or 5 to the next level. When you pass 8 to the children, it means that its children can be the new head because root is not in the path in this case. When you pass 5 to the children, then the children cannot be the new head anymore because in this case, root is the head. That's why you need the has_head variable so you know if the current node can be head or not with the given sum value
void countPath(TreeNode* root, int sum, int& count, bool has_head){ 
  if (!root) {
    return;
  }
  if (root->val == sum) {
    count++;
  }
  if (!has_head){  //in this case current node can be new head
      countPath(root->left, sum, count, false); 
      countPath(root->right, sum, count, false);
  }
  countPath(root->left, sum-root->val, count, true);
  countPath(root->right, sum-root->val, count, true); 
}

int pathSum(TreeNode* root, int sum) { 
  int count = 0;
  countPath(root, sum, count, false);
  return count;
}

//############################ Wrong : Only considers path from root to leaf ############################ 
void helper(TreeNode *root,int sum,int org_sum,int& cnt ) {
  if(!root) {
    return;
  }
  int l_val = root->val;
  if(sum == org_sum) {
    cnt += 1;
  }  
  sum += l_val;
  helper(root->left,sum,org_sum,cnt);
  helper(root->right,sum,org_sum,cnt);
}

int pathSum(TreeNode* root, int sum) {
    int cnt = 0;
    helper(root,0,sum,cnt);
    return cnt;
}


//############################# Prefix sum ############################# 

public int pathSum(TreeNode root, int sum) {
    Map<Integer, Integer> map = new HashMap<>();
    map.put(0, 1);  //Default sum = 0 has one count
    return backtrack(root, 0, sum, map); 
}
//BackTrack one pass
public int backtrack(TreeNode root, int sum, int target, Map<Integer, Integer> map){
    if(root == null)
        return 0;
    sum += root.val;
    int res = map.getOrDefault(sum - target, 0);    //See if there is a subarray sum equals to target
    map.put(sum, map.getOrDefault(sum, 0)+1);
    //Extend to left and right child
    res += backtrack(root.left, sum, target, map) + backtrack(root.right, sum, target, map);
    map.put(sum, map.get(sum)-1);   //Remove the current node so it wont affect other path
    return res;
}

//############################# recursion  ############################# 
///Time Complexity should be O(N^2) for the worst case and O(NlogN) for balanced binary Tree.
//
//So the idea is similar as Two sum, using HashMap to store ( key : the prefix sum, value : how many ways get to this prefix sum) , and whenever reach a node, we check if prefix sum - target exists in hashmap or not, if it does, we added up the ways of prefix sum - target into res.
//For instance : in one path we have 1,2,-1,-1,2, then the prefix sum will be: 1, 3, 2, 1, 3, let's say we want to find target sum is 2, then we will have{2}, {1,2,-1}, {2,-1,-1,2} and {2}ways.
//used global variable count, but obviously we can avoid global variable by passing the count from bottom up. The time complexity is O(n). This is my first post in discuss, open to any improvement or criticism. :)
public class Solution {
    public int pathSum(TreeNode root, int sum) {
        if(root == null)
            return 0;
        return findPath(root, sum) + pathSum(root.left, sum) + pathSum(root.right, sum);
    }
    
    public int findPath(TreeNode root, int sum){
        int res = 0;
        if(root == null)
            return res;
        if(sum == root.val)
            res++;
        res += findPath(root.left, sum - root.val);
        res += findPath(root.right, sum - root.val);
        return res;
    }
   
}
