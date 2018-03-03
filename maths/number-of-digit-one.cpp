//Number of Digit One
//Given an integer n, count the total number of digit 1 appearing in all
//non-negative integers less than or equal to n.
//For example:
//Given n = 13,
//Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12,
//13.
//Hint:
//Beware of overflow.

#include "../headers/global.hpp"

//1         1                                                        [1, 9]
//
//11        10  11  12  13  14  15  16  17  18  19                   [10, 19]
//
//1         21                                                       [20, 29]
//
//1         31                                                       [30, 39]
//
//1         41                                                       [40, 49]
//
//1         51                                                       [50, 59]
//
//1         61                                                       [60, 69]
//
//1         71                                                       [70, 79]
//
//1         81                                                       [80, 89]
//
//1         91                                                       [90, 99]
//
//11       100  101  102  103  104  105  106  107  108  109          [100, 109]
//
//21       110  111  112  113  114  115  116  117  118  119          [110, 119]
//
//11       120  121  122  123  124  125  126  127  128  129          [120, 129]

//########################
int countDigitOne(int n) {
    int ones = 0;
    for (long long m = 1; m <= n; m *= 10) {
        int a = n/m, b = n%m; //a = left , b = right
        //left,right,# of digits from left side ,# of digits from right side
        cout << a << ","  << b << "," << (a + 8) / 10 * m   << "," << (a % 10 == 1) * (b + 1)<< endl;
        ones += (a + 8) / 10 * m + (a % 10 == 1) * (b + 1);
        //left part(a) last digit = 0 (b+1)
        //left part(a) last digit >= 2 (a+8/10) *m
    }
    return ones;
}


//##################################### Formula  ########################################################################
// h= xyzdabc
int countDigitOne1(int n) {
   if (n <= 0) return 0;
    int q = n, x = 1, ans = 0;
    do {
        int digit = q % 10;
        q /= 10;
        ans += q * x;
        if (digit == 1) ans += n % x + 1;
        if (digit >= 2) ans += x;
        x *= 10;
    } while (q > 0);
    return ans;
}

int main() {
  countDigitOne(3141592);
}
