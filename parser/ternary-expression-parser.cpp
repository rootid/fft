//Ternary Expression Parser
//Given a string representing arbitrarily nested ternary expressions, calculate
//the result of the expression. You can always assume that the given expression
//is valid and only consists of digits 0-9, ?, :, T and F (T and Frepresent
//True and False respectively).
//Note:
//The length of the given string is ≤ 10000.
//Each number will contain only one digit.
//The conditional expressions group right-to-left (as usual in most languages).
//The condition will always be either T or F. That is, the condition will never
//be a digit.
//The result of the expression will always evaluate to either a digit 0-9, T or
//F.
//Example 1:
//Input: "T?2:3"
//Output: "2"
//Explanation: If true, then result is 2; otherwise result is 3.
//Example 2:
//Input: "F?1:T?4:5"
//Output: "4"
//Explanation: The conditional expressions group right-to-left. Using
//parenthesis, it is read/evaluated as:
//             "(F ? 1 : (T ? 4 : 5))"                   "(F ? 1 : (T ? 4 : 5))"
//          -> "(F ? 1 : 4)"                 or       -> "(T ? 4 : 5)"
//          -> "4"                                    -> "4"
//Example 3:
//Input: "T?T?F:5:3"
//Output: "F"
//Explanation: The conditional expressions group right-to-left. Using
//parenthesis, it is read/evaluated as:
//             "(T ? (T ? F : 5) : 3)"                   "(T ? (T ? F : 5) : 3)"
//          -> "(T ? F : 3)"                 or       -> "(T ? F : 5)"
//          -> "F"                                    -> "F"
//

//######################################### Recursive #########################################
public String parseTernary(String expression) {
    Stack<Character> stack = new Stack<>();
    stack.push(expression.charAt(expression.length() - 1));

    for (int i = expression.length() - 3; i >= 0; i -= 2) {
        if (expression.charAt(i + 1) == '?') {
            char cTrue = stack.pop();
            char cFalse = stack.pop();
            stack.push(expression.charAt(i) == 'T' ? cTrue : cFalse);
        } else {
            stack.push(expression.charAt(i));
        }
    }

    return String.valueOf(stack.peek());
}

//Iterate the expression from tail, whenever encounter a character before '?',
//calculate the right value and push back to stack.
//P.S. this code is guaranteed only if "the given expression is valid" base on
//the requirement.
//######################################### Stack + Iterative  #########################################
public String parseTernary(String expression) {
    if (expression == null || expression.length() == 0) return "";
    Deque<Character> stack = new LinkedList<>();

    //start from rt -> lt
    for (int i = expression.length() - 1; i >= 0; i--) {

        char c = expression.charAt(i);
        if (!stack.isEmpty() && stack.peek() == '?') {

            stack.pop(); //pop '?'
            char first = stack.pop();
            stack.pop(); //pop ':'
            char second = stack.pop();

            if (c == 'T') stack.push(first);
            else stack.push(second);
        } else {
            stack.push(c);
        }
    }

    return String.valueOf(stack.peek());
}


//######################################### Recursive way #########################################
class Solution {
    int idx;
    public String parseTernary(String expression) {
        idx = 0;
        return Character.toString(helper(expression));
    }
    char helper(String s) {
        char ch = s.charAt(idx);
        if (idx + 1 == s.length() || s.charAt(idx + 1) == ':') {
            idx += 2; // pass ':'
            return ch;
        }
        idx += 2; // pass '?'
        char first = helper(s), second = helper(s);
        return ch == 'T' ? first : second;
    }
}

//######################################### Recursive way #########################################
public class Solution {
    public String parseTernary(String expression) {
        if(expression == null || expression.length() == 0){
            return expression;
        }
        char[] exp = expression.toCharArray();

        return DFS(exp, 0, exp.length - 1) + "";

    }
    public char DFS(char[] c, int start, int end){
        if(start == end){
            return c[start];
        }
        int count = 0, i =start;
        for(; i <= end; i++){
            if(c[i] == '?'){
                count ++;
            }else if (c[i] == ':'){
                count --;
                if(count == 0){
                    break;
                }
            }
        }
        return c[start] == 'T'? DFS(c, start + 2, i - 1) : DFS(c, i+1,end);
    }
}

//######################################### Recursive way #########################################
public String parseTernary(String expression) {
        if (expression.length()==1) return expression;
        int i=1, count=1;
        while (count !=0){
            char c=expression.charAt(++i);
            count += c=='?' ? 1: c==':'? -1: 0;
        }
        return expression.charAt(0) == 'T'? parseTernary(expression.substring(2,i)): parseTernary(expression.substring(i+1));
    }
