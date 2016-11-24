//Strobogrammatic Number II
//A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
//Find all strobogrammatic numbers that are of length = n.
//For example,
//Given n = 2, return ["11","69","88","96"].
//Hint:
//Try to use recursion and notice that it should recurse with n - 2 instead of n - 1.
//
//Recursive
vector<string> dfs_helper(int m,int n) {
    if(m == 0) {
        return vector<string>({""});
    }
    if(m == 1) {
          return vector<string>({"0","1","8"});
    }
    vector<string> res = dfs_helper(m-2,n); 
    vector<string> st_list;
    for(int i=0;i<res.size();i++) {
        string tmp = res[i];
        if(m != n) {
          st_list.push_back('0' + tmp + '0');
        }
        st_list.push_back('1' + tmp + '1');
        st_list.push_back('6' + tmp + '9');
        st_list.push_back('8' + tmp + '8');
        st_list.push_back('9' + tmp + '6');
    }
    return st_list;
    
}
vector<string> findStrobogrammatic(int n) {
    return dfs_helper(n,n);
}
//Iterative
vector<string> findStrobogrammatic(int n) {
     vector<string> cur, ans;
     if( (n&1) == 0) {
         ans = vector<string>({""});
     } else {
         ans =  vector<string>({"0","1","8"});
     }
     if(n < 2) {
         return ans;
     }
     for (;n > 1; n -= 2) {
         cur = ans;
         ans.clear();
         for (auto &i : cur) {
             if (n > 3)  { 
                 ans.push_back('0' + i + '0');
             }
             ans.push_back('1' + i + '1');
             ans.push_back('8' + i + '8');
             ans.push_back('6' + i + '9');
             ans.push_back('9' + i + '6');
         }
     }
     
     return ans;
}
int main() {
}
