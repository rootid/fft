//Remove Duplicate Letters
//Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.
//Example:
//Given "bcabc"
//Return "abc"
//Given "cbacdcbc"
//Return "acdb"

#include "../headers/global.hpp"

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
