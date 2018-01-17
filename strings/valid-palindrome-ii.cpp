//Valid Palindrome II
//Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.
//Example 1:
//Input: "aba"
//Output: True
//Example 2:
//Input: "abca"
//Output: True
//Explanation: You could delete the character 'c'.
//Note:
//The string will only contain lowercase characters a-z. The maximum length of the string is 50000.

//######################################### Iterative version  ######################################### 
class Solution {
    public boolean validPalindrome(String s) {
        int l=0;
        int r=s.length()-1;
        while(l<r){
            if(s.charAt(l)!=s.charAt(r)){
                return isPalindrome(s,l+1,r) || isPalindrome(s,l,r-1);
            }
            ++l;
            --r;
        }
        return true;
    }
    public boolean isPalindrome(String s,int l,int r){
        while(l<r){
            if(s.charAt(l)==s.charAt(r)){
                ++l;
                --r;
            }
            else
                return false;
        }
        return true;
    }
}
//######################################### Recursion ######################################### 
def validPalindrome(self, s):
      def isPalindrome(s, i, j, deleted):
          while i < j:
              if s[i] != s[j]: 
                  return not deleted and (isPalindrome(s, i+1, j, True) or isPalindrome(s, i, j-1, True))
              i, j = i+1, j-1
          return True
      return isPalindrome(s, 0, len(s)-1, False)

//######################################### 2-pointer  ######################################### 
// two-pointer approach that starts at the left and right of the string and move inwards. Whenever there is a mismatch, we can either exclude the character at the left or the right pointer. We then take the two remaining substrings and compare against its reversed and see if either one is a palindrome.
class Solution(object):
    def validPalindrome(self, s):
        """
        :type s: str
        :rtype: bool
        """
        # Time: O(n)
        # Space: O(n)
        left, right = 0, len(s) - 1
        while left < right:
            if s[left] != s[right]:
                one, two = s[left:right], s[left + 1:right + 1]
                return one == one[::-1] or two == two[::-1]
            left, right = left + 1, right - 1
        return True


//#########################################  T : O(n) , S O(1) #########################################  
public boolean validPalindrome(String s) {
    int l = -1, r = s.length();
    while (++l < --r) 
        if (s.charAt(l) != s.charAt(r)) return isPalindromic(s, l, r+1) || isPalindromic(s, l-1, r);
    return true;
}

public boolean isPalindromic(String s, int l, int r) {
    while (++l < --r) 
        if (s.charAt(l) != s.charAt(r)) return false;
    return true;
}

//#########################################  T : O(n) , S O(1) #########################################  
class Solution {
public:
    bool validPalindrome(string s) {
        int i = 0, j = s.size() - 1;
        while(i <= j && s[i] == s[j]) i++, j--;
        return i > j || isValid(s.substr(i, j - i)) || isValid(s.substr(i + 1, j - i));
    }
    
    bool isValid(string s){
        int i = 0, j = s.size() - 1;
        while(i <= j && s[i] == s[j]) i++, j--;
        return i > j;
    }
};
