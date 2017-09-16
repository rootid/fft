#include<bits/stdc++.h>
using namespace std;
#define INT_SZ sizeof(int)*8

int swapBits(int n) {
    int zeroOnes=0,oneZeroes=0;
    for(int i=0;i<INT_SZ;i+=2) {
        zeroOnes=(zeroOnes<<2)|1;       //generating the 32bit 010101... no. -> 0xAAAAAAAA
        oneZeroes=(oneZeroes<<2)|2;     //generating the 32bit 101010... no. -> 0x55555555
    }
    int oddBits=n&oneZeroes;        //1th positon from right side of binary form of no. is considered odd position
    int evenBits=n&zeroOnes;       //0th position from right side of binary form of no. is considered even position
    
    return (oddBits>>1)|(evenBits<<1);
}


int main()
{
    unsigned int x = 23; // 00010111
 
    // Output is 43 (00101011)
    printf("%u ", swapBits(x));
 
    return 0;
}
