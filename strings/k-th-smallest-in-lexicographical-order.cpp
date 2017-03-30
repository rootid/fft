//K-th Smallest in Lexicographical Order
//Given integers n and k, find the lexicographically k-th smallest integer in the range from 1 to n.
//Note: 1 ≤ k ≤ n ≤ 109.
//Example:
//Input:
//n: 13   k: 2
//Output:
//10
//Explanation:
//The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.


//https://discuss.leetcode.com/topic/64624/concise-easy-to-understand-java-5ms-solution-with-explaination/6
//################################### Denary tree ################################### 

#include "../headers/global.hpp"

int helper(long curr, long next, long n) {  //This compute the level differene between curr and next
  int result = 0;
  //eg. compute distance between 1,2 @same level
  while (curr <= n) {
      result += min(next, n + 1) - curr; 
      cout << "R = " << result << " next " << next << " curr " << curr << endl;
      curr *= 10; //next preorder ele
      next *= 10;
  }
  return result; 
}

int findKthNumber(int n, int k) { 
  int result = 1;
  while (k > 1) { 
    //determine distance between the adjacent node/next node
    int count = helper(result, result + 1, n);
    cout << count << endl;
    if (count < k) { 
        result++;
        k -= count; //update the k
    } else { 
      result *= 10; //Go the next preorder element
      k--; 
    }
  }
  return result; 
}

int main() {

  findKthNumber(13,4);
}
