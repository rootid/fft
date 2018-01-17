//Given two binary strings, return their sum (also a binary string).
//
//For example,
//a = "11"
//b = "1"
//Return "100".
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;


//######################################### Recursive  ######################################### 
class Solution:
     def addBinary(self, a, b):
         if len(a)==0: return b
         if len(b)==0: return a
         if a[-1] == '1' and b[-1] == '1':
             return self.addBinary(self.addBinary(a[0:-1],b[0:-1]),'1')+'0'
         if a[-1] == '0' and b[-1] == '0':
             return self.addBinary(a[0:-1],b[0:-1])+'0'
         else:
             return self.addBinary(a[0:-1],b[0:-1])+'1'


//######################################### Iterative ######################################### 
public String addBinary(String a, String b) {
     StringBuilder sum = new StringBuilder();
     int i = a.length() - 1;
     int j = b.length() - 1;
     int carry = 0;
     while (i >= 0 || j >= 0 || carry == 1) {
         int digitA = i < 0 ? 0 : a.charAt(i--) - '0';
         int digitB = j < 0 ? 0 : b.charAt(j--) - '0';
         sum.insert(0, (digitA + digitB + carry) % 2); //insert instead of append+reverse
         carry = (digitA + digitB + carry) / 2;
     }
     return sum.toString();
}

//######################################### Iterative ######################################### 
public String addBinary(String a, String b) {  
    char[] aC = a.toCharArray();
    char[] bC = b.toCharArray();
    int m = aC.length;
    int n = bC.length;
    StringBuilder result = new StringBuilder();
    int idx = 0;
    int carry = 0;
    while(carry != 0 || idx < m || idx < n) {
        if(idx < m)
            carry += aC[m-1-idx] - '0';
        if(idx < n)
            carry += bC[n-1-idx] - '0';
        result.append(String.valueOf(carry % 2));
        carry /= 2;
        idx++;
    }
    return result.reverse().toString();
}


//######################################### Iterative ######################################### 
string addBinary(string a, string b) {
      string result = "";
      int carry = 0;
      int idx = 0;
      while(carry != 0 || idx < a.size() || idx < b.size()) {
          if(idx < a.size() ){
              carry += (a[a.size() - 1 - idx] - '0');
          }
          if(idx <b.size()) {
              carry += (b[b.size() - 1 - idx] - '0');
          }
          result.push_back( (carry % 2) + '0');
          carry = carry/2;  
          idx += 1;
      }
      reverse(result.begin(),result.end());
      return result;
}


//######################################### Ugly solution  ######################################### 
public String addBinary(String a, String b) {
        if(a.length() == 0) return b;
        if(b.length() == 0) return a;
        char[] aC = a.toCharArray();
        char[] bC = b.toCharArray();
        int m = aC.length - 1;
        int n = bC.length -1;
        StringBuilder result = new StringBuilder();
        int sum = 0;
        int carry = 0;
        while(m >=0 && n >=0) {
            sum = aC[m--] - '0' + bC[n--] - '0' + carry;
            carry = sum/2;
            sum %= 2;
            result.append(String.valueOf(sum));
        }
        while(m >= 0) {
             sum = aC[m--] - '0' + carry;
             carry = sum/2;
             sum %= 2;
             result.append(String.valueOf(sum));
        }
        while(n >= 0) {
             sum = bC[n--] - '0' + carry;
             carry = sum/2;
             sum %= 2;
             result.append(String.valueOf(sum));
        }
        if(carry == 1) result.append(String.valueOf(1));
        
        return result.reverse().toString();
}


int main() {
  string a = "11";
  string b = "1";
  string r = addBinary(a,b);
  cout << " R = " << r << endl;
}
