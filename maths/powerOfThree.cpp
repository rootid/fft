//Power of Three
#include<iostream>
using namespace std;


bool isPowerOfThree(int n) {
    if (n == 0) {
        return false;
    } 
    while(n%3 == 0) {
        n = n /3;
    }
    return n == 1;
}

int main() {

}
