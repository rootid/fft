import java.util.*;
// Write a method to determine whether a postive number is Happy.
// A number is Happy (Yes, it is a thing!) if it follows a sequence that ends in
// 1 after following the steps given below :
// Beginning with the number itself, replace it by the sum of the squares of its
// digits until either the number becomes 1 or loops endlessly in a cycle that
// does not include 1.
// For instance, 19 is a happy number. Sequence:
// 1^2 + 9^2 = 82
// 8^2 + 2^2 = 68
// 6^2 + 8^2 = 100
// 1^2 + 0^2 + 0^2 = 1
// Example:
// Input : 19
// Output: true

public class HappyNumbers {
  public static boolean isHappyNumber(int n) {
    if (n == 1) {
      return true;
    }
    Set<Integer> s = new HashSet<>();
    int sum = 0;
    while (n != 1) {
      if (s.contains(n)) return false;
      s.add(n);
      while (n > 0) {
        int rem = n % 10;
        sum += Math.pow(rem, 2);
        n /= 10;
      }
      n = sum;
      sum = 0;
    }
    return true;
  }

  //#########################################  Bad Thinking too much of Data
  // structure  #########################################
  public static boolean isHappyNumberUgly(int n) {
    // get unit digit + add 2
    HashSet<List<Integer>> set = new HashSet<>();
    // 19 % 10  = A
    // 102 , 102/10 = 10 , 2
    List<Integer> lst = getAllUnitDigits(n);
    set.add(lst);
    int result = 0;
    while (result != 1) {
      for (int i : lst) result += i;
      lst = getAllUnitDigits(result);
      if (set.contains(lst)) return false;
      set.add(lst);
    }
    return true;
  }

  private static List<Integer> getAllUnitDigits(int n) {
    List<Integer> lst = new ArrayList<>();
    while (n > 0) {
      int rem = n % 10;
      n = n / 10;
      lst.add(rem);
    }
    return lst;
  }

  //#########################################  Bad Thinking too much of Data
  // structure  #########################################
  public static boolean isHappyNumberUgly1(int n) {
    int[] digitArray = getInputDigits(n);
    int sum;

    do {
      sum = 0;
      for (int i = 0; i < digitArray.length; i++) {
        sum = sum + digitArray[i] * digitArray[i];
      }
      digitArray = getInputDigits(sum);
    } while (sum > 9);

    if (sum == 1) return true;

    return false;
  }

  public static int[] getInputDigits(int n) {
    String s = String.valueOf(n);
    int[] digits = new int[s.length()];
    int i = 0;

    while (n > 0) {
      int m = n % 10;
      digits[i++] = m;
      n = n / 10;
    }
    return digits;
  }
}
