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


int main() {

}
