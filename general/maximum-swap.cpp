//Maximum Swap
//Given a non-negative integer, you could swap two digits at most once to get
//the maximum valued number. Return the maximum valued number you could get.
//Example 1:
//Input: 2736
//Output: 7236
//Explanation: Swap the number 2 and the number 7.
//Example 2:
//Input: 9973
//Output: 997e
//Explanation: No swap.
//Note:
//The given number is in the range [0, 10^8]


//######################################### Bucket #########################################
//Use buckets to record the last position of digit 0 ~ 9 in this num.
//Loop through the num array from left to right. For each position, we check
//whether there exists a larger digit in this num (start from 9 to current
//digit). We also need to make sure the position of this larger digit is behind
//the current one. If we find it, simply swap these two digits and return the
//result.
//
class Solution {
    public int maximumSwap(int num) {
        char[] digits = Integer.toString(num).toCharArray();

        int[] buckets = new int[10];
        for (int i = 0; i < digits.length; i++) {
            buckets[digits[i] - '0'] = i;
        }

        for (int i = 0; i < digits.length; i++) {
            for (int k = 9; k > digits[i] - '0'; k--) {
                if (buckets[k] > i) {
                    char tmp = digits[i];
                    digits[i] = digits[buckets[k]];
                    digits[buckets[k]] = tmp;
                    return Integer.valueOf(new String(digits));
                }
            }
        }

        return num;
    }
}

//######################################### Check all possibilites  #########################################
def maximumSwap(self, num):
    places = [10**i for i in range(len(str(num)))]
    return max(num + num/p%10*(q-p) + num/q%10*(p-q)
               for p in places for q in places)

//######################################### Check all possibilites  #########################################
int maximumSwap(int num) {
    int maxi = 0;
    for (int p=1; p<=num; p*=10)
        for (int q=p; q<=num; q*=10)
            maxi = max(maxi, num + num/p%10*(q-p) + num/q%10*(p-q));
    return maxi;
}

//######################################### Check all possibilites  #########################################
public int maximumSwap(int num) {
    int max = 0;
    for (int p=1; p<=num; p*=10)
        for (int q=p; q<=num; q*=10)
            max = Math.max(max, num + num/p%10*(q-p) + num/q%10*(p-q));
    return max;
}
//There are so very few possibilities that I just try them all, swapping
//between any two places p and q (where places are 1, 10, 100, 1000, etc, i.e.,
//the "ones place", "tens place", "hundreds place", etc). With num/p%10 I get
//the digit at place p, and multiplying it with (q-p) takes it out of place p
//and puts it into place q. And move the digit from place q to place p the same
//way.

//######################################### 8C2 #########################################
//The number only has 8 digits, so there are only 8 choose 2 = 28 available
//swaps. Brute force them all for an O(N^2) solution which passes.
//We will store the candidates as lists of length len(num). For each candidate
//swap with positions (i, j), we swap the number and record if the candidate is
//larger than the current answer, then swap back to restore the original
//number. The only detail is possibly to check that we didn't introduce a
//leading zero. We don't actually need to check it, because our original number
//doesn't have one.

def maximumSwap(self, num):
    A = list(str(num))
    ans = A[:]
    for i in xrange(len(A)):
        for j in xrange(i+1, len(A)):
            A[i], A[j] = A[j], A[i]
            if A > ans: ans = A[:]
            A[i], A[j] = A[j], A[i]

    return int("".join(ans))

//######################################### O(N) ########################################
//We can also get an O(N) solution. At each digit, if there is a larger digit
//that occurs later, we want the swap it with the largest such digit that
//occurs the latest.
def maximumSwap(self, num):
    A = map(int, str(num))
    last = {x: i for i, x in enumerate(A)}
    for i, x in enumerate(A):
        for d in xrange(9, x, -1):
            if last.get(d, None) > i:
                A[i], A[last[d]] = A[last[d]], A[i]
                return int("".join(map(str, A)))
    return num

//######################################### With Stack #########################################
//create a min and max stack and keep track of the lower and greater elements.
//If the min stack is empty, array is reversely sorted return same. else pop
//the max stack until we find a max number index after the min element index.
//The idea is to replace the earliest smallest number with the latest greater
//number. (so ignore duplicates)

class Solution {
public:
    int maximumSwap(int num) {
        stack<int> minS, maxS;
        string temp = to_string(num);
        int maxi=INT_MIN;

        for (int i=temp.size()-1;i>=0;i--){
            int num = temp[i]-'0';
            if (num>maxi){
                maxi = num;
                maxS.push(i);
            }else if (num<maxi){
                minS.push(i);
            }
        }

        if (minS.empty())
            return num;

        while (maxS.top()<=minS.top()){
            maxS.pop();
        }
        swap(temp[minS.top()], temp[maxS.top()]);
        return stoi(temp);
    }
};
