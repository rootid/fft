//Given a non-negative number represented as an array of digits, plus one to the number.
//The digits are stored such that the most significant digit is at the head of the list.
#include<iostream>
#include<vector>
using namespace std;
vector<int> plusOne(vector<int>& digits) {
    
    int l = digits.size() - 1;
    int sum = 0;
    int carry = 1;
    vector<int> result;
    for(int i= l;i>=0;i--) {
        sum = carry  + digits[i];
        carry = sum / 10;
        sum = sum % 10;
        result.push_back(sum);
    } 
    if(carry != 0) {
        result.push_back(carry);
    }
    reverse(result.begin(),result.end());
    return result;
}

// In-Place
vector<int> plusOne(vector<int> &digits) {
      bool carry = true;
      
      for(int i=digits.size()-1; i >= 0 && carry; i--) {
          carry = (++digits[i]%=10) == 0;
      }
      if(carry) {
          digits.insert(digits.begin(), 1);
      }
  
      return digits;
}

vector<int> plusOne(vector<int> &digits) {
      int i,j,carry=1;
      // traditional long addition..
      for(i=digits.size()-1;i>=0&&carry;i--){
          int sum=carry+digits[i];
          carry=sum/10;
          digits[i]=sum%10;
      }
      if(carry){ // if carry is 1, then digits must be all 99..999
          digits[0]=1;
          digits.push_back(0);
      }
      return digits;
}

int main() {
}
