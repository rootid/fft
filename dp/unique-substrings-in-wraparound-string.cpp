//Unique Substrings in Wraparound String
//Consider the string s to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so s will look like this: "...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".
//Now we have another string p. Your job is to find out how many unique non-empty substrings of p are present in s. In particular, your input is the string p and you need to output the number of different non-empty substrings of p in the string s.
//Note: p consists of only lowercase English letters and the size of p might be over 10000.
//Example 1:
//Input: "a"
//Output: 1
//Explanation: Only the substring "a" of string "a" is in the string s.
//Example 2:
//Input: "cac"
//Output: 2
//Explanation: There are two substrings "a", "c" of string "cac" in the string s.
//Example 3:
//Input: "zab"
//Output: 6
//Explanation: There are six substrings "z", "a", "b", "za", "ab", "zab" of string "zab" in the string s.
int findSubstringInWraproundString(string p) { 
  if(p.empty()) {
   return 0;
 } 
 int sum = 1; //maintains total uniq patterns
 int current = 1;
 int letter[26] = {0};
 letter[p[0] - 'a'] = 1;
 for (int i = 1; i < p.size(); i++) {
  //find 2 chars in increasing order za/ab/bc etc.
 	if ( (p[i-1] - p[i] + 1) % 26 == 0) {
 		if (letter[p[i] - 'a'] == 0) { //new unique char
 			letter[p[i] - 'a'] = ++current;
 			sum += current;
 		} else {
 			if ( letter[p[i] - 'a'] >= current + 1 ) { 
 				current++;
 			} else {
 				sum += current + 1 - letter[p[i] - 'a'];
 				letter[p[i] - 'a'] = ++current;
 			}
 		}
 	} else {
 		if (letter[p[i] - 'a'] == 0) {
 			sum++;
 			letter[p[i] - 'a'] = 1;
 		}
 		current = 1;
 	}
 } 
 return sum; 
}

int findSubstringInWraproundString(string p) {
  int res = 0; vector<int> lens(26);
  for (auto init = p.begin(), i = init+1; i <= p.end(); ++i) {
    if (i == p.end() || (*(i-1)-*i+1)%26) { //found 2-uniq chars
      for (auto j = init; j < min(init+26, i); ++j) {
        res -= lens[*j-'a'], lens[*j-'a'] = max(lens[*j-'a'], (int)(i-j)), res += lens[*j-'a'],
      }
      init = i; 
    }
  }
  return res;
} 
//O(n^2) check each substr, a hashtable is used to remove duplicate strings.
int findSubstringInWraproundString(string p) {
    int n = p.size();
    unordered_set<string> ht;
    for(int i=0;i<n;i++) {
        for(int j=i;j<n;j++) {
            if(j>i && ( (p[j-1] - p[j] + 1) % 26 != 0) ) {
              break;
            }
            ht.insert(p.substr(i,j-i+1));
        }
    }
    return ht.size();
}
//O(n^2 logn), Each valid substr can be represented by the first char and the length, instead of the whole string.
int findSubstringInWraproundString(string p) {
    int n = p.size();
    set<pair<char,int>> bst;
    for(int i=0;i<n;i++)
        for(int j=i;j<n;j++) {
            if(j>i && ( (p[j-1] - p[j] + 1) % 26 != 0) ) {
              break;
            }
            bst.insert(pair<char,int>(p[i],j-i+1));
        }
    return bst.size();
}
//ACCEPTED
//O(n^2). For substrs starting at the same char, we only need to record the longest one. Because it covers all the shorter substrs starting from the char. The length is the number of substrings starting at the char.
int findSubstringInWraproundString(string p) {
    int n = p.size(), len[26]={0};
    for(int i=0;i<n;i++)
        for(int j=i;j<n;j++) {
            if(j>i && ( (p[j-1] - p[j] + 1) % 26 != 0) ) {
              break;
            }
            len[p[i]-'a'] = max(len[p[i]-'a'],j-i+1);
        }
    return accumulate(len,len+26,0);
}
//O(n). Getting the longest substr starting from each char can be done in linear time. We can use two pointers to keep track of the current valid substring.
//
//1. A non-empty substring sub of s is uniquely defined by the initial char sub[0] and length sub.size().
//2. If string sub is a non-empty substring of s, then all its prefix sub.substr(0, L) must also be unique substrings of s, where 1 <= L <= sub.size().
int findSubstringInWraproundString(string p) {
    int len[26]={0}, i = 0, n = p.size();
    for(int j=0;j<n;j++) {
          if(j>i && ( (p[j-1] - p[j] + 1) % 26 != 0) ) {
            for(int k=i;k<min(j,i+26);k++) {
              len[p[k]-'a'] = max(len[p[k]-'a'],j-k);
            }
            i = j--;
        } 
    }
    for(int k=i;k<min(n,i+26);k++) {
      len[p[k]-'a'] = max(len[p[k]-'a'],n-k);
    }
    return accumulate(len,len+26,0);
}
