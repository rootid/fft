//Power of Three
//Given an integer, write a function to determine if it is a power of three.
//Follow up:
//Could you do it without using any loop / recursion?

#include<iostream>
using namespace std;

//######################################### Recursion ######################################### 
public boolean isPowerOfThree(int n) {
    if(n == 0) return false;
    if(n == 1 || n == 3) return true;
    int rem = n%3;
    if(rem == 0) return isPowerOfThree(n/3);
    return false;
}

//######################################### Iterative ######################################### 
bool isPowerOfThree(int n) {
    if (n == 0) 
        return false;
    while(n%3 == 0) 
        n = n /3;
    return n == 1;
}


public boolean isPowerOfThree(int n) {
    return n>0 && (n==1 || (n%3==0 && isPowerOfThree(n/3)));
}

public boolean isPowerOfThree(int n) {
    if(n>1)
        while(n%3==0) n /= 3;
    return n==1;
}

int main() {

}
