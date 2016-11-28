//Closest Binary Search Tree Value
//Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.
//Note:
//Given target value is a floating point.
//You are guaranteed to have only one unique value in the BST that is closest to the target.

//TODO : while comparing 2 doubles use below format
bool doubleEqual(double a, double b){
    return abs(a-b) <= std::numeric_limits<double>::epsilon();
}

//recursive
int closestValue(TreeNode *root,double target) {
    if(!root) {
      return 0;
    }
    int a = root->val;
    if(target < a) {
      root = root->left;  
    } else {
      root = root->right;  
    }
    if (!root) return a;
    int b = closestValue(root, target);
    if (abs(a - target) < abs(b - target) ) {
      return a;
    } 
    return b;
}

int closest_iter(TreeNode* root,double target) {
  int closest = root->val;
  while (root) {
      if (abs(closest - target) >= abs(root->val - target)) {
          closest = root->val;
      }
      if(target < root->val) {
        root = root->left;
      } else {
        root = root->right;
      }
  }
  return closest;
}

void helper(TreeNode* root,double& target,double& res) {
  if(!root) {
    return;
  }
  double tmp = (double) root->val;
  if(tmp == target) {
    res = tmp;
    return;
  }
  if(res == INT_MAX || abs(tmp-target) < abs(res-target)  ) {
    res = tmp;
    helper(root->left,target,res); 
  } else {
    helper(root->right,target,res); 
  }
}

int closestValue(TreeNode* root, double target) {
  double res = INT_MAX;
  helper(root,target,res); 
  return res;
}

int main() {

}
