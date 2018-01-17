//Basic Calculator
//Implement a basic calculator to evaluate a simple expression string.
//The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .
//You may assume that the given expression is always valid.
//Some examples:
//"1 + 1" = 2
//" 2-1 + 2 " = 3
//"(1+(4+5+2)-3)+(6+8)" = 23
//Note: Do not use the eval built-in library function.

//############################### Traverse from R-L ############################### 
int calculate(string s) {
    stack<int> operands;
    stack<char> operations;
    string operand;
    //traverse from R-L
    for (int i = (int)s.length() - 1; i >= 0; i--) {
        if (s[i] == ')' || s[i] == '+' || s[i] == '-')
            operations.push(s[i]);
        else if (isdigit(s[i])) {
            operand = s[i] + operand; //add current char as a prefix to existing operand
            if (!i || !isdigit(s[i - 1])) {
                operands.push(stoi(operand));
                operand.clear(); //clean the operand to store the next operand
            }
        } else if (s[i] == '(') { //evaluate the inner operation first
            while (operations.top() != ')') {
                compute(operands, operations);
            }
            //remove ')'
            operations.pop();
        }
    }
    while (!operations.empty())
        compute(operands, operations);
    return operands.top();
}

void compute(stack<int>& operands, stack<char>& operations) {
    int left = operands.top();
    operands.pop();
    int right = operands.top();
    operands.pop();
    int op = operations.top();
    operations.pop();
    if (op == '+') operands.push(left + right);
    if (op == '-') operands.push(left - right);
} 


//############################### sign stack evaluation ############################### 
//  remaining   sign stack      total
//3-(2+(9-4))   [1, 1]            0 
// -(2+(9-4))   [1]               3 //if \d+ remove sign from top
//  (2+(9-4))   [1, -1]           3 //if - add inverted sign to top
//   2+(9-4))   [1, -1, -1]       3 //if ( add sign to top
//    +(9-4))   [1, -1]           1
//     (9-4))   [1, -1, -1]       1 //if + add sign to top
//      9-4))   [1, -1, -1, -1]   1
//       -4))   [1, -1, -1]      -8
//        4))   [1, -1, -1, 1]   -8
//         ))   [1, -1, -1]      -4
//          )   [1, -1]          -4
//              [1]              -4
int calculate(string s) { 
  int total = 0;
  vector<int> signs(2, 1);
  for (int i=0; i<s.size(); i++) { 
    char c = s[i];
    if (c >= '0') {
        int number = 0;
        while (i < s.size()  &&  s[i] >= '0') {
            number = 10 * number + s[i++] - '0';
        }
        //evaluate the result + remove the last element from sign
        total += signs.back() * number;
        signs.pop_back();
        i--;
    } else if (c == ')') {
        //remove the last element from sign
        signs.pop_back();
    } else if (c != ' ') {
        //copy + add the sign + if(-) change the sign
        signs.push_back(signs.back() * (c == '-' ? -1 : 1));
    }
  }
  return total;
}

