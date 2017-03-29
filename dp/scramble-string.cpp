//Scramble String
//Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.
//Below is one possible representation of s1 = "great":
//    great
//   /    \
//  gr    eat
// / \    /  \
//g   r  e   at
//           / \
//          a   t
//To scramble the string, we may choose any non-leaf node and swap its two children.
//For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".
//    rgeat
//   /    \
//  rg    eat
// / \    /  \
//r   g  e   at
//           / \
//          a   t
//We say that "rgeat" is a scrambled string of "great".
//Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".
//    rgtae
//   /    \
//  rg    tae
// / \    /  \
//r   g  ta  e
//       / \
//      t   a
//We say that "rgtae" is a scrambled string of "great".
//Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.

//recursive (without cache) is O(a^n), dp is O(n^a)
//##############################################  Recursion ##############################################  
bool isScramble(string s1, string s2) {
    if(s1==s2)
        return true;
    int len = s1.length();
    int count[26] = {0};
    for(int i=0; i<len; i++) {
        count[s1[i]-'a']++;
        count[s2[i]-'a']--;
    }
    for(int i=0; i<26; i++) {
        if(count[i] !=0 )
            return false;
    }
    for(int i=1; i<=len-1; i++) {
       //upto i
        if( isScramble(s1.substr(0,i), s2.substr(0,i)) && isScramble(s1.substr(i), s2.substr(i)))
            return true;
        //len-i = right of i
        if( isScramble(s1.substr(0,i), s2.substr(len-i)) && isScramble(s1.substr(i), s2.substr(0,len-i)))
            return true;
    }
    return false;
}


//##############################################  DP + Map  ##############################################  
bool dpHelper(unordered_map<string, bool> &isScramblePair, string s1, string s2) {
    int i,len = s1.size();
    bool res = false;
    if(0==len) return true;
    else if(1==len) {
      return s1 == s2;
    } else {
        if(isScramblePair.count(s1+s2)) 
          return isScramblePair[s1+s2]; // checked before, return intermediate result directly
        if(s1 == s2) res=true;
        else {
            for(i=1; i<len && !res; ++i) {
                //s1[0..i-1] with s2[0..i-1] and s1[i..len-1] and s2[i..len-1]
                res = res || (dpHelper(isScramblePair, s1.substr(0,i), s2.substr(0,i)) && dpHelper(isScramblePair, s1.substr(i,len-i), s2.substr(i,len-i)));
                //match, then check s1[0..i-1] with s2[len-k.. len-1] and s1[i..len-1] and s2[0..len-i]
               res = res || (dpHelper(isScramblePair, s1.substr(0,i), s2.substr(len-i,i)) && dpHelper(isScramblePair, s1.substr(i,len-i), s2.substr(0,len-i)));
            }
        }
        return isScramblePair[s1+s2]= res; //save the intermediate results
    }
}
bool isScramble(string s1, string s2) {
   unordered_map<string, bool> isScramblePair;
   return dpHelper(isScramblePair, s1, s2);
}

//##############################################  DP + Array  ##############################################  
//isS[len][i][j], which indicates whether s1[i..i+len-1] is a scramble of s2[j..j+len-1].
//O(N^4)
bool isScramble(string s1, string s2) {
      int sSize = s1.size(), len, i, j, k;
      if(0==sSize) return true;
      if(1==sSize) return s1==s2;
      bool isS[sSize+1][sSize][sSize];

      for(i=0; i<sSize; ++i)
          for(j=0; j<sSize; ++j)
              isS[1][i][j] = s1[i] == s2[j]; //for length 1 string
              
      for(len=2; len <=sSize; ++len)
          for(i=0; i<=sSize-len; ++i)
              for(j=0; j<=sSize-len; ++j) {
                  isS[len][i][j] = false;
                      for(k=1; k<len && !isS[len][i][j]; ++k) {
                          isS[len][i][j] = isS[len][i][j] || (isS[k][i][j] && isS[len-k][i+k][j+k]);
                          isS[len][i][j] = isS[len][i][j] || (isS[k][i+len-k][j] && isS[len-k][i][j+k]);
                      }
              }
      return isS[sSize][0][0];            
}
//##############################################  Recusrion + Cache + Check for repeated chars  ##############################################  
//hist : check for the chars
bool DP_helper(string &s1, string &s2, int idx1, int idx2, int len, char isS[]) {
    int sSize = s1.size(),i, j, k, hist[26] , zero_count =0;
    if(isS[(len*sSize+idx1)*sSize+idx2]) return isS[(len*sSize+idx1)*sSize+idx2]==1;
    bool res = false;
    
    fill_n(hist, 26, 0);
    for(k=0; k<len;++k) { // check if s1[idx1:idx1+len-1] and s2[idx2:idx2+len-1] have same characters
        zero_count +=  (0==hist[s1[idx1+k]-'a']) - (0== ++hist[s1[idx1+k]-'a']);
        zero_count +=  (0==hist[s2[idx2+k]-'a']) - (0== --hist[s2[idx2+k]-'a']);
    }
    if(zero_count) {isS[(len*sSize+idx1)*sSize+idx2] = 2; return false;} //if not, return directly
    if(len==1)     {isS[(len*sSize+idx1)*sSize+idx2] = 1; return true;}
    for(k=1;k<len && !res;++k) //otherwise, recursion with cache
    {
        res = res || (DP_helper(s1, s2, idx1, idx2, k, isS) && DP_helper(s1, s2, idx1+k, idx2+k, len-k, isS) );
        res = res || (DP_helper(s1, s2, idx1+len-k, idx2, k, isS) && DP_helper(s1, s2, idx1, idx2+k, len-k, isS) );
    }
    isS[(len*sSize+idx1)*sSize+idx2] = res?1:2;
    return res;
}
bool isScramble(string s1, string s2) {
    const int sSize = s1.size();
    if(0==sSize) return true;
    char isS[(sSize+1)*sSize*sSize];
    fill_n(isS, (sSize+1)*sSize*sSize, 0);
    return DP_helper(s1, s2, 0, 0, sSize, isS);
}

//##############################################  DP with 3d array ##############################################  
bool isScramble(string s1, string s2) { 
  if(s1.size() != s2.size()) { 
    return false; 
  }
  bool dp[s1.size()][s1.size()][s1.size()];
  memset(dp, 0, s1.size()*s1.size()*s1.size());
  for(int l=1; l<=s1.size(); l++) { 
    for(int i=0; i+l<=s1.size(); i++) { 
      for(int j=0; j+l<=s1.size(); j++) { 
        if(l==1) { 
          dp[i][j][0] = s1[i]==s2[j]; 
        } else { 
          int cnt[26] = {0};
          int zeros= 0;
          for(int p =0; p<l; p++) {
              zeros+=(cnt[s1[i+p]-'a']==0)-(++cnt[s1[i+p]-'a']==0); 
              zeros+=(cnt[s2[j+p]-'a']==0)-(--cnt[s2[j+p]-'a']==0); 
          }
          if(zeros) {
            dp[i][j][l-1]=false;
            continue;
          }
          for(int p = i+1; p-i<l; p++){
              if(dp[i][j][l-1]) 
                break;
              dp[i][j][l-1] = (dp[i][j][p-i-1]&&dp[p][j+p-i][l-(p-i)-1])||(dp[i][j+l-(p-i)][p-i-1]&&dp[p][j][l-(p-i)-1]);
          } 
        } 
      } 
    }
  }
  return dp[0][0][s1.size()-1]; 
}

//############################################# DP with 3-d array different interpretion ############################################# 
//For the DP matrix "scramble", scramble[i][j][k] means the substring of 's1' start at 'i' with length 'k' and the substring of 's2' start at 'j' with length'k' is scramble.
public boolean isScramble(String s1, String s2) {
        boolean[][][] scramble = new boolean[s1.length() + 1][s1.length() + 1][s1.length() + 1];
        boolean[][][] visited = new boolean[s1.length() + 1][s1.length() + 1][s1.length() + 1];
        for (int i = 0; i < s1.length(); i++) {
            for (int j = 0; j < s2.length(); j++) {
                scramble[i][j][1] = s1.charAt(i) == s2.charAt(j);
                visited[i][j][1] = true;
            }
        }
        return isScramble(s1, s2, 0, 0, s1.length(), scramble, visited);
    }
    
    public boolean isScramble(String s1, String s2, int i1, int i2, int len, boolean[][][] scramble, boolean[][][] visited) {
        if (visited[i1][i2][len]) return scramble[i1][i2][len];
        visited[i1][i2][len] = true;
        
        if (s1.equals(s2)) {
            scramble[i1][i2][len] = true;
            return true;
        }
        
        boolean result = false;
        for (int i = 1; i < s1.length(); i++) {
            String s11 = s1.substring(0, i);
            String s12 = s1.substring(i, s1.length());
            String s21 = s2.substring(s1.length() - i, s1.length());
            String s22 = s2.substring(0, s1.length() - i);
            String s23 = s2.substring(0, i);
            String s24 = s2.substring(i, s1.length());
            if ((isScramble(s11, s21, i1, i2 + s1.length() - i, i, scramble, visited) && isScramble(s12, s22, i1 + i, i2, s1.length() - i, scramble, visited)) ||
                (isScramble(s11, s23, i1, i2, i, scramble, visited) && isScramble(s12, s24, i1 + i, i2 + i, s1.length() - i, scramble, visited))) {
                scramble[i1][i2][len] = true;
                return true;
            }
        }
        
        scramble[i1][i2][len] = false;
        return false;
    }
//############# CYK Algo
bool isScramble(string s1, string s2) {
  int len = s1.length();
  if (!len) return true;
  if (len == 1) return s1 == s2;
  //CYK
  int ***p = new int**[len + 1];
  for (int i = 0; i < len + 1; i++) {
    p[i] = new int*[len];
    for (int j = 0; j < len; j++) {
      p[i][j] = new int[len];
      memset(p[i][j], 0, len * sizeof(int));
    }
  }
  //p[i][j][k] means s1[j..j+i] is scrambled string of s2[k..k+i]
  for (int k = 0; k < len; k++) {
    for (int j = 0; j < len; j++) {
      p[1][j][k] = s1[j] == s2[k];
    }
  }
  int tmp;
  for (int i = 2; i <= len; i++) {//length of span
    for (int j = 0; j <= len - i; j++) {//start of span
      for (int l = 0; l <= len - i; l++) {//start of span2
        for (int k = 1; k < i; k++) {//partition of span
          if ((p[k][j][l] && p[i - k][j + k][l + k]) || (p[k][j][l + i - k] && p[i - k][j + k][l])) {
            p[i][j][l] = 1;
          }
        }
      }
    }
  }
  return p[len][0][0];
}
