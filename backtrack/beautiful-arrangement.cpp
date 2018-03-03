//Beautiful Arrangement
//Suppose you have N integers from 1 to N. We define a beautiful arrangement as
//an array that is constructed by these N numbers successfully if one of the
//following is true for the ith position (1 ≤ i ≤ N) in this array:
//The number at the ith position is divisible by i.
//i is divisible by the number at the ith position.
//Now given N, how many beautiful arrangements can you construct?
//Example 1:
//Input: 2
//Output: 2
//Explanation:
//The first beautiful arrangement is [1, 2]:
//Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).
//Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).
//The second beautiful arrangement is [2, 1]:
//Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).
//Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.
//Note:
//N is a positive integer and will not exceed 15.

//######################################### Backtracking bottom-up  #########################################
//TC : O(N!)
int countArrangement(int N) {
  int count = 0;
  vector<bool> visited(N + 1,false);
  helper(N, visited, 1,count);
  return count;
}
void helper(int N, vector<bool>& visited, int k,int& count) {
    if (k == N + 1) {
        count++;
        return;
    }
    for (int i = 1; i <= N; i++) { //Each k position will hold the numbers from [1..n]
        if (!visited[i] && (i % k == 0 || k % i == 0)) {
            visited[i] = true;
            helper(N, visited, k + 1,count);
            visited[i] = false;
        }
    }
}

//######################################### Backtracking top-down #########################################
int countArrangement(int N) {
    int res = 0;
    vector<bool> numbers(N+1, false);
    dfs_helper(N, res, numbers);
    return res;
 }

 void dfs_helper(int N, int& res, vector<bool>& numbers){
    if(N == 1){
        res++;
        return;
    }
    for(int i = 1; i < numbers.size(); ++i){
        if(numbers[i]) continue;
        if(N%i ==0 || i%N == 0){
            numbers[i] = true;
            find(N-1, res, numbers);
            numbers[i] = false;
        }
    }
    return;
}

//######################### BAcktracking + memoization #########################
int countArrangement(int N) {
      if (N == 0) return 0;
      vector<int> m(1<<(N+1), -1);
      return dfs(1, N, 0, m);
  }

  int dfs(int start, int n, int used, vector<int>& m) {
      if (start == n+1) return 1;
      if (m[used] != -1) return m[used];
      int res = 0;
      for (int i = 1; i <= n; ++i) {
          if (!(used & (1<<i)) && (i%start == 0 || start%i == 0))
              res += dfs(start+1, n, used|(1<<i), m);
      }
      m[used] = res;
      return res;
}


//###########################################################################
//i = N t0 1 (bottom up) : 230ms
//Because position i = 1 can hold any number, so I don't even have to check
//whether the last remaining number fits there. Also, position i = 2 happily
//holds every second number and i = 3 happily holds every third number, so
//filling the lowest positions last has a relatively high chance of success. In
//other words, it's relatively hard to end up with dead ends this way.
//def countArrangement(self, N):
//    def count(i, X):
//        if i == 1:
//            return 1
//        return sum(count(i - 1, X - {x})
//                   for x in X
//                   if x % i == 0 or i % x == 0)
//    return count(N, set(range(1, N + 1)))
//###########################################################################
// i = 1 to N Top down : 2300ms
//def countArrangement(self, N):
//    def count(i, X):
//        if i > N:
//            return 1
//        return sum(count(i + 1, X - {x})
//                   for x in X
//                   if x % i == 0 or i % x == 0)
//    return count(1, set(range(1, N + 1)))
