//Find the Closest Palindrome
//Given an integer n, find the closest integer (not including itself), which is
//a palindrome.
//The 'closest' is defined as absolute difference minimized between two
//integers.
//Example 1:
//Input: "123"
//Output: "121"
//Note:
//The input n is a positive integer represented by string, whose length will
//not exceed 18.
//If there is a tie, return the smaller one as answer.



//#################################################### compare only 5 nuos  ##########################################################
string nearestPalindromic(string n) {
  int l = n.size();
  set<long> candidates;
  // biggest, one more digit, 10...01
  candidates.insert(long(pow(10, l)) + 1);
  // smallest, one less digit, 9...9 or 0
  candidates.insert(long(pow(10, l - 1)) - 1);
  // the closest must be in middle digit +1, 0, -1, then flip left to right
  long prefix = stol(n.substr(0, (l + 1) / 2));
  for ( long i = -1; i <= 1; ++i ) {
      string p = to_string(prefix + i);
      string pp = p + string(p.rbegin() + (l & 1), p.rend());
      candidates.insert(stol(pp));
  }
  long num = stol(n), minDiff = LONG_MAX, diff, minVal;
  candidates.erase(num);
  for ( long val : candidates ) {
      diff = abs(val - num);
      if ( diff < minDiff ) {
          minDiff = diff;
          minVal = val;
      } else if ( diff == minDiff ) {
          minVal = min(minVal, val);
      }
  }
  return to_string(minVal);
}

//#################################################### +1,-1 and 0 mid ##########################################################
string makePalindromic(string s) {
  for (int i = 0, j = (int)s.length() - 1; i < j; i++, j--)
    s[j] = s[i];
  return s;
}

string nearestPalindromic(string n) {
  if (n == "0")
    return "1";

  long long orgVal = stoll(n);

  // candidate #1 (ex: 123xx -> 12321, 123xxx -> 123321)
  string res = makePalindromic(n);
  long long resVal = stoll(res);
  long long diff = abs(resVal - orgVal);

  long long scale = (long long)pow(10, (int)n.length() / 2);

  // candidate #2 (ex: 123xx -> 12221, 123xxx -> 122221, 100xx -> 9999)
  string smaller = makePalindromic(to_string((orgVal / scale) * scale - 1)); //-1
  // candidate #3 (ex: 123xx -> 12421, 123xxx -> 124421, 99xx -> 10001)
  string bigger = makePalindromic(to_string((orgVal / scale) * scale + scale)); //+1

  long long smallerVal = stoll(smaller);
  if (diff == 0 || abs(orgVal - smallerVal) <= diff) {
      res = smaller;
      diff = abs(orgVal - smallerVal);
  }

  long long biggerVal = stoll(bigger);
  if (abs(orgVal - biggerVal) < diff)
      res = bigger;

  return res;
}
//#############################################################
//
//The basic idea is to find the smallest palindromic integer up > n and the
//largest palindromic integer low < n. This can be done by first adjust n into
//a palindrome number called pal by copying left half of n into right half in
//the mirror way. This pal may be smaller, equal or larger than n. Let us
//assume pal < n. Then pal = low.
//To find up, just consider the left half of the low as an integer and add 1
//into it, then copy this new left half into right half in the mirror way. For
//example, low = 1991, then up = 2002 as 19 + 1 = 20. Also, low = 292, then up
//= 303 as 29+1 = 30. For the special case if the left half of low is 9, 99,
//..., the corresponding value is 11, 101, 1001, ...
//For the case pal > n, the similar idea can apply. If pal = n, we need to find
//out low and up but using the same approach
   string palindromeStr(const string& s) {
        int i = 0;
        int j = s.size() - 1;
        string ret = s;
        while (i<=j) {
            ret[j] = ret[i];
            i++;
            j--;
        }
        return ret;
    }

    string dec2Palindrome(const string& s) {
        string pal = s;
        int left = (int) (s.size() - 1) / 2;
        int right = (int) s.size() / 2;
        while (left >= 0) {
            if (pal[left] > '0') {
                pal[left] = pal[left] - 1;
                if (left < right) {
                    pal[right] = pal[right] - 1;
                }
                break;
            } else {
                pal[left] = pal[right] = '9';
                left--;
                right++;
            }
        }
        if ((pal[0] == '0') && (pal.size() > 1)) {
            pal[right] = '9';
            pal.erase(pal.begin());
        }
        return pal;
    }

    string inc2Palindrome(const string& s) {
        string pal = s;
        int left = (int) (s.size() - 1) / 2;
        int right = (int) s.size() / 2;
        while (left >= 0) {
            if (pal[left] < '9') {
                pal[left] = pal[left] + 1;
                if (left < right) {
                    pal[right] = pal[right] + 1;
                }
                break;
            } else {
                pal[left] = pal[right] = '0';
                left--;
                right++;
            }
        }
        if (pal[0] == '0') {
            pal.back() = '1';
            pal.insert(pal.begin(), '1');
        }
        return pal;
    }

    string nearestPalindromic(string n) {
        if (n == "0") {
            return "-1";
        }
        //Find the almost closest palindrome integer
        string pal = palindromeStr(n);
        long low;
        long up;
        long num = stoll(n);
        string lowPal;
        string upPal;
        if (pal == n) {
            //For n is a palindrome number, find the two closest palindrome integer,
            //one is larger than n and the other is less than n
            lowPal = dec2Palindrome(n);
            upPal = inc2Palindrome(n);
        }
        //For the other cases, find the corresponding another palindrome integer
        else if (pal < n) {
            lowPal = pal;
            upPal = inc2Palindrome(pal);
        } else {
            upPal = pal;
            lowPal = dec2Palindrome(pal);
        }
        low = stoll(lowPal);
        up = stoll(upPal);
        if (num - low <= up - num) {
            return lowPal;
        } else {
            return upPal;
        }
    }

//#################################################  pytonic #####################################################
//If the final answer has the same number of digits as the input string S, then
//the answer must be the middle digits + (-1, 0, or 1) flipped into a
//palindrome. For example, 23456 had middle part 234, and 233, 234, 235 flipped
//into a palindrome yields 23332, 23432, 23532. Given that we know the number
//of digits, the prefix 235 (for example) uniquely determines the corresponding
//palindrome 23532, so all palindromes with larger prefix like 23732 are
//strictly farther away from S than 23532 >= S.
//If the final answer has a different number of digits, it must be of the form
//999....999 or 1000...0001, as any palindrome smaller than 99....99 or bigger
//than 100....001 will be farther away from S.
//def nearestPalindromic(self, S):
//    K = len(S)
//    candidates = [str(10**k + d) for k in (K-1, K) for d in (-1, 1)]
//    prefix = S[:(K+1)/2]
//    P = int(prefix)
//    for start in map(str, (P-1, P, P+1)):
//        candidates.append(start + (start[:-1] if K%2 else start)[::-1])
//
//    def delta(x):
//        return abs(int(S) - int(x))
//
//    ans = None
//    for cand in candidates:
//        if cand != S and not cand.startswith('00'):
//            if (ans is None or delta(cand) < delta(ans) or
//                    delta(cand) == delta(ans) and int(cand) < int(ans)):
//                ans = cand
//    return ans


//>>> from timeit import timeit
//>>> timeit('str(10**l+1)', 'l = 9', number=10**7)
//2.035366696803692
//>>> timeit('"1"+"0"*(l-1)+"1"', 'l = 9', number=10**7)
//1.2266172815913734
//
//>>> timeit('10**l+1', 'l = 9', number=10**7)
//0.5076245496346132
//>>> timeit('str(10**9+1)', number=10**7)
//1.6099952195391438
//
//>>> import dis
//>>> dis.dis(compile('str(10**9+1)', '', 'exec'))
//  1           0 LOAD_NAME                0 (str)
//              3 LOAD_CONST               5 (1000000001)
//              6 CALL_FUNCTION            1
//              9 POP_TOP
//             10 LOAD_CONST               3 (None)
//             13 RETURN_VALUE
//
//class Solution(object):
//    def nearestPalindromic(self, n):
//        """
//        :type n: str
//        :rtype: str
//        """
//        # based on @awice and @o_sharp
//        l = len(n)
//        # with different digits width, it must be either 10...01 or 9...9
//        candidates = set((str(10 ** l + 1), str(10 ** (l - 1) - 1)))
//        # the closest must be in middle digit +1, 0, -1, then flip left to right
//        prefix = int(n[:(l + 1)/2])
//        for i in map(str, (prefix - 1, prefix, prefix + 1)):
//            candidates.add(i + [i, i[:-1]][l & 1][::-1])
//        candidates.discard(n)
//        return min(candidates, key=lambda x: (abs(int(x) - int(n)), int(x)))
//
//
//########################################## With operator overloading ##########################################
string mathop(const string &s1, const string &s2, bool is_plus) {
    string result;
    for (int i1 = s1.size() - 1, i2 = s2.size() - 1, c = 0; i1 >= 0 || i2 >= 0 || c != 0; -- i1, -- i2) {
        int c1 = i1 < 0 ? 0 : s1[i1] - '0';
        int c2 = i2 < 0 ? 0 : s2[i2] - '0';
        int d = is_plus ?  c1 + c2 + c : c1 - c2 -c;
        c = is_plus ? d >= 10 : d < 0;
        result.push_back((d + 10) % 10 + '0');
    }
    result.resize(result.find_last_not_of('0') + 1);
    reverse(result.begin(), result.end());
    return result.empty() ? "0" : result;
}
string operator+(const string &s1, const string &s2) {
    return mathop(s1, s2, true);
}
string operator-(const string &s1, const string &s2) {
   return mathop(s1, s2, false);
}
bool operator<(const string &s1, const string &s2) {
    if (s1.size() != s2.size())
        return s1.size() < s2.size();
    for (int i = 0; i < s1.size(); ++i)
        if (s1[i] != s2[i])
            return s1[i] < s2[i];
    return false;
}
class Solution {
    string palindromify(const string & s, int tag = 0)
    {
        string result(s);
        string midone (s.size()/2 + 1, '0');
        midone[0] = '1';
        if (tag > 0)
            result = s + midone;
        else if (tag < 0)
        {
            result = s - midone;
            if (result.size() % 2 == 1 && s.size() % 2 == 0)
                result[result.size()/2] = '9'; //Special case here.
        }
        for (int i = 0; i <= result.size()/2. - 1; ++i)
            result[result.size() - 1 - i] = result[i];
        return result;
    }
public:
    string nearestPalindromic(string s) {
        string p = palindromify(s);
        string higher = s < p ? p : palindromify(s, 1);
        string lower = p < s ? p : palindromify(s, -1);
        string diff_higher = higher - s;
        string diff_lower = s - lower;
        return diff_higher < diff_lower ? higher : lower;
    }
};

//
//###################################################### NEED to verify  ######################################################
//https://discuss.leetcode.com/topic/88897/java-solution-with-detailed-proof
public String nearestPalindromic(String n) {
    char[] arr = n.toCharArray();
    for (int i = 0, j = arr.length - 1; i < j; i++, j--) arr[j] = arr[i];

    String curP = String.valueOf(arr);
    String preP = nearestPalindrom(curP, false);
    String nextP = nearestPalindrom(curP, true);

    long num = Long.valueOf(n);
    long cur = Long.valueOf(curP);
    long pre = Long.valueOf(preP);
    long next = Long.valueOf(nextP);

    long d1 = Math.abs(num - pre);
    long d2 = Math.abs(num - cur);
    long d3 = Math.abs(num - next);

    if (num == cur) {
        return d1 <= d3 ? preP : nextP;
    } else if (num > cur) {
        return d2 <= d3 ? curP : nextP;
    } else {
        return d1 <= d2 ? preP : curP;
    }
}

private String nearestPalindrom(String curP, boolean dir) {
    int k = curP.length() >> 1, p = curP.length() - k;
    int l = Integer.valueOf(curP.substring(0, p));
    l += (dir ? 1 : -1);

    if (l == 0) return k == 0 ? "0" : "9";

    String left = String.valueOf(l);
    StringBuilder right = new StringBuilder(left).reverse();
    if (k > left.length()) right.append("9");

    return left + right.substring(right.length() - k);
}
