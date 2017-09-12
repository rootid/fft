import java.util.*;
// Write a method to recursively check whether an equation has a balanced number
// of left and right parentheses and brackets - (including (,),[,],{,}).
// Examples:
// isBalanced("() [] ()") ==> true
// isBalanced("([)]") ==> false
public class CheckBalancedParentheses {

  //### Regex + recursion  ### 
  public static boolean isBalancedGood(String input) {
    if (input == null) return true;
    int originalLength = input.length();
    if (originalLength == 0) return true;
    // Remove all occurences of (), [], or {}.
    input = input.replaceAll("(\\(\\)|\\[\\]|\\{\\})", "");
    if (input.length() == originalLength)  // No change made
      return false;
    return isBalancedGood(input);
  }

  public boolean isBalancedRec(String s) {
    Stack<Character> stack = new Stack<Character>();
    for (char c : s.toCharArray()) {
      if (c == '(')
        stack.push(')');
      else if (c == '{')
        stack.push('}');
      else if (c == '[')
        stack.push(']');
      else if (stack.isEmpty() || stack.pop() != c)
        return false;
    }
    return stack.isEmpty();
  }

  private static boolean isBalancedDFS(String input) {
    return isBalanced(input, 0);
  }

  private static boolean isBalanced(String input, int balance) {
    if (input.length() == 0 && balance == 0) return true;
    if (input.length() == 0) return false;
    char c = input.charAt(0);
    if (c == '(' || c == '[' || c == '{')
      return isBalanced(input.substring(1), balance + 1);
    if (c == ')' || c == ']' || c == '}')
      return isBalanced(input.substring(1), balance - 1);
    return isBalanced(input.substring(1), balance);
  }
}
