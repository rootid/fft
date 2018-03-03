//Repeated String Match
//Given two strings A and B, find the minimum number of times A has to be
//repeated such that B is a substring of it. If no such solution, return -1.
//For example, with A = "abcd" and B = "cdabcdab".
//Return 3, because by repeating A three times (“abcdabcdabcd”), B is a
//substring of it; and B is not a substring of A repeated two times
//("abcdabcd").
//Note:
//The length of A and B will be between 1 and 10000.

//######################################### Append string  #########################################
//a = "abc"
//b= "abcabc" - in this case we need 2 copies of a
//b= "cabcab" - in this case we need 3 copies of a
//b="cabca"  - in this case we need 3 copies of a
//StringBuilder may be better, thus saving space, same idea
class Solution {
    public int repeatedStringMatch(String A, String B) {
        StringBuilder as = new StringBuilder(A);
        for (int rep = 1; rep <= B.length() / A.length() + 2; rep++) {
            if (as.toString().contains(B)) {
                return rep;
            }
            as.append(new StringBuilder(A));
        }
        return -1;
    }
}

//######################################### Append string  #########################################
//Assume the repeated string does exist. Then, we must have
//B = [some nullable suffix of A] AA..AA [some nullable prefix of A].
//Let k = floor(|B| / |A|). Then, we just need to test
//whether the string by repeating A k times contains B as a substring,
//whether the string by repeating A (k+1) times contains B as a substring,
//whether the string by repeating A (k+2) times contains B as a substring.
//Note that, test 1 makes sense only if |B| is divisible by |A|. But for
//convenience, we include this case anyway, without increasing the overall
//asymptotic runtime.
//Each test can be done in O(|A| + |B|) time using (say) KMP. Therefore, the
//total runtime is still O(|A| + |B|).
//Java code:
public int repeatedStringMatch(String A, String B) {
    StringBuilder builder = new StringBuilder(A);
    while (builder.length() < B.length())
        builder.append(A);

    for (int i = 0; i < 3; i++) {
        if (builder.toString().contains(B)) // For simplicity, pretend that String.contains is implemented using KMP.
            return builder.length() / A.length();
        builder.append(A);
    }
    return -1;
}

//Using KMP:
class Solution {
    public int repeatedStringMatch(String A, String B) {
        StringBuilder builder = new StringBuilder(A);
        while (builder.length() < B.length())
            builder.append(A);
        int[] next = new int[B.length()];
        for (int i = 0, j = -1; i < B.length(); i++) {
            while (j != -1 && B.charAt(i) != B.charAt(j + 1))
                j = next[j];
            next[i] = i > 0 && B.charAt(i) == B.charAt(j + 1) ? j + 1 : -1;
            j = next[i];
        }

        for (int i = 0; i < 3; i++) {
            if (kmpMatch(builder.toString(), B, next))
                return builder.length() / A.length();
            builder.append(A);
        }
        return -1;
    }

    private boolean kmpMatch(String s, String pattern, int[] next) {
        for (int i = 0, j = -1; i < s.length(); i++) {
            while (j != -1 && s.charAt(i) != pattern.charAt(j + 1))
                j = next[j];
            if (s.charAt(i) == pattern.charAt(j + 1))
                j++;
            if (j == pattern.length() - 1)
                return true;
        }
        return false;
    }

