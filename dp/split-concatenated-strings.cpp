//Given a list of strings, you could concatenate these strings together into a loop, where for each string you could
//choose to reverse it or not. Among all the possible loops, you need to find the lexicographically biggest string after
//cutting the loop, which will make the looped string into a regular one.
//Specifically, to find the lexicographically biggest string, you need to experience two phases:
//Concatenate all the strings into a loop, where you can reverse some strings or not and connect them in the same order
//as given.
//Cut and make one breakpoint in any place of the loop, which will make the looped string into a regular one starting
//from the character at the cutpoint.
//And your job is to find the lexicographically biggest one among all the possible regular strings.
//Example:
//Input: "abc", "xyz"
//Output: "zyxcba"
//Explanation: You can get the looped string "-abcxyz-", "-abczyx-", "-cbaxyz-", "-cbazyx-",
//where '-' represents the looped status.
//The answer string came from the fourth looped one,
//where you could cut from the middle character 'a' and get "zyxcba".
//Note:
//The input strings will only contain lowercase letters.
//The total length of all the strings will not over 1,000.


//["b", "z", "a", "bza"]
//o/p : "zbbzaa".
//["b", "z", "a", "b", "z", "a", "bza"]
//o/p : zbbzabzaa
//

//######################################### Optimized #########################################
public class Solution {
    public String splitLoopedString(String[] strs) {
        for (int i = 0; i < strs.length; i++) {
            String rev = new StringBuilder(strs[i]).reverse().toString();
            if (strs[i].compareTo(rev) < 0)
                strs[i] = rev;
        }
        String res = "";
        for (int i = 0; i < strs.length; i++) {
            String rev = new StringBuilder(strs[i]).reverse().toString();
            for (String st: new String[] {strs[i], rev}) {
                for (int k = 0; k < st.length(); k++) {
                    StringBuilder t = new StringBuilder(st.substring(k));
                    for (int j = i + 1; j < strs.length; j++)
                        t.append(strs[j]);
                    for (int j = 0; j < i; j++)
                        t.append(strs[j]);
                    t.append(st.substring(0, k));
                    if (t.toString().compareTo(res) > 0)
                        res = t.toString();
                }
            }
        }
        return res;
    }
}

//We are given a list of strings: s1,s2,s3,..,sns_1, s_2, s_3,.., s_n. We need to concatenate all these strings in a
//circular fashion in the same given order, but we can reverse every individual string before concatenating. Now, we
//need to make a cut in the final concatenated string such that the new string formed is the largest one possible in the
//lexicographic sense
//######################################### DFS  #########################################
//TC : O(2^n)
//SC : O(n)
public class Solution {
    String res = "";
    public String splitLoopedString(String[] strs) {
        dfs(strs, "", 0, strs.length);
        return res;
    }
    public void dfs(String[] strs, String s, int i, int n) {
        if (i < n) {
            dfs(strs, s + strs[i], i + 1, n);
            dfs(strs, s + new StringBuffer(strs[i]).reverse().toString(), i + 1, n);
        } else {
            for (int j = 0; j < s.length(); j++) {
                String t = s.substring(j) + s.substring(0, j);
                if (t.compareTo(res) > 0)
                    res = t;
            }
        }
    }
}

//######################################### BFS  #########################################
//TC : O(2^n)
//SC : O(2^n)
public class Solution {

    public String splitLoopedString(String[] strs) {
        Queue < String > queue = new LinkedList < > ();
        String res = "";
        int i = 0, j = 0;
        queue.add("");
        while (i < strs.length) {
            String t = queue.remove();
            queue.add(t + strs[i]);
            queue.add(t + new StringBuffer(strs[i]).reverse().toString());
            j++;
            if (j == 1 << i) {
                i++;
                j = 0;
            }
        }
        while (!queue.isEmpty()) {
            String t = queue.remove();
            for (int k = 0; k < t.length(); k++) {
                String t1 = t.substring(k) + t.substring(0, k);
                if (t1.compareTo(res) > 0)
                    res = t1;
            }
        }
        return res;
    }
}


//#########################################  O(N^2) #########################################
//1. We know the cut point must come from the one string, assumed it is called c-string.
//2. Then except the c-string, all the other string must become its lexicographically biggest status, assumed it is
//called b-status. Since only in this situation, we could get the lexicographically biggest string after cutting.
//3. To reach the point 2, we need to first let all the string reach its b-status for the convenience of traversing all
//the strings afterward.
//4.Then, for each string's traversal procedure, we need to decide whether it should be reversed or not since we don't
//know which might generate the final answer, and then we enumerated all the characters in this string.
public static String splitLoopedString(String[] strs) {
    int n = strs.length;
    for (int i = 0; i < n; i++) {
        String rev = new StringBuilder(strs[i]).reverse().toString();
        if (strs[i].compareTo(rev) < 0) strs[i] = rev;
    }
    StringBuilder sb = new StringBuilder();
    for (int i = 0; i < n-1; i++) sb.append(strs[i]);
    String mid = sb.toString(), result = mid+strs[n-1];
    for (int i = 0; i < n; i++) {
        String str = strs[i], rev = new StringBuilder(str).reverse().toString();
        mid = mid.substring(str.length())+strs[(i+n-1)%n];
        for (int j = 0; j <= str.length(); j++) {
            String s1 = str.substring(j)+mid+str.substring(0, j), s2 = rev.substring(j)+mid+rev.substring(0, j);
            if (s1.compareTo(s2) >= 0 && s1.compareTo(result) > 0) result = s1;
            else if (s2.compareTo(s1) >= 0 && s2.compareTo(result) > 0) result = s2;
        }
    }
    return result;
}

//#########################################  O(N^2) #########################################
public class Solution {
    public String splitLoopedString(String[] strs) {
        int n = strs.length;
        List<String> lst = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            String s = strs[i];
            String reversed = new StringBuilder(s).reverse().toString();
            lst.add((s.compareTo(reversed) > 0) ? s : reversed);
        }
        String res = "";
        for (int i = 0; i < n; i++) {
            String[] temp = new String[] {strs[i], new StringBuilder(strs[i]).reverse().toString()};
            for (String start : temp) {
                for (int j = 0; j < start.length(); j++) {
                    StringBuilder loop = new StringBuilder();
                    loop.append(start.substring(j));
                    // join
                    for (int k = 0; k < n - 1; k++) {
                        loop.append(lst.get((i + 1 + k) % n));
                    }
                    loop.append(start.substring(0, j));
                    res = (res.compareTo(loop.toString()) > 0) ? res : loop.toString();
                }
            }
        }
        return res;
    }
}

//#########################################  O(N^2) #########################################
//Repeated sring problem
//auto twice = strs;
//twice.insert(twice.end(), strs.begin(), strs.end());
//int k = search(twice.begin() + 1, twice.end(), strs.begin(), strs.end()) - twice.begin();
string splitLoopedString(vector<string>& strs) {
    string s;
    for (const auto& str : strs) {
        auto rev{str};
        reverse(rev.begin(), rev.end());
        s += max(str, rev);
    }
    string result{"a"};
    for (auto i = 0, st = 0; i < strs.size(); st += strs[i++].size()) {
        auto rev{strs[i]}, body{s.substr(st + strs[i].length())};
        body += s.substr(0, st);
        reverse(rev.begin(), rev.end());
        for (const auto& p : {strs[i], rev}) {
            for (auto j = 0; j < strs[i].size(); ++j) {
                if (p[j] >= result[0]) {
                    string tmp{p.substr(j)};
                    tmp += body;
                    tmp += p.substr(0, j);
                    result = max(result, tmp);
                }
            }
        }
    }
    return result;
}

//#########################################  pytonic #########################################
//B : For every starting direction and letter, let's determine the best string we can make.
//For subsequent fragments we encounter, we always want them flipped in the orientation that makes them largest.
//Thus, for every token, for every starting direction, for every starting letter in the token,
//we can compute the candidate string directly. We take the maximum of these.
def splitLoopedString(self, A):
    B = [max(x, x[::-1]) for x in A]
    ans = None
    for i, token in enumerate(B):
        for start in (token, token[::-1]):
            for j in xrange(len(start) + 1):
                ans = max(ans, start[j:] + "".join(B[i+1:] + B[:i]) + start[:j])
    return ans


def splitLoopedString(self, strs):
    strs = [max(s, s[::-1]) for s in strs]
    return max(s[j:] + ''.join(strs[i+1:] + strs[:i]) + s[:j]
               for i, s in enumerate(strs)
               for s in (s, s[::-1])
               for j in xrange(len(s)))
//The one "real" difference is that I don't do the + 1 in the range for j. I don't think it's necessary or even
//meaningful, as in that case your start really isn't the start but only the end.

// vim: set sw=2 sts=2 tw=120 et nospell :
