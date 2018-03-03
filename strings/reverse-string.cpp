//Reverse String
//Write a function that takes a string as input and returns the string
//reversed.
//Example:
//Given s = "hello", return "olleh".
//


//######################################### O(n) #########################################
public String reverseString(String s) {
    StringBuilder sb = new StringBuilder(s);
    return sb.reverse().toString();
}

//######################################### O(n) #########################################
public String reverseString(String s) {
     char[] charArr = s.toCharArray();
     int start = 0;
     int end = charArr.length-1;
     while(start< end) swap(charArr,start++,end--);
     return String.valueOf(charArr);
 }
 private void swap(char[] nums, int i, int j) {
     nums[i] ^= nums[j];
     nums[j] ^= nums[i];
     nums[i] ^= nums[j];
 }


class Solution(object):
    def reverseString(self, s):
        l = len(s)
        if l < 2:
            return s
        return self.reverseString(s[l/2:]) + self.reverseString(s[:l/2])


//######################################### O(n) #########################################
class SolutionClassic(object):
    def reverseString(self, s):
        r = list(s)
        i, j  = 0, len(r) - 1
        while i < j:
            r[i], r[j] = r[j], r[i]
            i += 1
            j -= 1

        return "".join(r)

//######################################### O(n) #########################################
class SolutionPythonic(object):
    def reverseString(self, s):
        return s[::-1]
