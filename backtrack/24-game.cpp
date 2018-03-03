//24 Game
//You have 4 cards each containing a number from 1 to 9. You need to judge
//whether they could operated through *, /, +, -, (, ) to get the value of 24.
//Example 1:
//Input: [4, 1, 8, 7]
//Output: True
//Explanation: (8-4) * (7-1) = 24
//Example 2:
//Input: [1, 2, 1, 2]
//Output: False
//Note:
//1. The division operator / represents real division, not integer division. For
//example, 4 / (1 - 2/3) = 12.  2. Every operation done is between two numbers.
//In particular, we cannot use - as a unary operator. For example, with [1, 1,
//1, 1] as input, the expression -1 - 1 - 1 - 1 is not allowed.
//You cannot concatenate numbers together. For example, if the input is [1, 2,
//1, 2], we cannot write this as 12 + 12.
//Use python 3

//######################################### Backtrack #########################################
class Solution {

    boolean res = false;
    final double eps = 0.001;

    public boolean judgePoint24(int[] nums) {
        List<Double> arr = new ArrayList<>();
        for(int n: nums) arr.add((double) n);
        helper(arr);
        return res;
    }

    private void helper(List<Double> arr){
        if(res) return;
        if(arr.size() == 1){
            if(Math.abs(arr.get(0) - 24.0) < eps)
                res = true;
            return;
        }
        for (int i = 0; i < arr.size(); i++) {
            for (int j = 0; j < i; j++) {
                List<Double> next = new ArrayList<>();
                Double p1 = arr.get(i), p2 = arr.get(j);
                next.addAll(Arrays.asList(p1+p2, p1-p2, p2-p1, p1*p2));
                if(Math.abs(p2) > eps)  next.add(p1/p2);
                if(Math.abs(p1) > eps)  next.add(p2/p1);

                arr.remove(i);
                arr.remove(j);
                for (Double n: next){
                    arr.add(n);
                    helper(arr);
                    arr.remove(arr.size()-1);
                }
                arr.add(j, p2);
                arr.add(i, p1);
            }
        }
    }
}

//######################################### Backtrack #########################################
def judgePoint24(self, nums):
    if len(nums) == 1:
        return math.isclose(nums[0], 24)
    return any(self.judgePoint24([x] + rest)
               for a, b, *rest in itertools.permutations(nums)
               for x in {a+b, a-b, a*b, b and a/b})

//Just go through all pairs of numbers a and b and replace them with a+b, a-b, a*b and a/b, . Use recursion for the now smaller list. Positive base case is the list being [24] (or close enough).
//I prevent division-by-zero by using b and a/b instead of just a/b. If b is zero, then b and a/b is zero. And it's ok to have that zero, since a*b is zero as well. It's not even a second zero, because I'm creating a set of the up to four operation results, so duplicates are ignored immediately.
//Oh and note that I'm using Python 3, so / is "true" division, not integer division like in Python 2. And it would be better to use fractions.Fraction instead of floats. I actually just realized that there is in fact an input where simple floats fail, namely [3, 3, 8, 8]. Floats calculate 23.999999999999989341858963598497211933135986328125 instead of 24. It's not in the judge's test suite, but it should be soon (Edit: it now is). Using Fraction however made my solution exceed the time limit, so I settled for the above approximation solution.

//In the top call I go through 4!=24 permutations and thus 24 recursive calls instead of just 4*3=12. But it gets accepted in about 440 ms, so that's not a problem.
//I also wrote a version that prevents those duplicates and more, it gets accepted in about 160 ms:
//######################################### Avoid duplicates #########################################
def judgePoint24(self, nums):
    if len(nums) == 1:
        return math.isclose(nums[0], 24)
    return any(map(self.judgePoint24,
                   {tuple(sorted([x] + rest))
                    for a, b, *rest in itertools.permutations(nums)
                    for x in (a+b, a-b, a*b, b and a/b)}))
//Another version, using global memoization (i.e., across all test cases), fast enough to use Fraction (gets accepted in about 750 ms):

//######################################### Memoization #########################################
from functools import lru_cache as memoize
from fractions import Fraction

class Solution:
    def judgePoint24(self, nums):
        return judge(tuple(sorted(nums)))

@memoize(None)
def judge(nums):
    if len(nums) == 1:
        return 24 in nums
    return any(map(judge,
                   {tuple(sorted([x] + rest))
                    for a, b, *rest in itertools.permutations(nums)
                    for x in (a+b, a-b, a*b, b and Fraction(a, b))}))

//######################################### Backtrack #########################################
bool judgePoint24(vector<int>& nums){ return judge24({nums.begin(), nums.end()}); }

static bool judge24(vector<double> nums) {
    auto n = nums.size();
    if(n == 1) return abs(nums[0] - 24) < 1e-10;

    sort(nums.begin(), nums.end());
    // For each permutation,
    do {
        // merge the last two numbers.
        vector<double> temp(nums.begin(), nums.end()-1);
        auto a = nums[n-1], b = nums[n-2];
        for(auto num: {a+b, a-b, a*b, a?b/a:0}){
            // For each merged number, combine with the rest and test it
            temp.back() = num;
            if(judge24(temp)) return true;
        }
    } while(next_permutation(nums.begin(), nums.end()));

    return false;
}

//######################################### Python functional #########################################
//We write a function apply that takes two sets of possibilities for A and B and returns all possible results operator(A, B) or operator(B, A) for all possible operators.
//Ignoring reflection, there are only two ways we can apply the operators: (AB)(CD) or ((AB)C)D. When C and D are ordered, this becomes three ways - the third way is ((AB)D)C.
//This solution is a little slow because it has to manage sets - my article has a solution that is almost 10x faster. I think this one is cool though.
//https://leetcode.com/articles/24-game/

def judgePoint24(self, nums):
    from operator import truediv, mul, add, sub
    from fractions import Fraction

    def apply(A, B):
        ans = set()
        for x, y, op in itertools.product(A, B, (truediv, mul, add, sub)):
            if op is not truediv or y: ans.add(op(x, y))
            if op is not truediv or x: ans.add(op(y, x))
        return ans

    A = [{x} for x in map(Fraction, nums)]
    for i, j in itertools.combinations(range(4), 2):
        r1 = apply(A[i], A[j])
        k, l = {0, 1, 2, 3} - {i, j}
        if 24 in apply(apply(r1, A[k]), A[l]): return True
        if 24 in apply(apply(r1, A[l]), A[k]): return True
        if 24 in apply(r1, apply(A[k], A[l])): return True

    return False

//######################################### Python #########################################
//Use itertools.permutations to generate all the possible operands and operators to form an array of length 7, representing an equation of 4 operands and 3 operators.
//The possible function tries to evaluate the equation with different combinations of brackets, terminating as soon as an equation evaluates to 24. Each time evaluate is called, it reduces the length of the equation by 2, as it takes a triplet (operand, operator, operand) and evaluates into a value.
//Compare the final result of the equation with a small delta because of floating point inaccuracies.
class Solution(object):
    def judgePoint24(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        import itertools
        TARGET = 24
        EQN_LEN = 3 # (Operand, Operator, Operand) triplet.
        # Generate all possible number sequences. Convert to float string so that
        # division does not result in truncation.
        number_orders = set(tuple(itertools.permutations([str(num) + '.0' for num in nums])))
        # Generate all possible operator sequences.
        operator_orders = set(tuple(itertools.permutations('***///+++---', len(nums) - 1)))

        # Evaluate an equation with different permutation of brackets
        # and return True if any of them evaluate to the target.
        def possible(equation):
            found = [False]
            def evaluate(eqn):
                # Reduces an equation by length 2 each time:
                # An equation of ['1.0', '*', '2.0', '+', '3.0', '/', '4.0'] becomes:
                # - [2.0', '+', '3.0', '/', '4.0'] (1.0 * 2.0 reduced to 2.0)
                # - [1.0', '*', '5.0', '/', '4.0'] (2.0 + 3.0 reduced to 5.0)
                # - [1.0', '*', '2.0', '+', '0.75'] (3.0 / 4.0 reduced to 0.75)
                if found[0]:
                    return
                if len(eqn) == EQN_LEN:
                    val = eval(''.join(eqn))
                    # Compare against a delta because of floating point inaccuracies.
                    if abs(val - TARGET) < 0.0001:
                        found[0] = True
                    return
                # Recursively try different permutations
                # of operands + operators triplets, simulating brackets.
                for i in range(0, len(eqn) - 1, 2):
                    try:
                        # Wrap in try/except as there can be a division by 0 error.
                        evaluate(eqn[:i] + [str(eval(''.join(eqn[i:i + EQN_LEN])))] + eqn[i + EQN_LEN:])
                    except:
                        pass
            evaluate(equation)
            return found[0]

        for number_order in number_orders:
            for operator_order in operator_orders:
                equation = [None] * (len(number_order) + len(operator_order))
                for i, number in enumerate(number_order):
                    equation[0 + i * 2] = number
                for i, operator in enumerate(operator_order):
                    equation[1 + i * 2] = operator
                # Generate an equation to test whether it is possible to get 24 using it.
                # Example equation: ['1.0', '*', '2.0', '+', '3.0', '/', '4.0']
                if possible(equation):
                    return True
        return False

//######################################### BT #########################################
 bool flag=false;
    bool judgePoint24(vector<int>& nums) {
        vector<double> ns;
        for(int i=0;i<nums.size();i++) ns.push_back(nums[i]);
        BT(ns);
        return flag;
    }

    void BT(vector<double> ns) {
        if(flag) return;
        if(ns.size()==1&&abs(ns[0]-24.0)<0.001) flag=true;
        for(int i=0;i<ns.size();i++) {
            for(int j=0;j<ns.size();j++) {
                if(i==j) continue;
                vector<double> t=ns;
                double a=t[i], b=t[j], p=min(i, j);
                if(i<j) t.erase(t.begin()+j);
                else t.erase(t.begin()+i);
                t[p]=a+b;
                BT(t);
                t[p]=a-b;
                BT(t);
                t[p]=a*b;
                BT(t);
                if(b==0) continue;
                t[p]=a/b;
                BT(t);
            }
        }
    }

//######################################### BT #########################################
//we can find all the permutation of the input array, then for each permutation we can evaluate the result from left to right or half and half.
//
//the complexity would be O(4! * 6^3), where 4! is number of all permutation, and two number can have 6 operation result, 4 number have 3 operations. After all, we cannot call it O(1). Should be O(n! * 6^(n-1)).
class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        return perm(nums, 0);
    }

    bool perm(vector<int>& nums, int idx)
    {
        if(idx == 3)
            return leftRight(nums) || halfHalf(nums);
        for(int j = idx; j < 4; j++)
        {
            if(j > idx && nums[j] == nums[idx]) continue;
            swap(nums[j], nums[idx]);
            if(perm(nums, idx+1)) return true;
            swap(nums[j], nums[idx]);
        }
        return false;
    }

    bool leftRight(vector<int>& nums)
    {
        unordered_set<double> val1, val2;
        val1 = getVal(nums[0], nums[1]);
        for(auto e : val1)
        {
            unordered_set<double> tmp = getVal(e, nums[2]);
            val2.insert(tmp.begin(), tmp.end());
        }
        for(auto e : val2)
        {
            unordered_set<double> tmp = getVal(e, nums[3]);
            for(auto e : tmp)
                if(e == 24)
                    return true;
        }
        return false;
    }

    bool halfHalf(vector<int>& nums)
    {
        unordered_set<double> val1 = getVal(nums[0], nums[1]);
        unordered_set<double> val2 = getVal(nums[2], nums[3]);
        for(auto e : val1)
        {
            for(auto f : val2)
            {
                unordered_set<double> tmp = getVal(e, f);
                for(auto e : tmp)
                    if(e == 24)
                        return true;
            }
        }
        return false;
    }

    unordered_set<double> getVal(double n1, double n2)
    {
        return unordered_set<double>{n1+n2, n1*n2, n1-n2, n2-n1, n1/(n2?n2:1), n2/(n1?n1:1)};
    }
};

//######################################### BT #########################################
    def judgePoint24(self, nums):
        def f(s1, s2):
            res = []
            for a in s1:
                for b in s2:
                    res.append('(' + a + '+' + b + ')')
                    res.append('(' + a + '-' + b + ')')
                    res.append('(' + b + '-' + a + ')')
                    res.append(a + '*' + b)
                    res.append(a + '/' + b)
                    res.append(b + '/' + a)
            return res

        nums = [str(float(i)) for i in nums]
        for c in itertools.permutations(nums):
            eq1 = f(f(f([c[0]], [c[1]]), [c[2]]), [c[3]])
            eq2 = f(f([c[0]], [c[1]]), f([c[2]], [c[3]]))
            for eq in eq1 + eq2:
                try:
                    if 23.9 <= eval(eq) <= 24.1:
                        print eq.replace(".0", "")
                        return True
                except:
                    pass
        return False
