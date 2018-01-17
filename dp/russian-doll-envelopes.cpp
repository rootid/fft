//Russian Doll Envelopes
//You have a number of envelopes with widths and heights given as a pair of integers (w, h). One envelope can fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.
//What is the maximum number of envelopes can you Russian doll? (put one inside other)
//Example:
//Given envelopes = [[5,4],[6,4],[6,7],[2,3]], the maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).


//########################################## Sort + LIS O(n log n)  ########################################## 
static bool cmp_first(const pair<int, int>& i, const pair<int, int>& j) { 
  if (i.first == j.first) { 
    return i.second > j.second;
  } 
  return i.first < j.first; 
}

int maxEnvelopes(vector<pair<int, int>>& envelopes) { 
  vector<int> candidates;
  sort(envelopes.begin(), envelopes.end(), cmp_first);
  
  //get the LISubsequece
  vector<int> dp;
  for (int i = 0; i < envelopes.size(); ++i) {
      auto itr = lower_bound(dp.begin(), dp.end(), envelopes[i].second);
      if (itr == dp.end()) {
          dp.push_back(envelopes[i].second);
      } else {
          *itr = envelopes[i].second;
      }
  }
  return dp.size();
}


//########################################## Sort + LIS O(n^2)  ########################################## 
static bool cmp (pair<int, int> i, pair<int, int> j) { 
  if (i.first == j.first) 
    return i.second < j.second; 
  return i.first < j.first; 
}
int maxEnvelopes(vector<pair<int, int>>& envelopes) { 
  int N = envelopes.size();
  vector<int> dp(N, 1);
  int lis_mx = (N == 0) ? 0 : 1;
  sort(envelopes.begin(), envelopes.end(), cmp);
  //Find the LIS
  //for (int i = 0; i < N; i++) {
  for (int i = 1; i < N; i++) { //starts with 1 : reason we know that we always have at least one envelop regardless of w.h
      for (int j = i - 1; j >= 0; j--) {
          if (envelopes[i].first > envelopes[j].first && envelopes[i].second > envelopes[j].second) {
              dp[i] = max(dp[i], dp[j] + 1);
              lis_mx = max(dp[i], lis_mx); 
          }
      }
  }
  return lis_mx; 
}
