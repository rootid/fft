// Generate Combinations of Parentheses
// Write a method to return all valid combinations of n-pairs of parentheses.
// The method should return an ArrayList of strings, in which each string
// represents a valid combination of parentheses.
// The order of the strings in the ArrayList does not matter.
// Examples:
// combParenthesis(2) ==> {"(())","()()"}
// Note: Valid combination means that parentheses pairs are not left open.
// ")()(" is not a valid combination.

public class GenerateCombinationsOfParentheses {

  //######################################### Iterative ######################################### 
  public static ArrayList<String> combParenthesis(int pairs) {
    ArrayList<ArrayList<String> > lists = new ArrayList<>();
    lists.add(new ArrayList<String>(Collections.singletonList("")));
    // lists.add(new ArrayList<String>(Collections.AsList("")) );
    // ArrayList<String> tmpString = new ArrayList<>();
    // tmpString.add("");
    // lists.add("");
    for (int i = 1; i <= pairs; ++i) {
      final ArrayList<String> list = new ArrayList<>();
      for (int j = 0; j < i; ++j) {
        for (final String first : lists.get(j)) {
          for (final String second : lists.get(i - 1 - j)) {
            list.add("(" + first + ")" + second);
          }
        }
      }
      lists.add(list);
    }
    return lists.get(lists.size() - 1);
  }

  //######################################### DFS ######################################### 
  public static ArrayList<String> combParenthesisR(int pairs) {
    ArrayList<String> res = new ArrayList<String>();
    dfsHelper(pairs, pairs, "", res);
    return res;
  }

  public static void dfsHelper(int left, int right, String build, ArrayList<String> res) {
    if (right == 0 && left == 0) {
      res.add(build);
      return;
    }
    if (left > 0) dfsHelper(left - 1, right, build + "(", res);
    if (right > left) dfsHelper(left, right - 1, build + ")", res);
  }
}
