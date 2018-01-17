#include<iostream>
#include<string>
using namespace std;
char findTheDifference(string s, string t) {
        int idx = 0;
        int l1 = s.size() - 1;
        int l2 = t.size() - 1;
        while(l1 >= 0 && l2>= 0) {
           idx = idx ^ (int)t[l2];
           idx = idx ^ (int)s[l1];
           l1 -= 1;
           l2 -= 1;
        }
        while(l1 >= 0) {
            idx ^= s[l1];
            l1 -= 1;
        }
        while(l2 >=0 ) {
            idx ^= t[l2];
            l2 -= 1;
  
        }   
        cout << (char)idx << endl;
        return (char)idx;
}

char findTheDifferenceBest(string s, string t) {
        char idx = 0;
        for(char x:s+t) {
          idx ^= x;
        }
        return  idx;
}

int main() {
  string s = "abcde";
  string t = "abcd";
  findTheDifference(s,t);
}
