//Add Strings
//Given two non-negative numbers num1 and num2 represented as string, return
//the sum of num1 and num2.
//Note:
//The length of both num1 and num2 is < 5100.
//Both num1 and num2 contains only digits 0-9.
//Both num1 and num2 does not contain any leading zero.
//You must not use any built-in BigInteger library or convert the inputs to
//integer directly.
#include<iostream>
#include<string>
using namespace std;

//################################GOOD
string addStrings(string num1, string num2) {
        string result = "";
        int sum = 0;
        int carry = 0;
        int l1 = num1.size() - 1;
        int l2 = num2.size() - 1;
        stringstream ss;
        while(l1 >= 0 || l2 >= 0) {
            if(l1 >= 0) {
             sum =  (num1[l1] - '0') ;
             l1--;
            }
            if(l2 >= 0) {
             sum +=  (num2[l2] - '0') ;
             l2--;
            }
            sum += carry;
            carry = sum/10;
            sum = sum % 10;
            ss << sum;
            sum = 0;
        }
        if(carry > 0) {
            ss << carry;
        }

        string t = ss.str();
        reverse(t.begin(),t.end());
        return t;
}

//####################################Ugly
string addStrings(string num1, string num2) {
    string result = "";
    int sum = 0;
    int carry = 0;
    int l1 = num1.size() - 1;
    int l2 = num2.size() - 1;
    stringstream ss;
    while(l1 >= 0 && l2 >= 0) {
        sum =  (carry + num1[l1] - '0' + num2[l2] - '0') % 10;
        carry = ( carry + num1[l1] - '0' + num2[l2] - '0') / 10;
        ss << sum; l1--;l2--;
    }
    while(l1 >= 0) {
        sum =  (carry + num1[l1] - '0') % 10;
        carry = (num1[l1] - '0' + carry) / 10;
        ss << sum; l1--;
    }
     while(l2 >= 0) {
        sum =  (carry  + num2[l2] - '0') % 10;
        carry = (carry + num2[l2] - '0') / 10;
        ss << sum; l2--;
    }
    if(carry > 0) {
        ss << carry;
    }

    string t = ss.str();
    reverse(t.begin(),t.end());
    return t;
}
int main() {
}
