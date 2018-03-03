//Palindrome Partitioning II
//Given a string s, partition s such that every substring of the partition is a
//palindrome.
//Return the minimum cuts needed for a palindrome partitioning of s.
//For example, given s = "aab",
//Return 1 since the palindrome partitioning ["aa","b"] could be produced using
//1 cut.
 int minCut(string s) {
   if(s.empty()) return 0;
   int n = s.size();
   vector<vector<bool>> pal(n,vector<bool>(n,false));
   vector<int> d(n);
   //traverse from R-L
   for(int i=n-1;i>=0;i--) {
       d[i] = n-i-1;
       for(int j=i;j<n;j++) {
          //j-i < 2 : i-1,i,i+1,i+2
           if(s[i]==s[j] && (j-i<2 || pal[i+1][j-1])) {
              pal[i][j]=true;
              if(j == n-1) {
                  d[i]=0;
              }else if(d[j+1]+1<d[i]) {
                  d[i]=d[j+1]+1;
              }
           }
       }
   }
   return d[0];
}

//############################################ DAG + shorted path #######################################################################
int minCut(string s) {
  int n = s.size();
  if (n <= 0) return 0;
   vector<vector<bool> > lut(n, vector<bool>(n, true));
   vector<vector<int> > adjList(n+1, vector<int>());
   // build the palindrome look up table, O(n^2)
   for (int k = 1; k <= n-1; ++k) {
     int i = 0, j = k;
     while (j < n) {
       lut[i][j] = (s[i] == s[j] && lut[i+1][j-1]);
       ++i;
       ++j;
     }
   }
   // build the graph, O(n^2);
   for (int i = 0; i < n; ++i) {
     for (int j = i; j < n; ++j) {
       if (lut[i][j] == true) {
         adjList[i].push_back(j+1);
       }
     }
   }
   // Use bfs to find shortest path from 0 to n, O(|E|)
   // |E| is the number of edges, at most O(n^2)
   vector<int> dist(n+1, -1);
   queue<int> q;
   dist[0] = 0;
   q.push(0);
   while (!q.empty()) {
     int u = q.front();
     q.pop();
     if (u == n) break;
     vector<int>& neighbors = adjList[u];
     // Greedy strategy, in reversed order so that furthest nodes are explored first.
     for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
       int v = *it;
       if (dist[v] == -1) {
         q.push(v);
         dist[v] = dist[u] + 1;
       }
     }
   }
   return dist[n] - 1;
}
