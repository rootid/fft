//Reverse bits of a given 32 bits unsigned integer.
//For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as 00111001011110000010100101000000).
//Follow up:
//If this function is called many times, how would you optimize it?

#include "../headers/global.hpp"

uint32_t reverseBits(uint32_t n) {
 
     //reverse bits
     int end = sizeof(n) * 8;
     end -= 1;
     int start = 0;
     uint32_t res = 0;
     for(int i=0;i<= end;i++) {
       res |=  (n >> i & 1) << (end - i);
     }
     return res;
}

//uint32_t reverseBits(uint32_t n) {
//  int count = 32;
//  for(int i=0;i<count;i++) {
//    if(n<<count-i ^ n>>i == 0 {
//
//    }
//  }
//  return n;
//}


//cout << " end " << end << endl;
//cout << "00000010100101000001111010011100" << endl;
//while(end >= start) {
//  uint32_t x = (n >> end) & 1;
//  uint32_t y = (n >> start) & 1;
//  if(x ^ y != 0) {
//    cout << "(s = " << start << ",e = " << end << " )";
//    n |= ( (1 << end) ^ n );
//    n |= ( (1 << start) ^ n );
//  }
//  end -= 1;
//  start += 1;
//}
//cout << endl;
//end = sizeof(n) * 8;
//end -= 1;
//while(end >= 0) {
//  uint32_t x = (res >> end) & 1;
//  end -= 1;
//  cout << x ;
//}
//cout << endl;

int main() {

  reverseBits (43261596);
}
