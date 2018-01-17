// Given two input integers a and b, write a method to determine the number of
// bits required to be swapped to convert a to b.
// Example:
// a = 21, Binary code = 10101
// b = 31, Binary code = 11111
// bitSwapRequired(a,b) --> 2

public class BitConversion {
  public int bitSwapRequired(int a, int b) { return Integer.bitCount(a ^ b); }

  public int bitSwapRequiredBad(int a, int b) {
    int result = a ^ b;
    int cnt = 0;
    while (result != 0) {
      cnt++;
      result = result & (result - 1);
    }
    return cnt;
  }
}
