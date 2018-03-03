//Sort Transformed Array
//Given a sorted array of integers nums and integer values a, b and c. Apply a function of the form f(x) = ax2 + bx + c
//to each element x in the array.
//The returned array must be in sorted order.
//Expected time complexity: O(n)
//Example:
//nums = [-4, -2, 2, 4], a = 1, b = 3, c = 5,
//Result: [3, 9, 15, 33]
//nums = [-4, -2, 2, 4], a = -1, b = 3, c = 5
//Result: [-23, -5, 1, 7]

#include "../headers/global.hpp"
//ax^2+bx+c
long eval_exp(int x,const int &a,const int& b,const int &c) {
    return a*x*x + b*x + c;
}
vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
    int i=0;
    int n = nums.size();
    int j=n-1;
    int index = 0;
    vector<int> res(n,0);
    if( a >= 0) {
        index = n - 1;
    }
    while(i<=j){
        int left = eval_exp(nums[i],a,b,c);
        int right = eval_exp(nums[j],a,b,c);
        if(a >= 0){
            if( left > right ) {
                res[index--] = left;
                i++;
            } else {
               res[index--] = right;
               j--;
            }
        } else {
              if(left < right ) {
                res[index++] = left;
                i++;
            } else {
               res[index++] = right;
               j--;
            }

        }
    }
    return res;
}
int main() {
  vector<int> av({-4 , -2 , 2 , 4 });

  for(auto &i:av) {
    cout << i << "\t";
  }
  cout << endl;
  for(auto &i:av) {
    cout << eval_exp(i,1,3,5) << "\t";
  }
  cout << endl;
  for(auto &i:av) {
    cout << eval_exp(i,10,3,5) << "\t";
  }
  cout << endl;
  for(auto &i:av) {
    cout << eval_exp(i,-1,3,5) << "\t";
  }
  cout << endl;
}
// vim: set sw=2 sts=2 tw=120 et nospell :
