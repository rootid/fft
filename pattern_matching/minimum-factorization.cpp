//Minimum Factorization
//Given a positive integer a, find the smallest positive integer b whose multiplication of each digit equals to a.
//If there is no answer or the answer is not fit in 32-bit signed integer, then return 0.
//Example 1
//Input:
//48 
//Output:
//68
//Example 2
//Input:
//15
//Output:
//35
//
//

//################################################### Start with largest factor 9 and put factors from RHS to LHS ###################################################
//Time complexity : O(8loga). Outer loop will iterate only 8 times, while inner loop takes O(logi) for particular ii.
//Space complexity : O(1). Constant space is used.
int smallestFactorization(int a) {
    if (a < 10) return a;
    long res = 0;
    for (long i = 9, f = 1; i > 1; i--)
        while (a % i == 0) {
            res += i * f;
            if (res > INT_MAX) return 0;
            a /= i;
            f *= 10;
        }
    return a == 1 ? res : 0;
}


public class Solution {
    public int smallestFactorization(int n) {
        // Case 1: If number is smaller than 10
        if (n < 10) return n;
        
        // Case 2: Start with 9 and try every possible digit
        List<Integer> res = new ArrayList<>();
        for (int i = 9; i > 1; i--) {
            // If current digit divides n, then store all
            // occurrences of current digit in res
            while (n % i == 0) {
                n = n / i;
                res.add(i);
            }
        }

        // If n could not be broken in form of digits
        if (n != 1) return 0;

        // Get the result from the array in reverse order
        long result = 0;
        for (int i = res.size() - 1; i >= 0; i--) {
            result = result * 10 + res.get(i);
            if (result > Integer.MAX_VALUE) return 0;
        }
        
        return (int)result;
    }
}

//################################################### Pick / Skip ######################################### 
//Time complexity : O(l). Here l refers to total number of combinations.
//Space complexity : O(log(a)). In worst case, depth of recursion tree can go upto the O(log(a))O(log(a)) .
public class Solution  {
    long ans;
    public int smallestFactorization(int a) {
        if(a < 2)
            return a;
        int[] dig=new int[]{9, 8, 7, 6, 5, 4, 3, 2};
        if (search(dig, 0, a, 1, "") && ans <= Integer.MAX_VALUE)
            return (int)ans;
        return 0;
    }
    public boolean search(int[] dig, int i, int a, long mul, String res) {
        if (mul > a || i == dig.length )
            return false;
        if (mul == a) {
            ans = Long.parseLong(res);
            return true;
        }
		//pick or skip
        return search(dig, i, a, mul * dig[i], dig[i] + res) || search(dig, i + 1, a, mul, res);

		//pick : 99,98,97,96
		//skip : itera over indices (9-2)
    }
}


//######################################### build a long number and stop at the 10th digit ######################################### 
class Solution {
public:
    int smallestFactorization(int a) {
        if (a < 2) return a;
        long l = 0;
        for (int i = 9, d = 0; i >= 2 && d < 10; i--) {
            while (a % i == 0 && d < 10) {
                l += i * pow(10, d++);
                a /= i;
            }
        }
        return a > 1 || l > INT_MAX ? 0 : l;
    }
};

//######################################### build a string and stop at the 10th digit ######################################### 
class Solution {
public:
    int smallestFactorization(int a) {
        if (a < 2) return a;
        string s(10, '0');  // only collect 10 digit, for INT_MAX is 10 digit;
        for (int i = 9, d = 9; i >= 2 && d; i--) {
            while (a % i == 0 && d) {
                s[d--] = '0' + i;
                a /= i;
            }
        }
        return a > 1 || stol(s) > INT_MAX ? 0 : stoi(s);
    }
};

//################################################### build a string all the way to the end ################################################### 
class Solution {
public:
    int smallestFactorization(int a) {
        if (a < 2) return a;
        string s;
        for (int i = 9; i >= 2; i--) {
            while (a % i == 0) {
                s.insert(s.begin(), ('0' + i));
                a /= i;
            }
        }
        return (a > 1 || s.size() > 10 || stol(s) > INT_MAX) ? 0 : stoi(s);
    }
}

//############################################################# python  ############################################################# 
//Suppose N > 1. Let's greedily try to divide N by 9, 8, 7, ..., 2. If we can't divide by some factor here (eg. N = 13) then it's invalid.
//Otherwise, we have some set of digits in descending order whose product equals N. This set is also the smallest possible size (*proof below.) Let's write these digits in sorted order. If it would overflow a 32 bit int, we'll write zero instead.
//Let's prove the set is smallest. If N has factors of 5 or 7, there's only one way to write them. Also, if N = 2^(3w + x) + 3^(2y + z) where 0 <= x < 3 and 0 <= z < 2, then writing 8's and 9's are at least as efficient as optimal. So now we want to write 2^x * 3^z only. If x = 0 or z = 0 we're fine writing 9, 3 or 8, 4, 2. If (x, z) = (1, 1) then we'll write a 6 optimally; if (x, z) = (2, 1) then we'll write 6 * 2 which can't be beaten.
def smallestFactorization(self, N):
    if N == 1:
        return 1
        
    A = []
    while N > 1:
        for d in xrange(9, 1, -1):
            if N % d == 0:
                N /= d
                A.append(d)
                break
        else:
            return 0
    
    ans = int("".join(map(str, A[::-1])))
    return ans if ans < 2**31 else 0
