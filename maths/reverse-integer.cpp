//Reverse digits of an integer.
//Example1: x = 123, return 321
//Example2: x = -123, return -321
//click to show spoilers.
//Have you thought about this?
//Here are some good questions to ask before coding. Bonus points for you if you have already thought through this!
//If the integer's last digit is 0, what should the output be? ie, cases such as 10, 100.
//Did you notice that the reversed integer might overflow? Assume the input is a 32-bit integer, then the reverse of 1000000003 overflows. How should you handle such cases?
//For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
//Update (2014-11-10):
//Test cases had been added to test the overflow behavior.

#include<iostream>
#include<limits.h>
#include<assert.h>

int reverse(int x) {
    //123 : 3 2 1
    //123 % 10 = 3
    //12 % 10 = 2
    //1 % 10 = 1
    // bool isNeg = false;
    // if (x < 0) {
    //     x = -x;
    //     isNeg = true;
    // }
    long no = 0;
    while(x != 0) {
        no *= 10;
        int tmp_ = x % 10;
        x /= 10;
        no += tmp_;

      assert(no < INT_MAX && no > INT_MIN);
        
        if(no > INT_MAX || no < INT_MIN) {
            no = 0;
            break;
        }
    }
    // if(isNeg == true) {
    //     no = -no;
    // }
    return no;
}


int reverseGood(int x) {
    long rev= 0;
    while( x != 0){
        rev= rev*10 + x % 10;
        x= x/10;
        if( rev > INT_MAX || rev < INT_MIN)
            return 0;
    }
    return (int) rev;
}


int reverse(int x) {
		bool neg=false;
		if (x < 0) neg = true, x = -x;
		unsigned int ret = 0;
		while (x / 10){
			ret = ret*10+ x%10;
			x = x / 10;
		}
		ret =ret*10+x;
		if (ret>0x7fffffff) return 0; //overflow check.
		if (neg) return -(int)ret;
		return (int)ret;
	}

int main() {


  reverse(1000000003);
}
