//UTF-8 Validation
//A character in UTF8 can be from 1 to 4 bytes long, subjected to the following
//rules:
//For 1-byte character, the first bit is a 0, followed by its unicode code.
//For n-bytes character, the first n-bits are all one's, the n+1 bit is 0,
//followed by n-1 bytes with most significant 2 bits being 10.
//This is how the UTF-8 encoding would work:
//   Char. number range  |        UTF-8 octet sequence
//      (hexadecimal)    |              (binary)
//   --------------------+---------------------------------------------
//   0000 0000-0000 007F | 0xxxxxxx
//   0000 0080-0000 07FF | 110xxxxx 10xxxxxx
//   0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
//   0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
//Given an array of integers representing the data, return whether it is a
//valid utf-8 encoding.
//Note:
//The input is an array of integers. Only the least significant 8 bits of each
//integer is used to store the data. This means each integer represents only 1
//byte of data.
//Example 1:
//data = [197, 130, 1], which represents the octet sequence: 11000101 10000010
//00000001.
//Return true.
//It is a valid utf-8 encoding for a 2-bytes character followed by a 1-byte
//character.
//Example 2:
//data = [235, 140, 4], which represented the octet sequence: 11101011 10001100
//00000100.
//Return false.
//The first 3 bits are all one's and the 4th bit is 0 means it is a 3-bytes
//character.
//The next byte is a continuation byte which starts with 10 and that's correct.
//But the second continuation byte does not start with 10, so it is invalid

//########################## Bit Pattern lookup ##########################
public boolean validUtf8(int[] data) {
	int noOfOctet = 0;
    for(int d:data) {
      if(noOfOctet == 0) {
        if( ((d >>> 3) & 31) == 31) return false; //11111xxx (invalid)
        else if( ((d >>> 4) & 15) == 15) noOfOctet = 3; //11110xxx
        else if (((d >>> 5) & 7) == 7) noOfOctet = 2; //1110xxxx
        else if (((d >>> 6) & 3)  == 3) noOfOctet = 1; //110xxxxx
        else if (((d >>> 7) & 1)  == 1) return false; //1xxxxxxx (invalid)
      } else {
        if(((d >>> 6) & 2)  == 2) noOfOctet -= 1; //10xxxxxx
        else return false;
      }
    }
	return noOfOctet == 0;
}

//########################## Bit pattern lookup ##########################
bool validUtf8(vector<int>& data) {
  int cnt = 0;
  for (int c: data) {
    if (cnt == 0) {
      if (((c >> 3) & 31) == 31) {  //11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        return false;
      } else if (((c >> 4) & 15) == 15) { //11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
          cnt = 3;
      } else if (((c >> 5) & 7) == 7) { //1110xxxx 10xxxxxx 10xxxxxx
          cnt = 2;
      } else if (((c >> 6) & 3) == 3) { //110xxxxx 10xxxxxx
          cnt = 1;
      } else if (((c >> 7) & 1) == 1) { //0xxxxxxx
        return false;
      }
    } else {
      if (((c >> 6) & 2) != 2) {  //must be 10XXXXXX
        return false;
      }
      cnt--;
      }
  }
  return cnt == 0;
}

//###################################### pytonic ######################################
//def check(nums, start, size):
//    for i in range(start + 1, start + size + 1):
//        if i >= len(nums) or (nums[i] >> 6) != 0b10: return False
//    return True
//
//class Solution(object):
//    def validUtf8(self, nums, start=0):
//        while start < len(nums):
//            first = nums[start]
//            if   (first >> 3) == 0b11110 and check(nums, start, 3): start += 4
//            elif (first >> 4) == 0b1110  and check(nums, start, 2): start += 3
//            elif (first >> 5) == 0b110   and check(nums, start, 1): start += 2
//            elif (first >> 7) == 0:                                 start += 1
//            else:                                                   return False
//        return True
//
//# 45 / 45 test cases passed.
//# Status: Accepted
//# Runtime: 89 ms
//
//def validUtf8(self, data):
//    try:
//        ''.join(map(chr, data)).decode('utf8')
//        return True
//    except Exception as e:
//        return False


//########################## FIXME ##########################
bool validUtf8(vector<int>& data) {
  int cnt  = 0 ;
  for(auto c:data) {
    if(cnt == 0) {
      if((c >> 3) & 31) {
        return false;
      }else if((c >> 4) & 15) {
        cnt = 4;
      } else if((c >> 5) & 7) {
        cnt = 3;
      } else if((c >> 6) & 5) {
        cnt = 2;
      }
    } else {
      if((c >> 6) & 2) { //must be 10XXXXXX
        cnt--;
      }
    }
  }
  return cnt == 0;
  //if(cnt == 0) {
  //  return true;
  //}
  //return false;
}
