// Longest Palindrome
//Given a string which consists of lowercase or uppercase letters, find the
//length of the longest palindromes that can be built with those letters.
//This is case sensitive, for example "Aa" is not considered a palindrome here.
//Note:
//Assume the length of given string will not exceed 1,010.
//Example:
//Input:
//"abccccdd"
//Output:
//7
//Explanation:
//One longest palindrome that can be built is "dccaccd", whose length is 7.

#include<iostream>
#include<string>
#include<assert.h>
#include<vector>
using namespace std;


//######################################### With Set #########################################
public int longestPalindrome(String s) {
        Set<Character> set = new HashSet<>();
        for (char c : s.toCharArray()) {
            if (set.contains(c)) set.remove(c);
            else set.add(c);
        }

        int odd = set.size();
        return s.length() - (odd == 0 ? 0 : odd - 1);
    }

//######################################### With Map  #########################################
//Partial Contribution(# of chars are odd)  + Full Contribution (# of chars are
//even) + If Partial contribution then Odd length palindrome
public int longestPalindrome(String s) {
    int len = s.length();
    int palLen = 0;
    Map<Character, Integer> freqMap = new HashMap<>();
    boolean isOddLen = false;
    for(int i=0;i<len;i++) freqMap.put(s.charAt(i), freqMap.getOrDefault(s.charAt(i), 0) + 1);
    for(char key: freqMap.keySet()) {
        if(freqMap.get(key) % 2 == 0) palLen += freqMap.get(key);
        else {
            palLen += freqMap.get(key) - 1;
            isOddLen = true;
        }
    }
    return isOddLen == true ? palLen + 1 : palLen;
}

//######################################### With Array#########################################
int longestPalindrome(string s) {
      assert(s.size() <= 1010);
      int pal_len = 0;
      vector<int> c_store(256,0);
      bool is_odd = false;
      for(int i=0;i<s.size();i++) {
          c_store[s[i]]++;
      }
      for(int j=0;j<256;j++) {
        if(c_store[j] % 2 == 0) {
            pal_len += c_store[j];
          cout <<  "pal_len = " << pal_len << endl;
        } else {
            pal_len += (c_store[j] - 1);
          cout <<  "O pal_len = " << pal_len << endl;
            is_odd = true;
        }
      }

      if(is_odd) {
           pal_len += 1;
      }

      cout <<  "pal_len = " << pal_len << endl;
      return pal_len;
}

int main() {
  string s = "abccccdd";
  longestPalindrome(s);
}
