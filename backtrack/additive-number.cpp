//Additive Number
//Additive number is a string whose digits can form additive sequence.
//A valid additive sequence should contain at least three numbers. Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.
//For example:
//"112358" is an additive number because the digits can form an additive sequence: 1, 1, 2, 3, 5, 8.
//1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
//"199100199" is also an additive number, the additive sequence is: 1, 99, 100, 199.
//1 + 99 = 100, 99 + 100 = 199
//Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.
//Given a string containing only digits '0'-'9', write a function to determine if it's an additive number.
//Follow up:
//How would you handle overflow for very large input integers?

//####################### Backtrack with smart sample set ####################### 
//Choose first two number then recursively check.
//Note that the length of first two numbers can't be longer than half of the initial string, so the two loops in the first function will end when i>num.size()/2 and j>(num.size()-i)/2, this will actually save a lot of time.
//Update the case of heading 0s
//e.g. "100010" should return false
//
bool isAdditiveNumber(string num) {
  int n = num.size();
  for(int i=1; i<=n/2; i++){ 
    for(int j=1; j<=(n-i)/2; j++){ 
      if(check(num.substr(0,i), num.substr(i,j), num.substr(i+j))) 
        return true; 
    }
  }
  return false;
}
bool check(string num1, string num2, string num) { 
    int m = num1.size();
    int n = num2.size();
    if(m>1 && num1[0] == '0' || n>1 && num2[0]=='0') 
        return false;
    long inum1 = atol(num1.c_str());
    long inum2 = atol(num2.c_str());
    long isum = inum1 + inum2;
    string sum = to_string(isum);
    if(sum == num) 
        return true;
    if(num.size() <= sum.size() || sum.compare(num.substr(0,sum.size())) != 0) 
        return false;
    else return check(num2, sum, num.substr(sum.size())); 
} 

//####################### Backtrack with smart sample set ####################### 
bool isAdditiveNumber(string num) {
  int n = num.size();
  for(int i=1; i<=n/2; i++) { 
    for(int j=1; j<=(n-i)/2; j++) { //i/2 + (n-i)/2 = n/2
      if(check(num.substr(0,i), num.substr(i,j), num.substr(i+j))) 
        return true; 
    }
  }
  return false;
}
bool check(string num1, string num2, string num) { 
  int m = num1.size();
  int n = num2.size();
  //Skip strings with leading zeros
  if(m>1 && num1[0] == '0' || n>1 && num2[0]=='0') 
    return false;
  string sum = add(num1, num2);
  if(num == sum) 
    return true;
  if(num.size() <= sum.size() || sum.compare(num.substr(0,sum.size())) != 0) 
    return false;
  else return check(num2, sum, num.substr(sum.size())); 
} 
string add(string n, string m) {
    string res;
    int i=n.size()-1, j=m.size()-1, carry=0;
    while(i>=0 || j>=0){
        int sum = carry+(i>=0 ? (n[i--]-'0') : 0) + (j>=0?  (m[j--]-'0') : 0);
        res.push_back(sum%10+'0');
        carry=sum/10;
    }
    if(carry) res.push_back(carry+'0');
    reverse(res.begin(), res.end());
    return res;
}

//####################### Same Idea with built in function ####################### 
bool check(const string& s, int pos, int len1, int len2) { 
  int start = pos+len1+len2;
  if(start == s.length()) { if(pos==0) return false; return true; }
  int minLen = max(len1, len2);
  if((s[pos]=='0'&&len1>1) || (s[pos+len1]=='0'&&len2>1)) return false;
  long num1 = atol(s.substr(pos, len1).c_str()), num2 = atol(s.substr(pos+len1, len2).c_str());
  if(num1>INT_MAX || num2>INT_MAX) return false;
  for(int l = minLen; l <= (int)s.length()-start; ++l) {
      if(l>1 && s[start]=='0') return false;
      long num3 = atol(s.substr(start, l).c_str());
      if(num3 > num1+num2) return false;
      if(num3==num1+num2 && check(s, pos+len1, len2, l)) return true; 
  }
  return false; 
}
public:
bool isAdditiveNumber(string s) {
    int len = s.length();
    for(int l1 = 1; l1 <= len/2; ++l1)
        for(int l2 = 1; l2 < len-max(l1, l2); ++l2)
            if(check(s, 0, l1, l2)) return true;
    return false;
}
