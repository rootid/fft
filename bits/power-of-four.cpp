//Power of Four
//Given an integer (signed 32 bits), write a function to check whether it is a
//power of 4.
//Example:
//Given num = 16, return true. Given num = 5, return false.
//Follow up: Could you solve it without loops/recursion?
//

//0101 0101 0101 0101 0101 0101 0101 0101 = 0x55555555
//Every power of 2:
//
//0000 0001 = 1
//0000 0010 = 2
//0000 0100 = 4
//0000 1000 = 8
//0001 0000 = 16
//0010 0000 = 32
//0100 0000 = 64
//1000 0000 = 128
//
//Every other power of 2 is a power of 4. 0x55 is used as the bitmask to obtain
//every other power of 2 as follows by bitwise AND. I've left the values which
//align with 1s in the bitmask "as is", and I have crossed-out the values which
//align with 0s in this bitmask.
//
//0101 0101 = 0x55
//
//0000 0001 = 1
//0000 0010 = 2<<<<<< Discard
//0000 0100 = 4
//0000 1000 = 8<<<<<<
//0001 0000 = 16
//0010 0000 = 32<<<<<<
//0100 0000 = 64
//1000 0000 = 128<<<<<<
//######################################### Filter Power of Two #########################################
public boolean isPowerOfFour(int num) {
	return  (num > 0) && ((num & 0x55555555) == num) && ((num & (num-1)) == 0);
}
