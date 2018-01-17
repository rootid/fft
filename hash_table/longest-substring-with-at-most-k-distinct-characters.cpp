//Given a string, find the length of the longest substring T that contains at most k distinct characters.
//For example, Given s = “eceba” and k = 2,
//T is "ece" which its length is 3.
#include "../headers/global.hpp"


int lengthOfLongestSubstringKDistinct(string s, int k) {
        int max_len = 0;
        int len = s.size();
        unordered_map<char,int> u_map;
        int j = -1;
        for(int i=0;i<len;i++) {
            u_map[s[i]]++;
            while(u_map.size() > k) {     //Once you find k charcters or more erase the first characters
                 if (--u_map[s[++j]] == 0) {
                    u_map.erase(s[j]);
                 }
            }
            max_len = max(max_len,i-j);
        }
        return max_len;
        
     
//         int len = s.size();
//           if(k == 0) {
//             return max_len;
//         }
//         unordered_set<char> us;
//         for(int i=0;i<len;i++) {
//             int tmp_len = 0;
//             int nc = k;
//             int c_idx = i;
//             while(nc >= 0 && c_idx < len) {
//                 if(us.find(s[c_idx]) == us.end()) {
//                     nc--;
//                     tmp_len++;
//                     us.insert(s[i]);
//                 }
//                 us.clear();
//                 c_idx++;
//             }
//             if(max_len < tmp_len) {
//                 max_len = tmp_len;
//             }
//         }
 
//   return max_len;
    
}
