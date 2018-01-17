//Multiply Strings
//Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2.
//Note:
//The length of both num1 and num2 is < 110.
//Both num1 and num2 contains only digits 0-9.
//Both num1 and num2 does not contain any leading zero.
//You must not use any built-in BigInteger library or convert the inputs to integer directly.
//


//num1[i] * num2[j]` will be placed at indices `[i + j`, `i + j + 1]` 
//####################### Iterative O(n^2) ####################### 
string multiply(string num1, string num2) {
 string result;
  int m = num1.size(), n = num2.size();
  vector<int> rIdx(m+n,0);
  for(int i = m - 1; i >= 0; i--) {
      for(int j = n - 1; j >= 0; j--) {
          int mul = (num1[i] - '0') * (num2[j] - '0'); 
          //Result always between startIdx and endIdx
          int startIdx = i + j, endIdx = i + j + 1;
          int sum = mul + rIdx[endIdx];
          rIdx[startIdx] += sum / 10;
          rIdx[endIdx] = (sum) % 10;
      }
  }  
  for(auto p: rIdx) {
    if(!(result.size() == 0 && p == 0)) {
      result.push_back(p + '0');
    }
  }
  return result.size() == 0 ? "0" : result; 
}


//####################### Iterative O(n^2) ####################### 
string multiply(string num1, string num2) {
    string sum(num1.size() + num2.size(), '0');
    
    for (int i = num1.size() - 1; 0 <= i; --i) {
        int carry = 0;
        for (int j = num2.size() - 1; 0 <= j; --j) {
            int tmp = (sum[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0') + carry;
            sum[i + j + 1] = tmp % 10 + '0';
            carry = tmp / 10;
        }
        sum[i] += carry;
    }
    
    size_t startpos = sum.find_first_not_of("0");
    if (string::npos != startpos) {
        return sum.substr(startpos);
    }
    return "0";
}
