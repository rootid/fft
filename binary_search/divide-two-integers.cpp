//Divide two integers without using multiplication, division and mod operator.
//If it is overflow, return MAX_INT.

//Use of bit shifting to reduce the iterations
int divide(int dividend, int divisor) {
    int ans = 0;
    int is_neg = 0;
    //int sign = (dividend > 0 ^ divisor > 0) ? -1 : 1;
    if(dividend == INT_MIN && divisor == -1)
        return INT_MAX;
    if(divisor == 1) 
        return dividend;
    if (dividend < 0) 
        is_neg = 1 - is_neg;
    if (divisor < 0) 
        is_neg = 1 - is_neg;
    long end = abs((long)dividend);
    long strt = abs((long)divisor);
    while(end - strt >= 0) {
       long tmp = strt;
       long mult = 1;
       while((tmp << 1) < end) { //x<<1 = x*2
            mult <<= 1;
            tmp  <<= 1;
        }
        ans += mult;
        end -= tmp;
    }
    if(is_neg == 1) {
        return -ans;
    }
    return ans;
}

