//Permutation in String
//Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.
//Example 1:
//Input:s1 = "ab" s2 = "eidbaooo"
//Output:True
//Explanation: s2 contains one permutation of s1 ("ba").
//Example 2:
//Input:s1= "ab" s2 = "eidboaoo"
//Output: False
//Note:
//The input strings only contain lower case letters.
//The length of both given strings is in range [1, 10,000].

//####################### window solution ####################### 
bool checkInclusion(string s1, string s2) {
    int s1s = s1.size(), s2s = s2.size(), start = 0, cnt = 0, arr[26] = {};
    for (auto l : s1) {
        ++arr[l - 'a'];
    }
    for (auto i = 0; i < s2s && cnt < s1s; ++i) {
        if (arr[s2[i] - 'a'] > 0) {
            --arr[s2[i] - 'a'];
            ++cnt;
        } else {
            while (s2[start++] != s2[i]) ++arr[s2[start - 1] - 'a'], --cnt; //reinit the map and reduce count
        }
    }
    return cnt == s1s; //cnt : window size
}
//####################### window solution ####################### 
/**
 * 1. try find a window (i, j) where s2.substr(i, j + 1 - i) contains all chars in s1;
 * i.e. j+1-i = s1.size()
 * 2. once found, try reduce window(i, j) such that j + 1 - i == s1.size() while the window still contains all chars in s1 by moving i, return true;
 * 3. if windows no longer contain all chars in s1, keep moving j forward;
 */
bool checkInclusion(string s1, string s2) {
    vector<int> cnts(256, 0);
    for (char ch : s1) {
        cnts[ch]++;
    }
    int left = s1.size();
    for (int i = 0, j = 0; j < s2.size(); j++) {
        if (cnts[s2[j]]-- > 0) { //j : determine rt limit of string
            left--;  //move window 
        }
        while (left == 0) { //found all chars 
            if (j + 1 - i == s1.size()) { //criteria : to make sure that we traversed the the string
                return true;
            } if (++cnts[s2[i++]] > 0) { // i : denotes lt limit of string
                left++;
            }
        }
    }
    return false;
}
//####################### fix me ####################### 
bool checkInclusion(string s1, string s2) {
  unordered_map<char,int> freq_map;
  for(auto c:s1) {
    freq_map[c]++;
  }
  unordered_map<char,int> traverse_map;
  for(auto c:s2) {
    if(freq_map[c].count() > 0) {
        //avoid repeated initilization 
        //Idea
        //1. reduce the count for every char
        //
    }
  }
}
//###################### Anagram ###################### 
    bool checkInclusion(string s1, string s2) {
        return findAnagrams(s2, s1).size();
    }
    
    // Copied&pasted old problem's solution
    vector<int> findAnagrams(string s, string p) {
        int miss[256] = {}, missSum = p.size();
        for (char c : p)
            miss[c]++;
        vector<int> result;
        for (int i=0; i<s.size(); i++) {
            missSum -= miss[s[i]]-- > 0;
            int start = i+1 - p.size();
            if (!missSum) {
                result.push_back(start);
            }
            missSum += start >= 0 && ++miss[s[start]] > 0;
        }
        return result;
    }
//###################### pytonic ###################### 
//class Solution(object):
//    def checkInclusion(self, s1, s2):
//        return len(self.minWindow(s2, s1)) == len(s1)
//    
//    # Copied&pasted old problem's solution
//    def minWindow(self, s, t):
//        need, missing = collections.Counter(t), len(t)
//        i = I = J = 0
//        for j, c in enumerate(s, 1):
//            missing -= need[c] > 0
//            need[c] -= 1
//            if not missing:
//                while i < j and need[s[i]] < 0:
//                    need[s[i]] += 1
//                    i += 1
//                if not J or j - i <= J - I:
//                    I, J = i, j
//        return s[I:J]
//
//    
