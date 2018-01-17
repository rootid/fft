//Longest Word in Dictionary through Deleting
//Given a string and a string dictionary, find the longest string in the dictionary that can be formed by deleting some characters of the given string. If there are more than one possible results, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.
//Example 1:
//Input:
//s = "abpcplea", d = ["ale","apple","monkey","plea"]
//Output: 
//"apple"
//Example 2:
//Input:
//s = "abpcplea", d = ["a","b","c"]
//Output: 
//"a"
//Note:
//All the strings in the input will only contain lower-case letters.
//The size of the dictionary won't exceed 1,000.
//The length of all the strings in the input won't exceed 1,000.

//################################  Only scan  ################################  
string findLongestWord(string s, vector<string>& d) {
    string ans;
    //pick word from dictionary
    for (int i = 0; i < d.size(); i++) {
        int pi = 0, pj = 0;
        //verify whether dict contains the given string s
        for (; pi < s.size() && pj < d[i].size(); pi++) {
            pj += s[pi] == d[i][pj]; //pj : matched characters
        }
        //pj == d[i].size()  : word is present in the dictionary
        //ans > d[i] : pick the first matched string eg a,b,c
        if (pj == d[i].size() && (ans.size() < d[i].size() || (ans.size() == d[i].size() && ans > d[i])))
            ans = d[i];
    }
    return ans;
}

//############################################ pytonic ############################################ 
//def findLongestWord(self, s, d):
//    def isSubsequence(x):
//        it = iter(s)
//        return all(c in it for c in x)
//    return max(sorted(filter(isSubsequence, d)) + [''], key=len)
////More efficient version (no sorting):
//def findLongestWord(self, s, d):
//    def isSubsequence(x):
//        it = iter(s)
//        return all(c in it for c in x)
//    return min(filter(isSubsequence, d) + [''], key=lambda x: (-len(x), x))
////Different style:
//def findLongestWord(self, s, d):
//    best = ''
//    for x in d:
//        if (-len(x), x) < (-len(best), best):
//            it = iter(s)
//            if all(c in it for c in x):
//                best = x
//    return best
////Optimized as suggested by @easton042, testing from longest to shortest and returning the first valid one without testing the rest:
//def findLongestWord(self, s, d):
//    def isSubsequence(x):
//        it = iter(s)
//        return all(c in it for c in x)
//    d.sort(key=lambda x: (-len(x), x))
//    return next(itertools.ifilter(isSubsequence, d), '')
////Or:
//def findLongestWord(self, s, d):
//    for x in sorted(d, key=lambda x: (-len(x), x)):
//        it = iter(s)
//        if all(c in it for c in x):
//            return x
//    return ''
////And taking that even further by not sorting unnecessarily much:
//def findLongestWord(self, s, d):
//    heap = [(-len(word), word) for word in d]
//    heapq.heapify(heap)
//    while heap:
//        word = heapq.heappop(heap)[1]
//        it = iter(s)
//        if all(c in it for c in word):
//            return word
//    return ''
//
// #################################### JAVA  #################################### 
//public String findLongestWord(String s, List<String> d) {
//    String res = "";
//    if (s.length() == 0 || d.size() == 0) {
//        return res;
//    }
//    for (String str : d) {
//        int resLen = res.length();
//        int strLen = str.length();
//        if (isSequence(s, str) &&
//            (strLen > resLen || (strLen == resLen && str.compareTo(res) < 0))) {
//            res = str;
//        }
//    }
//    return res;
//}
//
//private boolean isSequence(String s, String d) {
//    int i = 0;
//    int j = 0;
//    while (i < s.length() && j < d.length()) {
//        while (i < s.length() && s.charAt(i) != d.charAt(j)) {
//            i ++;
//        }
//        if (i < s.length()) {
//            i ++;
//            j ++;
//        }
//    }
//    return j == d.length();
//}
