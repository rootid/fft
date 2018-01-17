import java.util.*;
// Given a List of Strings, write a method removeDuplicates that removes
// duplicate words from the List and returns an ArrayList of all the unique
// words. The returned ArrayList should be lexically alphabetically.
// Input: [Hi, Hello, Hey, Hi, Hello, Hey]
// Output: [Hello, Hey, Hi]

public class RemoveDuplicatesFromAListOfWords {
  //##################### O(n log n) #####################
  public static ArrayList<String> removeDuplicates(List<String> input) {
    // a,a,b,3,4,49,8
    ArrayList<String> test = new ArrayList<String>();
    Collections.sort(input);
    for (int i = 0; i < input.size(); i++) {
      if (test.size() == 0 || !test.get(test.size() - 1).equals(input.get(i))) {
        test.add(input.get(i));
      }
    }
    return test;
  }
}
