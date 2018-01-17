import java.util.*;
// Subset Summation with Number Constraint
// Given an array of integers and a target integer, write a method
// groupSumWithNum to determine if it is possible to choose a group of integers
// from the array such that the group sums to the given target. An additional
// constraint is that the summation must include the integer must_have if it is
// present in the array.
// Examples:
// groupSumWithNum({1,2,3,6,5},5,10) ==> true
// groupSumWithNum({1,2,3,6,5},3,7) ==> false
public class SubsetSummationWithNumberConstraint {
  //########### update index param ###########
  public static boolean groupSumWithNumHelper(int[] arr, int from, int target) {
    if (target == 0) return true;

    if (from >= arr.length) return false;

    return groupSumWithNumHelper(arr, from + 1, target) ||
        groupSumWithNumHelper(arr, from + 1, target - arr[from]);
  }

  public static boolean groupSumWithNum(int[] arr, int must_have, int target) {
    int from = 0;
    for (int i = 0; i < arr.length; i++) {
      if (arr[i] == must_have) {
        // swap the must_have with a[0]
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        from = 1;
        target = target - must_have;
        break;
      }
    }
    return groupSumWithNumHelper(arr, from, target);
  }

  //########### update must_have param ###########
  public static boolean groupSumWithNumWithParamUpdate(int[] arr, int must_have,
                                                       int target) {
    for (int i = 0; i < arr.length; i++) {
      if (arr[i] == must_have) {
        target -= must_have;
        arr[i] = 0;
        break;
      }
    }
    return groupSumWithNumHelper(arr, 0, 0, target);
  }

  private static boolean groupSumWithNumHelper(int[] arr, int k, int sum,
                                               int target) {
    if (k >= arr.length && target != sum) return false;  // This is wron
    if (target == sum) return true;
    return groupSumWithNumHelper(arr, k + 1, sum + arr[k], target) ||
        groupSumWithNumHelper(arr, k + 1, sum, target);
  }

  // private void subsetSum(int [] arr,int k, int sum, int target) {
  //		if(sum == target) {
  //			subsetSum(arr,k+1,sum-arr[k],target);
  //			return;
  //		}
  //		for(int i=k;i<arr.length;i++) {
  //			subsetSum(arr,i+1,sum+arr[i],target);
  //		}
  //
  //}
}
