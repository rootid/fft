//Longest Substring with At Least K Repeating Characters
//Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.
//Example 1:
//Input:
//s = "aaabb", k = 3
//Output:
//3
//The longest substring is "aaa", as 'a' is repeated 3 times.
//Example 2:
//Input:
//s = "ababbc", k = 2
//Output:
//5
//The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.


//########################### Divide and Conquer ########################### 
//O (n^2)
//k = 5
//a4,b4,c4.......y4,z5 as in "aaaabbbbcccc.........yyyyzzzzz"
//answer: 5 ("zzzzz")
public int longestSubstring(String s, int k) {
     char[] arr = s.toCharArray();
     return longestSubstringHelper(arr, 0, arr.length, k);
 }
   
 private int longestSubstringHelper(char[] arr, int start, int end, int k) {
     int maxLen = end - start;
     if(maxLen < k)  //substring length shorter than k.
         return 0; 
     int[] map = new int[26];
     for(int i=start;i < end;i++) map[arr[i] - 'a']++; 
     for(int i=start;i<end;i++) {
         if(map[arr[i] - 'a'] < k) //Divide the problem at position i where # of char < k
             return Math.max(longestSubstringHelper(arr, start, i,k),  longestSubstringHelper(arr, i+1, end,k));
     }
     return maxLen;
 }


//########################### Divide and Conquer ########################### 
public int longestSubstring(String s, int k) {
    return dc(s, 0, s.length(), k);
}
    
public int dc(String s, int start, int end, int k) {
    if (end - start < k) return 0;
    int[] cnt = new int[26];
    for (int i = start; i < end; i++) cnt[s.charAt(i) - 'a']++;
    for (int i = start; i < end; i++) {
        if (cnt[s.charAt(i) - 'a'] < k)  //if found char less than k divide into 2
            return Math.max(dc(s, start, i, k), dc(s, i + 1, end, k));
    }
    return end - start;
}


//########################### Divide and Conquer : TLE ########################### 
   public int longestSubstring(String s, int k) {
        char[] arr = s.toCharArray();
        return longestSubstringHelper(arr, 0, arr.length, k);
    }
      
    private int longestSubstringHelper(char[] arr, int start, int end, int k) {
        if(end-start < k)  //substring length shorter than k.
            return 0; 
      Map<Character, Integer> map = new HashMap<>();
        for(int i=start;i < end;i++) map.put(arr[i], map.getOrDefault(arr[i], 0) + 1);
        for(Character key : map.keySet() ) {
            if(map.get(key) < k && map.get(key) > 0) {
                for(int j=start;j< end;j++) {
                    if(arr[j] == key) { //divide/split the string using less frquent char
                    int left = longestSubstringHelper(arr,start,j,k);
                    int right = longestSubstringHelper(arr,j+1,end,k);
                    return Math.max(left,right);
                }

                }
            }
        }
        return end - start;
    }

//########################### Divide and Conquer ########################### 
int longestSubstring(string s, int k) {
    return helper(s,0,s.size(),k);
}

int helper(string& str, int start, int end,  int k) {
    if(end-start < k)  //substring length shorter than k.
      return 0; 
    int count[26] = {0};
    for(int i = start;i<end;i++){
        int idx = str[i]-'a';
        count[idx]++;
    }
    for(int i=0;i<26;i++) {
        if(count[i]<k && count[i]>0) {  //Find the less frquent character
            for(int j = start;j<end;j++) {
                if(str[j] == i+'a') { //divide/split the string using less frquent char
                    int left = helper(str,start,j,k);
                    int right = helper(str,j+1,end,k);
                    return max(left,right);
                }
            }
        }
    }
    return end-start;
}

//###################################### optimized D&C ###################################### 

int longestSubstring(const string &s, int k) {
    return helper(s, 0, s.size(), k);
}
int helper(const string &s, int beg, int end, int k){
    if(end - beg < k) {
      return 0;
    }
    int cnt[26]{};
    for(int i = beg; i < end; ++i) {
      ++cnt[s[i]-'a'];
    }
    for(int i = beg; i < end; ++i) {
        if (cnt[s[i] - 'a'] < k) {
            return max(helper(s, beg, i, k), helper(s, i + 1, end, k));
        }
    }
    return end - beg;
}

//### Pochman's O(n^2) analysis
//
//
//class Solution(object):
//        def longestSubstring(self, s, k):
//            print s
//            for c in set(s):
//                print c,
//                if s.count(c) < k:
//                    print; print
//                    return max(self.longestSubstring(t, k) for t in s.split(c))
//            return len(s)
//
//>>> Solution().longestSubstring('aaccbbeeddggffiihhkkjjmmllzxyvwturspqno', 2)
//aaccbbeeddggffiihhkkjjmmllzxyvwturspqno
//a c b e d g f i h k j m l o
//
//aaccbbeeddggffiihhkkjjmmllzxyvwturspqn
//a c b e d g f i h k j m l n
//
//aaccbbeeddggffiihhkkjjmmllzxyvwturspq
//a c b e d g f i h k j m l q
//
//aaccbbeeddggffiihhkkjjmmllzxyvwtursp
//a c b e d g f i h k j m l p
//
//aaccbbeeddggffiihhkkjjmmllzxyvwturs
//a c b e d g f i h k j m l s
//
//aaccbbeeddggffiihhkkjjmmllzxyvwtur
//a c b e d g f i h k j m l r
//
//aaccbbeeddggffiihhkkjjmmllzxyvwtu
//a c b e d g f i h k j m l u
//
//aaccbbeeddggffiihhkkjjmmllzxyvwt
//a c b e d g f i h k j m l t
//
//aaccbbeeddggffiihhkkjjmmllzxyvw
//a c b e d g f i h k j m l w
//
//aaccbbeeddggffiihhkkjjmmllzxyv
//a c b e d g f i h k j m l v
//
//aaccbbeeddggffiihhkkjjmmllzxy
//a c b e d g f i h k j m l y
//
//aaccbbeeddggffiihhkkjjmmllzx
//a c b e d g f i h k j m l x
//
//aaccbbeeddggffiihhkkjjmmllz
//a c b e d g f i h k j m l z
//
//aaccbbeeddggffiihhkkjjmmll
//a c b e d g f i h k j m l 
//26
