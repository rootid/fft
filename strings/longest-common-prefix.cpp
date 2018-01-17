//Longest Common Prefix
//Write a function to find the longest common prefix string amongst an array of strings.

#include "../headers/global.hpp"

//############################################## Good  ############################################## 
string longestCommonPrefix(vector<string>& strs) {
       string prefix="";
       if(strs.size()==0)  return prefix;

       for(int k=0; k<strs[0].size(); k++){
           int i=1;
           for(; i<strs.size() && strs[i].size()>k; i++){
               if(strs[i][k]!=strs[0][k])
                   return prefix;
           }
           if(i==strs.size()) prefix+=strs[0][k];
       }
       return prefix;
}

//############################################## Good  ############################################## 
string longestCommonPrefix(vector<string>& strs) {
     string prefix = "";
     for(int idx=0; strs.size()>0; prefix+=strs[0][idx], idx++)
         for(int i=0; i<strs.size(); i++)
             if(idx >= strs[i].size() ||(i > 0 && strs[i][idx] != strs[i-1][idx]))
                 return prefix;
     return prefix;
}

//############################################## Bad ############################################## 
string longestCommonPrefix(vector<string>& strs) {
       char charSet[256];
       for(int i=0;i<256;i++) {
           charSet[i] = 0;
       }
       string result = "";
       int tStr = strs.size();
       if(tStr == 0) {
           return result;
       }
       int idx = 0;
       while(true) {
           if(idx == strs[0].length() ){
               return strs[0];
           }
           charSet[idx] = strs[0][idx];
           for(int i=1;i<tStr;i++) {
               if(idx == strs[i].length() || charSet[idx] != strs[i][idx] ){
                   return strs[i].substr(0,idx);
               }
           }
           idx += 1;
       }
       return result;
}

//############################################## Bad ############################################## 
string longestCommonPrefix(vector<string>& strs) {
  int tLen = strs.size();
  int idx =0;
  bool found = true;
  if(tLen == 0) {
      return "";
  }
  if(tLen == 1) {
      return strs[0];
  }
  while(found == true) {
    for(int i=1;i<tLen;i++) {
      int lLen = strs[i].length();
      if(idx > lLen || idx > strs[0].length() || strs[i][idx] != strs[0][idx]) {
        //cout << "idx " << idx << endl;
        found = false;
        break; 
      }
    }
    idx += 1;
  }
   return strs[0].substr(0,idx-1);
}

