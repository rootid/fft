//Given a non-negative number represented as an array of digits, plus one to
//the number.
//The digits are stored such that the most significant digit is at the head of
//the list.
#include<iostream>
#include<vector>
using namespace std;

//######################################### Only check digit < 9 #########################################
public int[] plusOne(int[] digits) {
    //99 + 1 = 100
    //19 + 1 = 20
    int n = digits.length;
    for(int i=n-1;i>=0;i--) {
        if(digits[i] < 9) {
            digits[i]++;
            return digits;
        }
        digits[i] = 0;
    }
    int[] result = new int[n+1];;
    result[0] = 1;
    return result;
}


//######################################### Only check digit < 9 #########################################
public int[] plusOne(int[] digits) {
    int n = digits.length;
    for(int i=n-1; i>=0; i--) {
        if(digits[i] < 9) {
            digits[i]++;
            return digits;
        }
        digits[i] = 0;
    }
    int[] newNumber = new int [n+1];
    newNumber[0] = 1;
    return newNumber;
}

//######################################### Dumb solution #########################################
public int[] plusOne(int[] digits) {

    //99 + 1 = 1
    int n = digits.length;
    int carry = (digits[n-1] + 1) /10;
    digits[n-1] = (digits[n-1] + 1) % 10;
    for(int i=n-2;i>=0;i--) {
        int cVal = digits[i];
        digits[i] = (carry +  cVal) % 10;
        carry = (carry + cVal)/10;
    }
    if(carry == 0) return digits;
    int[] newDigits = new int[n + 1];
    newDigits[0] = carry;
    for(int i=0;i<n;i++) newDigits[i+1] = digits[i];
    return newDigits;
}


//######################################### Xtra space #########################################
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
