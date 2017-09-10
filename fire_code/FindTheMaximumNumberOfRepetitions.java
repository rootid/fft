// Given an Array of integers, write a method that will return the integer with
// the maximum number of repetitions. Your code is expected to run with O(n)
// time complexity and O(1) space complexity. The elements in the array are
// between 0 to size(array) - 1 and the array will not be empty.
// f({3,1,2,2,3,4,4,4}) --> 4

// O(n) , O(1)
// Idea : Add constant K to array index which is derived from array value.
// arr[] = {2, 3, 3, 5, 3, 4, 1, 7}, k = 8, n = 8
// 1) Iterate though input array arr[], for every element arr[i], increment
// arr[arr[i]%k] by k (arr[] becomes {2, 11, 11, 29, 11, 12, 1, 15 })
// 2) Find the maximum value in the modified array (maximum value is 29).
// 3) Find Index of the maximum value is the maximum repeating element (index of
// 29 is 3).
// 4) If we want to get the original array back, we can iterate
// through the array one more time and do arr[i] = arr[i] % k where i varies
// from 0 to n-1.

public class FindTheMaximumNumberOfRepetitions {
  public static int getMaxRepetition(int[] a) {
    int k = a.length;
    for (int i = 0; i < k; ++i) {
      a[a[i] % k] += k;  // k = const ,  a[i] % k = idx derived from a value
    }
    int max = 0;
    int maxVal = 0;
    for (int i = 0; i < k; ++i) {
      if (a[i] > max) {
        max = a[i];
        maxVal = i;
      }
    }
    return maxVal;
  }
}
