//Longest Substring with At Most Two Distinct Characters
//Given a string, find the length of the longest substring T that contains at most 2 distinct characters.
//For example, Given s = “eceba”,
//T is "ece" which its length is 3.

//same category as those such as "longest substring without repeating characters", 
//"minimum window substring", and "substring with concatenation of all words". 
//To solve this kind of question we can use two pointers and a hash table. When the key of the hash table is char, we can simply use an array as the hash table. The most important idea in solving this kind of questions is "how to update the "start" pointer" and the solution to these questions seem usually differ only in this respect.


//################################################### hash map ################################################### 
public int lengthOfLongestSubstringTwoDistinct(String s) {
    Map<Character, Integer> lastSeen = new HashMap<>();
    int low = 0, max = 0;
    for (int i = 0; i < s.length(); i++) {
        lastSeen.put(s.charAt(i), i);
        if (lastSeen.size() > 2) {
            int toRemoveLastSeen = i;
            for (Integer val : lastSeen.values()) toRemoveLastSeen = Math.min(val, toRemoveLastSeen);
            lastSeen.remove(s.charAt(toRemoveLastSeen));
            low = toRemoveLastSeen + 1;
        }
        max = Math.max(max, i - low + 1);
    }
    return max;
}
//################################################### 2-pointer  ################################################### 
public int LengthOfLongestSubstringTwoDistinct(string s) 
    {
        int left1 = -1;
        int left2 = -1;
        int len = 0;
        int max = 0;
        for (int i = 0; i < s.Length; i++)
        {
            if (left1 == -1 || s[i] == s[left1]) 
            {
                left1 = i;
                len++;
                max = Math.Max(max, len);
            }
            else if (left2 == -1 || s[i] == s[left2]) 
            {
                left2 = i;
                len++;
                max = Math.Max(max, len);
            }
            else
            {
                if (left1 < left2) { len = i - left1; left1 = i; }
                else { len = i - left2; left2 = i; }
            }
        }
        return max;
    }

//################################################### array  ################################################### 
int lengthOfLongestSubstringTwoDistinct(string s) {
    if(s.empty()) return 0;
    
    int dict[256]; 
    fill_n(dict,256,0);
    int start = 0, len = 1, count = 0;
    for(int i=0; i<s.length(); i++) {
        dict[s[i]]++;
        if(dict[s[i]] == 1) { // new char
            count++;
            while(count > 2) {
                dict[s[start]]--;
                if(dict[s[start]] == 0) count--; 
                start++;
            }
        }
        if(i-start+1 > len) len = i-start+1;
    }
    return len;
}

//################################################### hashtable ################################################### 
class Solution { 
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int l = 0, r = -1, len = 0, n = s.length();
        for (int i = 1; i < n; i++) {
            if (s[i] == s[i - 1]) continue;
            if (r >= 0 && s[i] != s[r]) {
                len = max(len, i - l); 
                l = r + 1;
            }
            r = i - 1;
        }
        return max(n - l, len);  
    }
};

//######################################### array ######################################### 
public class Solution {
    public int lengthOfLongestSubstringKDistinct(String s, int k) {
        int[] count = new int[256];
        int num = 0, i = 0, res = 0;
        for (int j = 0; j < s.length(); j++) {
            if (count[s.charAt(j)]++ == 0) num++;
            if (num > k) {
                while (--count[s.charAt(i++)] > 0);
                num--;
            }
            res = Math.max(res, j - i + 1);
        }
        return res;
    }
}
//######################################### array ######################################### 
int lengthOfLongestSubstringKDistinct(string s, int k=2) {
    int ctr[256] = {}, j = -1, distinct = 0, maxlen = 0;
    for (int i=0; i<s.size(); ++i) {
        distinct += ctr[s[i]]++ == 0;
        while (distinct > k)
            distinct -= --ctr[s[++j]] == 0;
        maxlen = max(maxlen, i - j);
    }
    return maxlen;
}

//######################################### unordered_map ######################################### 
int lengthOfLongestSubstringKDistinct1(string s, int k) {
    unordered_map<char, int> ctr;
    int j = -1, maxlen = 0;
    for (int i=0; i<s.size(); ++i) {
        ++ctr[s[i]];
        while (ctr.size() > k)
            if (--ctr[s[++j]] == 0)
                ctr.erase(s[j]);
        maxlen = max(maxlen, i - j);
    }
    return maxlen;
}


//######################################### python ######################################### 
class Solution(object):
    def lengthOfLongestSubstringKDistinct(self, s, k):
       i, j, freqs, res = 0, 0, collections.defaultdict(int), 0
       for j in range(len(s)):
            freqs[s[j]] += 1
            if len(freqs) <= k: 
                res = max(res, j - i + 1)
            while i <= j and len(freqs) > k:
                freqs[s[i]] -= 1
                if not freqs[s[i]]: 
                    freqs.pop(s[i], 0)
                i += 1
        return res
