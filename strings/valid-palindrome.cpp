//Valid Palindrome
//Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
//For example,
//"A man, a plan, a canal: Panama" is a palindrome.
//"race a car" is not a palindrome.
//Note:
//Have you consider that the string might be empty? This is a good question to ask during an interview.
//For the purpose of this problem, we define empty string as valid palindrome
//
//

#include "../headers/global.hpp"



//######################################### Iterative  #########################################
public boolean isPalindrome(String s) {
    String actual = s.replaceAll("[^A-Za-z0-9]", "").toLowerCase(); //replace all non alphnemeric chars w/ empty string
    String rev = new StringBuffer(actual).reverse().toString();
    return actual.equals(rev);
}

//######################################### Iterative  #########################################
public boolean isPalindrome(String s) {
     char[] arr = s.toCharArray();
     int end = s.length() -1;
     int start = 0;
     while(start < end) {
         if(!Character.isDigit(arr[start]) && !Character.isAlphabetic(arr[start])) start++;
         else if(!Character.isDigit(arr[end]) && !Character.isAlphabetic(arr[end])) end--;
         else if(Character.toUpperCase(arr[start]) == Character.toUpperCase(arr[end])) {
             start++;
             end--;
         } else return false;
     }
     return true;
}

//######################################### Iterative  #########################################
bool isPalindrome(string s) {
   int i = 0, j = s.size() - 1;
   while(i < j)
   {
       while(i < j && !isalnum(s[i])) i++;
       while(i < j && !isalnum(s[j])) j--;
       if (toupper(s[i])!=toupper(s[j]))
           return false;
       i++;j--;
   }
   return true;
}

//######################################### Recursive  #########################################
//For large input getting stack overflow
class Solution {
    public boolean isPalindrome(String s) {
        if(s == null || s.length() == 0) return true;
        String dummyS = s.toLowerCase();
        int end = dummyS.length() - 1;
        int start = 0;
        return isPalindromeHelper(dummyS, start, end);
    }

    private boolean isPalindromeHelper(String s, int start, int end) {
        //System.out.println( "(strt = " + start + " , end = " + end + " )");
        if(start < end) {
           if(!Character.isLetterOrDigit(s.charAt(start)))
               return isPalindromeHelper(s, start+1, end);
           if(!Character.isLetterOrDigit(s.charAt(end)))
               return isPalindromeHelper(s, start, end-1);
           if(s.charAt(start) == s.charAt(end))
                return isPalindromeHelper(s, start+1, end-1);
           return false;
        }
        return true;
    }
}

//#################### Ugly ####################
bool isValid(char c) {
  if( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ) {
    return true;
  }
  return false;
}

char getLower(char c) {
  if(c >= 'A' && c <= 'Z') {
      c = c - 'A';
      c = c + 'a';
  }
  return c;
}

bool isPalindrome(string s) {

  int n = s.size();
  for(int i=0,j=n-1;i<n,j>=0;) {
    if(!isValid(s[i])) {
      i++;
      continue;
    }
    if(!isValid(s[j])) {
      j--;
      continue;
    }
    if(getLower(s[i]) == getLower(s[j]) ) {
      i++;
      j--;
    } else {
      return false;
    }
  }

  return true;

}


int main() {

  string s = "A man, a plan, a canal: Panama";
  //string s = "race a car";
  bool r = isPalindrome(s);
  if(r == true) {
    cout << s << " is palindorme " << endl;
  } else {
    cout << s << " is not palindorme " << endl;
  }

}
