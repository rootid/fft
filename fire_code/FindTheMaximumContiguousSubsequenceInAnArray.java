import java.util.*;
// Given an array of integers consisting of both positive and negative
// numbers, find the contiguous subsequence that has the maximum sum among all
// subsequences in the array (click the red text to learn more about
// subsequences). Write a method that takes in
// an array of integers arr and returns an array res containing 3 integers in
// the following format:
// res[0] = max sum
// res[1] = starting index of the subsequence
// res[2] = ending index of the subsequence
// Examples:
// maxContSequence({-1,-2,3,4,5}) ==> {12,2,4}
// maxContSequence({1,2,3,-2,5}) ==> {6,0,2}

public class FindTheMaximumContiguousSubsequenceInAnArray {
  //### Kadane algorithm ###
  public static int[] maxContSequence(int[] arr) {
    int maxSoFar = Integer.MIN_VALUE;
    int maxEndingHere = 0;
    int startIdx = 0;
    int[] result = {0, 0, -1};
    for (int i = 0; i < arr.length; i++) {
      maxEndingHere += arr[i];
      if (maxEndingHere > maxSoFar) {
        maxSoFar = maxEndingHere;
        result[0] = maxSoFar;
        result[1] = startIdx;
        result[2] = i;
      }
      if (maxEndingHere < 0) {
        maxEndingHere = 0;
        startIdx = i + 1;
      }
    }
    return result;
  }
}
