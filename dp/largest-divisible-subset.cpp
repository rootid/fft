//Largest Divisible Subset
//Given a set of distinct positive integers, find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies: Si % Sj = 0 or Sj % Si = 0.
//If there are multiple solutions, return any subset is fine.
//Example 1:
//nums: [1,2,3]
//Result: [1,2] (of course, [1,3] will also be ok)
//Example 2:
//nums: [1,2,4,8]
//Result: [1,2,4,8]

//################################################### DP bottom-up ###########################################  
vector<int> largestDivisibleSubset(vector<int>& nums) {
      sort(nums.begin(), nums.end());
      vector< vector<int> > result(nums.size()); //2-d vector
      vector<int> ret;
      for (int i = 0;i < nums.size();++i) {
          for (int j = 0;j < i;++j) {
              if (nums[i] % nums[j] == 0 && result[j].size() > result[i].size()) {
                  result[i] = result[j];
              }
          }
          result[i].push_back(nums[i]); //pick the current and add to result
          if (ret.size() < result[i].size()) {
            ret = result[i];
          }
      }
      return ret;
  }


//################################################### DP bottom-up ###########################################  
//T[n] = the length of the largest divisible subset whose largest number is a[n] 
vector<int> largestDivisibleSubset(vector<int>& nums) { 
  int i,j,len=nums.size(),m=0,mi;
  vector<int> T(len,0); //max length of seq 
  vector<int> sos(len,0); //store the start of seqe
  sort(nums.begin(),nums.end());
  for(i=0;i<len;i++) {
      for(j=i;j>=0;j--) {
          if(nums[i]%nums[j]== 0 && T[j]+1>T[i]){
              T[i] = T[j]+1;
              sos[i] = j;
          }
      }
      if(T[i]>m) {
          m=T[i];
          mi=i;
      }
  }
  vector<int> re;
  for(i=0;i<m;i++){
      re.insert(re.begin(),nums[mi]);
      mi = sos[mi];
  }
  return re; 
}

//################################################### DP top-down   ###########################################  
vector<int> largestDivisibleSubset(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<int> T(nums.size(), 0);
    vector<int> parent(nums.size(), 0);
    int m = 0;
    int mi = 0;
    // for(int i = 0; i < nums.size(); ++i) // if extending by larger elements
    for(int i = nums.size() - 1; i >= 0; --i) // iterate from end to start since it's easier to track the answer index
    {
        // for(int j = i; j >=0; --j) // if extending by larger elements
        for(int j = i; j < nums.size(); ++j) {
            // if(nums[i] % nums[j] == 0 && T[i] < 1 + T[j]) // if extending by larger elements
            // check every a[j] that is larger than a[i]
            if(nums[j] % nums[i] == 0 && T[i] < 1 + T[j]) {
                // if a[j] mod a[i] == 0, it means T[j] can form a larger subset by putting a[i] into T[j]
                T[i] = 1 + T[j];
                parent[i] = j;
                
                if(T[i] > m) {
                    m = T[i];
                    mi = i;
                }
            }
        }
    }
    vector<int> ret;
    for(int i = 0; i < m; ++i) {
        ret.push_back(nums[mi]);
        mi = parent[mi];
    }
    // sort(ret.begin(), ret.end()); // if we go by extending larger ends, the largest "answer" element will come first since the candidate element we observe will become larger and larger as i increases in the outermost "for" loop above.
   // alternatively, we can sort nums in decreasing order obviously. 
    return ret;
}

//########################################### sort + backtrack ########################################### 
//O(2^n) : 2 state pick/don't pick num[i]
//TC: O(2^n), SC: O(n).
private :
  int bSz=0, sPos=0, nSz;
  vector<int> nums, sol, best=vector<int>(0);
  int passes(int v, int i) {
      return ( (sPos==0) || ((v%sol[sPos-1])==0) );
  }

  //generate possible subset of legth i
  void recHelper(int i) {
      for ( ; i<nSz; ++i ) {
          if ( passes(nums[i],i) ) {
              sol[sPos++]=nums[i];
              recHelper(i+1);   // w/ num[i] in solution / pick num[i]
              --sPos;
          }               // else, w/o num[i] in solution / do not pick num[i]
      }
      if ( bSz < sPos ) {
          bSz = sPos;     // store best
          best = vector<int>(sol.begin(), sol.begin()+sPos);
      }
  }
public:
    vector<int> largestDivisibleSubset(vector<int>& numsOrig) {
        if ( (nSz=numsOrig.size())<=1 ) return numsOrig; 
        nums = numsOrig;
        sol = vector<int>(nSz);
        sort (nums.begin(), nums.end());
        recHelper(0);
        return best;
    }

//########################################### sort + backtrack + prune ########################################### 
private : 
  int bSz=0, sPos=0, nSz, largest;
  vector<int> nums, sol, furthest, best=vector<int>(0);
  
  int passes(int v, int i) {
      if ( sPos==0 ) return 1;
      if ( (sPos>furthest[i]) && ((v%sol[sPos-1])==0) ) {
          furthest[i]=sPos;
          return 1;       // mark the position
      }
      return 0;
  }
  void rec(int i) {
      for ( ; i<nSz; ++i ) {
          if ( bSz>sPos && ((((long)1)<<(bSz-sPos))*nums[i])>largest ) break;
          if ( passes(nums[i],i) ) {
              sol[sPos++]=nums[i];
              rec(i+1);   // w/ num[i] in solution
              --sPos;
          }               // else, w/o num[i] in solution
      }
      if ( bSz < sPos ) {
          bSz = sPos;     // store best
          best = vector<int>(sol.begin(), sol.begin()+sPos);
      }
  }
public:
    vector<int> largestDivisibleSubset(vector<int>& numsOrig) {
        if ( (nSz=numsOrig.size())<=1 ) return numsOrig; 
        nums = numsOrig;
        sol = vector<int>(nSz);
        furthest = vector<int>(nSz,0);
        sort (nums.begin(), nums.end());
        largest = nums.back();
        rec(0);
        return best;
    }
