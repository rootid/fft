//Bulb Switcher II
//There is a room with n lights which are turned on initially and 4 buttons on the wall. After performing exactly m unknown operations towards buttons, you need to return how many different kinds of status of the n lights could be.
//Suppose n lights are labeled as number [1, 2, 3 ..., n], function of these 4 buttons are given below:
//Flip all the lights.
//Flip lights with even numbers.
//Flip lights with odd numbers.
//Flip lights with (3k + 1) numbers, k = 0, 1, 2, ...
//Example 1:
//Input: n = 1, m = 1.
//Output: 2
//Explanation: Status can be: [on], [off]
//Example 2:
//Input: n = 2, m = 1.
//Output: 3
//Explanation: Status can be: [on, off], [off, on], [off, off]
//Example 3:
//Input: n = 3, m = 1.
//Output: 4
//Explanation: Status can be: [off, on, off], [on, off, on], [off, off, off], [off, on, on].
//Note: n and m both fit in range [0, 1000].


//######################################### T: O(n) ######################################### 
//Suppose we did f[0] of the first operation, f[1] of the second, f[2] of the third, and f[3] of the fourth, where sum(f) == m.
//4 Options : # of possibilites = 2^4
//First, all these operations commute: doing operation A followed by operation B yields the same result as doing operation B followed by operation A. Also, doing operation A followed by operation A again is the same as doing nothing. So really, we only needed to know the residues cand[i] = f[i] % 2. There are only 16 different possibilities for the residues in total, so we can try them all.
//We'll loop cand through all 16 possibilities (0, 0, 0, 0), (0, 0, 0, 1), ..., (1, 1, 1, 1). A necessary and sufficient condition for cand to be valid is that sum(cand) % 2 == m % 2 and sum(cand) <= m, as only when these conditions are satisfied can we find some f with sum(f) == m and cand[i] = f[i] % 2.
//Also, as the sequence of lights definitely repeats every 6 lights, we could replace n with min(n, 6). Actually, we could replace it with min(n, 3), as those lights are representative: that is, knowing the first 3 lights is enough to reconstruct what the next 3 lights will be. If the first 3 lights are X, Y, Z, then with a little effort we can prove the next 3 lights will be (X^Y^Z), Z, Y.

def flipLights(self, n, m):
    seen = set()
    for cand in itertools.product((0, 1), repeat = 4):
        if sum(cand) % 2 == m % 2 and sum(cand) <= m:
            A = []
            for i in xrange(min(n, 3)):
                light = 1
                light ^= cand[0]
                light ^= cand[1] and i % 2
                light ^= cand[2] and i % 2 == 0
                light ^= cand[3] and i % 3 == 0
                A.append(light)
            seen.add(tuple(A))

    return len(seen)

//###############################  T:O(n) ############################### 
//n == 1
//Only 2 possibilities: 1 and 0.
//n == 2
//After one operation, it has only 3 possibilities: 00, 10 and 01.
//After two and more operations, it has only 4 possibilities: 11, 10, 01 and 00.
//n == 3
//After one operation, it has only 4 possibilities: 000, 101, 010 and 011.
//After two operations, it has 7 possibilities: 111,101,010,100,000,001 and 110.
//After three and more operations, it has 8 possibilities, plus 011 on above case.
//n >= 4
//After one operation, it has only 4 possibilities: 0000, 1010, 0101 and 0110.
//After two or more operations: it has 8 possibilities, 1111,1010,0101,0111,0000,0011, 1100 and 1001.

class Solution {
    public int flipLights(int n, int m) {
        if (m == 0) return 1;
        if (n <= 0 || m < 0) return 0;
        
        if (n == 1) return 2;
        else if (n == 2) return (m == 1) ? 3 : 4;
        else return (m == 1) ? 4 : ((m == 2) ? 7 : 8);
    }
}


//The first operation repeats every 1 light. The second and third operations repeat every 2 lights. The fourth operation repeats every 3 lights. In total, they must all repeat every lcm(1, 2, 2, 3) = 6 lights.
//Firstly, we may take n = min(n, 3). The sequence of lights clearly repeats every 6, so the first 6 lights are representative of the whole sequence, as we can construct eg. the 7th light (it's equal to the 1st).
//
//Actually, the first 3 lights are representative of the whole sequence. If the operations are a, b, c, d; then modulo 2:
//
//Light 1 = 1 + a + c + d
//Light 2 = 1 + a + b
//Light 3 = 1 + a + c
//Light 4 = 1 + a + b + d
//Light 5 = 1 + a + c
//Light 6 = 1 + a + b
//So that (modulo 2):
//
//Light 4 = (Light 1) + (Light 2) + (Light 3)
//Light 5 = Light 3, and
//Light 6 = Light 2.
//Now, we can do cases on m, and analyze the possible lightbulb states for n >= 3. The transitions are to XOR by (1, 1, 1), (0, 1, 0), (1, 0, 1), or (1, 0, 0).
//
//If m = 0 there is only one state (1, 1, 1).
//If m = 1 then we could get (0, 0, 0), (1, 0, 1), (0, 1, 0), (0, 1, 1).
//If m = 2 we could get all 8 possibilities except (0, 1, 1).
//If m = 3 we can get every possibility.
//This reduced the problem to knowing the answer for m <= 3, n <= 3. The final answer is:
//
//When n == 1, the answer is 1 if m == 0, else 2.
//When n == 2, the answer is 1 if m == 0, 3 if m == 1, else 4.
//
//
