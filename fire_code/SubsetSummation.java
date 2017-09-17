// Subset Summation
// Given an array of integers and a target number, determine if it is possible
// to choose a group of integers from the array,
// such that the numbers in the group sum to the given target.
// Examples:
// groupSum({1,2,3,6,5},10) ==> true
// groupSum({1,2,3,6,5},18) ==> false

public class SubsetSummation {
  public static boolean groupSum(int[] arr, int target) {
    // Arrays.sort(arr);
    return groupSumHelper(arr, 0, 0, target);
  }
  private static boolean groupSumHelper(int[] arr, int k, int sum, int target) {
    int m = arr.length;
    if (k >= m) return false;
    if (sum == target) return true;
    // pick the sum or not
    return (groupSumHelper(arr, k + 1, sum + arr[k], target) ||
            groupSumHelper(arr, k + 1, sum, target));
  }
}
