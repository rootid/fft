//Remove Invalid Parentheses
//Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.
//Note: The input string may contain letters other than the parentheses ( and ).
//Examples:
//"()())()" -> ["()()()", "(())()"]
//"(a)())()" -> ["(a)()()", "(a())()"]
//")(" -> [""]

//################################################### BFS ################################################### 
bool isValid(string s){
    int count=0;
    for(int i=0; i<s.size(); i++){
        char c=s[i];
        if(c=='(') count++;
        if(c==')') {
            if(count==0)    return false; 
            count--;
        }
    }
    return count==0;
}
vector<string> removeInvalidParentheses(string s) { 
  vector<string> result;
  if(s == "") {
      result.push_back(s);
      return result;
  } 
  /*** use the visited to record the visited string ***/
  unordered_set<string> visited;
  /*** use the deque to do the BFS ***/
  deque<string> queue;
  queue.push_back(s);
  visited.insert(s);
  bool found=false;
  while(!queue.empty()) { 
    string tmp = queue.front(); 
    queue.pop_front();
    if(isValid(tmp)){
        result.push_back(tmp);
        found=true;
    }
    /*** if found, stop to increase the level depth ***/
    if(found)  continue;
    //No valid parenthesis found
    for(int i=0; i<tmp.size(); i++){
        if(tmp[i] != '(' && tmp[i] != ')') 
          continue;
        //0,i - >  all non-parenthesis chars like [a-z|0-9]
        string str = tmp.substr(0, i) + tmp.substr(i+1); //skip ith char
        if(visited.find(str) == visited.end()){
            queue.push_back(str);
            visited.insert(str);
        }
    }
  }
  return result;
}

//################################################### DFS + Pruning prefix ################################################### 
public List<String> removeInvalidParentheses(String s) {
    List<String> ans = new ArrayList<>();
    remove(s, ans, 0, 0, new char[]{'(', ')'});
    return ans;
}

public void remove(String s, List<String> ans, int last_i, int last_j,  char[] par) {
    for (int stack = 0, i = last_i; i < s.length(); ++i) {
        //validate parenthesis
        if (s.charAt(i) == par[0]) stack++;
        if (s.charAt(i) == par[1]) stack--;
        if (stack >= 0) continue; 
        for (int j = last_j; j <= i; ++j) { //last_j : store the last pos of removed prefix 
            if (s.charAt(j) == par[1] && (j == last_j || s.charAt(j - 1) != par[1])) {
                remove(s.substring(0, j) + s.substring(j + 1, s.length()), ans, i, j, par);
            }
        }
        return;
    }
    String reversed = new StringBuilder(s).reverse().toString(); // reverse string to detect extra '(' par
    if (par[0] == '(') // finished left to right
        remove(reversed, ans, 0, 0, new char[]{')', '('}); 
    else // finished right to left
        ans.add(reversed);
}

//################################################### DFS + Pruning prefix ################################################### 
private : 
  vector<string> res; 
  string p = {'(',')'};

void helper(string& s, int si, int sj, int rev) { 
  int stn=0;
  for(int i=si;i<s.size();i++){
      //validate parenthesis
      if(s[i]==p[rev]) stn++;
      else if(s[i]==p[1-rev]) stn--;

      if(stn<0) { //found invalid parenthesis
          for(int j=sj;j<=i;j++){
              if(s[j] == p[1-rev] && (j==sj || s[j-1]!=p[1-rev])){
                  string t=s.substr(0,j)+s.substr(j+1);
                  helper(t, i, j, rev);
              }
          }
          return ;
      }
  }
  string rs=s;
  reverse(rs.begin(), rs.end());
  if(p[rev]=='('){
      helper(rs, 0, 0, 1-rev);
  }else{
      res.push_back(rs);
  } 
}    
public:
vector<string> removeInvalidParentheses(string s) { 
  res.clear();
  helper(s, 0, 0, 0);
  return res;
}
   
//################################################### DFS ################################################### 
//T = 2^d where d = num1 + num2
private :
   bool isValid(string s) {
        int sum = 0;
        for(char &c : s) {
            if(c == '(') ++sum;
            else if(c == ')') --sum;
            if(sum < 0) return false;
        }
        return sum == 0;
    }
public:
    vector<string> removeInvalidParentheses(string s) {
        int num1 = 0, num2 = 0;
        for(char &c : s) {
            num1 += c == '(';
            if (num1 == 0) {
                num2 += c == ')';
            } else {
                num1 -= c == ')';
            }
        }
        vector<string> ret;
        dfs(s, 0, num1, num2, ret);
        return ret;
    }
    void dfs(string s, int beg, int num1, int num2, vector<string> &ret) {
        if(num1 == 0 && num2 == 0) {
            if(isValid(s))
                ret.push_back(s);
        } else {
            for(int i = beg; i < s.size(); ++i) {
                string tmp = s;
                if(num2 == 0 && num1 > 0 && tmp[i] == '(') { // For pruning
                    if(i == beg || tmp[i] != tmp[i - 1]) {
                        tmp.erase(i, 1);
                        dfs(tmp, i, num1 - 1, num2, ret);
                    }
                }
                if(num2 > 0 && tmp[i] == ')') {
                    if(i == beg || tmp[i] != tmp[i - 1]) {
                        tmp.erase(i, 1);
                        dfs(tmp, i, num1, num2 - 1, ret);
                    }
                }
            }
        }
    }
