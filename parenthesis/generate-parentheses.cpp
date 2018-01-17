//Generate Parentheses
//Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
//For example, given n = 3, a solution set is:
//[
//  "((()))",
//  "(()())",
//  "(())()",
//  "()(())",
//  "()()()"
//]
//

//T(n) = 2T(n-1)
//#########################################  Backtrack pruning #########################################  
class Solution {
    List<String> result = new ArrayList<>();
    public List<String> generateParenthesis(int n) {
        char[] curr = new char[2*n];
        generateParenthesisHelper(n,n,curr,0);
        return result;
    }
    private void generateParenthesisHelper(int left, int right, char[] curr,int k) {
        if(left == right && left == 0) {
            result.add(new String(curr)); 
            return;
        }      
        if(left > 0) {
            curr[k] = '(';
            generateParenthesisHelper(left-1,right, curr,k+1);
        }
        if(right > left) { 
            curr[k] = ')';
            generateParenthesisHelper(left,right-1, curr,k+1);
        }
    }
}

//CFG grammar : S -> S(S) | empty
//#########################################
public List<String> ans(int n) {				
	List<String> parens = new ArrayList<String>();  
	if (n == 0) parens.add(""); //base case
	else { // recursive case
		for (int i = 0; i < n; i++){
			for ( String front:ans(i))
				for (String back:ans(n-i-1)) 
					parens.add( front + 
							      "(" +  
							     back + 
							       ")");
		}
	}
	return parens;
}

//######################################### Recursive ######################################### 
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ret;
        helper(ret, "", n, n);
        return ret;
    }
    void helper(vector<string> & res, string str, int left, int right){
        if(left == 0 && right == 0){
            res.push_back(str);
            return;
        }
        if(left > 0) helper(res, str + "(", left - 1, right);
        if(right > left) helper(res, str + ")", left, right - 1);
    }
};


//######################################### Recursive : List ######################################### 
//For 2, it should place one "()" and add another one insert it but none tail it,
//'(' f(1) ')' f(0)
//or add none insert it but tail it by another one,
//'(' f(0) ')' f(1)
//Thus for n, we can insert f(i) and tail f(j) and i+j=n-1,
//'(' f(i) ')' f(j)

public List<String> generateParenthesis(int n) {
	List<String> result = new ArrayList<String>();
	if (n == 0) {
		result.add("");
	} else {
		for (int i = n - 1; i >= 0; i--) {
			List<String> insertSub = generateParenthesis(i);
			List<String> tailSub = generateParenthesis(n - 1 - i);
			for (String insert : insertSub) {
				for (String tail : tailSub) {
					result.add("(" + insert + ")" + tail);
				}
			}

		}
	}
	return result;
}


//######################################### Recursive : Stringbuilder ######################################### 
public List<String> generateParenthesis(int n) {
     List<String> res = new ArrayList<>();
     helper(res, new StringBuilder(), 0, 0, n);
     return res;
}

private void helper(List<String> res, StringBuilder sb, int left, int right, int n) {
    if(left == n && right == n) {
        res.add(sb.toString());
        return;
    }
    if(left < n) {
        sb.append("(");
        helper(res, sb, left+1, right, n);
        sb.setLength(sb.length()-1);
    } 
    if(right < left) {
        sb.append(")");
        helper(res, sb, left, right+1, n);
        sb.setLength(sb.length()-1);
    }
}

//######################################### Iterative ######################################### 
//f(n) = (f(0))f(n-1) + (f(1))f(n-2) + ... + (f(n-2))f(1) + (f(n-1))f(0)
//
public List<String> generateParenthesis(int n) { 
    List<List<String>> lists = new ArrayList<>();
    lists.add(Collections.singletonList(""));
    for (int i = 1; i <= n; ++i) {
        final List<String> list = new ArrayList<>();
        for (int j = 0; j < i; ++j) {
            for (final String first : lists.get(j)) {
                for (final String second : lists.get(i - 1 - j)) {
                    list.add("(" + first + ")" + second);
                }
            }
        }
        lists.add(list);
    } 
	return lists.get(lists.size() - 1); 
}

//######################################### BFS O(n^2) ######################################### 
public List<String> generateParenthesis(int n) { 
	LinkedList<String> queueBracket = new LinkedList<>(); 
	queueBracket.add("(");
	// 0 means # of left brackets; 1 means # of right brackets
	LinkedList<List<Integer>> queueBracketNum = new LinkedList<>();
	queueBracketNum.add(Arrays.asList(new Integer[]{1, 0}));

	for (int i = 1; i <= n * 2 - 1; i++) { //total # of parenthesis
		while (queueBracket.peek().length() == i) {
			String bracket = queueBracket.remove();
			List<Integer> bracketNum = queueBracketNum.remove();
			if (bracketNum.get(0) < n) {
				queueBracket.add(bracket + "(");
				queueBracketNum.add(Arrays.asList(new Integer[]{bracketNum.get(0) + 1, bracketNum.get(1)}));
			}
			if (bracketNum.get(0) > bracketNum.get(1) && bracketNum.get(1) < n) {
				queueBracket.add(bracket + ")");
				queueBracketNum.add(Arrays.asList(new Integer[]{bracketNum.get(0), bracketNum.get(1) + 1}));
			}
		}
	} 
	return queueBracket;
}

//######################################### Iterative : python ######################################### 
class Solution(object):
def generateParenthesis(self, n):
    """
    :type n: int
    :rtype: List[str]
    """
    
    comp_list = [['']]
    
    for i in range(1,n+1):
        res = []
        
        for j in range(i):
            for left in comp_list[i-1-j]:
                for right in comp_list[j]:
                    res.append( '(' + left + ')' + right)
        comp_list.append(res)
    return comp_list[-1]
//######################################### Backtracking  ######################################### 
//p is the parenthesis-string built so far, left and right tell the number of left and right parentheses still to add, and parens collects the parentheses.
def generateParenthesis(self, n):
    def generate(p, left, right, parens=[]):
        if left:         generate(p + '(', left-1, right)
        if right > left: generate(p + ')', left, right-1)
        if not right:    parens += p,
        return parens
    return generate('', n, n)

//######################################### yield + python 3 ######################################### 
//put the yield q at the end of the line because it's not that bad and because in "real life" I use Python 3 where I just say yield from generate(...).
def generateParenthesis(self, n):
    def generate(p, left, right):
        if right >= left >= 0:
            if not right:
                yield p
            for q in generate(p + '(', left-1, right): yield q
            for q in generate(p + ')', left, right-1): yield q
    return list(generate('', n, n))

//######################################### optimized ######################################### 
//Parameter open tells the number of "already opened" parentheses, and I continue the recursion 
//as long as I still have to open parentheses (n > 0) and I haven't made a mistake yet (open >= 0).

def generateParenthesis(self, n, open=0):
    if n > 0 <= open:
        return ['(' + p for p in self.generateParenthesis(n-1, open+1)] + \
               [')' + p for p in self.generateParenthesis(n, open-1)]
    return [')' * open] * (not n)

//######################################### optimized ######################################### 
def generateParenthesis(self, n, left=0, right=0, cur=''):
        if left == n: return [cur + ')' * (n - right)]
        if left == right: return self.generateParenthesis(n, left + 1, right, cur + '(')
        return self.generateParenthesis(n, left + 1, right, cur + '(') \
            + self.generateParenthesis(n, left, right + 1, cur + ')')
