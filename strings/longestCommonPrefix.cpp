//Write a function to find the longest common prefix string amongst an array of strings.

#include<iostream>
#include<string>
using namespace std;

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

int main() {

}
