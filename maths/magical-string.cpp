//Magical String
//A magical string S consists of only '1' and '2' and obeys the following
//rules:
//The string S is magical because concatenating the number of contiguous
//occurrences of characters '1' and '2' generates the string S itself.
//The first few elements of string S is the following: S = "122 112 122 122
//112112 2……"
//If we group the consecutive '1's and '2's in S, it will be:
//1 22 11 2 1 22 1 22 11 2 11 22 ......
//and the occurrences of '1's or '2's in each group are:
//1 2	2 1 1 2 1 2 2 1 2 2 ......
//You can see that the occurrence sequence above is the S itself.
//Given an integer N as input, return the number of '1's in the first N number
//in the magical string S.
//Note: N will not exceed 100,000.
//Example 1:
//Input: 6
//Output: 3
//Explanation: The first 6 elements of magical string S is "12211" and it
//contains three 1's, so return 3.

//https://en.wikipedia.org/wiki/Kolakoski_sequence

#include "../headers/global.hpp"

int magicalString(int n) {
  string str = "122"; //first 3-sequences
  int i = 2;
  while (str.size() < n) {
    str += string(str[i++] - '0', str.back() ^ 3);  //str[i++] - '0' : # of copies 1/2 sequential increase
                                                    //str.back() ^ 3 : negate the last generated output
                                    //XOR : And 49^3 is 50 = '2' and 50^3 is 49 = '1'
  }
  return count(str.begin(), str.begin() + n, '1'); //count total number of 1's
}


//"The digits 0–9 are prefixed with 011, but the remaining 4 bits correspond to their respective values in binary, making conversion with binary-coded decimal straightforward". When I wrote my solution, I didn't think about 49 and 50, I knew I could instead just think of 1 and 2 because of how ASCII is organized.
int main() {
  magicalString(16);
}


