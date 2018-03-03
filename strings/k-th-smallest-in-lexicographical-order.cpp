//K-th Smallest in Lexicographical Order
//Given integers n and k, find the lexicographically k-th smallest integer in
//the range from 1 to n.
//Note: 1 ≤ k ≤ n ≤ 109.
//Example:
//Input:
//n: 13   k: 2
//Output:
//10
//Explanation:
//The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so
//the second smallest number is 10.


//https://discuss.leetcode.com/topic/64624/concise-easy-to-understand-java-5ms-solution-with-explaination/6

#include "../headers/global.hpp"


//################################### Denary tree ###################################
//calculate the steps between curr and curr + 1 (neighbor nodes in same level),
//in order to skip some unnecessary moves.
int distance(long curr, long nxt, int n) {
    int dist = 0;
    while(curr <= n) {
        dist += Math.min(n+1, nxt) - curr;
        curr *= 10;
        nxt *= 10;
    }
    return dist;
}

public int findKthNumber(int n, int k) {
    int curr = 1;
    k = k -1;
    while(k > 0) {
        int dist = distance(curr, curr+1, n);
        if(dist <= k) {
            curr++; //Go wide (BFS)
            k -= dist;
        } else {
            curr *= 10; //Go deep (DFS)
            k -= 1;
        }
    }
    return curr;
}


//################################### Denary tree ###################################
int result = Integer.MIN_VALUE;
int level = Integer.MIN_VALUE;

void findKthNumberHelper(int i, int n) {
    if(level == 1) {
        result = i;
        return;
    }
    for(int j=0;j<=9;j++) {
        if(i*10+j > n) break;
        level -= 1;
        findKthNumberHelper(i*10+j,n);
    }
}

public int findKthNumber(int n, int k) {
    level = k;
    for(int i=1;i<=9;i++) {
        if(result != Integer.MIN_VALUE) return result;
        findKthNumberHelper(i,n);
        level -= 1;
    }
    return result;
}


//################################### Denary tree ###################################
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
