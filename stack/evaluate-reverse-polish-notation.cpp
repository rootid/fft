//Evaluate Reverse Polish Notation
//Evaluate the value of an arithmetic expression in Reverse Polish Notation.
//Valid operators are +, -, *, /. Each operand may be an integer or another
//expression.
//Some examples:
//  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
//  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
#include "../headers/global.hpp"

int evalRPN(vector<string>& tokens) {

     stack<int> sol_stack;
     int sign = 1;
     for(auto st:tokens) {
         if(st[0] >= '0' || (st.size() > 1 && st[1] >= '0') ) {
             int num = 0;
             for(auto c : st) {
                 if(c == '-') {
                     sign = -1;
                     continue;
                 }
                 num = num*10  + (c - '0');
             }
             num = num * sign;
             sign = 1;
             sol_stack.push(num);
         } else {
             int b = sol_stack.top();
             sol_stack.pop();
             int a = sol_stack.top();
             sol_stack.pop();
             int result;
             if(st[0] == '+') {
                 result = a + b;
             } else if(st[0] == '-') {
                 result = a - b;
             } else if(st[0] == '*') {
                 result = a * b;
             }else if(st[0] == '/') {
                 result = a / b;
             }
             sol_stack.push(result);
         }

     }
     if(sol_stack.empty()) {
         return 0;
     }
     return sol_stack.top();
 }
int main() {
    //how to deal with overflow errors?
    //how to deal with divide by zero?
    vector<string> tokens( {"18"} );
    vector<string> tokens( {"3","-4","+"} );
    evalRPN(tokens);
}
