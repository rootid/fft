// Recursive String Permutation
// String permutations are the various possible strings made by the
// rearrangement of the characters in the original String.
// For example, the permutations of car are
// car, cra, acr, arc, rac, rca
// Write a recursive method getPermutations() that returns all permutations of
// an input String in an ArrayList. Define a helper method if needed. For the
// sake of simplicity, assume that all characters in the input String are
// unique.
// Examples:
// getPermutations("") -> ArrayList -> []
// getPermutations("c") -> ArrayList -> ["c"]
// getPermutations("cat") -> ArrayList -> ["cat","cta","act","atc","tca","tac"]*
//*Order does not matter.

public class RecursiveStringPermutation {
  // Generates n! elements
  //#####################Use swapping for permutation#####################
  public static ArrayList<String> getPermutations(String s) {
    if (s == null) return null;
    StringBuilder sb = new StringBuilder(s);
    ArrayList<String> result = new ArrayList<>();
    dfsHelper(sb, 0, result);
    return result;
  }

  private static void dfsHelper(StringBuilder sb, int k,
                                ArrayList<String> result) {
    int len = sb.length();
    if (k == len - 1) {
      result.add(sb.toString());
      return;
    }
    for (int i = k; i < len; i++) {
      swap(sb, i, k);
      dfsHelper(sb, k + 1, result);
      swap(sb, i, k);
    }
  }

  private static void swap(StringBuilder sb, int i, int j) {
    char l = sb.charAt(i), r = sb.charAt(j);
    sb.setCharAt(i, r);
    sb.setCharAt(j, l);
  }

  //################## DFS helper ##################
  public static ArrayList<String> getPermutationsRec(String s) {
    if (s == null) return null;
    ArrayList<String> list = new ArrayList<>();
    dfsHelper(s, "", list);
    return list;
  }

  public static void dfsHelper(String s, String curr, ArrayList<String> list) {
    if (s.length() == 0 && curr.length() >= 1) list.add(curr);
    for (int i = 0; i < s.length(); i++) {
      char a = s.charAt(i);
      String front = s.substring(0, i);
      String back = s.substring(i + 1);
      dfsHelper(front + back, curr + a, list);
    }
  }
}
