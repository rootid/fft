//Power of Two
#include<iostream>
using namespace std;


bool isPowerOfTwo() {
       if ( n == 1 || n == 2) {
            return true;
        } else if (n%2 != 0) {
            return false;
        } else if (n == 0) {
            return false;
        }
        return isPowerOfTwo(n/2);
}


bool isPowerOfFour() {
        if ( n == 1 || n == 4) {
            return true;
        } else if (n%4 != 0) {
            return false;
        } else if (n == 0) {
            return false;
        }
        return isPowerOfFour(n/4);
}


int main() {

}
