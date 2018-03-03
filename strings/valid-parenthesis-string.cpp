//Valid Parenthesis String
//Given a string containing only three types of characters: '(', ')' and '*',
//write a function to check whether this string is valid. We define the
//validity of a string by these rules:
//Any left parenthesis '(' must have a corresponding right parenthesis ')'.
//Any right parenthesis ')' must have a corresponding left parenthesis '('.
//Left parenthesis '(' must go before the corresponding right parenthesis ')'.
//'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
//An empty string is also valid.
//Example 1:
//Input: "()"
//Output: True
//Example 2:
//Input: "(*)"
//Output: True
//Example 3:
//Input: "(*))"
//Output: True
//Note:
//The string size will be in the range [1, 100].
//


//######################################### FSM #########################################
// -ve cases leads to invalid path
// 0 leads to valid path
// +ve cases optimistic path
 public boolean checkValidString(String s) {
        int low = 0;
        int high = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '(') {
                low++;
                high++;
            } else if (s.charAt(i) == ')') {
                if (low > 0) {
                    low--;
                }
                high--;
            } else {
                if (low > 0) { // if low is 0 then * is don't care
                    low--;
                }
                high++;
            }
            if (high < 0) {
                return false;
            }
        }
        return low == 0;
    }

//When the character is '*', there are three cases, ‘(’, empty, or ‘)’, we can
//think those three cases as three branches in the ongoing route.
//Take “(**())” as an example. There are 6 chars:
//----At step 0: only one count = 1.
//----At step 1: the route will be diverted into three branches.
//so there are three counts: 1 - 1, 1, 1 + 1 which is 0, 1, 2, for ‘)’, empty
//and ‘(’ respectively.
//----At step 2 each route is diverged into three routes again. so there will be 9 possible routes now.
//--	For count = 0, it will be diverted into 0 – 1, 0, 0 + 1, which is -1, 0, 1, but when the count is -1, that means there are more ‘)’s than ‘(’s, and we need to stop early at that route, since it is invalid. we end with 0, 1.
//--	For count = 1, it will be diverted into 1 – 1, 1, 1 + 1, which is 0, 1, 2
//--	For count = 2, it will be diverted into 2 – 1, 2, 2 + 1, which is 1, 2, 3
//To summarize step 2, we end up with counts of 0,1,2,3
//----At step 3, increment all counts --> 1,2,3,4
//----At step 4, decrement all counts --> 0,1,2,3
//----At step 5, decrement all counts --> -1, 0,1,2, the route with count -1 is invalid, so stop early at that route. Now we have 0,1,2.
//In the very end, we find that there is a route that can reach count == 0.
//Which means all ‘(’ and ‘)’ are cancelled. So, the original String is valid.


//######################################### Backtracking #########################################
//1. How to check valid parenthesis w/ only ( and )? Easy. Count each char from
//left to right. When we see (, count++; when we see ) count--; if count < 0,
//it is invalid () is more than (); At last, count should == 0.
//2. This problem added *. The easiest way is to try 3 possible ways when we
//see it. Return true if one of them is valid.
class Solution {
    public boolean checkValidString(String s) {
        return check(s, 0, 0);
    }

    private boolean check(String s, int start, int count) {
        if (count < 0) return false;

        for (int i = start; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '(') {
                count++;
            }
            else if (c == ')') {
                if (count <= 0) return false;
                count--;
            }
            else if (c == '*') {
                return check(s, i + 1, count + 1) || check(s, i + 1, count - 1) || check(s, i + 1, count);
            }
        }

        return count == 0;
    }
}


//######################################### Backtrack #########################################
//backtracking solution using recursion with focus on simple readability, which
//was inspired by this Java solution. Base case is when the index equals the
//size of the string. This occurs when the entire string has been completely
//processed. When the base case is reached, if the count of remaining open
//parens without a corresponding close paren is equal to 0, then return true,
//otherwise return false. The ongoing count of open parens is continually
//processed for each index of the string from left-to-right. Whenever an open
//paren ( is found, the count of open parens is incremented by 1. Likewise,
//whenever a close paren ) is found, the count of open parens in decremented by
//1. If the ongoing count of open parens is less than 0, then we know there are
//too many close parens, and return false immediately. Whenever a * occurs in
//the string, this is processed by checking each of 3 possibilities:
//
//the * as a ( ==> this is processed by incrementing the ongoing open count by
//1: open+1
//the * as a ) ==> this is processed by decrementing the ongoing open count by
//1: open-1
//the * as a ""(empty string) ==> this is processed by keeping the ongoing
//count of open "as is" without changing the value
//Continue processing the string for each of these possibilities. If at least
//one of these three possibilities results in a valid string, then return true,
//otherwise return false.

class Solution{
public:
    bool checkValidString(string s){
        return helper(s, 0, 0);
    }

    bool helper(const string& s, int index, int open){
        if (index==s.size()){return open==0;}
        if (s[index]=='('){
            ++open;
        } else if (s[index]==')'){
            if (--open<0){return false;}
        } else {
            return helper(s,index+1,open+1) || helper(s,index+1,open-1) || helper(s,index+1,open);
        }
        return helper(s,index+1,open);
    }
};
//My original solution ended up iteratively traversing the string twice
//(left-to-right followed by right-to-left). Originally, I didn't expect to
//have to traverse the string backwards, until I failed the test case
//"(())((())()()()(()(())())())()()((()())((()))(*". At which point, I hacked
//this solution to check the reverse string as well:

//############################### FSM ###############################
//The number of open parenthesis is in a range [cmin, cmax]
//cmax counts the maximum open parenthesis, which means the maximum number of
//unbalanced '(' that COULD be paired.
//cmin counts the minimum open parenthesis, which means the number of
//unbalanced '(' that MUST be paired.
//The string is valid for 2 condition:
//cmax will never be negative.
//cmin is 0 at the end.
def checkValidString(self, s):
        cmin = cmax = 0
        for i in s:
            if i == '(':
                cmax += 1
                cmin += 1
            if i == ')':
                cmax -= 1
                cmin = max(cmin - 1, 0)
            if i == '*':
                cmax += 1
                cmin = max(cmin - 1, 0)
            if cmax < 0:
                return False
        return cmin == 0

//############################### FSM ###############################
def checkValidString(self, s):
        cmin = cmax = 0
        for i in s:
            cmax = cmax-1 if i==")" else cmax+1
            cmin = cmin+1 if i=='(' else max(cmin - 1, 0)
            if cmax < 0: return False
        return cmin == 0

//######################################### 2-Pass solution #########################################
class Solution {
public:
    bool checkValidString(string s) {
        for (int i = 0, cnt = 0, star = 0; i < n; i++) {
            if (s[i] == '(')
                cnt++;
            else if (s[i] == '*')
                star++;
            else {
                if (cnt == 0 && star == 0) return false;
                if (cnt)
                    cnt--;
                else
                    star--;
            }
        }
        for (int i = n-1, cnt = 0, star = 0; i >= 0; i--) {
            if (s[i] == ')')
                cnt++;
            else if (s[i] == '*')
                star++;
            else {
                if (cnt == 0 && star == 0) return false;
                if (cnt)
                    cnt--;
                else
                    star--;
            }
        }
        return true;
    }
};
