//Valid Anagram
//Given two strings s and t, write a function to determine if t is an anagram
//of s.
//
//For example,
//s = "anagram", t = "nagaram", return true.
//s = "rat", t = "car", return false.

#include<iostream>
#include<vector>
#include<string>
#include<limits.h>
#include<stdlib.h>

using namespace std;

//######################################### O(n log n + m log m) #########################################
public boolean isAnagram(String s, String t) {
    if(s.length() != t.length()) return false;
    char[] sA = s.toCharArray();
    char[] tA = t.toCharArray();
    Arrays.sort(sA);
    Arrays.sort(tA);
	return Arrays.equals(sA, tA);
    //int idx = 0;
    //while(idx < sA.length) {
    //    if(sA[idx] != tA[idx]) return false;
    //    idx++;
    //}
    //return true;
}

//######################################### O(n log n + m log m) #########################################
//I don't think LeetCode tells the compiler to optimize, though, and when you
//do, the difference shrinks. I tried this on my PC.
//Without optimizer, your way took 3724 ms and mine took 1965 ms. With compiler
//flag -O3, yours took 481 ms and mine took 435 ms.
//(Time without sorting, i.e., for preparing the strings, was only 19 ms.)
#include <iostream>
#include <algorithm>
#include <chrono> //Measure time
using namespace std;

int main () {
    string s(10000, ' ');
    auto t0 = chrono::high_resolution_clock::now();
    for (int i=0; i<1000; i++) {
        for (int j=0; j<10000; j++)
            s[j] = 'a' + j & 15;
        //sort(s.begin(), s.end());
        sort((char*)s.c_str(), (char*)s.c_str()+s.size());
    }
    auto t = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<std::chrono::milliseconds>(t-t0).count()<<" ms\n";
}


//######################################### O(n) #########################################
bool isAnagrams(string &s,string &s1) {

  int MAX_CHAR = 26;
  if (s.length() == s1.length()) {
    int len_ = s1.length();
    char mx[MAX_CHAR] = {0};
    for (int i=0;i<len_;i++) {
      mx[s[i] - 'a']++;   //aaaa
      mx[s1[i] - 'a']--;   //aaaa
    }
    for(int i=0;i<MAX_CHAR;i++) {
      if ( mx[i] != 0 ) {
        return false;
      }
    }
    return true;
  }
  return false;
}


void testMe(string& s,string& s1) {

    if ( isAnagrams(s,s1) == true) {
      cout << " s= " << s<< "| s1= " << s1 << " are anagrams." << endl;
    } else {
      cout << " s= " << s<< "| s1= " << s1 << " are not anagrams." << endl;
    }
}


int main() {
    string s = "quick";
    string s1 = "fox";
    testMe(s1,s);

    s = "anagram";
    s1 = "nagaram";
    testMe(s1,s);
}
