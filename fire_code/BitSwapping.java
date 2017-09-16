import java.util.*;
// Bit Swapping
// Given a 32 bit integer input x, swap its odd and even bits and return the
// resulting integer. (e.g., bit 0 and bit 1 are swapped, bit 2 and bit 3 are
// swapped, and so on).
// For example:
// x = 5, Binary code = 0101
// swapOddEvenBits(5) --> 10
// Binary representation of 10 = 1010

public class BitSwapping {
  public int swapOddEvenBits(int x) {
    int INT_SZ = Integer.SIZE / 2;
    int zeroOnes = 0, oneZeroes = 0;
    for (int i = 0; i < INT_SZ; i += 2) {
      zeroOnes = (zeroOnes << 2) |
                 1;  // generating the INT_SZ bit 010101... no. -> 0xAAAAAAAA
      oneZeroes = (oneZeroes << 2) |
                  2;  // generating the INT_SZ bit 101010... no. -> 0x55555555
    }
    int oddBits = x & oneZeroes;  // 1th positon from right side of binary form
                                  // of no. is considered odd position
    int evenBits = x & zeroOnes;
    return (oddBits >> 1) | (evenBits << 1);
  }
}
