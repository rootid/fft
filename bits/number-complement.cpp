//Given a positive integer, output its complement number. The complement
//strategy is to flip the bits of its binary representation.
//
//Note:
//The given integer is guaranteed to fit within the range of a 32-bit signed
//integer.
//You could assume no leading zero bit in the integer’s binary representation.
//Example 1:
//Input: 5
//Output: 2
//Explanation: The binary representation of 5 is 101 (no leading zero bits),
//and its complement is 010. So you need to output 2.
//Example 2:
//Input: 1
//Output: 0
#include "../headers/global.hpp"


//num          = 00000101
//mask         = 11111111
//                    ^ ^ overlap!
//num          = 00000101
//mask         = 11111110
//                    ^   overlap!
//num          = 00000101
//mask         = 11111100
//                    ^   overlap!
//num          = 00000101
//mask         = 11111000

//num          = 00000101
//mask         = 11111000
//
//~num         = 11111010
//~mask        = 00000111
//~mask & ~num = 00000010
//or
//~mask ^ num =

int findComplement(int num) {
  //~ : 1's complelement
  unsigned int mask = ~0;
  while(num & mask) {
    mask = mask << 1;
  }
  return num ^ ~mask;
}

int main() {

  findComplement(5);
  findComplement(1);
  findComplement(15);
  findComplement(20);
}
