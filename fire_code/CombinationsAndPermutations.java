// Combinations and Permutations
// Given a string, list all possible combinations and permutations of its
// characters.
// Examples:
// getCombPerms("a") ==> {"a"}
// getCombPerms("ab") ==> {"a","ab","ba","b"}

// Revisit
public class CombinationsAndPermutations {
  public static ArrayList<String> getCombPerms(String s) {
    ArrayList<String> result = new ArrayList<String>();
    if (s == null) return null;
    int m = s.length();
    if (m == 1) {
      result.add(s);
      return result;
    }
    // permuation
    StringBuilder sb = new StringBuilder(s);
    String first = sb.substring(0, 1);
    result.add(first);
    String remainder = sb.substring(1);
    ArrayList<String> words = getCombPerms(remainder);
    for (String word : words)
      for (int j = 0; j <= word.length(); j++)
        result.add(insertCharAt(word, first, j));
    result.addAll(words);
    return result;
  }

  // combination
  public static String insertCharAt(String word, String c, int i) {
    String start = word.substring(0, i);
    String end = word.substring(i);
    return start + c + end;
  }
}
