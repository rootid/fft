#include<iostream>
using namespace std;

//f(n) = f(n-1) + f(n-2)
//0,1,1,2,3,5
int fibo (int n) {
    if (n <= 1 && n >= 0) {
       return n;
    }   
    return fibo (n-1) + fibo(n-2);
}


int fibo (int n) {

    int prev = 0;
    int current = 1;
    int result = 0;
    for (int i = 2;i<n;i++) {
        int tmpResult = prev + current;
        result += tmpResult;
        prev = current;
        current = result;
    }
    return result;
}
