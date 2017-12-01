//Remove Duplicate Letters
//Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.
//Example:
//Given "bcabc"
//Return "abc"
//Given "cbacdcbc"
//Return "acdb"

#include "../headers/global.hpp"


//######################################### Repeatative removal of left substring ######################################### 
//O(n^2) 
    public String removeDuplicateLetters(String s) {
        if(s == null || s.length() == 0) return s;
        
        char[] cntr = new char[256];
        for(int i=0;i<s.length();i++) cntr[s.charAt(i)]++;
        
        StringBuilder sb = new StringBuilder();
        Set<Character> visited = new HashSet<>();
        
        for(int i=0;i<s.length();i++) {
            cntr[s.charAt(i)]--;
            
            if(visited.contains(s.charAt(i))) continue;
            
            while(sb.length() >= 1 && s.charAt(i) < sb.charAt(sb.length() - 1) && cntr[sb.charAt(sb.length() - 1)] > 0) {
                visited.remove(sb.charAt(sb.length() - 1));
                sb.setLength(sb.length() - 1);
            }
            
            sb.append(s.charAt(i));
            visited.add(s.charAt(i));
        }
        return sb.toString();
    }

//######################################### stack ######################################### 
string removeDuplicateLetters(string s) {
     string res = "0";
     vector<int> cntr(256, 0);
     vector<bool> visited(256, false);
     int len = s.size();
     for(auto& i:s) {
         cntr[i]++;
     }
     for(auto& c : s) {
        cntr[c]--;
        
        if(visited[c]) {
             continue;
         }
         //current charcter is less than the previous chracter => c < result.back()
         //and previous character is present in the future => dict[result.back()])
         while(c < res.back() && cntr[res.back()]) {
             visited[res.back()] = false;
             res.pop_back();
         }
         res += c;
         visited[c] = true;
     }
     return res.substr(1);
}


//######################################### greedy  ######################################### 
//Given the string s, the greedy choice (i.e., the leftmost letter in the answer) is the smallest s[i], s.t.
//the suffix s[i .. ] contains all the unique letters. (Note that, when there are more than one smallest s[i]'s, 
//we choose the leftmost one. Why? Simply consider the example: "abcacb".)
//
//After determining the greedy choice s[i], we get a new string s' from s by
//
//removing all letters to the left of s[i],
//removing all s[i]'s from s.
//We then recursively solve the problem w.r.t. s'.
//
//The runtime is O(26 * n) = O(n).

public class Solution {
    public String removeDuplicateLetters(String s) {
        int[] cnt = new int[26];
        int pos = 0; // the position for the smallest s[i]
        for (int i = 0; i < s.length(); i++) cnt[s.charAt(i) - 'a']++;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) < s.charAt(pos)) pos = i;
            if (--cnt[s.charAt(i) - 'a'] == 0) break;
        }
        return s.length() == 0 ? "" : s.charAt(pos) + removeDuplicateLetters(s.substring(pos + 1).replaceAll("" + s.charAt(pos), ""));
    }
}
