//Find Permutation
//By now, you are given a secret signature consisting of character 'D' and 'I'. 'D' represents a decreasing relationship between two numbers, 'I' represents an increasing relationship between two numbers. And our secret signature was constructed by a special integer array, which contains uniquely all the different number from 1 to n (n is the length of the secret signature plus 1). For example, the secret signature "DI" can be constructed by array [2,1,3] or [3,1,2], but won't be constructed by array [3,2,4] or [2,1,3,4], which are both illegal constructing special string that can't represent the "DI" secret signature.
//On the other hand, now your job is to find the lexicographically smallest permutation of [1, 2, ... n] could refer to the given secret signature in the input.
//Example 1:
//Input: "I"
//Output: [1,2]
//Explanation: [1,2] is the only legal initial spectial string can construct secret signature "I", where the number 1 and 2 construct an increasing relationship.
//Example 2:
//Input: "DI"
//Output: [2,1,3]
//Explanation: Both [2,1,3] and [3,1,2] can construct the secret signature "DI",
//	but since we want to find the one with the smallest lexicographical permutation, you need to output [2,1,3]
//	Note:
//	1.The input string will only contain the character 'D' and 'I'.
//	2.The length of input string is a positive integer and will not exceed 10,000

//############################### W/ stack  ###############################
//TC : O(N)
//SC : O(N)
public class Solution {
    public int[] findPermutation(String s) {
        int[] res = new int[s.length() + 1];
        Stack < Integer > stack = new Stack < > ();
        int j = 0;
        for (int i = 1; i <= s.length(); i++) {
            if (s.charAt(i - 1) == 'I') {
                stack.push(i);
                while (!stack.isEmpty())
                    res[j++] = stack.pop();
            } else
                stack.push(i);
        }
        stack.push(s.length() + 1);
        while (!stack.isEmpty())
            res[j++] = stack.pop();
        return res;
    }
}

//############################### Approach #2 Reversing the subarray
//TC : O(N)
//SC : O(1)
//Algorithm
//
//In order to reverse the subsections of the minminmin array, as discussed in the last approach, we can also start by initializing the resultant arrangement resresres with the minminmin array i.e. by filling with elements (1,n)(1,n)(1,n) in ascending order. Then, while traversing the pattern sss, we can keep a track of the starting and ending indices in resresres corresponding to the D's in the pattern sss, and reverse the portions of the sub-arrays in resresres corresponding to these indices. The reasoning behind this remains the same as discussed in the last approach.
public class Solution {
    public int[] findPermutation(String s) {
        int[] res = new int[s.length() + 1];
        for (int i = 0; i < res.length; i++)
            res[i] = i + 1;
        int i = 1;
        while (i <= s.length()) {
            int j = i;
            while (i <= s.length() && s.charAt(i - 1) == 'D')
                i++;
            reverse(res, j - 1, i);
            i++;
        }
        return res;
    }
    public void reverse(int[] a, int start, int end) {
        for (int i = 0; i < (end - start) / 2; i++) {
            int temp = a[i + start];
            a[i + start] = a[end - i - 1];
            a[end - i - 1] = temp;
        }
    }
}

//############################### 2 pointers ###############################
//TC : O(N) "WC : DDDDD"
//SC : O(1)
public class Solution {
    public int[] findPermutation(String s) {
        int[] res = new int[s.length() + 1];
        res[0]=1;
        int i = 1;
        while (i <= s.length()) {
            res[i]=i+1;
            int j = i;
            if(s.charAt(i-1)=='D')
            {
                while (i <= s.length() && s.charAt(i - 1) == 'D')
                    i++;
                for (int k = j - 1, c = i; k <= i - 1; k++, c--) {
                    res[k] = c;
                }
            }
            else
                i++;
        }
        return res;
    }
}

//############################### O(n^2) w/o reverse operation ###############################
vector<int> findPermutation(string s) {
  vector<int> ret;
  for (int i = 0; i <= s.size(); ++i) {
    if (i == s.size() || s[i] == 'I') {
      for (int j = i + 1, lenTmp = ret.size(); j > lenTmp; --j) {
        ret.push_back(j);
	  }
	}
  }
  return ret;
}


//############################### O(n^2) with reverse operation ###############################
//IDIIDD
//1234567 // sorted
//1324765 // answer
vector<int> findPermutation(string s) {
	int n = s.size(), vector<int> ret;
    for (int i = 0; i <= n; i++) {
		ret[i] = i + 1; // sorted
	}
    for (int h = 0; h < n; h++) {
        if (s[h] == 'D') {
            int l = h;
            while (h < n && s[h] == 'D') h++; //find all D's
            reverse(ret.begin()+l, ret.begin()+h);
        }
    }
    return ret;
}

//############################### O(n^2) with reverse operation ###############################
vector<int> findPermutation(string s) {
	int n = s.size();
    vector<int> res(n+1);
    for (int i = 0; i <= n; i++) {
        res[i] = i+1;
    }
    int dStart = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'D') {
            if (dStart == -1)
                dStart = i;
            if (i == n-1) {
                reverse(res.begin()+dStart, res.end());
            }
        } else {
            if (dStart != -1) {
                reverse(res.begin()+dStart, res.begin()+i+1);
                dStart = -1;
            }
        }
    }
    return res;
}
////######################################### pytonic #########################################
//def findPermutation(self, s):
//    a = range(1, len(s) + 2)
//    for m in re.finditer('D+', s):
//        i, j = m.start(), m.end() + 1
//        a[i:j] = a[i:j][::-1]
//    return a
//
////######################################### pytonic #########################################
//My 1-liner tells sorted that the (larger) number i comes before the (smaller) number j iff they're both under the same D-streak, i.e., iff there's no I between them. (I'm not totally sure that i will always be the larger number, but it appears to be the case).
//
//def findPermutation(self, s):
//    return sorted(range(1, len(s) + 2), cmp=lambda i, j: -('I' not in s[j-1:i-1]))
//
//

////######################################### pytonic - greedy #########################################
//Loop on the input and insert a decreasing numbers when see a 'I'
//Insert a decreasing numbers to complete the result.
//Simple example:
//Input: "DIDDID"
//0 []
//1 [2, 1]
//2 [2, 1]
//3 [2, 1]
//4 [2, 1, 5, 4, 3]
//5 [2, 1, 5, 4, 3]
//[2, 1, 5, 4, 3, 7, 6]
//
//Then, output is [2, 1, 5, 4, 3, 7, 6]
//
//def findPermutation(self, s):
//    ret = []
//    for i in range(len(s)):
//      if s[i] == 'I':
//        ret.extend(range(i + 1, len(ret), -1))
//    ret.extend(range(len(s) + 1, len(ret), -1))
//    return ret
