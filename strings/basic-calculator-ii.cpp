//Basic Calculator II
//Implement a basic calculator to evaluate a simple expression string.
//The expression string contains only non-negative integers, +, -, *, /
//operators and empty spaces . The integer division should truncate toward
//zero.
//You may assume that the given expression is always valid.
//Some examples:
//"3+2*2" = 7
//" 3/2 " = 1
//" 3+5 / 2 " = 5
//Note: Do not use the eval built-in library function.

//########################################################### Linear traversal and evaluate  ###########################################################
int nextNum(string &s, int &i) {
  int num = 0;
  int len = s.size();
  for (;i<len; i++) {
    if(isspace(s[i])) {
      continue;
    } else if (s[i] >='0' && s[i] <= '9') {
      num = num*10 + s[i]-'0';
    } else {
      break;
    }
  }
  return num;
}

//3+4+9*4 = 43
int calculate(string s) {
    int i = 0;
    int result = 0; //store the +/- result
    int cur = nextNum(s, i); //store current elem and *|/ result
    char last_op = ' ';
    int len = s.length();
    while (i != len) {
        if (s[i] == '*') { //* and / have higher precedence than + and -
          cur *= nextNum(s, ++i);
        } else if (s[i] == '/') {
          cur /= nextNum(s, ++i);
        } else if (last_op == '+') {
          result += cur, last_op=s[i], cur = nextNum(s, ++i);
        } else if (last_op == '-') {
          result -= cur, last_op=s[i], cur = nextNum(s, ++i);
        } else {
          result = cur, last_op = s[i], cur = nextNum(s, ++i); //store +/- and get the next number //3+2*4
        }
    }
    if (last_op == ' ') {
      return cur;
    } else if (last_op == '+') {
      return result+cur;
    }
    return result-cur;
}
