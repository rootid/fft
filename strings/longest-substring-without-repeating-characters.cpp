//Given a string, find the length of the longest substring without repeating characters.
//Examples:
//Given "abcabcbb", the answer is "abc", which the length is 3.
//Given "bbbbb", the answer is "b", with the length of 1.
//Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
//

#include "../headers/global.hpp"

//###################################################### G ###################################################### 
int lengthOfLongestSubstring(string s) {
    int charSet[256] = {0};
    int minLen = 0;
    int curLen = 0;
    for(int i=0;i<s.length();i++) {
        if(charSet[s[i] ] != 0) {
            for(int i=0;i<256;i++) {
                charSet[i] = 0;
            }
            curLen = 0;
        }
        charSet[s[i] ] = 1;
        curLen += 1;
        if(curLen > minLen) {
            minLen = curLen;
        }
    }
    return minLen;
}

//######################################################
//aab,abag,aaaa,abacda
int getLongestNRSubstr(string &s) {
  int len = s.length();
  int startIdx = 0;
  int endIdx = 0;
  int maxLen = 0;
  char matrix[256] = {0};

  for(int i=0;i<len;i++) {
    if (matrix[ s[i] - 'a' ] == 1) {

      maxLen = max(maxLen,endIdx - startIdx);
      //Failure case : aba : ideally startIdx must start from b not from a after match.
      //for(int i=startIdx;i<endIdx;i++) {
      //  matrix[ s[i] - 'a'] = 0;
      //}
      while (s[startIdx] != s[endIdx]) {
        matrix[s[startIdx] - 'a'] = 0;
        startIdx++;
      }
      endIdx++; // need to consider the duplicate element as the part of next visit
      startIdx++;
    } else {
      matrix[ s[i] - 'a' ] = 1;
      endIdx += 1;
    }
  }

  maxLen = max(maxLen,len - startIdx);
  return maxLen;
}

//######################################### O(n) ######################################### 
//"pwwkew" : 3
//"abba" : 2
 public int lengthOfLongestSubstring(String s) {
		//startIdx -- Always increasing should never go back
        int len = s.length();
        int max = 0;
        int[] store = new int[256];
        for(int i=0,startIdx=0 ;i<len;i++) {
            if(store[s.charAt(i)] != 0) 
              startIdx = Math.max(startIdx, store[s.charAt(i)]); //"abba" : 2 a
            store[s.charAt(i)] = i + 1;
            max = Math.max(max,  i - startIdx + 1);
        }
        return max;
    }
}


//######################################### HashMap  ######################################### 
public int lengthOfLongestSubstring(String s) {
        if (s.length()==0) return 0;
        HashMap<Character, Integer> map = new HashMap<Character, Integer>();
        int max=0;
        for (int i=0, j=0; i<s.length(); ++i){
            if (map.containsKey(s.charAt(i))){
                j = Math.max(j,map.get(s.charAt(i))+1);
            }
            map.put(s.charAt(i),i);
            max = Math.max(max,i-j+1);
        }
        return max;
    }

int wrapperLR(string s) {
  int len = getLongestNRSubstr(s);
  cout << "Longest str " << s << " = "  << len << endl;
}


int main() {
  wrapperLR("aab");
  wrapperLR("abcderf");
  wrapperLR("aa");
  wrapperLR("aaaaaa");
  wrapperLR("aabeff");
  wrapperLR("aabac");
  wrapperLR("aabc");
}





