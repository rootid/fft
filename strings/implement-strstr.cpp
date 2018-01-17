//Implement strStr().
//Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

#include "../headers/global.hpp"
//Hash beats 13.66%
int strStr(string haystack, string needle) {
    int nLen = (int)needle.size();
    int hLen = (int)haystack.size();
    int validLength = hLen - nLen + 1;
    if (validLength < 1) {
        return -1;
    }
    int nKey = 0;
    int key = 0;
    for (int i = 0; i < nLen; ++i) {
        nKey += needle[i];
    }
    for (int i = 0; i < nLen; ++i) {
        key += haystack[i];
    }
    for (int i = 0; i < validLength; ++i) {
        if (key == nKey) {
         // if(needle == haystack.substr(i,nLen)) {
         //   return i;
         // }
          bool found = true;
          for (int j = 0; j < nLen; ++j) {
              if (haystack[i+j] != needle[j]) {
                  found = false;
                  break;
              }
          }
          if (found) {
              return i;
          }
        } 
        key -= haystack[i];
        key += haystack[i+nLen];
    }
    return -1;
}
int strStr(string haystack, string needle) {
    int len = needle.size();
    int maxLen = haystack.size();
    if(len == maxLen && len == 0) {
        return 0;
    }
    if(maxLen < len) {
      return -1;
    }
    int key = 0;
    int hKey = 0;
    for(int i=0;i<len;i++) {
      key += needle[i];
    }
    for(int i=0;i<len;i++) {
      hKey += haystack[i];
    }
    //cout << maxLen << "," << len << endl;
    //cout << hKey << "," << key  << endl;
    for(int i=0;i<= (maxLen - len); i++) {
      cout << hKey << endl;
      if(hKey == key) {
        //cout << haystack.substr(i,len) << endl;
        if(needle == haystack.substr(i,len)) {
          return i;
        }
      }
      hKey -= haystack[i];
      hKey += haystack[i+len];
    }
    return -1;
}
//Beats only 6.35%
//int strStr(string haystack, string needle) {
//    int len = needle.size();
//    int maxLen = haystack.size();
//    if(len == maxLen && len == 0) {
//        return 0;
//    }
//    for(int i=0;i <= maxLen - len; i++) {
//        //NOTE : substr : always creates a new string object
//        if(haystack.substr(i,len) == needle) {
//            return i;
//        }
//    }
//    return -1;
//}
////KMP beats 13.66%
//int strStr(string haystack, string needle) {
//       if(needle.empty()) return 0;
//       if(haystack.empty()) return -1;
//       vector<int> pi(needle.size(), 0);
//       //KMP-algorithm:
//       //Pre-process
//       int k = 0, i;
//       for(i = 1; i < needle.size(); i++) {
//           while(k > 0  && needle[k] != needle[i]) k = pi[k - 1];
//           if(needle[k] == needle[i]) pi[i] = ++k;
//       }
//       k = 0;
//       //Matching
//       for(i = 0; i < haystack.size(); i++) {
//           while(k > 0 && haystack[i] != needle[k]) k = pi[k - 1];
//           if(haystack[i] == needle[k]) k++;
//           if(k == needle.size()) return i - needle.size() + 1;
//       }
//       return -1;
//}
int main() {
  //strStr("a","a");
  strStr("abb","abaaa");
}
