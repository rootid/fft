//Palindrome Partitioning
//Given a string s, partition s such that every substring of the partition is a palindrome.
//Return all possible palindrome partitioning of s.
//For example, given s = "aab",
//Return
//[
//  ["aa","b"],
//  ["a","a","b"]
//]
//Backrack with Pruning by checking palindrome
//####################################################### Backtrack GOOD  ####################################################### 
vector<vector<string>> partition(string s) { 
  vector<vector<string> > res;
  vector<string> tmp;
  getPartition(s, 0, tmp, res);
  return res;
}
void getPartition(string& s, int idx, vector<string>& tmp, vector<vector<string> >& res) {
    if (idx == s.length()) {
        res.push_back(tmp);
        return;
    }
    for (int i = idx, n = s.length(); i < n; i++) {
        int l = idx, r = i;
        while (l < r && s[l] == s[r]) l++, r--;  //Pruning
        if (l >= r) {
            tmp.push_back(s.substr(idx, i - idx + 1));
            getPartition(s, i + 1, tmp, res);
            tmp.pop_back();
        }
    }
}
//####################################################### Backtrack BAD ####################################################### 
bool is_palindrome(string s) {
    int end = s.length()-1;
    int start = 0;
    while (start <= end) {
        if (s[start++] != s[end--])  return false;
    }
    return true;
}
void enum_palindrome (string& s,int k,vector<string> &result_vec,vector<vector<string> >& op) {
    int len = s.length();
    if (len == 0) {
        op.push_back(result_vec);
        //cout << "The stack size = " << result_vec.size();
        return;
    } else {
        //k = k + 1;
        //cout << s << endl;
        for (int i=1;i<=len;i++) {
            //Principle here is (0,i) and (i,len)
            string sub_str = s.substr(0,i);
            if (is_palindrome(sub_str)) {
                result_vec.push_back(sub_str);
                string rest_str = s.substr(i);
                enum_palindrome (rest_str,i,result_vec,op);
                result_vec.pop_back();
            }
        }
    }
}
vector<vector<string> > partition(string s) {
    vector<string> result_stack;
    vector<vector<string> > op;
    enum_palindrome (s,0,result_stack,op);
    return op;
}
//############################## DP + DFS  ############################## 
vector<vector<string>> partition(string s) {
    //first step is to find all the palindromes in the string
    //then use dfs method to walk though the whole word using palindrome records
    
    //dp[startindex][len] indicates whether s[start]~[start+len] is palindome
    vector<vector<bool> > dp(s.size(), vector<bool>(s.size()+1, false)); 
    for(int i=0;i<s.size();++i){
        dp[i][0]=dp[i][1]=true;
    }
    for(int j=2;j<=s.size();++j){
        for(int i=0;i+j<=s.size();++i){
            dp[i][j]=dp[i+1][j-2]&&(s[i]==s[i+j-1]);
        }
    }
    vector<vector<string>> finalRes;
    vector<string> curRes;
    dfs(s, 0, curRes, finalRes, dp);
    return finalRes;
}
void dfs(string &s, int index, vector<string> &curRes, vector<vector<string>> &finalRes, vector<vector<bool> > &dp){
    if(index==s.size()){
        finalRes.push_back(curRes);
        return;
    }
    for(int i=1;i+index<=s.size();++i){
        if(dp[index][i]) {
            curRes.push_back(s.substr(index, i));
            dfs(s, index+i, curRes, finalRes, dp);
            curRes.pop_back();
        }
    }
}

//##################################### NEED to fix O(n^2) ##################################### 
vector<vector<string>> partition(string s) {
	int len = s.length();
	vector<vector<string> >result;
    result.push_back(vector<string>{} );
	vector< vector<bool> > pair(len,vector<bool>(len,false));
	for (int i = 0; i < len; i++) {
		for (int left = 0; left <= i; left++) {
			if (s[left] == s[i] && (i-left <= 1 || pair[left + 1][i - 1])) {
				pair[left][i] = true;
	
				string str = s.substr(left, len- i + 1);
				for (auto r : result[left]) {
					vector<string> ri; 
                    ri.push_back(r);
					ri.push_back(str);
					result.push_back(ri);
				}
			}
		}
	}
	return result;
}
//Check each suffix of the given string, if the suffix is a palindrome, add it to each solution for subproblem of the matching prefix, else skip it.
//result[0..right] = result[0..left-1] + s[left..right] if s[left..right] is a palindrome
//To check if a substring is a palindrome, we can use a 2D boolean array:
//p[left,right] = true if right-left<=1 or s[left] == s[right] && p[left+1,right-1]
//p will look something like this:
//
//   0 1 2 3 ...
//0  x x x x
//1    x x x
//2      x x
//3        x
//...
//Result of prev row can be use to calculate current row. You may wonder if we are wrong to access next row by checking p[left+1,right-1], but the right-left<=1 condition effectively prevents it.
//Use 2 pointers to keep track of left & right (where left <= right obviously) and we have a DP solution.
//O(n^2)
public static List<List<String>> partition(String s) {
		int len = s.length();
		List<List<String>>[] result = new List[len + 1];
		result[0] = new ArrayList<List<String>>();
		result[0].add(new ArrayList<String>());
		boolean[][] pair = new boolean[len][len];
		for (int i = 0; i < s.length(); i++) {
			result[i + 1] = new ArrayList<List<String>>();
			for (int left = 0; left <= i; left++) {
				if (s.charAt(left) == s.charAt(i) && (i-left <= 1 || pair[left + 1][i - 1])) {
					pair[left][i] = true;
					String str = s.substring(left, i + 1);
					for (List<String> r : result[left]) {
						List<String> ri = new ArrayList<String>(r);
						ri.add(str);
						result[i + 1].add(ri);
					}
				}
			}
		}
		return result[len];
	}
