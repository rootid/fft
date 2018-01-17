//Longest Substring Without Repeating Characters
//Given a string, find the length of the longest substring without repeating characters.
//Examples:
//Given "abcabcbb", the answer is "abc", which the length is 3.
//Given "bbbbb", the answer is "b", with the length of 1.
//Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
int lengthOfLongestSubstring(string s) {
    vector<int> dict_idx(256,-1);
    int max_len = 0;
    int c_idx = -1;
    int len = s.size();
    for(int i=0;i<len;i++) {
        if(dict_idx[ s[i] ] != -1) {
            //or  if (dict_idx[s[i]] > start)  {  c_idx = dict_idx[ s[i] ] ; }
            c_idx = max(c_idx,dict_idx[ s[i] ]); //"abba" expected 2 // Reason : always increment the c_idx so max();
        }
        dict_idx[s[i] ] = i;
        max_len = max(max_len, i - c_idx);  // for string with all distinct characters. need to compute local_len every time
    }
    return max_len;
}
